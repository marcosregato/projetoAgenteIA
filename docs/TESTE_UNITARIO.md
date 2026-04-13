# Teste Unitário com Catch2

> **Guia completo do framework Catch2 para testes unitários em C++**

---

## O que é Catch2?

Catch2 é um framework de testes unitários moderno para a linguagem C++. Ele é amplamente utilizado por desenvolvedores para garantir a qualidade do código através de testes automatizados, sendo conhecido por sua simplicidade de configuração e sintaxe expressiva.

### Principais Características

- **Sintaxe Amigável**: Permite escrever casos de teste que parecem código C++ comum, utilizando macros intuitivas como `TEST_CASE` e `REQUIRE`.
- **Facilidade de Integração**: Historicamente famoso por ser um framework de "header único" (basta incluir um arquivo .hpp), embora versões mais recentes (v3) tenham migrado para um modelo de biblioteca compilado para melhorar o tempo de compilação.
- **Suporte a BDD e TDD**: Oferece ferramentas nativas para Behavior-Driven Development (Desenvolvimento Guiado por Comportamento), permitindo estruturar testes com as seções `GIVEN`, `WHEN` e `THEN`.
- **Modernidade**: Desenvolvido especificamente para versões modernas do C++ (C++14, C++17 e posteriores), aproveitando recursos como expressões lambda e smart pointers.
- **Benchmarks**: Além de testes unitários, o Catch2 também possui suporte para a criação de testes de performance (micro-benchmarks) no mesmo framework.

Você pode encontrar a documentação completa e o código-fonte no repositório oficial do Catch2 no GitHub ou no site catch2.org.

---

## Exemplo Prático

Aqui está um exemplo clássico. Imagine que você tem uma função simples de soma e quer testar se ela funciona e como ela lida com erros.

### 1. O Código (Soma.hpp)

```cpp
int somar(int a, int b) {
    return a + b;
}
```

### 2. O Teste com Catch2 (testes.cpp)

No Catch2 v3 (versão atual), o teste seria assim:

```cpp
#include <catch2/catch_test_macros.hpp>
#include "Soma.hpp"

TEST_CASE("Somas são calculadas corretamente", "[matematica]") {
    
    SECTION("Soma de números positivos") {
        REQUIRE(somar(2, 2) == 4);
        REQUIRE(somar(10, 5) == 15);
    }

    SECTION("Soma com zero") {
        REQUIRE(somar(0, 0) == 0);
        REQUIRE(somar(7, 0) == 7);
    }

    SECTION("Soma de números negativos") {
        CHECK(somar(-1, -1) == -2); // CHECK continua o teste mesmo se falhar
        REQUIRE(somar(-5, 2) == -3); // REQUIRE para o teste se falhar
    }
}
```

### Por que isso é legal?

- **Linguagem Natural**: O `TEST_CASE` recebe uma frase descrevendo o que está sendo testado.
- **REQUIRE vs CHECK**: O `REQUIRE` é rigoroso (para o teste na hora se der erro), enquanto o `CHECK` avisa do erro mas continua executando o restante da seção.
- **Relatórios Claros**: Se o teste `somar(2, 2) == 4` falhas, o Catch2 imprimiria no terminal exatamente os valores que causaram a falha (ex: `FAILED: 5 == 4`), sem você precisar configurar nada extra.

---

## Configuração com CMake

Para usar o Catch2 v3 sem precisar instalá-lo manualmente no sistema, a forma mais prática é utilizar o módulo FetchContent do CMake. Ele baixará e compilará o framework automaticamente durante o processo de configuração do seu projeto.

### 1. Configure o seu CMakeLists.txt

Crie este arquivo na raiz da sua pasta de projeto:

