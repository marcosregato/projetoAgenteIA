#include <catch2/catch_test_macros.hpp>
#include "utils/LogSistema.hpp"
#include <sys/stat.h>

TEST_CASE("LogSistema - Verificacao de Logs", "[utils][log]") {
    LogSistema logger;

    SECTION("Inicializacao do arquivo de log") {
        int result = logger.criarArquivoLog();
        REQUIRE(result == 1); // Retorna 1 se escrever com sucesso
    }

    SECTION("Escrita de mensagens em diferentes niveis") {
        REQUIRE(logger.logInfo("Teste de Info") == 1);
        REQUIRE(logger.logError("Teste de Erro") == 1);
        REQUIRE(logger.logDebug("Teste de Debug") == 1);
    }
}