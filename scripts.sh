#!/bin/bash

# Script unificado do projetoAgenteIA
# Combina funcionalidades de: test.sh, download-models.sh, check_gitignore.sh
# Uso: ./scripts.sh [comando] [opções]

set -e

# Cores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Função de ajuda principal
show_help() {
    echo -e "${CYAN}🔧 Script Unificado - projetoAgenteIA${NC}"
    echo -e "${YELLOW}Uso: $0 [comando] [opções]${NC}"
    echo ""
    echo -e "${BLUE}Comandos disponíveis:${NC}"
    echo ""
    echo -e "${GREEN}  🧪 Testes:${NC}"
    echo "    test menu        - Menu interativo de testes"
    echo "    test image       - Testar processamento de imagem"
    echo "    test voice       - Testar síntese de voz"
    echo "    test unit        - Testar unitários"
    echo "    test all         - Executar todos os testes"
    echo ""
    echo -e "${GREEN}  📥 Modelos:${NC}"
    echo "    models base.en   - Baixar modelo base do Whisper"
    echo "    models tiny.en   - Baixar modelo tiny do Whisper"
    echo "    models small.en  - Baixar modelo small do Whisper"
    echo "    models medium.en  - Baixar modelo medium do Whisper"
    echo "    models large     - Baixar modelo large do Whisper"
    echo "    models all       - Baixar todos os modelos Whisper"
    echo "    models help      - Ajuda dos modelos"
    echo ""
    echo -e "${GREEN}  🔧 Build:${NC}"
    echo "    build            - Compilar projeto e testes"
    echo "    build clean       - Limpar e recompilar"
    echo "    build models     - Compilar e baixar modelos"
    echo ""
    echo -e "${GREEN}  📁 Git:${NC}"
    echo "    git check        - Verificar .gitignore"
    echo "    git status       - Status completo do projeto"
    echo "    git clean        - Limpar arquivos não rastreados"
    echo ""
    echo -e "${GREEN}  🛠️ Utilitários:${NC}"
    echo "    utils setup       - Configurar dependências"
    echo "    utils flite       - Instalar Flite"
    echo "    utils opencv      - Verificar OpenCV"
    echo "    utils clean       - Limpar projeto"
    echo ""
    echo -e "${GREEN}  ℹ️  Info:${NC}"
    echo "    info             - Informações do projeto"
    echo "    help             - Esta ajuda"
    echo ""
    echo -e "${YELLOW}Exemplos:${NC}"
    echo "  $0 test menu     # Abrir menu de testes"
    echo "  $0 models base.en # Baixar modelo Whisper"
    echo "  $0 build          # Compilar projeto"
    echo "  $0 git check      # Verificar .gitignore"
}

