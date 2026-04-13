#include <iostream>
#include "../include/falaRobotica/SintetizadorVoz.h"

int main() {
    try {
        SintetizadorVoz voz(MotorVoz::FLITE);
        
        if (voz.inicializar()) {
            std::cout << "Motor Flite inicializado" << std::endl;
            voz.falar("Teste de voz");
            std::cout << "Teste concluido" << std::endl;
        } else {
            std::cout << "Falha na inicializacao" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Erro: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
