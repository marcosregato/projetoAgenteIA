#ifndef MANIPULARAQUIVOCSV_H
#define MANIPULARAQUIVOCSV_H
#include <string>

class ManipularArquivo{

public:
    int lerArquivoCsv(std::string nomeArquivo);
    int criarArquivoCsv(std::string nomeArquivo);
    int lerArquivoJson(std::string nomeArquivo);
    int criarArquivoFala(std::string nomeArquivo, std::string donoDaFala, std::string fala);
    int criarArquivoHistorico(std::string nomeArquivo);


};


#endif
