#include <catch2/catch_test_macros.hpp>
#include "arquivo/ManipularArquivo.hpp"
#include <fstream>
#include <cstdio>

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
    }

    SECTION("Ler arquivo CSV existente") {
        // Usamos o helper para garantir o conteúdo antes de testar a leitura
        prepararArquivoCsvParaTeste(testFile);
        REQUIRE(manipulator.lerArquivoCsv(testFile) == 0);
    }

    SECTION("Erro ao ler arquivo CSV inexistente") {
        REQUIRE(manipulator.lerArquivoCsv("arquivo_que_nao_existe.csv") == 4);
    }

    // Limpeza do arquivo temporário
    std::remove(testFile.c_str());
}

TEST_CASE("ManipularArquivo - Operações JSON", "[arquivo][json]") {
    ManipularArquivo manipulator;
    
    SECTION("Erro ao ler JSON inexistente") {
        // O método retorna 4 se o fopen falhar
        REQUIRE(manipulator.lerArquivoJson("arquivo_json_que_nao_existe.json") == 4);
    }
    
    // Nota: O método lerArquivoJson atual assume campos fixos ("nome", "idade").
    // Testes mais complexos exigiriam um arquivo JSON válido de teste.
}
