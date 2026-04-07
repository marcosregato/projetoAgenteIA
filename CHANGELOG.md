# Changelog

Todos os cambios notáveis neste projeto serão documentados neste arquivo.

O formato é baseado em [Keep a Changelog](https://keepachangelog.com/pt-BR/1.0.0/).

## [Unreleased]

## [1.0.0] - 2026-04-06

### Adicionado
- Sistema de versionamento semântico completo
- Script unificado `scripts.sh` para automação do projeto
- Suporte ao whisper.cpp para reconhecimento de fala
- Download automático de modelos durante o build
- Testes interativos para processamento de imagem
- Documentação completa em `conteudoParaEstudo.md`
- Script `version.sh` para gerenciamento de versões
- Arquivo `VERSION` para controle de versão
- Integração com OpenCV para detecção facial e pontos faciais
- Síntese de voz com Flite e eSpeak-ng
- Suporte a múltiplos modelos LLM (LLaMA, Phi, Qwen)

### Alterado
- Refatoração completa da estrutura do projeto
- Organização dos scripts em sistema unificado
- Melhoria na documentação e guias de estudo
- Otimização do processo de build e dependências

### Removido
- Scripts individuais obsoletos (movidos para backup)
- Arquivos de configuração duplicados
- Dependências desnecessárias

### Corrigido
- Problemas de linking com LogSistema
- Configuração do CMake para múltiplas plataformas
- Tratamento de erros em testes interativos
- Validação de dependências do sistema

### Segurança
- Validação de entradas do usuário
- Tratamento seguro de arquivos temporários
- Verificação de permissões de acesso à webcam
- Sanitização de caminhos de arquivo

---

## [0.1.0] - 2026-03-XX

### Adicionado
- Versão inicial do projeto
- Estrutura básica com CMake
- Integração com OpenCV básica
- Configuração inicial de dependências

### Alterado
- N/A

### Removido
- N/A

### Corrigido
- N/A

### Segurança
- N/A

---

## Formato da Versão

Este projeto segue [Semantic Versioning](https://semver.org/).

### Formato: MAJOR.MINOR.PATCH

- **MAJOR**: Mudanças incompatíveis com versões anteriores
- **MINOR**: Novas funcionalidades compatíveis com versões anteriores
- **PATCH**: Correções de bugs compatíveis com versões anteriores

### Pré-lançamentos

- **alpha**: Primeira versão de teste, instável
- **beta**: Versão mais estável que alpha, ainda em teste
- **rc** (Release Candidate): Versão final em teste antes do lançamento

Exemplo: `1.2.0-alpha.1`, `1.2.0-beta.1`, `1.2.0-rc.1`

---

## Como Usar

### Ver versão atual
```bash
./version.sh current
```

### Incrementar versão
```bash
./version.sh patch   # 1.0.0 → 1.0.1
./version.sh minor   # 1.0.1 → 1.1.0
./version.sh major   # 1.1.0 → 2.0.0
```

### Criar pré-lançamento
```bash
./version.sh pre alpha    # 1.1.0 → 1.1.0-alpha.1
./version.sh pre beta     # 1.1.0 → 1.1.0-beta.1
./version.sh pre rc       # 1.1.0 → 1.1.0-rc.1
```

### Criar lançamento
```bash
./version.sh release    # 1.1.0-rc.1 → 1.1.0
```

### Criar tag específica
```bash
./version.sh tag 2.0.0
```

---

## Notas de Desenvolvimento

- Use mensagens de commit claras e descritivas
- Atualize o changelog após cada alteração significativa
- Teste thoroughly antes de criar tags de lançamento
- Mantenha a compatibilidade backward quando possível

---

## Licença

Este changelog segue as mesmas diretrizes de licença do projeto principal.
