#ifndef CONVERTER_DADOS_H
#define CONVERTER_DADOS_H

class ConverterDados {


    public:
        int converterStringToInt(std::string valor);
        float converterStringToFloat(std::string valor);
        double converterStringToDouble(std::string valor);
        std::string converterStringToString(std::string valor);
        bool converterStringToBool(std::string valor);
        std::string detectarTipo(std::string valor);
  
    
};


#endif