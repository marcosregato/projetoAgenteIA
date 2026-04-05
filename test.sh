#!/bin/bash

# Script de atalho para executar testes do projetoAgenteIA
# Uso: ./test.sh [opção]

set -e

# Cores para saída
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Função de ajuda
show_help() {
    echo -e "${BLUE}🧪 Testes - projetoAgenteIA${NC}"
    echo -e "${YELLOW}Uso: $0 [opção]${NC}"
    echo ""
    echo "Opções disponíveis:"
    echo "  ${GREEN}menu${NC}     - Abre o menu interativo de testes"
    echo "  ${GREEN}image${NC}    - Executa testes de processamento de imagem"
    echo "  ${GREEN}voice${NC}     - Executa testes de voz"
    echo "  ${GREEN}unit${NC}      - Executa testes unitários"
    echo "  ${GREEN}all${NC}       - Executa todos os testes"
    echo "  ${GREEN}build${NC}     - Compila o projeto e todos os testes"
    echo "  ${GREEN}clean${NC}     - Limpa o diretório de build"
    echo "  ${GREEN}help${NC}     - Mostra esta ajuda"
    echo ""
    echo -e "${YELLOW}Exemplos:${NC}"
    echo "  $0 menu      # Abre o menu interativo"
    echo "  $0 image     # Testa processamento de imagem"
    echo "  $0 voice     # Testa síntese de voz"
    echo "  $0 build     # Compila tudo"
}

# Verificar se estamos no diretório correto
check_directory() {
    if [[ ! -f "CMakeLists.txt" ]]; then
        echo -e "${RED}❌ Erro: Execute este script na raiz do projeto!${NC}"
        exit 1
    fi
}

# Compilar projeto
build_project() {
    echo -e "${BLUE}🔨 Compilando projeto...${NC}"
    mkdir -p build
    cd build
    cmake ..
    make -j$(nproc)
    echo -e "${GREEN}✅ Compilação concluída!${NC}"
}

# Limpar build
clean_build() {
    echo -e "${YELLOW}🧹 Limpando diretório de build...${NC}"
    rm -rf build
    echo -e "${GREEN}✅ Build limpo!${NC}"
}

# Executar menu de testes
run_menu() {
    if [[ ! -f "build/tests/run_tests" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes primeiro...${NC}"
        build_project
    fi
    echo -e "${BLUE}🎥 Abrindo menu de testes...${NC}"
    cd build
    ./tests/run_tests
}

# Testar processamento de imagem
test_image() {
    if [[ ! -f "build/tests/test_image_processor" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes de imagem primeiro...${NC}"
        build_project
    fi
    echo -e "${BLUE}🎥 Executando testes de processamento de imagem...${NC}"
    cd build
    ./tests/test_image_processor
}

# Testar voz
test_voice() {
    if [[ ! -f "build/tests/test_voice_simple" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes de voz primeiro...${NC}"
        build_project
    fi
    echo -e "${BLUE}🔊 Executando testes de voz...${NC}"
    cd build
    ./tests/test_voice_simple
}

# Testar unitários
test_unit() {
    if [[ ! -f "build/tests/unit_tests" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes unitários primeiro...${NC}"
        build_project
    fi
    echo -e "${BLUE}📋 Executando testes unitários...${NC}"
    cd build
    ./tests/unit_tests
}

# Executar todos os testes
test_all() {
    if [[ ! -f "build/tests/run_tests" ]]; then
        echo -e "${YELLOW}⚠️  Compilando todos os testes primeiro...${NC}"
        build_project
    fi
    echo -e "${BLUE}🎯 Executando todos os testes...${NC}"
    cd build
    ./tests/test_image_processor
    ./tests/test_voice_simple
    ./tests/unit_tests
}

# Verificar parâmetros
check_directory

case "${1:-help}" in
    menu)
        run_menu
        ;;
    image)
        test_image
        ;;
    voice)
        test_voice
        ;;
    unit)
        test_unit
        ;;
    all)
        test_all
        ;;
    build)
        build_project
        ;;
    clean)
        clean_build
        ;;
    help|--help|-h)
        show_help
        ;;
    *)
        echo -e "${RED}❌ Opção desconhecida: $1${NC}"
        echo ""
        show_help
        exit 1
        ;;
esac
