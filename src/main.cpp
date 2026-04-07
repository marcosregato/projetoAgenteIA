#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include "utils/image_processor.hpp"
#include "utils/LogSistema.hpp"
#include "utils/VerificarArquivo.hpp"
#include "agente/Agente.hpp"
#include "arquivo/ManipularArquivo.hpp"
#include <memory>

#include "falaRobotica/SintetizadorVoz.h"



int main() {
    ImageProcessor cam;
    LogSistema logger;
    [[maybe_unused]] VerificarArquivo verificar;
    [[maybe_unused]] Agente agente;
    [[maybe_unused]] ManipularArquivo manipularArquivo;

    std::cout << "OpenCV version: " << CV_VERSION << std::endl;

    // Criar arquivo de log
    logger.criarArquivoLog();

    // Testar indices disponiveis
    // cam.testeIndiceWebCam();

    // Abrir webcam
    // int status = cam.openCam();
    /*if (status != 0) {
        std::cerr << "Falha ao abrir a webcam (código " << status << ")." << std::endl;
        logger.logError("Falha ao abrir a webcam");
        return status;
    }*/

    // Detectar rostos com landmarks
    /*int status = cam.detectarRosto();
    if (status != 0) {
        std::cerr << "Falha ao detectar rostos (código " << status << ")." << std::endl;
        logger.logError("Falha ao abrir a webcam");
        return status;
    }*/

    // Exemplo de uso do Agente (árvore de decisão)
    //auto raiz = std::make_unique<Agente::No>("Esta chovendo?");
    //auto perguntaVento = std::make_unique<Agente::No>("O vento esta forte?");

    // Montando a estrutura
    //perguntaVento->sim = std::make_unique<Agente::No>("Fique em casa! O vento esta muito forte.");
    //perguntaVento->nao = std::make_unique<Agente::No>("Leve o guarda-chuva!");

    //raiz->nao = std::make_unique<Agente::No>("Nao precisa de guarda-chuva.");
    //raiz->sim = std::move(perguntaVento); // Movemos a posse para a raiz

    //std::cout << "--- Sistema de Apoio a Decisao ---\n" << std::endl;
    //agente.arvoreDecisao(raiz.get());

    //verificar.getLbfmodel("isLbfmodel");

    SintetizadorVoz tts;
    tts.inicializar();
    tts.falar("Sistema inicializado com sucesso!");

    return 0;
}

//g++ -std=c++17 -Iinclude src/main.cpp src/utils/image_processor.cpp src/core/falaRobotica/SintetizadorVoz.cpp src/core/utils/LogSistema.cpp src/core/utils/VerificarArquivo.cpp src/core/arquivo/ManipularArquivo.cpp src/core/agente/Agente.cpp src/core/inference_engine.cpp -o app `pkg-config --cflags --libs opencv4` -Lbuild/bin -lllama -lggml -lggml-cpu -lggml-base -lflite -lflite_cmu_us_slt -lm -fopenmp -Wl,--allow-multiple-definition
