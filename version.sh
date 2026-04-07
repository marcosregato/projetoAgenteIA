#!/bin/bash

# Script de Versionamento Semântico
# Baseado em Semantic Versioning: https://semver.org/
# Uso: ./version.sh [comando] [opções]

set -e

# Cores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Arquivos de configuração
VERSION_FILE="VERSION"
CHANGELOG_FILE="CHANGELOG.md"
BUILD_INFO_FILE="include/build_info.hpp"

# Função de ajuda
show_help() {
    echo -e "${CYAN}🏷️  Versionamento Semântico - projetoAgenteIA${NC}"
    echo -e "${YELLOW}Uso: $0 [comando] [opções]${NC}"
    echo ""
    echo -e "${BLUE}Comandos disponíveis:${NC}"
    echo "  current           - Mostrar versão atual"
    echo "  patch            - Incrementar versão de patch (1.0.0 → 1.0.1)"
    echo "  minor            - Incrementar versão minor (1.0.1 → 1.1.0)"
    echo "  major            - Incrementar versão major (1.1.0 → 2.0.0)"
    echo "  pre [type]       - Criar versão de pré-lançamento"
    echo "  release          - Criar versão de lançamento"
    echo "  tag [version]    - Criar tag específica"
    echo "  init             - Inicializar versionamento"
    echo "  changelog        - Gerar changelog"
    echo "  help             - Esta ajuda"
    echo ""
    echo -e "${YELLOW}Exemplos:${NC}"
    echo "  $0 patch          # 1.0.0 → 1.0.1"
    echo "  $0 minor          # 1.0.1 → 1.1.0"
    echo "  $0 major          # 1.1.0 → 2.0.0"
    echo "  $0 pre alpha      # 1.1.0 → 1.1.0-alpha.1"
    echo "  $0 release        # 1.1.0-alpha.1 → 1.1.0"
}

# Ler versão atual
get_current_version() {
    if [[ -f "$VERSION_FILE" ]]; then
        cat "$VERSION_FILE"
    else
        echo "0.1.0"
    fi
}

# Validar formato semântico
validate_semver() {
    local version=$1
    if [[ ! $version =~ ^[0-9]+\.[0-9]+\.[0-9]+(-[a-zA-Z0-9]+)?$ ]]; then
        echo -e "${RED}❌ Versão inválida: $version${NC}"
        echo -e "${YELLOW}Formato esperado: MAJOR.MINOR.PATCH[-PRERELEASE]${NC}"
        exit 1
    fi
}

# Incrementar versão
increment_version() {
    local current_version=$(get_current_version)
    local type=$1
    
    # Extrair componentes
    local major=$(echo "$current_version" | cut -d. -f1)
    local minor=$(echo "$current_version" | cut -d. -f2)
    local patch=$(echo "$current_version" | cut -d. -f3 | cut -d- -f1)
    
    case "$type" in
        "patch")
            patch=$((patch + 1))
            ;;
        "minor")
            minor=$((minor + 1))
            patch=0
            ;;
        "major")
            major=$((major + 1))
            minor=0
            patch=0
            ;;
        *)
            echo -e "${RED}❌ Tipo de incremento inválido: $type${NC}"
            exit 1
            ;;
    esac
    
    echo "${major}.${minor}.${patch}"
}

# Criar versão de pré-lançamento
create_pre_release() {
    local current_version=$(get_current_version)
    local pre_type=$1
    local base_version=$(echo "$current_version" | cut -d- -f1)
    
    # Extrair componentes
    local major=$(echo "$base_version" | cut -d. -f1)
    local minor=$(echo "$base_version" | cut -d. -f2)
    local patch=$(echo "$base_version" | cut -d. -f3)
    
    # Verificar se já existe pré-lançamento
    if [[ "$current_version" == *"-"* ]]; then
        # Incrementar número do pré-lançamento
        local pre_number=$(echo "$current_version" | cut -d- -f2 | sed 's/[^0-9]//g')
        pre_number=$((pre_number + 1))
        echo "${major}.${minor}.${patch}-${pre_type}.${pre_number}"
    else
        # Primeiro pré-lançamento
        echo "${major}.${minor}.${patch}-${pre_type}.1"
    fi
}

# Criar versão de lançamento
create_release() {
    local current_version=$(get_current_version)
    
    # Remover sufixo de pré-lançamento se existir
    if [[ "$current_version" == *"-"* ]]; then
        echo "$current_version" | cut -d- -f1
    else
        echo "$current_version"
    fi
}

# Atualizar arquivo de versão
update_version_file() {
    local new_version=$1
    echo "$new_version" > "$VERSION_FILE"
    echo -e "${GREEN}✅ Versão atualizada para: $new_version${NC}"
}

# Criar tag no Git
create_git_tag() {
    local version=$1
    local message=$2
    
    if ! git rev-parse --git-dir > /dev/null 2>&1; then
        echo -e "${RED}❌ Repositório Git não inicializado${NC}"
        exit 1
    fi
    
    # Verificar se há alterações não commitadas
    if [[ -n $(git status --porcelain) ]]; then
        echo -e "${YELLOW}⚠️  Há alterações não commitadas${NC}"
        echo -e "${YELLOW}Deseja fazer commit antes de criar a tag? (s/N): ${NC}"
        read -r response
        if [[ ! $response =~ ^[Ss]$ ]]; then
            echo -e "${RED}❌ Operação cancelada${NC}"
            exit 1
        fi
    fi
    
    # Criar tag
    git tag -a "v$version" -m "$message"
    echo -e "${GREEN}✅ Tag v$version criada${NC}"
    
    # Perguntar se quer fazer push
    echo -e "${YELLOW}Deseja fazer push da tag para o repositório remoto? (s/N): ${NC}"
    read -r response
    if [[ $response =~ ^[Ss]$ ]]; then
        git push origin "v$version"
        echo -e "${GREEN}✅ Tag v$version enviada para o repositório${NC}"
    fi
}

