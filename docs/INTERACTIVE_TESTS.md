# Testes Interativos do ImageProcessor

## Visão Geral

Os testes interativos permitem verificar o funcionamento das funcionalidades de processamento de imagem e vídeo em tempo real, utilizando hardware real (webcam).

## Menu Principal

### Acesso Rápido
```bash
cd build
./tests/run_tests
```

### Execução Direta
```bash
cd build
./tests/test_image_processor
```

## Opções Interativas Disponíveis

### 1. Teste de Abertura de Webcam (`openCam`)

**Modos Disponíveis:**

#### Opção 1: Teste Rápido
- **Descrição**: Verificação apenas da disponibilidade do método
- **Uso**: Ideal para CI/CD ou ambientes sem webcam
- **Saída**: Confirmação que o método `openCam()` existe
- **Segurança**: Não abre hardware

#### Opção 2: Teste Interativo
- **Descrição**: Abertura real da webcam com exibição de vídeo
- **Uso**: Teste completo em ambiente de desenvolvimento
- **Segurança**: 
  - Aviso claro antes de iniciar
  - Contagem regressiva de 3 segundos
  - Encerramento com tecla ESC
- **Funcionalidades Testadas**:
  - Detecção automática de índices (0, 1, 2)
  - Abertura de dispositivo V4L2
  - Captura de frames em tempo real
  - Exibição em janela OpenCV

### 2. Teste de Detecção de Rosto (`detectarRosto`)

**Modos Disponíveis:**

#### Opção 1: Verificação Rápida
- **Descrição**: Teste de componentes sem usar webcam
- **Funcionalidades Verificadas**:
  - OpenCV básico (criação de matrizes)
  - Módulo OpenCV Face
  - Disponibilidade do método `detectarRosto()`
- **Uso**: Verificação de dependências

#### Opção 2: Teste Interativo
- **Descrição**: Detecção facial em tempo real
- **Segurança**:
  - Aviso antes de iniciar
  - Contagem regressiva de 3 segundos
  - Encerramento com ESC a qualquer momento
- **Funcionalidades Testadas**:
  - Carregamento de Haar Cascade
  - Detecção múltipla de faces
  - Desenho de retângulos nas faces detectadas
  - Processamento em tempo real
  - Equalização de histograma
  - Conversão BGR → Gray

## Fluxo de Teste Interativo

### Inicialização
```
🧪 Menu de Testes - projetoAgenteIA
======================================

Escolha o teste que deseja executar:

1. 🎥 Testes de Processamento de Imagem (interativo)
2. 🔊 Testes de Voz (simples)
3. 📋 Testes Unitários
4. 🎯 Todos os testes (automático)
0. 🚪 Sair
```

### Exemplo de Sessão Interativa

#### Teste de Webcam
```
=== Testando Abertura de Webcam ===
Escolha o modo de teste:
1. Teste rápido (verificação apenas)
2. Teste interativo com webcam
3. Pular teste
Opção: 2

🎥 Iniciando teste interativo com webcam...
⚠️  ATENÇÃO: Este teste abrirá sua webcam!
⚠️  Pressione ESC na janela para encerrar
🎥 Iniciando em 3 segundos...
Iniciando em 3 segundos...
Iniciando em 2 segundos...
Iniciando em 1 segundos...
🎥 Iniciando agora!

Sucesso! Webcam aberta no indice: 0
[Janela com vídeo ao vivo aparece]
```

#### Teste de Detecção Facial
```
=== Testando Detecção de Rosto ===
Escolha o modo de teste:
1. Verificação rápida (sem webcam)
2. Teste interativo com webcam
3. Pular teste
Opção: 2

🎥 Modo interativo selecionado - ATENÇÃO!
⚠️  Este teste usará sua webcam!
⚠️  Pressione ESC para encerrar a qualquer momento
🎥 Iniciando em 3 segundos...
Iniciando em 3 segundos...
Iniciando em 2 segundos...
Iniciando em 1 segundos...
🎥 Iniciando agora!

🎥 Executando detecção facial em tempo real...
📹 Procurando rostos... (pressione ESC para parar)
[Janela com detecção facial em tempo real]
✅ Detecção de rosto concluída com sucesso!
```

## Requisitos de Hardware

### Mínimos
- **Webcam USB**: Dispositivo V4L2 compatível
- **Permissões**: Acesso ao grupo `video`
  ```bash
  sudo usermod -a -G video $USER
  # Reiniciar sessão necessária
  ```
