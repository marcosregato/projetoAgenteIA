#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>
#include "../include/falaRobotica/SintetizadorVoz.h"

// Teste simples dos motores de voz
int main() {
    std::cout << "🧪 Teste Simplificado dos Motores de Voz" << std::endl;
    std::cout << "========================================" << std::endl;
    
    try {
        // Teste 1: Flite
        std::cout << "\n=== Testando Motor Flite ===" << std::endl;
        {
            SintetizadorVoz tts(MotorVoz::FLITE);
            
            bool inicializado = tts.inicializar();
            assert(inicializado && "Flite deveria inicializar com sucesso");
            std::cout << "✅ Flite inicializado com sucesso" << std::endl;
            
            assert(tts.getMotorAtual() == MotorVoz::FLITE && "Motor deveria ser FLITE");
            std::cout << "✅ Motor atual verificado: FLITE" << std::endl;
            
            std::cout << "🔊 Testando fala..." << std::endl;
            tts.falar("Hello! This is a test of the Flite voice engine.");
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        
        // Teste 2: eSpeak-ng
        std::cout << "\n=== Testando Motor eSpeak-ng ===" << std::endl;
        {
            SintetizadorVoz tts(MotorVoz::ESPEAK_NG);
            
            bool inicializado = tts.inicializar();
            if (inicializado) {
                std::cout << "✅ eSpeak-ng inicializado com sucesso" << std::endl;
                
                assert(tts.getMotorAtual() == MotorVoz::ESPEAK_NG && "Motor deveria ser ESPEAK_NG");
                std::cout << "✅ Motor atual verificado: ESPEAK_NG" << std::endl;
                
                std::cout << "🔊 Testando fala em português..." << std::endl;
                tts.falar("Olá! Este é um teste do motor eSpeak-ng.");
                std::this_thread::sleep_for(std::chrono::seconds(3));
            } else {
                std::cout << "⚠️  eSpeak-ng não disponível no sistema" << std::endl;
            }
        }
        
        // Teste 3: Mudança de motor
        std::cout << "\n=== Testando Mudança de Motores ===" << std::endl;
        {
            SintetizadorVoz tts;
            
            // Começar com Flite
            tts.inicializar();
            assert(tts.getMotorAtual() == MotorVoz::FLITE);
            std::cout << "✅ Motor inicial: FLITE" << std::endl;
            
            // Mudar para eSpeak-ng
            tts.setMotorVoz(MotorVoz::ESPEAK_NG);
            assert(tts.getMotorAtual() == MotorVoz::ESPEAK_NG);
            std::cout << "✅ Mudança para eSpeak-ng realizada" << std::endl;
            
            // Voltar para Flite
            tts.setMotorVoz(MotorVoz::FLITE);
            assert(tts.getMotorAtual() == MotorVoz::FLITE);
            std::cout << "✅ Retorno para Flite realizado" << std::endl;
            
            tts.inicializar();
            std::cout << "🔊 Testando fala após retorno..." << std::endl;
            tts.falar("Back to Flite engine!");
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        
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