```cmake
cmake_minimum_required(VERSION 3.14)
project(MeuProjetoDeTestes LANGUAGES CXX)

# Define o padrão C++ (Catch2 v3 exige pelo menos C++14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Configuração do Catch2 via FetchContent ---
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # Você pode usar uma versão mais recente se preferir
)

# Torna o Catch2 disponível para o projeto
FetchContent_MakeAvailable(Catch2)

# --- Definição do Executável de Teste ---
add_executable(executavel_testes testes.cpp)

# Linka com o Catch2::Catch2WithMain para não precisar escrever a função main()
target_link_libraries(executavel_testes PRIVATE Catch2::Catch2WithMain)
```

### 2. Como Compilar e Rodar

Abra o seu terminal na pasta do projeto e execute os seguintes comandos:

#### Gerar os arquivos de build:
```bash
cmake -B build
```
(Nesta etapa, o CMake vai baixar o código do Catch2 do GitHub, o que pode levar alguns segundos)

#### Compilar:
```bash
cmake --build build
```

#### Executar os testes:
```bash
./build/executavel_testes
```

### Dicas Úteis:

- **Catch2::Catch2WithMain**: Ao linkar com este alvo específico, o Catch2 fornece automaticamente um `main()` padrão para você. Assim, seu arquivo `testes.cpp` só precisa conter os `TEST_CASE`.
- **Velocidade**: A primeira compilação será mais demorada porque o CMake compilará o framework inteiro. As próximas serão instantâneas.
- **Alternativas**: Se você preferir não baixar o código toda vez em novos projetos, pode usar gerenciadores de pacotes como o Vcpkg ou Conan.

---

## Integração com CTest

Com o CTest, você consegue gerenciar e rodar centenas de testes com um único comando, além de obter relatórios resumidos de passagens e falhas.

### 1. Atualize o seu CMakeLists.txt

Adicione estas linhas logo após o `FetchContent_MakeAvailable(Catch2)`:

```cmake
# Habilita o suporte ao CTest no projeto
enable_testing()

# Importa as funções auxiliares do Catch2 para descobrir testes automaticamente
include(Catch)

# ... (seu add_executable e target_link_libraries continuam aqui) ...

# Registra os testes do executável no CTest
catch_discover_tests(executavel_testes)
```

### O que o catch_discover_tests faz?

Em vez de você registrar cada `TEST_CASE` manualmente no CMake, essa função "pergunta" ao executável quais testes existem dentro dele e os cadastra automaticamente no sistema do CTest.

### 2. Como Rodar com CTest

Após configurar e compilar (usando `cmake -B build` e `cmake --build build`), você não precisa mais chamar o executável pelo nome. Basta usar:

```bash
cd build
ctest
```

### Comandos úteis do CTest:

- `ctest -V`: Mostra a saída detalhada de cada teste (útil para ver o que falhou).
- `ctest -R "Soma"`: Roda apenas os testes que têm "Soma" no nome (filtro por Regex).
- `ctest -j4`: Roda os testes em paralelo usando 4 núcleos do processador.

### Exemplo de Saída no Terminal:

```
Test project /seu/projeto/build
    Start 1: Somas são calculadas corretamente
1/1 Test #1: Somas são calculadas corretamente ...   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1
```

Essa configuração é o padrão da indústria para CI/CD (integração contínua). Se um teste falhar no servidor, o CTest retorna um erro e trava o deploy automaticamente.

---

## Relatórios em XML e JUnit

Para gerar relatórios em formatos como JUnit ou XML, que são o padrão lido por ferramentas de CI/CD (GitHub Actions, GitLab, Jenkins), o Catch2 já vem preparado. Você não precisa mudar nada no código C++, apenas a forma como chama o executável ou o CTest.

### 1. Gerando relatórios via linha de comando

O executável de teste gerado pelo Catch2 aceita argumentos para trocar o "repórter" (formato de saída).

#### Para JUnit (formato universal):
```bash
./build/executavel_testes -r junit -o resultados.xml
```

#### Para XML próprio do Catch2:
```bash
./build/executavel_testes -r xml -o resultados.xml
```

#### Para ver os formatos disponíveis:
```bash
./build/executavel_testes --list-reporters
```

### 2. Integrando com o CTest no CMake

Se você quiser que o CTest sempre gere esses arquivos automaticamente, você pode configurar propriedades no CMakeLists.txt:

