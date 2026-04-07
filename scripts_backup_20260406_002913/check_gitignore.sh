#!/bin/bash

# Script para verificar se os arquivos estão sendo ignorados corretamente pelo .gitignore

set -e

# Cores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}🔍 Verificando .gitignore${NC}"
echo "=================================="

# Verificar se .gitignore existe
if [[ ! -f ".gitignore" ]]; then
    echo -e "${RED}❌ .gitignore não encontrado!${NC}"
    exit 1
fi

echo -e "${GREEN}✅ .gitignore encontrado${NC}"

# Verificar arquivos que deveriam ser ignorados
echo ""
echo -e "${YELLOW}📁 Verificando arquivos que devem ser ignorados:${NC}"

# Build artifacts
if [[ -d "build" ]]; then
    echo -e "${GREEN}✅ build/ existe e deve ser ignorado${NC}"
else
    echo -e "${YELLOW}⚠️  build/ não existe${NC}"
fi

# Test executables
if [[ -f "build/tests/run_tests" ]]; then
    echo -e "${GREEN}✅ build/tests/run_tests existe e deve ser ignorado${NC}"
else
    echo -e "${YELLOW}⚠️  build/tests/run_tests não existe${NC}"
fi

if [[ -f "build/tests/test_image_processor" ]]; then
    echo -e "${GREEN}✅ build/tests/test_image_processor existe e deve ser ignorado${NC}"
else
    echo -e "${YELLOW}⚠️  build/tests/test_image_processor não existe${NC}"
fi

if [[ -f "build/tests/test_voice_simple" ]]; then
    echo -e "${GREEN}✅ build/tests/test_voice_simple existe e deve ser ignorado${NC}"
else
    echo -e "${YELLOW}⚠️  build/tests/test_voice_simple não existe${NC}"
fi

# Verificar git status
echo ""
echo -e "${YELLOW}📊 Status do Git:${NC}"
if git rev-parse --git-dir > /dev/null 2>&1; then
    echo -e "${GREEN}✅ Repositório Git inicializado${NC}"
    
    # Verificar se há arquivos não rastreados que deveriam ser ignorados
    untracked=$(git ls-files --others --exclude-standard)
    if [[ -n "$untracked" ]]; then
        echo -e "${YELLOW}⚠️  Arquivos não rastreados:${NC}"
        echo "$untracked"
    else
        echo -e "${GREEN}✅ Nenhum arquivo não rastreado${NC}"
    fi
    
    # Verificar arquivos modificados
    modified=$(git status --porcelain | grep "^ M")
    if [[ -n "$modified" ]]; then
        echo -e "${YELLOW}⚠️  Arquivos modificados:${NC}"
        echo "$modified"
    else
        echo -e "${GREEN}✅ Nenhum arquivo modificado${NC}"
    fi
else
    echo -e "${RED}❌ Repositório Git não inicializado${NC}"
fi

# Verificar arquivos específicos no .gitignore
echo ""
echo -e "${YELLOW}📋 Padrões importantes no .gitignore:${NC}"

patterns=(
    "build/"
    "*.o"
    "*.exe"
    "*.log"
    "tests/test_*"
    "tests/run_tests"
    "*.gguf"
    ".vscode/"
    "*.swp"
)

for pattern in "${patterns[@]}"; do
    if grep -q "^$pattern" .gitignore; then
        echo -e "${GREEN}✅ $pattern${NC}"
    else
        echo -e "${RED}❌ $pattern (faltando)${NC}"
    fi
done

# Verificar se há arquivos grandes que deveriam ser ignorados
echo ""
echo -e "${YELLOW}🔍 Procurando arquivos grandes (>10MB):${NC}"
find . -type f -size +10M -not -path "./.git/*" -not -path "./build/*" 2>/dev/null | head -5 | while read file; do
    size=$(du -h "$file" | cut -f1)
    echo -e "${YELLOW}⚠️  $file ($size)${NC}"
done

echo ""
echo -e "${GREEN}✅ Verificação concluída!${NC}"
