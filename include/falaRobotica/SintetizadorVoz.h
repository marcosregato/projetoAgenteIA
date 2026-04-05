#ifndef SINTETIZADORVOZ_H_INCLUDED
#define SINTETIZADORVOZ_H_INCLUDED

#include <string>
#include <flite/flite.h>
#include "utils/LogSistema.hpp"

extern "C" {
    cst_voice *register_cmu_us_slt(); // Voz feminina
    cst_voice *register_cmu_us_kal(); // Voz masculina
}

// Enum para escolha do motor de síntese de voz
enum class MotorVoz {
    FLITE,      // Usa Flite (inglês)
    ESPEAK_NG   // Usa eSpeak-ng (português)
};

class SintetizadorVoz {
public:
    SintetizadorVoz();
    explicit SintetizadorVoz(MotorVoz motor);
    ~SintetizadorVoz();

    // Define qual motor de voz usar
    void setMotorVoz(MotorVoz motor);

    // Inicia o motor de voz selecionado
    bool inicializar();

    // Fala o texto recebido usando o motor selecionado
    void falar(const std::string& texto);
    
    // Fala em português (usa eSpeak-ng)
    void falarPortugues(const std::string& texto);
    
    // Fala em inglês (usa Flite)
    void falarIngles(const std::string& texto);

    // Obtém o motor atual
    MotorVoz getMotorAtual() const { return motorAtual; }

private:
    cst_voice* voz;
    bool inicializado;
    bool eSpeakInicializado;
    MotorVoz motorAtual;
    LogSistema logger;
    
    // Métodos privados para inicialização específica
    bool inicializarFlite();
    bool inicializarESpeak();
};

#endif
