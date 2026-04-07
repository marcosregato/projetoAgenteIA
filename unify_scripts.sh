#!/bin/bash

# Script para unificar e organizar os scripts do projeto
# Move scripts antigos para backup e mantém apenas o script unificado

set -e

# Cores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🔧 Unificando scripts do projeto...${NC}"
echo "=================================="

# Criar diretório de backup
BACKUP_DIR="scripts_backup_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$BACKUP_DIR"

echo -e "${YELLOW}📁 Criando backup em: $BACKUP_DIR${NC}"

# Lista de scripts para mover
SCRIPTS_TO_MOVE=(
    "test.sh"
    "download-models.sh"
    "check_gitignore.sh"
    "comandos_executados.sh"
)

# Mover scripts para backup
for script in "${SCRIPTS_TO_MOVE[@]}"; do
    if [[ -f "$script" ]]; then
        echo -e "${BLUE}📦 Movendo: $script -> $BACKUP_DIR/${NC}"
        mv "$script" "$BACKUP_DIR/"
    else
        echo -e "${YELLOW}⚠️  Script não encontrado: $script${NC}"
    fi
done

# Verificar se o script unificado existe
if [[ ! -f "scripts.sh" ]]; then
    echo -e "${RED}❌ Erro: scripts.sh não encontrado!${NC}"
    exit 1
fi

echo -e "${GREEN}✅ Scripts movidos para backup${NC}"
echo ""

# Mostrar conteúdo do backup
echo -e "${BLUE}📋 Conteúdo do backup:${NC}"
ls -la "$BACKUP_DIR/"

echo ""
echo -e "${GREEN}🎉 Unificação concluída!${NC}"
echo -e "${BLUE}📝 Use: ./scripts.sh help para ver todos os comandos${NC}"
echo -e "${YELLOW}⚠️  Os scripts antigos estão em: $BACKUP_DIR${NC}"
echo -e "${YELLOW}⚠️  Remova o backup quando confirmar que tudo funciona${NC}"
