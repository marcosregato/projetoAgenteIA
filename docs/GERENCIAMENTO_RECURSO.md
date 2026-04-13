# Gerenciamento de Recursos

## Visão Geral

Este documento descreve o gerenciamento de recursos utilizados no projeto AgenteIA, incluindo bibliotecas, dependências e componentes de síntese de voz.

## Bibliotecas Principais

### Síntese de Voz
- **Flite**: Motor de síntese para inglês
  - Biblioteca: `libflite`
  - Voz padrão: `cmu_us_slt` (feminina)
  - Uso: Inglês e textos sem acentos

- **eSpeak-ng**: Motor de síntese para português
  - Biblioteca: `libespeak-ng`
  - Voz padrão: `pt-br`
  - Configurações:
    - Velocidade: 150 (mais lenta)
    - Volume: 80%
    - Tom: 60 (ligeiramente agudo)
  - Uso: Português e textos com acentos

### Processamento de Áudio
- **OpenCV**: Processamento de imagem e áudio
  - Versão: 4.6.0+
  - Componentes: core, imgproc, imgcodecs, highgui, videoio, face

### Modelos de IA
- **Llama.cpp**: Inferência com modelos de linguagem
  - Modelos suportados:
    - Llama-3.2-1B-Instruct-Q4_K_M.gguf
    - Phi-3.5-mini-instruct-Q4_K_M.gguf
    - qwen2.5-0.5b-instruct-q5_k_m.gguf

## Arquitetura do Sistema

### Componentes de Voz
```
SintetizadorVoz
├── MotorVoz (enum)
│   ├── FLITE
│   └── ESPEAK_NG
├── Métodos Públicos
│   ├── inicializar()
│   ├── falar(texto)
│   ├── falarIngles(texto)
│   ├── falarPortugues(texto)
│   └── setMotorVoz(motor)
└── Estado Interno
    ├── voz* (ponteiro para Flite)
    ├── inicializado (bool)
    └── motorAtual (MotorVoz)
```

### Fluxo de Trabalho
1. **Inicialização**: Selecionar motor e inicializar biblioteca
2. **Processamento**: Remover acentos (Flite) ou configurar parâmetros (eSpeak-ng)
3. **Síntese**: Gerar áudio a partir do texto
4. **Saída**: Reproduzir áudio pelo sistema

## Configuração de Desenvolvimento

### Dependências Obrigatórias
```bash
# Ubuntu/Debian
sudo apt-get install libflite1 libflite-dev espeak-ng libespeak-ng-dev

# Bibliotecas de desenvolvimento
sudo apt-get install libopencv-dev pkg-config
```

### Compilação
```cmake
# Encontrar dependências
find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)

# Linkar bibliotecas
target_link_libraries(${PROJECT_NAME}
    ${FLITE_LIB}
    ${FLITE_KAL_LIB}
    ${FLITE_M_LIB}
    ${OpenCV_LIBS}
    espeak-ng
)
```

## Gerenciamento de Memória

### Alocação
- **Flite**: Gerenciado internamente pela biblioteca
- **eSpeak-ng**: Inicialização única, reutilização de instância
- **OpenCV**: RAII para objetos Mat e VideoCapture

### Liberação
```cpp
// Destrutor automático
~SintetizadorVoz() {
#if HAS_ESPEAK
    if (eSpeakInicializado) {
        espeak_Terminate();  // Libera recursos do eSpeak
    }
#endif
    // Flite libera automaticamente
}
```

## Tratamento de Erros

### Estratégias
1. **Validação Prévia**: Verificar inicialização antes de usar
2. **Fallback**: Mudar para motor alternativo se falhar
3. **Recuperação**: Tentar reinicialização em caso de erro
4. **Logging**: Registrar erros para depuração

### Códigos de Erro
```cpp
// Falha na inicialização
if (!inicializar()) {
    logger.registrar("Falha na inicialização do motor de voz");
    return false;
}

// Tratamento de exceções
try {
    voz.falar(texto);
} catch (const std::exception& e) {
    logger.registrar("Erro na síntese: " + std::string(e.what()));
}
```

