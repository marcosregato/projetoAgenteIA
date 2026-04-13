#include <catch2/catch_test_macros.hpp>
#include "arquivo/ManipularArquivo.hpp"
#include <fstream>
#include <cstdio>
#include <vector>
#include <filesystem>

// Método auxiliar para criar o arquivo CSV com dados específicos para o teste
void prepararArquivoCsvParaTeste(const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    arquivo << "Nome,Idade,Cidade\n";
    arquivo << "Ana,28,Sao Paulo\n";
    arquivo << "Bruno,34,Rio de Janeiro\n";
    arquivo << "Carlos,22,Belo Horizonte\n";
    arquivo.close();
}

TEST_CASE("ManipularArquivo - Operações CSV", "[arquivo][csv]") {
    ManipularArquivo manipulator;
    const std::string testFile = "test_temp.csv";

    SECTION("Criar arquivo CSV") {
        // O método deve retornar 0 em caso de sucesso
        REQUIRE(manipulator.criarArquivoCsv(testFile) == 0);
        
        std::ifstream f(testFile);
        REQUIRE(f.good());
        f.close();
        
        // Limpeza
        std::remove(testFile.c_str());
    }

    SECTION("Ler coluna de arquivo CSV existente") {
        // Preparar arquivo de teste
        prepararArquivoCsvParaTeste(testFile);
        
        // Testar método getColunaArquivoCsv
        auto coluna = manipulator.getColunaArquivoCsv(testFile);
        REQUIRE_FALSE(coluna.empty());
        
        // Limpeza
        std::remove(testFile.c_str());
    }

    SECTION("Erro ao ler coluna de arquivo CSV inexistente") {
        auto coluna = manipulator.getColunaArquivoCsv("dadoTeste.csv");
        REQUIRE(coluna.empty());
    }
}

TEST_CASE("ManipularArquivo - Operações JSON", "[arquivo][json]") {
    ManipularArquivo manipulator;
    
    SECTION("Erro ao ler JSON inexistente") {
        // O método retorna 4 se o fopen falhar
        REQUIRE(manipulator.lerArquivoJson("arquivo_json_que_nao_existe.json") == 4);
    }
}

TEST_CASE("ManipularArquivo - Operações de Fala", "[arquivo][fala]") {
    ManipularArquivo manipulator;
    const std::string testFile = "test_fala.txt";
    
    SECTION("Criar arquivo de fala") {
        REQUIRE(manipulator.criarArquivoFala(testFile, "Usuario", "Ola mundo") == 0);
        
        std::ifstream f(testFile);
        REQUIRE(f.good());
        f.close();
        
        // Limpeza
        std::remove(testFile.c_str());
    }
}

TEST_CASE("ManipularArquivo - Operações de Historico", "[arquivo][historico]") {
    ManipularArquivo manipulator;
    const std::string testFile = "test_historico.txt";
    
    SECTION("Criar arquivo de historico") {
        REQUIRE(manipulator.criarArquivoHistorico(testFile) == 0);
        
        std::ifstream f(testFile);
        REQUIRE(f.good());
        f.close();
        
        // Limpeza
        std::remove(testFile.c_str());
    }
}
