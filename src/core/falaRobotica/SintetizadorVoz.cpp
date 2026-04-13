#include <iostream>
#include <string>
#include "../include/falaRobotica/SintetizadorVoz.h"
#include <flite/flite.h>
#if HAS_ESPEAK
#include <espeak-ng/speak_lib.h>
#endif

static std::string removerAcentos(const std::string& texto) {
    std::string resultado = texto;
    const std::string acentos = "áàãâäÁÀÃÂÄéèêëÉÈÊËíìîïÍÌÎÏóòõôöÓÒÕÔÖúùûüÚÙÛÜçÇ";
    const std::string sem_acentos = "aaaaaAAAAeeeeEEEEiiiiIIIoooooOOOOOuuuuUUUUcC";
    
    for (size_t i = 0; i < acentos.length(); ++i) {
        size_t pos = 0;
        while ((pos = resultado.find(acentos[i], pos)) != std::string::npos) {
            resultado[pos] = sem_acentos[i];
            ++pos;
        }
    }
    return resultado;
}

SintetizadorVoz::SintetizadorVoz() : voz(nullptr), inicializado(false), motorAtual(MotorVoz::FLITE) {
}

SintetizadorVoz::SintetizadorVoz(MotorVoz motor) : voz(nullptr), inicializado(false), motorAtual(motor) {
}

SintetizadorVoz::~SintetizadorVoz() {
#if HAS_ESPEAK
    if (inicializado && motorAtual == MotorVoz::ESPEAK_NG) {
        espeak_Terminate();
    }
#endif
}

void SintetizadorVoz::setMotorVoz(MotorVoz motor) {
    motorAtual = motor;
    inicializado = false;
}

bool SintetizadorVoz::inicializar() {
    if (inicializado) return true;
    
    switch (motorAtual) {
        case MotorVoz::FLITE:
            flite_init();
            voz = register_cmu_us_slt();
            inicializado = (voz != nullptr);
            break;
            
        case MotorVoz::ESPEAK_NG:
#if HAS_ESPEAK

            inicializado = (espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 500, NULL, 0) > 0);
            if (inicializado) {
                espeak_SetParameter(espeakRATE, 150, 0);  // Velocidade mais lenta
                espeak_SetParameter(espeakVOLUME, 80, 0); // Volume em 80%
                espeak_SetParameter(espeakPITCH, 60, 0);  // Tom um pouco mais agudo
                espeak_SetVoiceByName("pt-br");
            }
#endif
            break;
    }
    
    return inicializado;
}

void SintetizadorVoz::falar(const std::string& texto) {
    if (texto.empty() || !inicializar()) return;
    
    switch (motorAtual) {
        case MotorVoz::FLITE:
            if (voz) {
                flite_text_to_speech(removerAcentos(texto).c_str(), voz, "play");
            }
            break;
            
        case MotorVoz::ESPEAK_NG:
#if HAS_ESPEAK
            if (inicializado) {
                espeak_Synth(texto.c_str(), texto.length() + 1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
                espeak_Synchronize();
            }
#endif
            break;
    }
}

void SintetizadorVoz::falarIngles(const std::string& texto) {
    if (motorAtual == MotorVoz::FLITE) {
        falar(texto);
    }
}

void SintetizadorVoz::falarPortugues(const std::string& texto) {
    if (motorAtual == MotorVoz::ESPEAK_NG) {
        falar(texto);
    }
}