- **Sistema Operacional**: Linux (testado no Ubuntu)

### Recomendados
- **Iluminação**: Boa iluminação facial
- **Distância**: 30-100cm da câmera
- **Fundo**: Fundo simples para melhor detecção

## Solução de Problemas

### Erros Comuns

#### "can't open camera by index"
```
❌ [ WARN:0@0.109] open VIDEOIO(V4L2:/dev/video0): can't open camera by index
```
**Causas:**
- Webcam não conectada
- Permissões insuficientes
- Dispositivo em uso por outro aplicativo

**Soluções:**
```bash
# Verificar dispositivos disponíveis
ls /dev/video*

# Verificar permissões
groups $USER | grep video

# Adicionar ao grupo video (se necessário)
sudo usermod -a -G video $USER
# Reiniciar sessão
```

#### "Nenhuma webcam encontrada"
**Soluções:**
1. Verificar conexão física
2. Testar diferentes índices: 0, 1, 2, 3
3. Verificar se outro aplicativo está usando a webcam
4. Reiniciar sistema

#### Detecção não funciona
**Causas:**
- Iluminação inadequada
- Distância incorreta
- Movimento excessivo
- Múltiplas faces na cena

**Soluções:**
1. Melhorar iluminação
2. Manter-se estável
3. Usar fundo simples
4. Ajustar distância da câmera

## Performance

### Resultados Esperados

#### Webcam
- **FPS**: 30+ frames por segundo
- **Resolução**: 640x480 ou superior
- **Latência**: <100ms

#### Detecção Facial
- **Precisão**: >85% em boas condições
- **Tempo de Detecção**: <50ms por frame
- **Faces Simultâneas**: Até 5 faces

### Métricas de Desempenho
```cpp
// Exemplo de código para medição
auto start = std::chrono::high_resolution_clock::now();
// ... processamento ...
auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
std::cout << "Tempo: " << duration.count() << "ms" << std::endl;
```

## Integração com Desenvolvimento

### Uso em Código
```cpp
#include "utils/image_processor.hpp"

int main() {
    ImageProcessor processor;
    
    // Teste rápido
    if (processor.openCam() == 0) {
        std::cout << "Webcam funcionando!" << std::endl;
    }
    
    // Teste de detecção
    if (processor.detectarRosto() == 0) {
        std::cout << "Detecção facial OK!" << std::endl;
    }
    
    return 0;
}
```

### Debug e Troubleshooting
```cpp
// Habilitar logs detalhados
LogSistema logger;
logger.criarArquivoLog();

// Verificar índices disponíveis
processor.testeIndiceWebCam();
```

## Scripts de Automação

### Teste Automatizado
```bash
#!/bin/bash
# test_webcam.sh

echo "🧪 Iniciando teste automatizado de webcam..."

cd build
./tests/test_image_processor << EOF
1
1
1
EOF

echo "✅ Teste concluído!"
```

### Validação em CI/CD
```yaml
# .github/workflows/test-webcam.yml
name: Teste de Webcam
on: [push, pull_request]

jobs:
  test-webcam:
    runs: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    - name: Setup dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y libopencv-dev v4l-utils
    
    - name: Test webcam availability
      run: |
        v4l2-ctl --list-devices
        ls /dev/video*
    
    - name: Run interactive tests
      run: |
        cd build
        echo "1" | ./tests/test_image_processor
```

## Referências

### Documentação
- [OpenCV Documentation](https://docs.opencv.org/)
- [V4L2 API](https://www.kernel.org/doc/html/latest/media/v4l-dev/)
- [Haar Cascades](https://github.com/opencv/opencv/tree/master/data/haarcascades)

### Tutoriais
- [OpenCV Face Detection](https://docs.opencv.org/4.x/d2/d0e/tutorial_py_face_detection.html)
- [Real-time Video Processing](https://www.learnopencv.com/real-time-face-detection-opencv-cpp-python/)

## Contribuição

### Adicionando Novos Testes
1. Criar método na classe `ImageProcessor`
2. Adicionar teste correspondente em `test_image_processor.cpp`
3. Incluir opção no menu interativo
4. Documentar novo teste
5. Atualizar CMakeLists.txt se necessário

### Padrões de Código
- Tratar exceções adequadamente
- Fornecer feedback claro ao usuário
- Implementar encerramento seguro (ESC)
- Limpar recursos ao finalizar
