# Testes do Projeto projetoAgenteIA

## Visão Geral

Este diretório contém suítes de testes para verificar o funcionamento das principais funcionalidades do sistema.

## Testes Disponíveis

### 1. Testes de Voz (SintetizadorVoz)

#### `test_voice_simple.cpp`
- **Descrição**: Teste simplificado dos motores de síntese de voz
- **Funcionalidades**: Flite (inglês) e eSpeak-ng (português)
- **Execução**: `./tests/test_voice_simple`

#### `test_voice_engines.cpp`
- **Descrição**: Teste completo com logging detalhado
- **Funcionalidades**: Todos os métodos dos motores de voz
- **Execução**: `./tests/test_voice_engines`

### 2. Testes de Processamento de Imagem (ImageProcessor)

#### `test_image_processor.cpp`
- **Descrição**: Teste abrangente de processamento de imagem e vídeo
- **Funcionalidades**: OpenCV, detecção facial, webcam, logging
- **Execução**: `./tests/test_image_processor`

### 3. Testes Unitários

#### `unit_tests`
- **Descrição**: Testes unitários usando framework Catch2
- **Cobertura**: Módulos core, utils, arquivo, agente
- **Execução**: `./tests/unit_tests`

## Compilação

### Compilar Todos os Testes
```bash
cd build
make test_voice_simple test_voice_engines test_image_processor unit_tests
```

### Compilação Individual
```bash
# Testes de voz
make test_voice_simple
make test_voice_engines

# Testes de imagem
make test_image_processor

# Testes unitários
make unit_tests
```

## Execução

### Executar Testes Específicos
```bash
cd build

# Teste rápido de voz
./tests/test_voice_simple

# Teste completo de processamento
./tests/test_image_processor

# Testes unitários
./tests/unit_tests
```

### Executar Todos os Testes
```bash
cd build
./tests/test_voice_simple && ./tests/test_image_processor
```

## Documentação

- **[Testes de Voz](docs/VOICE_ENGINE_SELECTION.md)**: Documentação completa dos motores de voz
- **[Testes de Imagem](docs/IMAGE_PROCESSOR_TESTS.md)**: Documentação detalhada do ImageProcessor
- **[OpenCV Setup](docs/OPENCV_SETUP.md)**: Configuração automática do OpenCV

## Estrutura dos Testes

```
tests/
├── README.md                    # Este arquivo
├── CMakeLists.txt              # Configuração de build
├── test_voice_simple.cpp         # Teste simplificado de voz
├── test_voice_engines.cpp        # Teste completo de voz
├── test_image_processor.cpp      # Teste de processamento de imagem
└── [arquivos de teste unitários] # Testes unitários existentes
```

## Requisitos para Execução

### Dependências do Sistema
- **OpenCV 4.6+**: Processamento de imagem e vídeo
- **Flite**: Síntese de voz em inglês
- **eSpeak-ng**: Síntese de voz em português
- **CMake 3.14+**: Sistema de build
- **C++17**: Compilador compatível

### Hardware Opcional
- **Webcam**: Para testes de captura de vídeo
- **Microfone**: Para verificação de áudio (eSpeak-ng)
- **Placa de vídeo**: Para aceleração OpenCV (opcional)

## Fluxo de Testes Recomendado

### 1. Verificação de Dependências
```bash
./tests/test_image_processor
```
Este teste verifica se todas as dependências estão instaladas e funcionando.

### 2. Testes de Funcionalidades
```bash
./tests/test_voice_simple
```
Testa os motores de voz sem necessidade de hardware adicional.

### 3. Testes Completos
```bash
# Com webcam disponível
./tests/test_voice_engines

# Testes unitários
./tests/unit_tests
```

## Saída e Interpretação

### ✅ Sucesso Indicado Por:
- **OpenCV version: X.X.X**: OpenCV funcionando
- **✅ [funcionalidade]**: Teste passou
- **🎉 Todos os testes concluídos**: Sistema funcional

### ⚠️ Avisos Comuns:
- **[WARN:0@0.109]**: Avisos do OpenCV (normais)
- **⚠️ Notas**: Informações adicionais sobre limitações
- **ℹ️**: Informações úteis para o usuário

### ❌ Erros e Soluções:
- **fatal error: opencv2/opencv.hpp**: OpenCV não encontrado
  - Solução: Verifique CMakeLists.txt para download automático
- **undefined reference**: Erro de linking
  - Solução: Verifique bibliotecas no CMakeLists.txt
- **can't open camera**: Sem permissão ou hardware ausente
  - Solução: `sudo usermod -a -G video $USER`

## Integração com CI/CD

### GitHub Actions Example
```yaml
name: Testes
on: [push, pull_request]

jobs:
  test:
    runs: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    - name: Configurar Dependências
      run: |
        sudo apt-get update
        sudo apt-get install -y libopencv-dev libflite-dev espeak-ng-dev
    
    - name: Build e Testar
      run: |
        mkdir build && cd build
        cmake ..
        make test_image_processor test_voice_simple
        ./tests/test_image_processor
        ./tests/test_voice_simple
```

## Contribuição

### Adicionando Novos Testes
1. Crie o arquivo `.cpp` no diretório `tests/`
2. Adicione o executável em `CMakeLists.txt`
3. Atualize este `README.md`
4. Documente o teste em `docs/`

### Padrões de Código
- Use namespaces apropriados (`std::`, `cv::`)
- Inclua headers necessários
- Trate exceções adequadmente
- Forneça saída clara e informativa

## Suporte

Para problemas ou dúvidas:
1. Verifique a documentação específica de cada teste
2. Consulte os logs gerados pelos testes
3. Revise os requisitos de hardware e software
