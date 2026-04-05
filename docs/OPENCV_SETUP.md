# Configuração Automática do OpenCV

## Visão Geral

O CMakeLists.txt deste projeto está configurado para detectar e instalar automaticamente o OpenCV caso não seja encontrado no sistema.

## Como Funciona

### 1. Detecção Automática
O sistema primeiro tenta encontrar o OpenCV instalado no sistema:
```cmake
find_package(OpenCV QUIET COMPONENTS core imgproc imgcodecs highgui videoio face)
```

### 2. Download e Compilação Automática
Se o OpenCV não for encontrado, o sistema automaticamente:
- Baixa o OpenCV versão 4.6.0 do GitHub oficial
- Baixa os módulos contrib para funcionalidades extras
- Configura o build com os módulos necessários
- Compila e instala localmente no projeto

### 3. Componentes Incluídos
- **core**: Funcionalidades básicas
- **imgproc**: Processamento de imagem
- **imgcodecs**: Leitura/escrita de imagens
- **highgui**: Interface gráfica
- **videoio**: Captura de vídeo
- **face**: Detecção facial

### 4. Configurações de Build
- **Testes desabilitados**: Acelera o processo de compilação
- **CUDA desabilitado**: Garante compatibilidade
- **OpenMP habilitado**: Melhora performance
- **Exemplos e documentação desabilitados**: Reduz tempo de build

## Mensagens de Status

Durante a configuração, você verá mensagens como:

```
-- OpenCV encontrado: versão 4.6.0
-- OpenCV include: /usr/include/opencv4
-- OpenCV libraries: opencv_core;opencv_imgproc;opencv_imgcodecs;opencv_highgui;opencv_videoio;opencv_face
```

Ou, se o OpenCV não for encontrado:

```
-- OpenCV não encontrado no sistema. Baixando e compilando OpenCV...
```

## Requisitos

- **CMake 3.14+**: Para suporte a FetchContent
- **Git**: Para clonar os repositórios
- **Compilador C++17**: Para compatibilidade com o projeto
- **Conexão com internet**: Para download do OpenCV

## Tempo de Compilação

- **Com OpenCV instalado**: ~2-5 minutos
- **Sem OpenCV (download + build)**: ~30-60 minutos

## Verificação

Após a compilação, o programa exibirá:
```
OpenCV version: 4.6.0
```

Isso confirma que o OpenCV está corretamente configurado e funcionando.
