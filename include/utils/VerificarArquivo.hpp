#ifndef VERIFICARARQUIVO_H_INCLUDED
#define VERIFICARARQUIVO_H_INCLUDED

#include <string>

class VerificarArquivo {
public:
    bool isVerificarArquivo(const std::string &nomeArquivo);
    std::string getFrontalfaceAlt2(const std::string &nomeArquivo);
    std::string getLbfmodel(const std::string &nomeArquivo);


};

#endif
