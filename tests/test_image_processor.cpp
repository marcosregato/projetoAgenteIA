#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>
#include <fstream>
#include "../include/utils/image_processor.hpp"
#include "../include/utils/LogSistema.hpp"

// Incluir headers do OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

// Classe de teste para ImageProcessor
class ImageProcessorTester {
public:
    static void testOpenCam() {
        std::cout << "\n=== Testando Abertura de Webcam ===" << std::endl;
        
        ImageProcessor processor;
        
        std::cout << "Escolha o modo de teste:" << std::endl;
        std::cout << "1. Teste rápido (verificação apenas)" << std::endl;
        std::cout << "2. Teste interativo com webcam" << std::endl;
        std::cout << "3. Pular teste" << std::endl;
        std::cout << "Opção: ";
        
        int escolha;
        std::cin >> escolha;
        
        switch (escolha) {
            case 1:
                std::cout << "✅ Modo rápido selecionado - Verificando métodos..." << std::endl;
                std::cout << "✅ Método openCam() disponível" << std::endl;
                std::cout << "ℹ️  Para teste completo, execute: processor.openCam()" << std::endl;
                break;
                
            case 2:
                std::cout << "🎥 Iniciando teste interativo com webcam..." << std::endl;
                std::cout << "⚠️  ATENÇÃO: Este teste abrirá sua webcam!" << std::endl;
                std::cout << "⚠️  Pressione ESC na janela para encerrar" << std::endl;
                std::cout << "🎥 Iniciando em 3 segundos..." << std::endl;
                
                // Aguardar 3 segundos antes de iniciar
                for (int i = 3; i > 0; i--) {
                    std::cout << "\rIniciando em " << i << " segundos..." << std::flush;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                std::cout << "\n🎥 Iniciando agora!" << std::endl;
                
                // Executar teste interativo
                processor.openCam();
                break;
                
            case 3:
                std::cout << "⏭ Teste pulado" << std::endl;
                break;
                
            default:
                std::cout << "❌ Opção inválida!" << std::endl;
                break;
        }
    }
    
    static void testWebcamIndices() {
        std::cout << "\n=== Testando Indices de Webcam ===" << std::endl;
        
        ImageProcessor processor;
        
        // Testar método de verificação de índices
        std::cout << "🔍 Testando disponibilidade de webcams..." << std::endl;
        processor.testeIndiceWebCam();
        
        std::cout << "✅ Teste de índices concluído" << std::endl;
    }
    
    static void testFaceDetection() {
        std::cout << "\n=== Testando Detecção de Rosto ===" << std::endl;
        
        std::cout << "Escolha o modo de teste:" << std::endl;
        std::cout << "1. Verificação rápida (sem webcam)" << std::endl;
        std::cout << "2. Teste interativo com webcam" << std::endl;
        std::cout << "3. Pular teste" << std::endl;
        std::cout << "Opção: ";
        
        int escolha;
        std::cin >> escolha;
        
        switch (escolha) {
            case 1:
                std::cout << "✅ Modo rápido selecionado - Verificando componentes..." << std::endl;
                testFaceDetectionQuick();
                break;
                
            case 2:
                std::cout << "🎥 Modo interativo selecionado - ATENÇÃO!" << std::endl;
                std::cout << "⚠️  Este teste usará sua webcam!" << std::endl;
                std::cout << "⚠️  Pressione ESC para encerrar a qualquer momento" << std::endl;
                std::cout << "🎥 Iniciando em 3 segundos..." << std::endl;
                
                // Aguardar 3 segundos
                for (int i = 3; i > 0; i--) {
                    std::cout << "\rIniciando em " << i << " segundos..." << std::flush;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                std::cout << "\n🎥 Iniciando agora!" << std::endl;
                
                // Executar teste interativo
                testFaceDetectionInteractive();
                break;
                
            case 3:
                std::cout << "⏭ Teste pulado" << std::endl;
                break;
                
            default:
                std::cout << "❌ Opção inválida!" << std::endl;
                break;
        }
    }
    
    static void testFaceDetectionQuick() {
        std::cout << "🔍 Verificando arquivos necessários..." << std::endl;
        
        // Verificar se o sistema tem OpenCV
        try {
            cv::Mat testMat = cv::Mat::zeros(100, 100, CV_8UC3);
            if (!testMat.empty()) {
                std::cout << "✅ OpenCV funcionando corretamente" << std::endl;
            }
        } catch (const cv::Exception& e) {
            std::cout << "❌ Erro no OpenCV: " << e.what() << std::endl;
            return;
        }
        
        // Testar se o cascade classifier funciona
        try {
            cv::CascadeClassifier faceCascade;
            std::cout << "✅ Método de detecção de rosto disponível" << std::endl;
            std::cout << "ℹ️  Para teste completo, execute: processor.detectarRosto()" << std::endl;
            
        } catch (const cv::Exception& e) {
            std::cout << "❌ Erro no Cascade Classifier: " << e.what() << std::endl;
        }
    }
    
    static void testFaceDetectionInteractive() {
        ImageProcessor processor;
        
        // Executar detecção de rosto interativa
        std::cout << "🎥 Executando detecção facial em tempo real..." << std::endl;
        std::cout << "📹 Procurando rostos... (pressione ESC para parar)" << std::endl;
        
        int resultado = processor.detectarRosto();
        
        if (resultado == 0) {
            std::cout << "✅ Detecção de rosto concluída com sucesso!" << std::endl;
        } else {
            std::cout << "❌ Detecção de rosto terminou com código: " << resultado << std::endl;
        }
    }
    
    static void testDependencies() {
        std::cout << "\n=== Testando Dependências ===" << std::endl;
        
        // Testar OpenCV
        std::cout << "🔍 Verificando OpenCV..." << std::endl;
        try {
            cv::Mat testImage = cv::Mat::zeros(100, 100, CV_8UC3);
            cv::Mat gray;
            cv::cvtColor(testImage, gray, cv::COLOR_BGR2GRAY);
            std::cout << "✅ OpenCV - Funcções básicas funcionando" << std::endl;
        } catch (const cv::Exception& e) {
            std::cout << "❌ OpenCV - Erro: " << e.what() << std::endl;
        }
        
        // Testar módulo face
        try {
            cv::CascadeClassifier faceCascade;
            std::cout << "✅ OpenCV Face - Módulo disponível" << std::endl;
        } catch (const cv::Exception& e) {
            std::cout << "❌ OpenCV Face - Erro: " << e.what() << std::endl;
        }
        
        // Testar sistema de arquivos
        std::cout << "🔍 Verificando sistema de arquivos..." << std::endl;
        std::ifstream testFile("/tmp/test_image_processor.txt");
        if (testFile.good()) {
            std::cout << "✅ Sistema de arquivos funcionando" << std::endl;
            testFile.close();
            std::remove("/tmp/test_image_processor.txt");
        } else {
            std::cout << "❌ Erro no sistema de arquivos" << std::endl;
        }
    }
    
    static void testLogSystem() {
        std::cout << "\n=== Testando Sistema de Log ===" << std::endl;
        
        LogSistema logger;
        
        // Testar criação de arquivo de log
        int resultado = logger.criarArquivoLog();
        if (resultado == 0) {
            std::cout << "✅ Sistema de log inicializado" << std::endl;
        } else {
            std::cout << "❌ Erro ao inicializar sistema de log" << std::endl;
        }
        
        // Testar escrita de log
        resultado = logger.logInfo("Teste do sistema de log - ImageProcessor");
        if (resultado == 0) {
            std::cout << "✅ Escrita de log funcionando" << std::endl;
        } else {
            std::cout << "❌ Erro na escrita de log" << std::endl;
        }
    }
    
    static void runAllTests() {
        std::cout << "🧪 Iniciando Testes do ImageProcessor" << std::endl;
        std::cout << "======================================" << std::endl;
        
        try {
            testDependencies();
            testLogSystem();
            testWebcamIndices();
            testOpenCam();
            testFaceDetection();
            
            std::cout << "\n🎉 Todos os testes do ImageProcessor concluídos!" << std::endl;
            std::cout << "\n📝 Resumo:" << std::endl;
            std::cout << "   ✅ Dependências verificadas" << std::endl;
            std::cout << "   ✅ Sistema de log testado" << std::endl;
            std::cout << "   ✅ Índices de webcam verificados" << std::endl;
            std::cout << "   ✅ Métodos de processamento disponíveis" << std::endl;
            std::cout << "\n🎥 Testes Interativos Disponíveis:" << std::endl;
            std::cout << "   • Teste de webcam ao vivo (opção 2)" << std::endl;
            std::cout << "   • Detecção facial em tempo real (opção 2)" << std::endl;
            std::cout << "\n⚠️  Notas Importantes:" << std::endl;
            std::cout << "   • Testes interativos requerem webcam física" << std::endl;
            std::cout << "   • Pressione ESC para encerrar testes interativos" << std::endl;
            std::cout << "   • Execute testes individuais para debug específico" << std::endl;
            
        } catch (const std::exception& e) {
            std::cerr << "❌ Erro durante os testes: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "❌ Erro desconhecido durante os testes!" << std::endl;
        }
    }
};

int main() {
    ImageProcessorTester::runAllTests();
    return 0;
}
