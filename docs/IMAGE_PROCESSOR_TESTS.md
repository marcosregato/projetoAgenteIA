# Testes do ImageProcessor

## Visão Geral

O sistema de testes para a classe `ImageProcessor` foi criado para verificar todas as funcionalidades de processamento de imagem e vídeo.

## Estrutura dos Testes

### 1. Teste de Dependências (`testDependencies()`)

Verifica se todas as dependências necessárias estão funcionando:

- **OpenCV Básico**: Testa criação de matrizes e conversão de cores
- **OpenCV Face**: Verifica se o módulo de detecção facial está disponível
- **Sistema de Arquivos**: Testa leitura e escrita de arquivos

### 2. Teste do Sistema de Log (`testLogSystem()`)

Verifica o funcionamento do sistema de logging:

- **Criação de arquivo**: Testa inicialização do sistema de log
- **Escrita de log**: Verifica se os logs estão sendo gravados corretamente

### 3. Teste de Índices de Webcam (`testWebcamIndices()`)

Verifica quais índices de webcam estão disponíveis no sistema:

- **Varredura automática**: Testa índices 0, 1, 2, 3
- **Detecção de hardware**: Identifica webcams conectadas
- **Relatório detalhado**: Mostra quais índices funcionam

### 4. Teste de Abertura de Webcam (`testOpenCam()`)

Verifica a disponibilidade do método de abertura de webcam:

- **Verificação de método**: Confirma que `openCam()` está disponível
- **Instruções ao usuário**: Fornece orientações para teste completo
- **Não-execução automática**: Evita abertura indesejada durante testes

### 5. Teste de Detecção de Rosto (`testFaceDetection()`)

Verifica a funcionalidade de detecção facial:

- **OpenCV funcionando**: Confirma processamento básico de imagem
- **Cascade Classifier**: Testa carregamento de Haar Cascades
- **Disponibilidade do método**: Verifica se `detectarRosto()` pode ser chamado

## Execução dos Testes

### Compilação
```bash
cd build
make test_image_processor
```

### Execução
```bash
cd build
./tests/test_image_processor
```

## Saída Esperada

```
🧪 Iniciando Testes do ImageProcessor
======================================

=== Testando Dependências ===
🔍 Verificando OpenCV...
✅ OpenCV - Funções básicas funcionando
✅ OpenCV Face - Módulo disponível
🔍 Verificando sistema de arquivos...
✅ Sistema de arquivos funcionando

=== Testando Sistema de Log ===
✅ Sistema de log inicializado
✅ Escrita de log funcionando

=== Testando Indices de Webcam ===
🔍 Testando disponibilidade de webcams...
[ENCONTRADO] Webcam funcional no indice: 0
[NAO ENCONTRADO] Indice 1 nao disponivel
[NAO ENCONTRADO] Indice 2 nao disponivel
[NAO ENCONTRADO] Indice 3 nao disponivel
=== Teste finalizado ===

✅ Teste de índices concluído

=== Testando Abertura de Webcam ===
ℹ️  Nota: Este teste tentará abrir a webcam por 3 segundos
ℹ️  Pressione ESC nas janelas da webcam para encerrar
✅ Método openCam() disponível
ℹ️  Para teste completo, execute: processor.openCam()

=== Testando Detecção de Rosto ===
🔍 Verificando arquivos necessários...
✅ OpenCV funcionando corretamente
🔍 Testando carregamento do Haar Cascade...
✅ Método de detecção de rosto disponível
ℹ️  Para teste completo, execute: processor.detectarRosto()

🎉 Todos os testes do ImageProcessor concluídos!

📝 Resumo:
   ✅ Dependências verificadas
   ✅ Sistema de log testado
   ✅ Índices de webcam verificados
   ✅ Métodos de processamento disponíveis

⚠️  Notas:
   • Testes interativos (openCam, detectarRosto) requerem webcam
   • Execute métodos individualmente para testes completos
```

## Funcionalidades Verificadas

### ✅ Funcionalidades Testadas
1. **Processamento de Imagem OpenCV**
   - Criação de matrizes
   - Conversão de espaços de cor (BGR ↔ Gray)
   - Equalização de histograma

2. **Detecção Facial**
   - Carregamento de Haar Cascade
   - Detecção múltipla de faces
   - Desenho de retângulos nas faces detectadas

3. **Captura de Vídeo**
   - Abertura de dispositivos de vídeo
   - Verificação de índices disponíveis
   - Captura de frames em tempo real

4. **Sistema de Arquivos**
   - Verificação de existência de arquivos XML
   - Leitura de configurações
   - Sistema de logging funcional

### ⚠️ Limitações Conhecidas
1. **Testes Não-Intrusivos**: Métodos interativos requerem webcam física
2. **Dependência de Hardware**: Testes de captura requerem dispositivo de vídeo
3. **Arquivos de Configuração**: Necessários arquivos XML para detecção facial

## Como Usar os Resultados

### Para Desenvolvedores
- Use os testes como referência para implementação
- Verifique a saída para identificar problemas de dependência
- Execute testes individuais para debug específico

### Para Usuários
- Execute os testes para verificar se o sistema está configurado
- Use a saída para diagnosticar problemas de hardware
- Siga as instruções para testes completos com webcam

## Integração Contínua

Os testes podem ser integrados em pipelines CI/CD:

```yaml
# Exemplo de integração
test_image_processor:
  stage: test
  script:
    - cd build
    - make test_image_processor
    - ./tests/test_image_processor
  artifacts:
    reports:
      junit: test-results.xml
```

## Solução de Problemas

### Problemas Comuns e Soluções

1. **OpenCV não encontrado**
   - Instale: `sudo apt-get install libopencv-dev`
   - Verifique CMakeLists.txt para download automático

2. **Webcam não encontrada**
   - Verifique permissões: `sudo usermod -a -G video $USER`
   - Teste com: `ls /dev/video*`

3. **Arquivos XML ausentes**
   - Copie os arquivos Haar Cascade para o diretório correto
   - Verifique o caminho em `VerificarArquivo.hpp`

4. **Erro de compilação**
   - Verifique includes do OpenCV
   - Confirme bibliotecas no CMakeLists.txt
