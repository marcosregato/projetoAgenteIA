#include <iostream>
#include "../include/agente/Agente.hpp"

void Agente::arvoreDecisao(const No* atual) {
    if (atual == nullptr) {
        std::cout << "No nulo em arvoreDecisao." << std::endl;
        return;
    }

    // Se não houver ramificações (filhos), chegamos a uma folha (resultado)
    if (atual->sim == nullptr && atual->nao == nullptr) {
        std::cout << "\n>>> Decisao final: " << atual->perguntaOuResultado << std::endl;
        return;
    }

    // Caso contrário, fazemos a pergunta do nó atual
    char resposta;
    std::cout << atual->perguntaOuResultado << " (s/n): ";
    std::cin >> resposta;

    if (resposta == 's' || resposta == 'S') {
        arvoreDecisao(atual->sim.get());
    } else {
        arvoreDecisao(atual->nao.get());
    }
}

void Agente::usarLlama() {
    std::cout << "Integracao com Llama iniciada... (Recurso em desenvolvimento)" << std::endl;
}






