# Arquitetura de Projetos de IA em C++

> **Guia completo para estruturação de projetos de Inteligência Artificial em C++ com CMake**

---

## Localização do CMakeLists.txt

A localização do arquivo CMakeLists.txt em um sistema de IA depende da complexidade do projeto, mas a arquitetura mais aceita e organizada segue o padrão de divisão por responsabilidade.

### Cenários Principais

#### 1. Arquitetura Modular (Recomendada)

Para sistemas profissionais onde você separa a lógica de IA (C++, CUDA) da interface ou do processamento de dados, o CMakeLists.txt deve ser estruturado de forma hierárquica:

- **Raiz do projeto (/)**: Um CMakeLists.txt principal que define o projeto, versões e inclui as subpastas (`add_subdirectory`).
- **Pasta de Código-Fonte (/src ou /core)**: Um CMakeLists.txt específico para compilar a lógica da IA, links de bibliotecas (como OpenCV, TensorRT ou LibTorch) e definições de hardware (GPU/CPU).
- **Pasta de Testes (/tests)**: Um arquivo separado para testes unitários.

#### 2. Arquitetura Simples (Projetos Menores)

Se o projeto for um script único de inferência em C++, o CMakeLists.txt fica na raiz do diretório.

---

## Estrutura Visual Sugerida

```
meu_projeto_ia/
|
|--- CMakeLists.txt          (Configuração global e dependências)
|--- data/                   (Datasets e pesos do modelo)
|--- include/                (Arquivos .h)
|--- src/
|    |--- CMakeLists.txt      (Alvos de compilação específicos)
|    |--- main.cpp
|    |--- inference_engine.cpp
|--- tests/
|    |--- test_model.cpp
```

### Onde NÃO colocar:
Nunca coloque dentro de pastas de dados (/data), modelos exportados (/models) ou ambientes virtuais (/venv), pois isso quebra a separação entre código e recursos.

---

## CUDA: Aceleração de Hardware para IA

### O que é CUDA?

O CUDA (Compute Unified Device Architecture) é uma plataforma de computação paralela e um modelo de programação criado pela NVIDIA.

Pense nele como o "tradutor" que permite que o seu código (C++, Python, etc.) converse diretamente com a Unidade de Processamento Gráfico (GPU) para realizar cálculos matemáticos complexos.

### Por que ele é vital para sua IA?

As IAs realizam bilhões de cálculos de matrizes simultaneamente. Enquanto um processador comum (CPU) tem poucos núcleos (8 a 16) para tarefas gerais, uma GPU NVIDIA tem milhares de núcleos especializados em matemática simples. O driver CUDA organiza esse exército de núcleos para trabalhar ao mesmo tempo.

### Driver vs Toolkit

Para desenvolver seu sistema em C++, você precisa entender esses dois componentes:

- **Driver CUDA**: É o software que você instala no sistema operacional (Windows/Linux) para que ele reconheça a placa de vídeo. Ele é a ponte básica de comunicação.
- **CUDA Toolkit**: É o pacote de ferramentas para desenvolvedores (incluindo o compilador nvcc). É o que o seu CMake vai procurar para transformar seu código C++ em algo que a GPU entenda.

### Como verificar se o driver está instalado?

No terminal do seu Linux, digite:
```bash
nvidia-smi
```

### Dica de Ouro para CMake

Em IA, é comum usar o CMake para gerenciar a detecção automática de drivers CUDA. Certifique-se de que seu arquivo na raiz contenha:
```cmake
find_package(CUDA REQUIRED)
```

Isso garante que o sistema encontre o hardware de aceleração.

---

## A Pasta /core: Coração Tecnológico do Sistema

A pasta `/core` (ou às vezes chamada de `/src/core`) é o coração tecnológico do seu sistema de IA. Ela é usada para separar a lógica pesada e essencial do restante do projeto (como interfaces de usuário, scripts de utilidade ou carregamento de dados).

### O que fica em /core?

Em um sistema de IA, a pasta `/core` geralmente contém:

1. **Mecanismo de Inferência (Inference Engine)**: O código C++/CUDA que carrega o modelo (ONNX, TensorRT, etc.) e executa as previsões.
2. **Algoritmos Principais**: Implementações matemáticas puras, processamento de tensores ou filtros de imagem customizados.
3. **Abstração de Hardware**: Código que gerencia se a IA vai rodar na CPU, GPU ou NPU, garantindo que o resto do sistema não precise se preocupar com isso.
4. **Gerenciamento de Memória**: Como os dados são movidos para a placa de vídeo e voltam para o processador.