## Otimização de Performance

### Estratégias
1. **Cache de Voz**: Manter instância inicializada
2. **Processamento Lote**: Múltiplos textos em sequência
3. **Thread Safety**: Usar mutex para acesso concorrente
4. **Memória Pool**: Reutilizar buffers de áudio

### Métricas
- **Latência**: < 100ms para síntese curta
- **Throughput**: 10+ textos por segundo
- **Memória**: < 50MB para instância única

## Testes e Validação

### Suite de Testes
- **Unitários**: 11 testes para métodos individuais
- **Integração**: 5 testes para fluxos completos
- **Erro**: 5 testes para casos excepcionais
- **Performance**: Testes de carga e estresse

### Execução
```bash
# Compilar testes
make test_sintetizador_unificado

# Executar suite completa
./tests/test_sintetizador_unificado

# Testes individuais
./tests/test_voice_simple
```

## Implantação

### Requisitos de Sistema
- **SO**: Linux (Ubuntu 20.04+)
- **Memória**: Mínimo 2GB RAM
- **Processador**: x86_64 com suporte a SSE4.1
- **Áudio**: ALSA ou PulseAudio

### Configuração de Produção
```bash
# Variáveis de ambiente
export FLITE_VOICE=cmu_us_slt
export ESPEAK_VOICE=pt-br
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# Verificação de dependências
ldd ./bin/agenteIA | grep -E "(flite|espeak|opencv)"
```

## Monitoramento

### Métricas de Saúde
- **Uso de CPU**: < 10% em operação normal
- **Memória**: < 100MB para processo completo
- **Latência**: < 200ms para resposta de voz
- **Taxa de Erro**: < 1% para solicitações normais

### Logs
```
[INFO] SintetizadorVoz: Motor FLITE inicializado
[INFO] SintetizadorVoz: Texto processado: "Hello world"
[WARN] SintetizadorVoz: eSpeak-ng não disponível, usando fallback
[ERROR] SintetizadorVoz: Falha na síntese: texto vazio
```

## Manutenção

### Atualizações
1. **Bibliotecas**: Manter versões estáveis
2. **Modelos**: Atualizar modelos de linguagem
3. **Security**: Aplicar patches de segurança
4. **Performance**: Otimizar baseado em métricas

### Backup
- **Configurações**: Exportar YAML/JSON
- **Modelos**: Backup em local seguro
- **Logs**: Rotacionar diariamente, manter 30 dias

## Troubleshooting

### Problemas Comuns

#### eSpeak-ng não inicializa
```bash
# Verificar instalação
dpkg -l | grep espeak

# Verificar bibliotecas
find /usr -name "*espeak*" 2>/dev/null

# Reinstalar se necessário
sudo apt-get install --reinstall espeak-ng libespeak-ng-dev
```

#### Flite não produz áudio
```bash
# Verificar sistema de áudio
aplay -l

# Testar reprodução
echo "test" | flite

# Verificar permissões
ls -la /dev/snd/
```

```bash
# Monitorar processo
top -p $(pgrep agenteIA)

# Verificar vazamentos
valgrind --leak-check=full ./bin/agenteIA
```

#### Monitoramento com htop

O htop é um monitor de processos interativo para o terminal que melhora a visualização do comando clássico top. Ele funciona como um "Gerenciador de Tarefas" (estilo Windows), mas muito mais detalhado e focado em performance.

No Debian, ele organiza as informações em três seções principais:

**1. O Cabeçalho (Status do Hardware)**
No topo, você vê barras coloridas que representam o uso em tempo real:

- **CPU**: Cada núcleo do seu processador tem uma barra dedicada.
- **Azul**: Processos de baixa prioridade (nice).
- **Verde**: Processos normais do usuário.
- **Vermelho**: Processos do sistema (Kernel).

**Memória (RAM):**
- **Verde**: Memória usada por processos.
- **Azul**: Buffers.
- **Amarelo**: Cache (memória que o Debian usa para acelerar o disco, mas que está "disponível" se um app precisar).
- **Swap**: Mostra quanto do disco está sendo usado como RAM de emergência.

