#ifndef MANIPULAR_AQUIVOCSV_H
#define MANIPULAR_AQUIVOCSV_H
#include <string>

class ManipularArquivo{

public:
    std::vector<std::vector<std::string>> getColunaArquivoCsv(const std::string& nomeArquivo);
    int criarArquivoCsv(std::string nomeArquivo);
    int lerArquivoJson(std::string nomeArquivo);
    int criarArquivoFala(std::string nomeArquivo, std::string donoDaFala, std::string fala);
    int criarArquivoHistorico(std::string nomeArquivo);


};


#endif
