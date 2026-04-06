#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "arquivo/ManipularArquivo.hpp"
#include "utils/LogSistema.hpp"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

LogSistema logger;

int ManipularArquivo::lerArquivoCsv(std::string nomeArquivo){

    std::ifstream arquivo(nomeArquivo);

    std::string linha, celula;

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        logger.logError("Erro ao abrir o arquivo");
        return 1;
    }

    while (std::getline(arquivo, linha)) {
        std::stringstream lineStream(linha);
        std::vector<std::string> row;

        while (std::getline(lineStream, celula, ',')) {
            row.push_back(celula);
        }

        for (const auto& column : row) {
            std::cout << column << " , ";
        }
        std::cout << std::endl;
    }

    arquivo.close();
    return 0;


}

int ManipularArquivo::criarArquivoCsv(std::string nomeArquivo){

    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
         logger.logError("Erro ao abrir o arquivo");
        return 1;
    }

    arquivo << "Nome,Idade,Cidade\n";

    arquivo << "Ana,28,Sao Paulo\n";
    arquivo << "Bruno,34,Rio de Janeiro\n";
    arquivo << "Carlos,22,Belo Horizonte\n";

    arquivo.close();

    std::cout << "Arquivo CSV criado com sucesso!" << std::endl;

    return 0;


}

int ManipularArquivo::lerArquivoJson(std::string nomeArquivo){

    FILE* arqJson = fopen(nomeArquivo.c_str(), "r");
    char readBuffer[65536];
    if(!arqJson){
        logger.logError("Erro ao ler o arquivo Json");
        return 1;

    }
    rapidjson::FileReadStream is(arqJson, readBuffer,sizeof(readBuffer));

    rapidjson::Document doc;
    doc.ParseStream(is);

    fclose(arqJson);

    std::cout << doc["nome"].GetString() << std::endl;
    std::cout << doc["idade"].GetInt() << std::endl;

    return 0;


}


