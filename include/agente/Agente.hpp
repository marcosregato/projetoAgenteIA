#ifndef AGENTE_H
#define AGENTE_H

#include <string>
#include <memory>

class Agente {
public:
    struct No {
        std::string perguntaOuResultado;
        std::unique_ptr<No> sim;
        std::unique_ptr<No> nao;

        // Construtor para facilitar a criação
        No(const std::string& texto) : perguntaOuResultado(texto), sim(nullptr), nao(nullptr) {}
    };

    void arvoreDecisao(const No* atual);
    void usarLlama();
};

#endif