```cmake
# Adicione isso logo após o catch_discover_tests
set_tests_properties(executavel_testes PROPERTIES 
    ENVIRONMENT "CATCH_OPTS=-r junit -o junit-report.xml"
)
```

### 3. Exemplo para GitHub Actions (YAML)

Se você for usar o GitHub, aqui está um trecho de como seria o seu arquivo `.github/workflows/tests.yml`:

```yaml
- name: Build and Test
  run: |
    cmake -B build
    cmake --build build
    ./build/executavel_testes -r junit -o report.xml

- name: Publish Test Report
  uses: mikepenz/action-junit-report@v3
  if: always() # Garante que o relatório seja postado mesmo se o teste falhar
  with:
    report_paths: '**/report.xml'
```

### Por que usar JUnit?

A maioria das ferramentas de visualização transforma esse arquivo .xml em uma interface gráfica bonita, mostrando exatamente qual `GIVEN/WHEN/THEN` falhou, quanto tempo levou e o log de erro, sem você precisar ler o arquivo bruto.

---

## CMake Unificado: Download, Execução e Teste

Sim, você pode e deve fazer isso! Essa é a abordagem moderna do CMake (chamada de Cloud-Native CMake ou Package Management via CMake), que torna seu projeto "clonável e executável" em qualquer máquina sem que o desenvolvedor precise instalar nada manualmente.

No CMake, você organiza isso em três blocos principais dentro do mesmo CMakeLists.txt:

### 1. Download (Gerenciamento de Dependências)
Usamos o FetchContent para baixar o Catch2 (ou qualquer outra biblioteca no GitHub) durante a fase de configuração.

### 2. Execução (O seu Código)
Definimos o seu executável principal ou a sua biblioteca lógica.

### 3. Teste (A Verificação)
Criamos um executável separado para os testes e o registramos no sistema.

### Exemplo de CMakeLists.txt Completo e Unificado:

```cmake
cmake_minimum_required(VERSION 3.14)
project(MeuSistemaCompleto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# ---------------------------------------------------------
# 1. DOWNLOAD DA BIBLIOTECA (Catch2)
# ---------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# ---------------------------------------------------------
# 2. EXECUÇÃO (Seu Programa Principal)
# ---------------------------------------------------------
# Supondo que você tenha um main.cpp para o seu app
add_executable(meu_app main.cpp soma.cpp)

# ---------------------------------------------------------
# 3. TESTE (Seus Testes Unitários)
# ---------------------------------------------------------
enable_testing()
include(Catch)

# Criamos um executável SÓ para os testes
add_executable(unit_tests testes.cpp soma.cpp)

# Linkamos o executável de teste com o Catch2
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

# Faz o CMake "enxergar" cada TEST_CASE do Catch2 individualmente
catch_discover_tests(unit_tests)
```

### Como isso funciona na prática?

1. `cmake -B build`: O CMake baixa o Catch2, configura as regras de compilação do seu app e as regras dos seus testes.
2. `cmake --build build`: Compila o seu programa (`meu_app`) e o seu testador (`unit_tests`).
3. `ctest --test-dir build`: Roda todos os testes automaticamente.

### Vantagens dessa estrutura:

- **Isolamento**: O código do seu aplicativo (`main.cpp`) fica separado do código de teste (`testes.cpp`).
- **Portabilidade**: Se você mandar esse código para um colega, ele só precisa ter o CMake e um compilador. O resto acontece sozinho.
- **Automação**: Ideal para colocar em um servidor (CI/CD), pois o script de build faz o download de tudo o que precisa.

---

## Estrutura de Pastas Profissional

Para manter um projeto profissional e fácil de expandir, a estrutura de pastas recomendada separa o código-fonte dos testes e dos arquivos de configuração.

### 1. Estrutura de Pastas

