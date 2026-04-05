#include <iostream>
#include <fstream>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <cerrno>
#include <cstring>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "utils/LogSistema.hpp"

static bool criarDiretorioArquivoLog(const std::string &dirPath) {
    struct stat st;
    if (stat(dirPath.c_str(), &st) == 0) {
        if (S_ISDIR(st.st_mode)){
         return true;
        }else{
         return false;
        }
    }

    if (mkdir(dirPath.c_str(), 0755) == 0) {
        return true;
    }

    if (errno == EEXIST) {
        return true;
    }

    return false;
}

static std::string getDatHorarioAtual() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    #ifdef _WIN32
        localtime_s(&tm, &now_c);
    #else
        localtime_r(&now_c, &tm);
    #endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

static std::string getNomeArquivoComDataHora() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    #ifdef _WIN32
        localtime_s(&tm, &now_c);
    #else
        localtime_r(&now_c, &tm);
    #endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    return oss.str();
}

static int escreverLinhaDeLog(const std::string &nivel, const std::string &mensagem) {
    const std::string dir = "logs";
    if (!criarDiretorioArquivoLog(dir)) {
        std::cerr << "Erro: Nao foi possivel criar ou achar o diretorio de logs ('" << dir << "'). "
                  << std::strerror(errno) << std::endl;
        return 0;
    }

    std::string nomeArquivo = getNomeArquivoComDataHora();
    const std::string path = dir + "/execucao_" + nomeArquivo + ".log";
    std::ofstream logFile(path, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir arquivo de log em '" << path << "'. "
                  << std::strerror(errno) << std::endl;
        return 0;
    }

    std::string dataHora = getDatHorarioAtual();
    logFile << "[" << dataHora << "] [" << nivel << "] " << mensagem << std::endl;
    logFile.close();
    return 1;
}

int LogSistema::criarArquivoLog(){
    return escreverLinhaDeLog("INFO", "Sistema iniciado");
}

int LogSistema::logInfo(const std::string &mensagem) {
    return escreverLinhaDeLog("INFO", mensagem);
}

int LogSistema::logError(const std::string &mensagem) {
    return escreverLinhaDeLog("ERROR", mensagem);
}

int LogSistema::logDebug(const std::string &mensagem) {
    return escreverLinhaDeLog("DEBUG", mensagem);
}
