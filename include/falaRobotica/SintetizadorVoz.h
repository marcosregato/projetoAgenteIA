#ifndef SINTETIZADORVOZ_H_INCLUDED
#define SINTETIZADORVOZ_H_INCLUDED

#include <string>
#include <flite/flite.h>
#include "utils/LogSistema.hpp"

extern "C" {
    cst_voice *register_cmu_us_slt(); // Voz feminina
    cst_voice *register_cmu_us_kal(); // Voz masculina
}

class SintetizadorVoz {
public:
    SintetizadorVoz();
    ~SintetizadorVoz();

    // Inicia a voz feminina por padrão e configura o eSpeak para Português
    bool inicializar();

    // Fala o texto recebido
    void falar(const std::string& texto);
    void falarPortugues(const std::string& texto);

private:
    cst_voice* voz;
    bool inicializado;
    bool eSpeakInicializado;
    LogSistema logger;
};

#endif