### Por que usar /core em vez de apenas /src?

- **Isolamento**: Se você decidir mudar de PyTorch para TensorFlow, você só mexe no que está dentro de `/core`. O resto do sistema (como o código que salva o resultado em um banco de dados) continua intacto.
- **Performance**: No `/core`, o CMakeLists.txt geralmente é configurado com otimizações máximas de compilador (-O3, -march=native), que podem não ser necessárias em outras partes do código.

### Exemplo Prático

Imagine um sistema de reconhecimento facial:
- `/src/main.cpp`: Abre a câmera.
- `/src/core/detector.cpp`: Onde a mágica da rede neural acontece (o "core").
- `/src/utils/logger.cpp`: Apenas salva logs.

---

## Melhor Arquitetura para IA em C++

A melhor arquitetura para um sistema de IA em C++ segue o padrão **Modular por Subdiretórios**. Isso é essencial porque sistemas de IA geralmente misturam código de alta performance (C++/CUDA) com bibliotecas externas pesadas (TensorRT, OpenCV, LibTorch).

### Estrutura de Diretórios Recomendada

```
meu_sistema_ia/
|
|--- CMakeLists.txt              # 1. Arquivo Raiz (Configurações Globais)
|--- extern/                     # Bibliotecas externas (git submodules)
|--- include/                    # Headers públicos (.hpp)
|--- src/                        # Implementação (.cpp)
|    |--- core/                   # Lógica da Rede Neural / Inferência
|    |    |--- CMakeLists.txt      # 2. Configuração do Módulo Core
|    |    |--- inference_engine.cpp
|    |--- utils/                  # Processamento de imagem/dados
|    |    |--- CMakeLists.txt      # 3. Configuração do Módulo Utils
|    |    |--- image_processor.cpp
|    |--- main.cpp                # Ponto de entrada do sistema
|--- tests/                      # Testes unitários
|    |--- CMakeLists.txt
```

### Por que esta é a melhor arquitetura?

1. **O CMakeLists.txt da Raiz**: Define o padrão do C++ (geralmente 17 ou 20), busca as dependências do sistema (`find_package`) e usa o comando `add_subdirectory(src)` para organizar a compilação.
2. **O CMakeLists.txt do /core**: É aqui que você isola as flags de otimização pesadas (-O3, -march=native) e vincula as bibliotecas de IA (como CUDA ou TensorRT). Isso evita que essas configurações "vazem" para partes simples do sistema, como logs ou interface.
3. **Separação de Interface e Implementação**: Manter os headers em `/include` e o código em `/src` facilita a reutilização do seu motor de IA como uma biblioteca (.lib ou .so) em outros projetos no futuro.

### Exemplo do arquivo na Raiz

```cmake
cmake_minimum_required(VERSION 3.15)
project(SistemaIA_Project)

set(CMAKE_CXX_STANDARD 17)

# Busca dependências de IA
find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)

# Adiciona os módulos
add_subdirectory(src/core)
add_subdirectory(src/utils)

# Executável principal
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ia_core ia_utils)
```

---

## Comando Linux para Criar a Arquitetura

Para criar toda essa estrutura de diretórios e os arquivos CMakeLists.txt básicos de uma só vez, copie e cole este comando no seu terminal Linux:

```bash
mkdir -p meu_sistema_ia/{src/{core,utils},include,extern,tests} && \
touch meu_sistema_ia/CMakeLists.txt \
      meu_sistema_ia/src/main.cpp \
      meu_sistema_ia/src/core/CMakeLists.txt \
      meu_sistema_ia/src/core/inference_engine.cpp \
      meu_sistema_ia/src/utils/CMakeLists.txt \
      meu_sistema_ia/src/utils/image_processor.cpp \
      meu_sistema_ia/tests/CMakeLists.txt && \
tree meu_sistema_ia
```

### O que esse comando faz:

- `mkdir -p`: Cria a pasta principal e todas as subpastas (src/core, src/utils, include, etc.) de forma hierárquica.
- `touch`: Cria os arquivos vazios nos locais corretos, incluindo os três níveis de CMakeLists.txt que discutimos.
- `tree`: Exibe o desenho da árvore de diretórios no final para você confirmar se está tudo certo.