# Lista de modelos Whisper
declare -A WHISPER_MODELS=(
    ["base.en"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-base.en.bin"
    ["tiny.en"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-tiny.en.bin"
    ["small.en"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-small.en.bin"
    ["medium.en"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-medium.en.bin"
    ["large"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-large-v3.bin"
)

# Verificar dependências
check_dependencies() {
    if ! command -v wget &> /dev/null && ! command -v curl &> /dev/null; then
        echo -e "${RED}❌ Erro: wget ou curl é necessário para download${NC}"
        exit 1
    fi
    
    if ! command -v cmake &> /dev/null; then
        echo -e "${RED}❌ Erro: CMake não encontrado${NC}"
        exit 1
    fi
}

# Funções de Testes
run_tests() {
    echo -e "${BLUE}🧪 Executando testes...${NC}"
    if [[ ! -f "build/tests/run_tests" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes primeiro...${NC}"
        build_project
    fi
    cd build
    ./tests/run_tests
}

test_image() {
    echo -e "${BLUE}🎥 Testando processamento de imagem...${NC}"
    if [[ ! -f "build/tests/test_image_processor" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes de imagem primeiro...${NC}"
        build_project
    fi
    cd build
    ./tests/test_image_processor
}

test_voice() {
    echo -e "${BLUE}🔊 Testando síntese de voz...${NC}"
    if [[ ! -f "build/tests/test_voice_simple" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes de voz primeiro...${NC}"
        build_project
    fi
    cd build
    ./tests/test_voice_simple
}

test_unit() {
    echo -e "${BLUE}📋 Testando unitários...${NC}"
    if [[ ! -f "build/tests/unit_tests" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes unitários primeiro...${NC}"
        build_project
    fi
    cd build
    ./tests/unit_tests
}

# Funções de Modelos
download_model() {
    local model=$1
    local url=${WHISPER_MODELS[$model]}
    
    if [[ -z "$url" ]]; then
        echo -e "${RED}❌ Modelo '$model' não encontrado!${NC}"
        echo -e "${YELLOW}Modelos disponíveis:${NC}"
        for m in "${!WHISPER_MODELS[@]}"; do
            echo -e "  ${GREEN}$m${NC}"
        done
        exit 1
    fi
    
    local filename="ggml-$model.bin"
    
    if [[ -f "$filename" ]]; then
        echo -e "${YELLOW}⚠️  Modelo '$filename' já existe. Pulando...${NC}"
        return 0
    fi
    
    echo -e "${BLUE}📥 Baixando modelo: $model${NC}"
    echo -e "${BLUE}🔗 URL: $url${NC}"
    echo -e "${BLUE}📁 Arquivo: $filename${NC}"
    echo ""
    
    if command -v wget &> /dev/null; then
        wget --progress=bar:force --show-progress -O "$filename" "$url"
    elif command -v curl &> /dev/null; then
        curl -L --progress-bar -o "$filename" "$url"
    else
        echo -e "${RED}❌ Erro: wget ou curl não encontrado${NC}"
        exit 1
    fi
    
    if [[ $? -eq 0 ]]; then
        echo -e "${GREEN}✅ Modelo '$filename' baixado com sucesso!${NC}"
        local size=$(du -h "$filename" | cut -f1)
        echo -e "${BLUE}📊 Tamanho: $size${NC}"
    else
        echo -e "${RED}❌ Falha ao baixar modelo '$model'${NC}"
        exit 1
    fi
}

download_all_models() {
    echo -e "${BLUE}📥 Baixando todos os modelos...${NC}"
    echo -e "${YELLOW}⚠️  Isso pode levar muito tempo e usar muito espaço!${NC}"
    echo ""
    
    read -p "Deseja continuar? (s/N): " -n 1 -r
    echo
    
    if [[ $REPLY =~ ^[Ss]$ ]]; then
        for model in "${!WHISPER_MODELS[@]}"; do
            download_model "$model"
            echo ""
        done
        echo -e "${GREEN}✅ Todos os modelos baixados!${NC}"
    else
        echo -e "${YELLOW}❌ Download cancelado.${NC}"
    fi
}

# Funções de Build
build_project() {
    echo -e "${BLUE}🔨 Compilando projeto...${NC}"
    mkdir -p build
    cd build
    cmake ..
    make -j$(nproc)
    echo -e "${GREEN}✅ Compilação concluída!${NC}"
}

build_clean() {
    echo -e "${YELLOW}🧹 Limpando e recompilando...${NC}"
    rm -rf build
    build_project
}

build_with_models() {
    echo -e "${BLUE}🔨 Compilando e baixando modelos...${NC}"
    build_project
    echo -e "${BLUE}📥 Baixando modelos automáticos...${NC}"
    cd build
    cmake --build . --target all
}

# Funções de Git
check_gitignore() {
    echo -e "${BLUE}🔍 Verificando .gitignore...${NC}"
    
    if [[ ! -f ".gitignore" ]]; then
        echo -e "${RED}❌ .gitignore não encontrado!${NC}"
        return 1
    fi
    
    echo -e "${GREEN}✅ .gitignore encontrado${NC}"
    
    if [[ -d "build" ]]; then
        echo -e "${GREEN}✅ build/ existe e deve ser ignorado${NC}"
    fi
    
    if [[ -f "build/tests/run_tests" ]]; then
        echo -e "${GREEN}✅ build/tests/run_tests existe e deve ser ignorado${NC}"
    fi
    
    if [[ -f "ggml-base.en.bin" ]]; then
        echo -e "${GREEN}✅ ggml-base.en.bin existe e deve ser ignorado${NC}"
    fi
    
    echo -e "${BLUE}📊 Status do Git:${NC}"
    if git rev-parse --git-dir > /dev/null 2>&1; then
        untracked=$(git ls-files --others --exclude-standard)
        if [[ -n "$untracked" ]]; then
            echo -e "${YELLOW}⚠️  Arquivos não rastreados:${NC}"
            echo "$untracked"
        else
            echo -e "${GREEN}✅ Nenhum arquivo não rastreado${NC}"
        fi
    else
        echo -e "${RED}❌ Repositório Git não inicializado${NC}"
    fi
}

git_status() {
    echo -e "${BLUE}📊 Status completo do projeto...${NC}"
    git status --porcelain
}

git_clean() {
    echo -e "${YELLOW}🧹 Limpando arquivos não rastreados...${NC}"
    git clean -fd
    echo -e "${GREEN}✅ Limpeza concluída!${NC}"
}

# Funções de Utilitários
setup_dependencies() {
    echo -e "${BLUE}🛠️ Configurando dependências...${NC}"
    
    echo -e "${YELLOW}📦 Atualizando pacotes...${NC}"
    sudo apt-get update
    
    echo -e "${YELLOW}🔊 Instalando Flite...${NC}"
    sudo apt-get install -y flite1-dev
    
    echo -e "${YELLOW}👁️  Instalando OpenCV...${NC}"
    sudo apt-get install -y libopencv-dev
    
    echo -e "${YELLOW}🔊 Instalando eSpeak...${NC}"
    sudo apt-get install -y libespeak-ng-dev espeak-ng libespeak-ng1
    
    echo -e "${GREEN}✅ Dependências configuradas!${NC}"
}

install_flite() {
    echo -e "${BLUE}🔊 Instalando Flite...${NC}"
    sudo apt-get update
    sudo apt-get install -y flite1-dev
    echo -e "${GREEN}✅ Flite instalado!${NC}"
}

check_opencv() {
    echo -e "${BLUE}👁️  Verificando OpenCV...${NC}"
    
    if pkg-config --exists opencv4; then
        version=$(pkg-config --modversion opencv4)
        echo -e "${GREEN}✅ OpenCV encontrado: $version${NC}"
    elif pkg-config --exists opencv; then
        version=$(pkg-config --modversion opencv)
        echo -e "${GREEN}✅ OpenCV encontrado: $version${NC}"
    else
        echo -e "${RED}❌ OpenCV não encontrado${NC}"
        echo -e "${YELLOW}Instale com: sudo apt-get install libopencv-dev${NC}"
    fi
}

clean_project() {
    echo -e "${YELLOW}🧹 Limpando projeto...${NC}"
    rm -rf build
    rm -f ggml-*.bin
    rm -f *.log
    rm -f *.tmp
    echo -e "${GREEN}✅ Projeto limpo!${NC}"
}

# Informações do projeto
show_info() {
    echo -e "${CYAN}📋 Informações do projetoAgenteIA${NC}"
    echo "=================================="
    echo -e "${BLUE}📁 Estrutura:${NC}"
    echo "  • src/          - Código-fonte"
    echo "  • include/      - Headers"
    echo "  • tests/        - Testes"
    echo "  • docs/         - Documentação"
    echo "  • build/        - Build (ignorado)"
    echo ""
    echo -e "${BLUE}🔧 Tecnologias:${NC}"
    echo "  • C++17        - Linguagem"
    echo "  • CMake         - Build system"
    echo "  • OpenCV        - Processamento de imagem"
    echo "  • Flite         - Síntese de voz"
    echo "  • eSpeak-ng     - Síntese PT-BR"
    echo "  • llama.cpp     - LLM inference"
    echo "  • whisper.cpp   - Reconhecimento de fala"
    echo "  • Catch2        - Testes unitários"
    echo ""
    echo -e "${BLUE}📦 Dependências principais:${NC}"
    echo "  • sudo apt-get install libflite-dev"
    echo "  • sudo apt-get install libopencv-dev"
    echo "  • sudo apt-get install libespeak-ng-dev"
    echo ""
    echo -e "${BLUE}🧪 Scripts disponíveis:${NC}"
    echo "  • ./scripts.sh    - Script unificado (este)"
    echo "  • ./test.sh       - Testes individuais"
    echo "  • ./download-models.sh - Download de modelos"
    echo "  • ./check_gitignore.sh - Verificação do .gitignore"
}

# Processar argumentos principais
case "${1:-help}" in
    "test")
        case "${2:-menu}" in
            "menu") run_tests ;;
            "image") test_image ;;
            "voice") test_voice ;;
            "unit") test_unit ;;
            "all") 
                test_image
                test_voice
                test_unit
                ;;
            *) echo -e "${RED}❌ Opção de teste inválida: $2${NC}" && exit 1 ;;
        esac
        ;;
    "models")
        case "${2:-help}" in
            "base.en"|"tiny.en"|"small.en"|"medium.en"|"large")
                download_model "$2"
                ;;
            "all")
                download_all_models
                ;;
            "help")
                echo -e "${BLUE}📥 Modelos Whisper disponíveis:${NC}"
                for model in "${!WHISPER_MODELS[@]}"; do
                    echo -e "  ${GREEN}$model${NC}"
                done
                echo ""
                echo -e "${YELLOW}Tamanhos:${NC}"
                echo "  • base.en  - 141MB (recomendado)"
                echo "  • tiny.en  - 39MB (mais rápido)"
                echo "  • small.en - 466MB (bom equilíbrio)"
                echo "  • medium.en- 1.5GB (melhor precisão)"
                echo "  • large    - 2.9GB (máxima precisão)"
                ;;
            *) echo -e "${RED}❌ Modelo inválido: $2${NC}" && exit 1 ;;
        esac
        ;;
    "build")
        case "${2:-normal}" in
            "clean") build_clean ;;
            "models") build_with_models ;;
            *) build_project ;;
        esac
        ;;
    "git")
        case "${2:-check}" in
            "check") check_gitignore ;;
            "status") git_status ;;
            "clean") git_clean ;;
            *) echo -e "${RED}❌ Comando git inválido: $2${NC}" && exit 1 ;;
        esac
        ;;
    "utils")
        case "${2:-help}" in
            "setup") setup_dependencies ;;
            "flite") install_flite ;;
            "opencv") check_opencv ;;
            "clean") clean_project ;;
            *) echo -e "${RED}❌ Utilitário inválido: $2${NC}" && exit 1 ;;
        esac
        ;;
    "info")
        show_info
        ;;
    "help"|"--help"|"-h")
        show_help
        ;;
    *)
        echo -e "${RED}❌ Comando desconhecido: $1${NC}"
        echo ""
        show_help
        exit 1
        ;;
esac

echo ""
echo -e "${GREEN}✅ Operação concluída!${NC}"
