#include <catch2/catch_test_macros.hpp>
#include "utils/VerificarArquivo.hpp"
#include <string>

TEST_CASE("VerificarArquivo - Busca de Modelos", "[utils][arquivo]") {
    VerificarArquivo verifier;

    SECTION("Busca de haarcascade inexistente") {
        // Deve retornar string vazia se não encontrar em nenhum dos paths padrão
        std::string path = verifier.getFrontalfaceAlt2("arquivo_fantasma_ia.xml");
        REQUIRE(path == "");
    }

    SECTION("Busca de lbfmodel inexistente") {
        std::string path = verifier.getLbfmodel("modelo_nao_existente.yaml");
        REQUIRE(path == "");
    }
}