### Conteúdo Básico para o CMakeLists.txt da Raiz

Se quiser que o arquivo principal já venha com o conteúdo básico para IA, rode este comando adicional dentro da pasta `meu_sistema_ia`:

```bash
cat meu_sistema_ia/CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(SistemaIA_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Exemplo: Buscar dependências comuns de IA
# find_package(OpenCV REQUIRED)
# find_package(CUDA REQUIRED)

add_subdirectory(src/core)
add_subdirectory(src/utils)

add_executable(\${PROJECT_NAME} src/main.cpp)
target_link_libraries(\${PROJECT_NAME} PRIVATE ia_core ia_utils)
EOF
```

---

## Descrição dos Diretórios Criados

### `meu_sistema_ia/` (Raiz)
É o "capitão" do projeto. Contém o CMakeLists.txt principal, que coordena a compilação de todos os módulos e define as versões do C++ e das bibliotecas globais (como CUDA ou OpenCV).

### `src/` (Source)
Onde reside todo o código-fonte executável.
- `main.cpp`: O ponto de entrada. Ele apenas "chama" as funções que estão no core e no utils.
- `core/`: Onde fica o motor de IA. Aqui você coloca o carregamento do modelo, a inferência (forward pass) e cálculos matemáticos pesados. É a parte que geralmente exige mais performance (GPU).
- `utils/`: Funções de apoio. Coisas como redimensionar imagens, converter cores (RGB para BGR), ler arquivos CSV ou salvar logs de processamento.

### `include/` (Headers)
Guarda os arquivos .hpp (ou .h). Separar os headers aqui permite que outros programadores usem suas funções sem precisar ver como o código foi escrito por dentro. Isso é uma boa prática de "encapsulamento".

### `extern/` (Externals)
Espaço para bibliotecas de terceiros que não estão instaladas no seu sistema. Se você baixar um pequeno repositório do GitHub para ajudar no projeto, ele deve morar aqui (geralmente como um Git Submodule).

### `tests/` (Testes)
Fundamental em IA para garantir que o modelo está retornando o que deveria. Aqui você coloca códigos que testam se a saída da sua rede neural faz sentido antes de rodar o sistema inteiro.

### `build/` (Geralmente criado depois)
Você não criou essa pasta com o comando, mas o CMake a criará. É onde ficam os arquivos binários temporários. **Regra de ouro**: nunca mexa manualmente nada dentro da `build/`, apenas delete-a se precisar "limpar" o projeto.

---

## Exemplo de Implementação

Para testar se a sua arquitetura está funcionando (especialmente a comunicação entre as pastas src, core e utils), vamos criar um exemplo simples onde o main.cpp chama funções dos outros módulos.

### 1. Arquivo `src/core/inference_engine.cpp`
(Simula o carregamento da IA)

```cpp
#include <iostream>

void runInference() {
    std::cout << "[CORE] Executando inferência na GPU (Simulada)..." << std::endl;
}
```

### 2. Arquivo `src/utils/image_processor.cpp`
(Simula o pré-processamento)

```cpp
#include <iostream>

void processImage() {
    std::cout << "[UTILS] Redimensionando imagem para 224x224..." << std::endl;
}
```

### 3. Arquivo `src/main.cpp`
(O arquivo principal)

```cpp
#include <iostream>

// Declarações simples (para teste rápido sem headers separados)
void runInference();
void processImage();

int main() {
    std::cout << "--- Iniciando Sistema de IA ---" << std::endl;
    
    processImage();   // Chama Utils
    runInference();   // Chama Core
    
    std::cout << "--- Sistema finalizado com sucesso! ---" << std::endl;
    return 0;
}
```

---

## Como Compilar

Siga estes passos no terminal dentro da pasta `meu_sistema_ia`:

### 1. Crie a pasta de build:
```bash
mkdir build && cd build
```

### 2. Configure o projeto com o CMake:
```bash
cmake ..
```

### 3. Compile e rode:
```bash
make && ./SistemaIA_Project
```

### Nota Importante:
Para esse teste funcionar, os arquivos CMakeLists.txt dentro de `src/core/` e `src/utils/` precisam dizer ao CMake que eles são bibliotecas.

---
