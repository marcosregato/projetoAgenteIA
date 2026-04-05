#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "falaRobotica/SintetizadorVoz.h"
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

SintetizadorVoz::SintetizadorVoz() : voz(nullptr), inicializado(false), eSpeakInicializado(false) {}

SintetizadorVoz::~SintetizadorVoz() {
    // O Flite gerencia a memória das vozes estáticas,
    // mas se você carregar vozes dinâmicas, aqui seria o local de limpar.
#if HAS_ESPEAK
    if (eSpeakInicializado) {
        espeak_Terminate();
    }
#endif
}

bool SintetizadorVoz::inicializar() {
    if (!inicializado) {
        flite_init();
        voz = register_cmu_us_slt(); // Escolhe a voz feminina
        if (voz) {
            inicializado = true;
        }
    }


    if (!eSpeakInicializado) {
        espeak_ERROR err = espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);
        if (err != EE_OK) {
            logger.logError("Erro eSpeak-ng: Falha na inicialização (Código " + std::to_string(err) + "). Verifique o servidor de áudio.");
        } else {
            // Tenta selecionar a voz pt-br, com fallback para pt.
            if (espeak_SetVoiceByName("pt-br") != EE_OK && espeak_SetVoiceByName("pt") != EE_OK) {
                logger.logError("Erro eSpeak-ng: Voz em Português não encontrada.");
            } else {
                eSpeakInicializado = true;
            }
        }
    }

    return inicializado || eSpeakInicializado;
}

// A fala sirá em Inglês
void SintetizadorVoz::falar(const std::string& texto) {
    if (inicializado && voz) {
        std::string textoTratado = removerAcentos(texto);
        flite_text_to_speech(textoTratado.c_str(), voz, "play");
    } else {
        std::cerr << "Erro: Sintetizador não inicializado!" << std::endl;
        logger.logError("Erro: Sintetizador não inicializado!");
    }
}


void SintetizadorVoz::falarPortugues(const std::string& texto) {
    if (texto.empty()) {
        logger.logError("Erro: texto vazio para falar em Português");
        return;
    }

    if (!eSpeakInicializado) {
        inicializar();
    }

    if (eSpeakInicializado) {
        espeak_Synth(texto.c_str(), texto.size() + 1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
        espeak_Synchronize(); // Espera terminar de falar
        return;
    }

    std::cerr << "Erro: eSpeak-ng não está disponível. Português não pode ser falado." << std::endl;
    logger.logError("Erro: eSpeak-ng não está disponível para falar em Português.");
}
