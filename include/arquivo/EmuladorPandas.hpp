#ifndef EMULADOR_PANDAS_H
#define EMULADOR_PANDAS_H
#include <string>


class EmuladorPandas {
    
    public:
        std::string getNomeColuna();
        void verificarTipoColuna();
        void verificarCelulaNull();
        void converterTipoColuna();
};


#endif