# Gerar arquivo de build info
generate_build_info() {
    local version=$(get_current_version)
    local timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    local git_hash=$(git rev-parse --short HEAD 2>/dev/null || echo "unknown")
    local git_branch=$(git rev-parse --abbrev-ref HEAD 2>/dev/null || echo "unknown")
    
    # Criar diretório include se não existir
    mkdir -p "$(dirname "$BUILD_INFO_FILE")"
    
    cat > "$BUILD_INFO_FILE" << EOF
#ifndef BUILD_INFO_HPP
#define BUILD_INFO_HPP

namespace projetoAgenteIA {
    constexpr const char* VERSION = "$version";
    constexpr const char* BUILD_DATE = "$timestamp";
    constexpr const char* GIT_HASH = "$git_hash";
    constexpr const char* GIT_BRANCH = "$git_branch";
}

#endif // BUILD_INFO_HPP
EOF
    
    echo -e "${GREEN}✅ Arquivo de build info gerado: $BUILD_INFO_FILE${NC}"
}

# Gerar changelog
generate_changelog() {
    local version=$(get_current_version)
    
    if [[ ! -f "$CHANGELOG_FILE" ]]; then
        cat > "$CHANGELOG_FILE" << EOF
# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/pt-BR/1.0.0/).

## [Unreleased]

## [1.0.0] - $(date +"%Y-%m-%d")
### Adicionado
- Versão inicial do projeto
- Implementação básica de detecção facial
- Integração com OpenCV

### Alterado
- N/A

### Removido
- N/A

### Corrigido
- N/A

### Segurança
- N/A
EOF
        echo -e "${GREEN}✅ Changelog inicial criado: $CHANGELOG_FILE${NC}"
    else
        echo -e "${BLUE}📋 Changelog já existe: $CHANGELOG_FILE${NC}"
        echo "Edite o arquivo manualmente para adicionar novas alterações"
    fi
}

# Inicializar versionamento
init_versioning() {
    if [[ -f "$VERSION_FILE" ]]; then
        echo -e "${YELLOW}⚠️  Versionamento já inicializado${NC}"
        echo -e "${BLUE}Versão atual: $(get_current_version)${NC}"
    else
        echo "0.1.0" > "$VERSION_FILE"
        echo -e "${GREEN}✅ Versionamento inicializado: 0.1.0${NC}"
    fi
    
    generate_build_info
    generate_changelog
}

# Mostrar versão atual
show_current_version() {
    local version=$(get_current_version)
    echo -e "${CYAN}🏷️  Versão atual: $version${NC}"
    
    # Tentar mostrar informações do Git
    if git rev-parse --git-dir > /dev/null 2>&1; then
        local git_hash=$(git rev-parse --short HEAD 2>/dev/null || echo "unknown")
        local git_branch=$(git rev-parse --abbrev-ref HEAD 2>/dev/null || echo "unknown")
        echo -e "${BLUE}📦 Git: $git_branch@$git_hash${NC}"
    fi
    
    # Mostrar data da última modificação
    if [[ -f "$VERSION_FILE" ]]; then
        local mod_date=$(stat -c %y "$VERSION_FILE" 2>/dev/null || stat -f %Sm "$VERSION_FILE" 2>/dev/null)
        echo -e "${YELLOW}📅 Modificado: $mod_date${NC}"
    fi
}

# Processar comandos
case "${1:-help}" in
    "current")
        show_current_version
        ;;
    "patch")
        new_version=$(increment_version "patch")
        update_version_file "$new_version"
        create_git_tag "$new_version" "Bump versão para $new_version (patch)"
        generate_build_info
        ;;
    "minor")
        new_version=$(increment_version "minor")
        update_version_file "$new_version"
        create_git_tag "$new_version" "Bump versão para $new_version (minor)"
        generate_build_info
        ;;
    "major")
        new_version=$(increment_version "major")
        update_version_file "$new_version"
        create_git_tag "$new_version" "Bump versão para $new_version (major)"
        generate_build_info
        ;;
    "pre")
        if [[ -z "$2" ]]; then
            echo -e "${RED}❌ Tipo de pré-lançamento é obrigatório${NC}"
            echo -e "${YELLOW}Tipos: alpha, beta, rc${NC}"
            exit 1
        fi
        new_version=$(create_pre_release "$2")
        update_version_file "$new_version"
        create_git_tag "$new_version" "Pré-lançamento $new_version"
        generate_build_info
        ;;
    "release")
        new_version=$(create_release)
        update_version_file "$new_version"
        create_git_tag "$new_version" "Lançamento versão $new_version"
        generate_build_info
        ;;
    "tag")
        if [[ -z "$2" ]]; then
            echo -e "${RED}❌ Versão é obrigatória${NC}"
            exit 1
        fi
        validate_semver "$2"
        create_git_tag "$2" "Tag versão $2"
        ;;
    "init")
        init_versioning
        ;;
    "changelog")
        generate_changelog
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
