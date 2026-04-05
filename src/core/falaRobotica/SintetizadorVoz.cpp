#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "../include/falaRobotica/SintetizadorVoz.h"
#include "utils/LogSistema.hpp"
#if HAS_ESPEAK
#include <espeak-ng/speak_lib.h>
#endif

static std::string removerAcentos(const std::string& texto) {
    static const std::vector<std::pair<std::string, std::string>> mapeamentos = {
        {"á", "a"}, {"à", "a"}, {"ã", "a"}, {"â", "a"}, {"ä", "a"},
        {"Á", "A"}, {"À", "A"}, {"Ã", "A"}, {"Â", "A"}, {"Ä", "A"},
        {"é", "e"}, {"è", "e"}, {"ê", "e"}, {"ë", "e"},
        {"É", "E"}, {"È", "E"}, {"Ê", "E"}, {"Ë", "E"},
        {"í", "i"}, {"ì", "i"}, {"î", "i"}, {"ï", "i"},
        {"Í", "I"}, {"Ì", "I"}, {"Î", "I"}, {"Ï", "I"},
        {"ó", "o"}, {"ò", "o"}, {"õ", "o"}, {"ô", "o"}, {"ö", "o"},
        {"Ó", "O"}, {"Ò", "O"}, {"Õ", "O"}, {"Ô", "O"}, {"Ö", "O"},
        {"ú", "u"}, {"ù", "u"}, {"û", "u"}, {"ü", "u"},
        {"Ú", "U"}, {"Ù", "U"}, {"Û", "U"}, {"Ü", "U"},
        {"ç", "c"}, {"Ç", "C"}
    };

    std::string resultado = texto;
    for (const auto& par : mapeamentos) {
        size_t pos = 0;
        while ((pos = resultado.find(par.first, pos)) != std::string::npos) {
            resultado.replace(pos, par.first.length(), par.second);
            pos += par.second.length();
        }
    }
    return resultado;
}

SintetizadorVoz::SintetizadorVoz() : voz(nullptr), inicializado(false), eSpeakInicializado(false), motorAtual(MotorVoz::FLITE) {
    // Construtor padrão usa Flite
}

SintetizadorVoz::SintetizadorVoz(MotorVoz motor) : voz(nullptr), inicializado(false), eSpeakInicializado(false), motorAtual(motor) {
    // Construtor com motor específico
}

SintetizadorVoz::~SintetizadorVoz() {
    // O Flite gerencia a memória das vozes estáticas,
    // mas se você carregar vozes dinâmicas, aqui seria o local de limpar.
#if HAS_ESPEAK
    if (eSpeakInicializado) {
        espeak_Terminate();
    }
#endif
}

void SintetizadorVoz::setMotorVoz(MotorVoz motor) {
    motorAtual = motor;
    // Resetar estados ao mudar o motor
    inicializado = false;
    eSpeakInicializado = false;
}

bool SintetizadorVoz::inicializar() {
    switch (motorAtual) {
        case MotorVoz::FLITE:
            return inicializarFlite();
        case MotorVoz::ESPEAK_NG:
            return inicializarESpeak();
        default:
            std::cerr << "Motor de voz não reconhecido!" << std::endl;
            return false;
    }
}

bool SintetizadorVoz::inicializarFlite() {
    if (!inicializado) {
        flite_init();
        voz = register_cmu_us_slt(); // Voz feminina
        if (voz) {
            inicializado = true;
            std::cout << "Flite inicializado com sucesso." << std::endl;
        } else {
            std::cerr << "Falha ao inicializar Flite." << std::endl;
        }
    }
    return inicializado;
}

bool SintetizadorVoz::inicializarESpeak() {
#if HAS_ESPEAK
    if (!eSpeakInicializado) {
        int samplerate = espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);
        if (samplerate > 0) {
            std::cout << "eSpeak-ng inicializado com sucesso. Sample rate: " << samplerate << std::endl;
            // Tenta selecionar a voz pt-br, com fallback para pt.
            if (espeak_SetVoiceByName("pt-br") != EE_OK && espeak_SetVoiceByName("pt") != EE_OK) {
                std::cerr << "Erro eSpeak-ng: Voz em Português não encontrada." << std::endl;
            } else {
                eSpeakInicializado = true;
                std::cout << "Voz em português configurada com sucesso." << std::endl;
            }
        } else {
            std::cerr << "Erro eSpeak-ng: Falha na inicialização. Verifique o servidor de áudio." << std::endl;
        }
    }
    return eSpeakInicializado;
#else
    std::cerr << "Erro: eSpeak-ng não foi compilado com suporte." << std::endl;
    return false;
#endif
}

// Fala usando o motor selecionado
void SintetizadorVoz::falar(const std::string& texto) {
    if (texto.empty()) {
        std::cerr << "Erro: texto vazio para falar" << std::endl;
        return;
    }

    switch (motorAtual) {
        case MotorVoz::FLITE:
            falarIngles(texto);
            break;
        case MotorVoz::ESPEAK_NG:
            falarPortugues(texto);
            break;
        default:
            std::cerr << "Erro: Motor de voz não definido!" << std::endl;
            break;
    }
}

// Fala em inglês (usa Flite)
void SintetizadorVoz::falarIngles(const std::string& texto) {
    if (motorAtual != MotorVoz::FLITE) {
        std::cerr << "Erro: Motor Flite não selecionado!" << std::endl;
        return;
    }
    
    if (!inicializar()) {
        std::cerr << "Erro: Flite não inicializado!" << std::endl;
        return;
    }

    if (inicializado && voz) {
        std::string textoTratado = removerAcentos(texto);
        flite_text_to_speech(textoTratado.c_str(), voz, "play");
    } else {
        std::cerr << "Erro: Sintetizador Flite não inicializado!" << std::endl;
    }
}


void SintetizadorVoz::falarPortugues(const std::string& texto) {
    if (texto.empty()) {
        std::cerr << "Erro: texto vazio para falar em Português" << std::endl;
        return;
    }

    if (motorAtual != MotorVoz::ESPEAK_NG) {
        std::cerr << "Erro: Motor eSpeak-ng não selecionado!" << std::endl;
        return;
    }

    if (!inicializar()) {
        std::cerr << "Erro: eSpeak-ng não inicializado!" << std::endl;
        return;
    }

#if HAS_ESPEAK
    if (eSpeakInicializado) {
        espeak_Synth(texto.c_str(), texto.size() + 1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
        espeak_Synchronize(); // Espera terminar de falar
        return;
    }
#endif

    std::cerr << "Erro: eSpeak-ng não está disponível. Português não pode ser falado." << std::endl;
}
