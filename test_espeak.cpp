#include <iostream>
#include <cstring>
#include <espeak-ng/speak_lib.h>

int main() {
    std::cout << "Testando eSpeak-ng..." << std::endl;
    
    // Inicializar eSpeak
    espeak_ERROR err = static_cast<espeak_ERROR>(espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0));
    std::cout << "Resultado da inicialização: " << err << std::endl;
    
    if (err == EE_OK) {
        std::cout << "eSpeak inicializado com sucesso!" << std::endl;
        
        // Tentar definir voz em português
        espeak_ERROR voice_err = espeak_SetVoiceByName("pt-br");
        std::cout << "Resultado da definição de voz pt-br: " << voice_err << std::endl;
        
        if (voice_err != EE_OK) {
            voice_err = espeak_SetVoiceByName("pt");
            std::cout << "Resultado da definição de voz pt: " << voice_err << std::endl;
        }
        
        if (voice_err == EE_OK) {
            std::cout << "Voz em português configurada!" << std::endl;
            
            // Falar um texto de teste
            const char* texto = "Olá, teste do eSpeak em português";
            espeak_Synth(texto, strlen(texto) + 1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
            espeak_Synchronize();
            std::cout << "Texto falado!" << std::endl;
        } else {
            std::cout << "Falha ao configurar voz em português" << std::endl;
        }
        
        // Finalizar
        espeak_Terminate();
    } else {
        std::cout << "Falha ao inicializar eSpeak!" << std::endl;
    }
    
    return 0;
}
