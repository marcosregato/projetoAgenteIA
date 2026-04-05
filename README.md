# projetoAgenteIA

## Sobre

Projeto em C++ que integra:

- detecção facial com OpenCV
- síntese de voz com Flite
- suporte a modelos LLM via llama.cpp
- gerenciamento de dependências com CMake

## Requisitos

- CMake 3.14 ou superior
- compilador C++17 (`g++` ou `clang++`)
- OpenCV com módulos: `core`, `imgproc`, `imgcodecs`, `highgui`, `videoio`, `face`
- Flite (`libflite` e `flite_cmu_us_slt`)

## Modelos necessários

O projeto precisa destes arquivos para funcionar corretamente:

- `haarcascades/haarcascade_frontalface_alt2.xml`
- `lbfmodel/lbfmodel.yaml`

### Download manual

```bash
cd /home/marcos/workspace/projetoAgenteIA
mkdir -p haarcascades lbfmodel
wget -O haarcascades/haarcascade_frontalface_alt2.xml \
  https://raw.githubusercontent.com/opencv/opencv/master/data/haarcascades/haarcascade_frontalface_alt2.xml
wget -O lbfmodel/lbfmodel.yaml \
  https://raw.githubusercontent.com/opencv/opencv_contrib/master/modules/face/data/lbfmodel.yaml
```

### Verificação

```bash
ls -la haarcascades/haarcascade_frontalface_alt2.xml
ls -la lbfmodel/lbfmodel.yaml
```

## Build

Antes de compilar, instale o pacote de desenvolvimento do eSpeak NG para habilitar a fala em Português:

```bash
sudo apt-get update && sudo apt-get install -y libespeak-ng-dev espeak-ng libespeak-ng1
```

Esse comando faz o seguinte:

- `sudo apt-get update`: atualiza a lista de pacotes disponíveis no sistema.
- `sudo apt-get install -y libespeak-ng-dev`: instala o pacote de desenvolvimento do eSpeak NG, incluindo headers e biblioteca necessários para a síntese de voz em Português.
### Configuração e Build

Prepare o ambiente de compilação:

```bash
cmake -S . -B build
```

Compile o projeto com CMake a partir da raiz do repositório:

```bash
cmake --build build --target projetoAgenteIA
```

## Executar

```bash
./build/src/projetoAgenteIA
```

## Estrutura do projeto

- `CMakeLists.txt` — build principal do projeto
- `src/` — código-fonte do aplicativo e módulos
- `include/` — cabeçalhos do projeto
- `haarcascades/` — arquivos Haar Cascade para detecção facial
- `lbfmodel/` — modelo de landmarks faciais
- `build/` — diretório de compilação gerado pelo CMake

## Observações

- O RapidJSON agora é gerenciado via CMake (`FetchContent`), então não é necessário manter cópias locais extras.
- Se a webcam não abrir, verifique se ela está conectada e não está em uso por outro software.
- Para alterar a lógica de detecção ou vídeo, edite `src/main.cpp`.

## Testes

O projeto inclui uma suíte completa de testes para verificar todas as funcionalidades:

### Menu Interativo de Testes

Execute o menu principal para acessar todos os testes disponíveis:

```bash
cd build
./tests/run_tests
```

**Ou use o script de atalho:**

```bash
./test.sh menu
```

**Opções Disponíveis:**
- **🎥 Testes de Processamento de Imagem (interativo)**: Testes de webcam e detecção facial com opções interativas
- **🔊 Testes de Voz (simples)**: Testes dos motores Flite e eSpeak-ng
- **📋 Testes Unitários**: Testes automatizados com framework Catch2
- **🎯 Todos os testes (automático)**: Execução completa da suíte de testes

### Testes Individuais

#### Testes de Processamento de Imagem
```bash
cd build
./tests/test_image_processor
```

#### Testes de Voz
```bash
cd build
./tests/test_voice_simple
```

#### Testes Unitários
```bash
cd build
./tests/unit_tests
```

### Testes Interativos

Os testes de processamento de imagem oferecem modos interativos que utilizam hardware real:

- **Modo Seguro**: Verificação rápida sem abrir hardware
- **Modo Interativo**: Teste completo com webcam em tempo real
- **Segurança**: Avisos claros, contagem regressiva e encerramento com ESC

Para mais detalhes, consulte `docs/INTERACTIVE_TESTS.md`.

### Script de Atalho

Para facilitar o uso dos testes, utilize o script `test.sh`:

```bash
./test.sh [opção]
```

**Comandos disponíveis:**
- `./test.sh menu` - Abre o menu interativo
- `./test.sh image` - Testa processamento de imagem
- `./test.sh voice` - Testa síntese de voz
- `./test.sh unit` - Testa unitários
- `./test.sh all` - Executa todos os testes
- `./test.sh build` - Compila o projeto
- `./test.sh clean` - Limpa o build
- `./test.sh help` - Mostra ajuda

O script automaticamente compila os testes se necessário e oferece saída colorida para melhor visualização.

## Execução sem detecção facial

Se quiser apenas abrir a webcam sem detectar rostos, ajuste `src/main.cpp` comentando a chamada de detecção:

```cpp
// status = cam.detectarRosto();
status = cam.openCam();
```

## Modelos LLM (opcional)

Baixe modelos `.gguf` do Hugging Face quando necessário:

```bash
wget -O modelo.gguf https://huggingface.co/USUARIO/REPOSITORIO/resolve/main/modelo.gguf
```

## Ajuda

Se precisar de suporte para dependências ou build, consulte a documentação das bibliotecas usadas (OpenCV, Flite, llama.cpp) ou abra uma issue no repositório.
# projetoAgenteIA