```
meu_projeto/
|
|--- CMakeLists.txt          # Arquivo principal (orquestrador)
|--- include/                # Arquivos de cabeçalho (.hpp)
|    |--- calculadora.hpp
|--- src/                    # Código-fonte da lógica (.cpp)
|    |--- CMakeLists.txt      # Configura a biblioteca do app
|    |--- main.cpp            # Ponto de entrada do programa
|    |--- calculadora.cpp
|--- tests/                  # Seus testes com Catch2
|    |--- CMakeLists.txt      # Configura o executável de testes
|    |--- test_calculadora.cpp
```

### 2. Como configurar os 3 arquivos CMakeLists.txt

#### O Principal (na raiz):

Este arquivo baixa as bibliotecas e chama as subpastas.

```cmake
cmake_minimum_required(VERSION 3.14)
project(MeuProjeto CXX)

set(CMAKE_CXX_STANDARD 17)

# 1. Download do Catch2
include(FetchContent)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com GIT_TAG v3.4.0)
FetchContent_MakeAvailable(Catch2)

# 2. Habilitar Testes
enable_testing()
include(Catch)

# 3. Incluir as subpastas
add_subdirectory(src)
add_subdirectory(tests)
```

#### O da pasta src/:

Criar uma biblioteca com a lógica para que os testes também possam usá-la.

```cmake
# Cria uma biblioteca estática com a lógica do sistema
add_library(logica_app calculadora.cpp)
target_include_directories(logica_app PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Cria o executável principal que usa essa biblioteca
add_executable(meu_app main.cpp)
target_link_libraries(meu_app PRIVATE logica_app)
```

#### O da pasta tests/:

Criar o executável de testes linkando com a lógica e o Catch2.

```cmake
add_executable(unit_tests test_calculadora.cpp)

# Linka com a lógica do app e com o Catch2
target_link_libraries(unit_tests PRIVATE logica_app Catch2::Catch2WithMain)

# Descobre os testes automaticamente
catch_discover_tests(unit_tests)
```

### Por que usar essa estrutura?

- **Reutilização**: Você define a lógica uma vez (`logica_app`) e a usa tanto no programa real quanto nos testes.
- **Limpeza**: O seu `main.cpp` não fica "poluído" com código de teste.
- **Escalabilidade**: Se você adicionar uma nova biblioteca (ex: para banco de dados), basta criar uma nova pasta e adicionar no `add_subdirectory`.

---

## SoA vs AoS com Catch2

### SoA (Structure of Arrays)

Integrar o padrão SoA (Structure of Arrays) com Catch2 e CMake é uma excelente escolha para performance (cache-friendly), especialmente em simulações ou processamento de dados.

Em vez de um array de objetos `struct { float x, y, z; }`, você tem uma struct com `vector<float> x, y, z`.

#### 1. Estrutura do Código (SoA)

No seu `include/posicoes.hpp`:

```cpp
#include <vector>

struct PosicoesSoA {
    std::vector<float> x;
    std::vector<float> y;

    void adicionar(float px, float py) {
        x.push_back(px);
        y.push_back(py);
    }

    size_t tamanho() const { return x.size(); }
};
```

#### 2. Testando SoA com Catch2

No arquivo `tests/test_soa.cpp`, o Catch2 facilita testar se os vetores paralelos estão sincronizados:

```cpp
#include <catch2/catch_test_macros.hpp>
#include "posicoes.hpp"

TEST_CASE("Data layout SoA funciona corretamente", "[performance][soa]") {
    PosicoesSoA pos;

    SECTION("Adicionando elementos") {
        pos.adicionar(10.0f, 20.0f);
        pos.adicionar(30.0f, 40.0f);

        REQUIRE(pos.tamanho() == 2);
        
        // No SoA, verificamos se os índices batem nos vetores separados
        CHECK(pos.x[0] == 10.0f);
        CHECK(pos.y[0] == 20.0f);
        CHECK(pos.x[1] == 30.0f);
        CHECK(pos.y[1] == 40.0f);
    }
}
```

#### 3. Ajuste no CMake

Como você já tem a estrutura de pastas que montamos, basta garantir que o `tests/CMakeLists.txt` inclua esse novo arquivo:

