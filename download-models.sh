#!/bin/bash

# Script para download de modelos GGML e Whisper
# Uso: ./download-models.sh [modelo]

set -e

# Cores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Lista de modelos disponíveis
declare -A MODELS=(
    ["base.en"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-base.en.bin"
    ["tiny.en"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-tiny.en.bin"
    ["small.en"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-small.en.bin"
    ["medium.en"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-medium.en.bin"
    ["large"]="https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-large-v3.bin"
)

# Função de ajuda
show_help() {
    echo -e "${BLUE}📥 Download de Modelos GGML/Whisper${NC}"
    echo -e "${YELLOW}Uso: $0 [modelo]${NC}"
    echo ""
    echo "Modelos disponíveis:"
    for model in "${!MODELS[@]}"; do
        echo -e "  ${GREEN}$model${NC}"
    done
    echo ""
    echo -e "${YELLOW}Exemplos:${NC}"
    echo "  $0 base.en    # Baixa modelo base em inglês"
    echo "  $0 tiny.en    # Baixa modelo tiny em inglês"
    echo "  $0 all        # Baixa todos os modelos"
    echo ""
    echo -e "${YELLOW}Observações:${NC}"
    echo "  • Os modelos serão baixados no diretório atual"
    echo "  • Modelos maiores requerem mais RAM e CPU"
    echo "  • base.en é recomendado para uso geral"
}

# Verificar argumentos
if [[ $# -eq 0 ]]; then
    show_help
    exit 1
fi

# Verificar dependências
check_dependencies() {
    if ! command -v wget &> /dev/null && ! command -v curl &> /dev/null; then
        echo -e "${RED}❌ Erro: wget ou curl é necessário para download${NC}"
        exit 1
    fi
}

# Função de download
download_model() {
    local model=$1
    local url=${MODELS[$model]}
    
    if [[ -z "$url" ]]; then
        echo -e "${RED}❌ Modelo '$model' não encontrado!${NC}"
        echo -e "${YELLOW}Modelos disponíveis:${NC}"
        for m in "${!MODELS[@]}"; do
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
    
    # Tentar wget primeiro, depois curl
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
        
        # Mostrar tamanho do arquivo
        local size=$(du -h "$filename" | cut -f1)
        echo -e "${BLUE}📊 Tamanho: $size${NC}"
    else
        echo -e "${RED}❌ Falha ao baixar modelo '$model'${NC}"
        exit 1
    fi
}

# Baixar todos os modelos
download_all() {
    echo -e "${BLUE}📥 Baixando todos os modelos...${NC}"
    echo -e "${YELLOW}⚠️  Isso pode levar muito tempo e usar muito espaço!${NC}"
    echo ""
    
    read -p "Deseja continuar? (s/N): " -n 1 -r
    echo
    
    if [[ $REPLY =~ ^[Ss]$ ]]; then
        for model in "${!MODELS[@]}"; do
            download_model "$model"
            echo ""
        done
        echo -e "${GREEN}✅ Todos os modelos baixados!${NC}"
    else
        echo -e "${YELLOW}❌ Download cancelado.${NC}"
    fi
}

# Verificar dependências
check_dependencies

# Processar argumentos
case "$1" in
    "all")
        download_all
        ;;
    "help"|"--help"|"-h")
        show_help
        ;;
    *)
        download_model "$1"
        ;;
esac

echo ""
echo -e "${GREEN}🎉 Download concluído!${NC}"
echo -e "${BLUE}📁 Modelos disponíveis em: $(pwd)${NC}"
