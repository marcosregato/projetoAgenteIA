#include <iostream>
#include <cstdlib>

// Menu principal para executar todos os testes do projeto
int main() {
    std::cout << "🧪 Menu de Testes - projetoAgenteIA" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << std::endl;
    
    while (true) {
        std::cout << "Escolha o teste que deseja executar:" << std::endl;
        std::cout << std::endl;
        std::cout << "1. 🎥 Testes de Processamento de Imagem (interativo)" << std::endl;
        std::cout << "2. 🔊 Testes de Voz (simples)" << std::endl;
        std::cout << "3. 📋 Testes Unitários" << std::endl;
        std::cout << "4. 🎯 Todos os testes (automático)" << std::endl;
        std::cout << "0. 🚪 Sair" << std::endl;
        std::cout << std::endl;
        std::cout << "Opção: ";
        
        int escolha;
        std::cin >> escolha;
        
        switch (escolha) {
            case 1:
                std::cout << "\n🎥 Executando testes de processamento de imagem..." << std::endl;
                std::system("./tests/test_image_processor");
                break;
                
            case 2:
                std::cout << "\n🔊 Executando testes de voz..." << std::endl;
                std::system("./tests/test_voice_simple");
                break;
                
            case 3:
                std::cout << "\n📋 Executando testes unitários..." << std::endl;
                std::system("./tests/unit_tests");
                break;
                
            case 4:
                std::cout << "\n🎯 Executando todos os testes..." << std::endl;
                std::cout << "📝 Isso executará:" << std::endl;
                std::cout << "   • Testes de processamento de imagem" << std::endl;
                std::cout << "   • Testes de voz" << std::endl;
                std::cout << "   • Testes unitários" << std::endl;
                std::cout << "\n⚠️  ATENÇÃO: Isso pode levar vários minutos!" << std::endl;
                
                // Executar todos os testes
                std::system("./tests/test_image_processor");
                std::system("./tests/test_voice_simple");
                std::system("./tests/unit_tests");
                break;
                
            case 0:
                std::cout << "\n🚪 Saindo..." << std::endl;
                return 0;
                
            default:
                std::cout << "\n❌ Opção inválida! Tente novamente." << std::endl;
                break;
        }
        
        std::cout << std::endl;
        std::cout << "Pressione ENTER para continuar..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        
        // Limpar tela (funciona em Linux/Windows)
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }
    
    return 0;
}