```cmake
# Em tests/CMakeLists.txt
add_executable(unit_tests 
    test_calculadora.cpp 
    test_soa.cpp          # Adicione o novo arquivo aqui
)

target_link_libraries(unit_tests PRIVATE logica_app Catch2::Catch2WithMain)
catch_discover_tests(unit_tests)
```

#### Por que testar SoA é importante?

Ao usar SoA, o erro mais comum é os vetores ficarem com tamanhos diferentes (ex: adicionar em x mas esquecer de y). Você pode usar o Catch2 para garantir essa integridade:

```cpp
REQUIRE(pos.x.size() == pos.y.size());
```

### AoS (Array of Structures)

A AoS (Array of Structures) é o padrão mais comum em C++. É quando você define uma struct para um objeto (como um Ponto) e cria um array/vetor de vários desses objetos.

Diferente do SoA, aqui todos os dados de um único objeto ficam juntos na memória.

#### 1. Estrutura do Código (AoS)

No seu `include/posicoes.hpp`:

```cpp
struct Ponto {
    float x;
    float y;
};

struct PosicoesAoS {
    std::vector<Ponto> pontos;

    void adicionar(float px, float py) {
        pontos.push_back({px, py});
    }

    size_t tamanho() const { return pontos.size(); }
};
```

#### 2. Testando AoS com Catch2

No arquivo `tests/test_aos.cpp`, o teste é mais direto porque você acessa um objeto por vez:

```cpp
#include <catch2/catch_test_macros.hpp>
#include "posicoes.hpp"

TEST_CASE("Data layout AoS funciona corretamente", "[layout][aos]") {
    PosicoesAoS pos;

    SECTION("Adicionando e verificando pontos") {
        pos.adicionar(10.0f, 20.0f);
        
        REQUIRE(pos.tamanho() == 1);
        
        // No AoS, acessamos o objeto no índice 0 e depois seus campos
        CHECK(pos.pontos[0].x == 10.0f);
        CHECK(pos.pontos[0].y == 20.0f);
    }
}
```

#### Comparação Rápida:

- **AoS (Array of Structures)**: `pontos[i].x`. Melhor para legibilidade e quando você precisa de todas as propriedades de um objeto ao mesmo tempo.
- **SoA (Structure of Arrays)**: `x[i]`. Melhor para performance em processamento em massa (SIMD), pois o processador lê apenas o que precisa (ex: só o eixo X de todos os pontos).

#### Como incluir no seu CMake:

Basta adicionar o arquivo de teste ao seu executável no `tests/CMakeLists.txt`:

```cmake
add_executable(unit_tests 
    test_soa.cpp 
    test_aos.cpp   # Adicionado aqui
)
```

---

## Benchmarks com Catch2

Quer que eu mostre como o Catch2 pode fazer um "Benchmark" para medir qual dos dois (AoS ou SoA) é mais rápido no seu computador?

O Catch2 v3 inclui suporte nativo para benchmarks, permitindo medir performance diretamente nos seus testes.

### Exemplo de Benchmark:

```cpp
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include "posicoes.hpp"

TEST_CASE("Benchmark SoA vs AoS", "[benchmark][performance]") {
    PosicoesSoA posSoA;
    PosicoesAoS posAoS;
    
    // Preencher com dados de teste
    for(int i = 0; i < 10000; ++i) {
        posSoA.adicionar(i * 0.1f, i * 0.2f);
        posAoS.adicionar(i * 0.1f, i * 0.2f);
    }
    
    BENCHMARK("SoA - Acessar X") {
        float sum = 0;
        for(size_t i = 0; i < posSoA.tamanho(); ++i) {
            sum += posSoA.x[i];
        }
        return sum;
    };
    
    BENCHMARK("AoS - Acessar X") {
        float sum = 0;
        for(size_t i = 0; i < posAoS.tamanho(); ++i) {
            sum += posAoS.pontos[i].x;
        }
        return sum;
    };
}
```

### Como executar benchmarks:

```bash
./build/unit_tests "[benchmark]"
```

---


