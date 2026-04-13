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
    echo "  ${GREEN}voice-engines${NC} - Executa testes completos de motores de voz"
    echo "  ${GREEN}arquivo${NC}  - Executa testes de manipulação de arquivos"
    echo "  ${GREEN}audio${NC}     - Executa testes de gravação de áudio"
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
    echo "  $0 voice-engines # Testa motores completos de voz"
    echo "  $0 arquivo   # Testa manipulação de arquivos"
    echo "  $0 audio     # Testa gravação de áudio"
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

# Testar motores de voz completos
test_voice_engines() {
    if [[ ! -f "build/tests/test_voice_engines" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes completos de voz primeiro...${NC}"
        build_project
    fi
    echo -e "${BLUE}🎙️ Executando testes completos de motores de voz...${NC}"
    cd build
    ./tests/test_voice_engines
}

# Testar manipulação de arquivos
test_manipular_arquivo() {
    if [[ ! -f "build/tests/TestManipularArquivo" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes de manipulação de arquivos primeiro...${NC}"
        build_project
    fi
    echo -e "${BLUE}📁 Executando testes de manipulação de arquivos...${NC}"
    cd build
    ./tests/TestManipularArquivo
}

# Testar gravação de áudio
test_gravar_audio() {
    if [[ ! -f "build/tests/GravarAudio_Test" ]]; then
        echo -e "${YELLOW}⚠️  Compilando testes de gravação de áudio primeiro...${NC}"
        build_project
    fi
    echo -e "${BLUE}🎤 Executando testes de gravação de áudio...${NC}"
    cd build
    ./tests/GravarAudio_Test
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
    echo -e "${YELLOW}📋 Testes unitários...${NC}"
    ./tests/unit_tests
    echo -e "${YELLOW}📁 Testes de manipulação de arquivos...${NC}"
    ./tests/TestManipularArquivo
    echo -e "${YELLOW}🎤 Testes de gravação de áudio...${NC}"
    ./tests/GravarAudio_Test
    echo -e "${YELLOW}🔊 Testes de voz simples...${NC}"
    ./tests/test_voice_simple
    echo -e "${YELLOW}🎙️ Testes completos de motores de voz...${NC}"
    ./tests/test_voice_engines
    echo -e "${YELLOW}🎥 Testes de processamento de imagem...${NC}"
    ./tests/test_image_processor
    echo -e "${GREEN}🎉 Todos os testes concluídos!${NC}"
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
    voice-engines)
        test_voice_engines
        ;;
    arquivo)
        test_manipular_arquivo
        ;;
    audio)
        test_gravar_audio
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
