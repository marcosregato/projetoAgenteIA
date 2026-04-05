#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>
#include "../include/falaRobotica/SintetizadorVoz.h"

// Classe de teste para os motores de voz
class VoiceEngineTester {
public:
    static void testFliteEngine() {
        std::cout << "\n=== Testando Motor Flite ===" << std::endl;
        
        SintetizadorVoz tts(MotorVoz::FLITE);
        
        // Testar inicialização
        bool inicializado = tts.inicializar();
        assert(inicializado && "Flite deveria inicializar com sucesso");
        std::cout << "✅ Flite inicializado com sucesso" << std::endl;
        
        // Testar motor atual
        assert(tts.getMotorAtual() == MotorVoz::FLITE && "Motor deveria ser FLITE");
        std::cout << "✅ Motor atual verificado: FLITE" << std::endl;
        
        // Testar fala em inglês
        std::cout << "🔊 Testando fala em inglês com Flite..." << std::endl;
        tts.falar("Hello! This is a test of the Flite voice engine.");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Testar método específico
        std::cout << "🔊 Testando método falarIngles..." << std::endl;
        tts.falarIngles("Testing the specific English speech method.");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        std::cout << "✅ Testes do Flite concluídos com sucesso!" << std::endl;
    }
    
    static void testESpeakEngine() {
        std::cout << "\n=== Testando Motor eSpeak-ng ===" << std::endl;
        
        SintetizadorVoz tts(MotorVoz::ESPEAK_NG);
        
        // Testar inicialização
        bool inicializado = tts.inicializar();
        if (!inicializado) {
            std::cout << "⚠️  eSpeak-ng não disponível no sistema, pulando testes..." << std::endl;
            return;
        }
        
        std::cout << "✅ eSpeak-ng inicializado com sucesso" << std::endl;
        
        // Testar motor atual
        assert(tts.getMotorAtual() == MotorVoz::ESPEAK_NG && "Motor deveria ser ESPEAK_NG");
        std::cout << "✅ Motor atual verificado: ESPEAK_NG" << std::endl;
        
        // Testar fala em português
        std::cout << "🔊 Testando fala em português com eSpeak-ng..." << std::endl;
        tts.falar("Olá! Este é um teste do motor de voz eSpeak-ng.");
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        // Testar método específico
        std::cout << "🔊 Testando método falarPortugues..." << std::endl;
        tts.falarPortugues("Testando o método específico de fala em português.");
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        std::cout << "✅ Testes do eSpeak-ng concluídos com sucesso!" << std::endl;
    }
    
    static void testEngineSwitch() {
        std::cout << "\n=== Testando Mudança de Motores ===" << std::endl;
        
        SintetizadorVoz tts;
        
        // Começar com Flite
        tts.inicializar();
        assert(tts.getMotorAtual() == MotorVoz::FLITE);
        std::cout << "✅ Motor inicial: FLITE" << std::endl;
        
        // Mudar para eSpeak-ng
        tts.setMotorVoz(MotorVoz::ESPEAK_NG);
        assert(tts.getMotorAtual() == MotorVoz::ESPEAK_NG);
        std::cout << "✅ Mudança para eSpeak-ng realizada" << std::endl;
        
        // Inicializar novo motor
        bool inicializado = tts.inicializar();
        if (inicializado) {
            std::cout << "🔊 Testando fala após mudança..." << std::endl;
            tts.falar("Mudança de motor realizada com sucesso!");
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        
        // Voltar para Flite
        tts.setMotorVoz(MotorVoz::FLITE);
        assert(tts.getMotorAtual() == MotorVoz::FLITE);
        std::cout << "✅ Retorno para Flite realizado" << std::endl;
        
        tts.inicializar();
        std::cout << "🔊 Testando fala após retorno..." << std::endl;
        tts.falar("Back to Flite engine!");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        std::cout << "✅ Testes de mudança de motor concluídos!" << std::endl;
    }
    
    static void testAutoSelection() {
        std::cout << "\n=== Testando Seleção Automática ===" << std::endl;
        
        SintetizadorVoz tts;
        
        // Testar com Flite (padrão)
        tts.inicializar();
        std::cout << "🔊 Falando com motor padrão (Flite)..." << std::endl;
        tts.falar("This should be spoken in English using Flite.");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Mudar para eSpeak-ng e testar seleção automática
        tts.setMotorVoz(MotorVoz::ESPEAK_NG);
        if (tts.inicializar()) {
            std::cout << "🔊 Falando com motor selecionado (eSpeak-ng)..." << std::endl;
            tts.falar("Isso deve ser falado em português usando eSpeak-ng.");
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        
        std::cout << "✅ Testes de seleção automática concluídos!" << std::endl;
    }
};

int main() {
    std::cout << "🧪 Iniciando Testes dos Motores de Voz" << std::endl;
    std::cout << "========================================" << std::endl;
    
    try {
        // Executar todos os testes
        VoiceEngineTester::testFliteEngine();
        VoiceEngineTester::testESpeakEngine();
        VoiceEngineTester::testEngineSwitch();
        VoiceEngineTester::testAutoSelection();
        
        std::cout << "\n🎉 Todos os testes concluídos com sucesso!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Erro durante os testes: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Erro desconhecido durante os testes!" << std::endl;
        return 1;
    }
    
    return 0;
}