**2. A Tabela de Processos**
Abaixo do cabeçalho, cada linha é um programa rodando. As colunas mais importantes são:

- **PID**: O número de identidade do processo (útil para encerrá-lo).
- **PRI e NI**: A prioridade do processo no sistema.
- **VIRT/RES**: A memória virtual total e a memória física real (RAM) que o app está usando agora.
- **CPU% e MEM%**: A porcentagem de recursos que aquele processo está consumindo.
- **Command**: O caminho do executável que iniciou o processo.

**3. O Rodapé (Comandos de Atalho)**
O htop é interativo. Você pode usar o teclado para gerenciar o sistema:

- **F3 (Search)**: Digite o nome de um processo para encontrá-lo.
- **F4 (Filter)**: Esconde tudo o que não tiver o nome que você digitou (ótimo para isolar processos de IA ou Python).
- **F5 (Tree)**: Mostra a hierarquia (quem abriu qual processo).
- **F6 (Sort by)**: Muda a ordenação (ex: ordenar por quem consome mais RAM).
- **F9 (Kill)**: Abre um menu para encerrar um processo travado (geralmente usa-se o sinal SIGTERM ou SIGKILL).
- **F10 (Quit)**: Sai do programa.

```bash
# Instalar htop
sudo apt-get install htop

# Monitorar processos do AgenteIA
htop -p $(pgrep agenteIA)

# Monitorar todos os processos de IA
htop --filter=python

# Verificar consumo específico
htop --sort-key=PERCENT_MEM
```

### Filtrando Scripts de IA no htop

Para filtrar apenas os seus scripts (como os de IA em Python) dentro do htop no Debian, você tem três caminhos principais:

#### 1. Filtro por Nome (F4) - O mais rápido
Se o seu script está rodando com um interpretador específico (como python3), faça o seguinte:
- Abra o htop
- Pressione F4
- Digite `python` (ou o nome do seu arquivo .py)
- O htop esconderá todos os outros processos do sistema (kernel, serviços, etc) e mostrará apenas as linhas que contêm essa palavra

#### 2. Visão de Árvore (F5) - Para ver Filhos e Zumbis
Como projetos de IA costumam abrir vários processos (usando multiprocessing ou dataloaders), a visão de árvore é essencial:
- Pressione F5
- Isso agrupa os processos filhos abaixo do processo pai
- Se houver processos zumbis ou processos travados consumindo RAM, você verá exatamente de qual "galho" do seu script eles vieram

#### 3. Filtro por Usuário (u)
Se você quer ver tudo o que o seu usuário está rodando, ignorando os processos do root (sistema):
- Pressione a tecla `u` (minúscula)
- Use as setas para selecionar o seu nome de usuário na lista que aparecer à esquerda
- Pressione Enter

#### Dica Pro: Mostrar o caminho completo do Script
Às vezes, o htop mostra apenas `python3` e você não sabe qual script é qual.
- Pressione `p` para alternar entre mostrar apenas o nome do executável ou o caminho completo (ex: `/home/user/projeto_ia/treino.py`)

```bash
# Monitorar processo
top -p $(pgrep agenteIA)

# Verificar vazamentos
valgrind --leak-check=full ./bin/agenteIA
```

### Soluções Alternativas
- **Motor Fallback**: Mudar para Flite se eSpeak falhar
- **Modo Seguro**: Desativar recursos avançados
- **Recursos Mínimos**: Operar com configuração básica

## Referências

### Documentação
- [Flite Documentation](http://www.festvox.org/flite/)
- [eSpeak-ng Documentation](https://github.com/espeak-ng/espeak-ng)
- [OpenCV Documentation](https://docs.opencv.org/)

### Comunidade
- [Fórum Flite](https://groups.google.com/g/flite-discuss)
- [GitHub eSpeak-ng](https://github.com/espeak-ng/espeak-ng/issues)
- [OpenCV Forum](https://forum.opencv.org/)

---

*Última atualização: 11/04/2026*
*Versão: 1.0.2*
