# Árvores de Decisão e Agentes de IA

> **Guia completo sobre árvores de decisão, agentes de IA e implementação em C++**

---

## O que é um Agente de IA?

Um agente de IA é um sistema que não apenas gera texto (como um chatbot comum), mas que consegue perceber o ambiente, raciocinar e tomar decisões para atingir uma meta específica de forma autônoma.

Diferente de um LLM padrão, que espera uma pergunta para dar uma resposta, o agente usa o modelo de linguagem como um "cérebro" para comandar outras ferramentas.

### Os 4 Pilares de um Agente:

1. **Percepção**: Ele recebe informações (texto, arquivos, sensores ou dados da web)
2. **Cérebro (LLM)**: Ele planeja os passos necessários para resolver o problema
3. **Ferramentas (Actions)**: Ele pode acessar a internet, rodar scripts de Python, editar arquivos ou consultar bancos de dados
4. **Autonomia**: Ele decide qual ferramenta usar e verifica se o resultado foi satisfatório antes de terminar a tarefa

### Exemplos de Diferença:

**IA Comum (Chatbot)**: Você pergunta "Qual o preço da ação da Apple?". Ela responde com o dado que conhece ou pesquisa.

**Agente de IA**: Você diz "Monitore o preço da Apple e me envie um e-mail se cair 5%, anexando um gráfico comparativo". O agente vai:
- Acessar a API de finanças
- Criar o gráfico (usando Python)
- Monitorar o tempo
- Logar no serviço de e-mail e enviar a mensagem

---

## Arquitetura de um Agente

Geralmente, um agente moderno segue o ciclo ReAct (Reason + Act):

1. **Pensamento**: "Preciso calcular a raiz quadrada de X"
2. **Ação**: Chama uma calculadora
3. **Observação**: Lê o resultado "Y"
4. **Conclusão**: Entrega a resposta final baseada na observação

---

## Árvores de Decisão: Fundamentos

### O que é uma Árvore de Decisão?

Uma árvore de decisão é uma estrutura de dados em forma de árvore usada para tomar decisões ou classificar informações. Ela é composta por:

- **Raiz (Root)**: ponto de partida da decisão
- **Nós internos (Internal nodes)**: representam perguntas ou condições a serem avaliadas
- **Ramos (Branches)**: representam respostas ou caminhos possíveis para cada decisão
- **Folhas (Leaves)**: representam o resultado final ou ação a ser tomada

### Estrutura Visual Simples

Exemplo de árvore de decisão para decidir o que um agente deve fazer baseado na energia:

```
          [Energia > 50?]     <-- Raiz
            /       \
         Sim          Não     <-- Ramos
        /               \
 [Trabalhar]         [Dormir] <-- Folhas (decisão final)
```

Se a energia > 50 -> agente vai trabalhar
Caso contrário -> agente vai dormir

### Como funciona? (Passo a passo)

1. Comece pelo nó raiz (primeira condição a ser avaliada)
2. Verifique a condição do nó
3. Siga pelo ramo correspondente à resposta (sim/não, verdadeiro/falso ou outras alternativas)
4. Continue percorrendo os nós internos até chegar a uma folha
5. A folha indica a decisão ou ação final

### Tipos de Árvore de Decisão

- **Árvore de classificação**: cada folha é uma categoria ou classe
- **Árvore de regressão**: cada folha é um valor numérico (ex.: previsão de temperatura)
- **Árvore binária**: cada nó tem no máximo dois ramos (sim/não)
- **Árvore multi-ramo**: cada nó pode ter mais de dois ramos (vários caminhos possíveis)

### Vantagens das Árvores de Decisão

- Fácil de entender e visualizar
- Boa para decisões baseadas em múltiplas condições
- Pode ser usada como base para agentes inteligentes
- Permite implementação simples em C++ com if/else ou structs de nós

---

## Árvores de Decisão vs Grafos

### Árvores de Decisão

É uma estrutura em árvore, que é um tipo de grafo.
- Cada nó representa uma decisão ou condição
- Cada ramo representa uma possível escolha ou resultado
- Cada folha representa a decisão final ou resultado

**Características importantes:**
- **Sem ciclos** -> você nunca volta a um nó anterior
- **Hierarquia clara** -> começa da raiz e vai para as folhas
- **Fluxo unidirecional** -> sempre do topo (raiz) para baixo (folhas)

### Grafo

Um grafo é um conjunto de nós e arestas que podem se conectar de qualquer forma.
- Pode ter ciclos (volta a um nó anterior)
- Pode ser direcionado ou não direcionado

### Comparação

| Característica | Árvore de Decisão | Grafo Geral |
|----------------|-------------------|------------|
| Ciclos | Não | Pode ter |
| Hierarquia | Sempre hierárquica (raiz -> folhas) | Não necessariamente |
| Direção | Unidirecional (raiz -> folhas) | Pode ser bidirecional ou direcionado |
| Uso | Tomada de decisão | Modelar redes, caminhos, conexões gerais |

**Resumo:** Uma árvore de decisão é um tipo especial de grafo (um grafo acíclico direcionado hierárquico). Mas nem todo grafo é uma árvore de decisão, porque grafos podem ter ciclos, conexões complexas e não seguir hierarquia.

---

## Diagrama Visual: Árvore de Decisão para Agente de IA

```
                        [Objetivo do Agente: Sobreviver]
                                  |
                 ------------------------------------------
                 |                                        |
         [Energia > 50?]                             [Energia <= 50?]
                 |                                        |
         ---------------                             ----------------
         |             |                             |              |
    [Inimigo perto?] [Explorar]                  [Descansar]     [Procurar comida]
         |            
    ------- -------
    |             |
 [Atacar]       [Fugir]
```

### Explicação do Diagrama

- **Raiz**: [Objetivo do Agente: Sobreviver] - Todo o processo de decisão começa aqui
- **Nós internos**: [Energia > 50?] e [Inimigo perto?] - verifica se o agente tem energia suficiente e se precisa reagir a uma ameaça
- **Ramos**: Cada decisão gera caminhos diferentes: Sim/Não ou múltiplas opções
- **Folhas (Decisão final)**: [Atacar], [Fugir], [Explorar], [Descansar], [Procurar comida] - ações que o agente executa
- **Subárvores**: [Inimigo perto?] forma uma subárvore com [Atacar] e [Fugir]

---

## Tipo de Árvore de Decisão em Agentes de IA

Em agentes de IA, o tipo de árvore de decisão usado depende do tipo de agente e do problema que ele precisa resolver, mas os mais comuns são:

### 1. Árvores de decisão binárias (mais comuns)

Cada nó tem duas opções: verdadeiro/falso, sim/não.
Ideal para agentes reativos ou deliberativos simples, onde cada decisão é baseada em condições booleanas.

**Exemplo de uso:**
- Agente decide entre "andar" ou "parar" baseado na energia
- Agente decide "atacar" ou "fugir" baseado na proximidade de um inimigo

```
          [Energia > 50?]
              /     \
            Sim      Não
            /         \
       [Trabalhar]   [Dormir]
```

### 2. Árvores multi-ramo (não binárias)

Cada nó pode ter mais de duas opções (ex.: "pequeno", "médio", "grande").
Útil para agentes com várias ações possíveis.

**Exemplo de uso:**
- Agente decide qual tarefa executar: "coletar recurso", "explorar" ou "descansar"

```
         [Energia?]
       /     |      \
  Alta   Média    Baixa
   |       |       |
Trabalhar Explorar Dormir
```

### 3. Árvores de decisão recursivas (nível hierárquico)

Estrutura hierárquica com subárvores dentro de cada decisão.
Comum em agentes mais complexos ou planejadores automáticos.

**Exemplo de uso:**
- Agente recebe objetivo "Construir base"
- Subárvore 1: "Reunir recursos"
- Subárvore 2: "Montar defesas"
- Subárvore 3: "Treinar unidades"

```
          [Objetivo: Construir Base]
           /                |          \
   [Reunir Recursos] [Montar Defesa] [Treinar Unidades]
      /      \
 [Madeira] [Pedra]
```

### 4. Árvores de decisão + aprendizado

Quando o agente precisa aprender com experiência, usamos árvores como Decision Trees de aprendizado de máquina.
Elas ajudam a gerar regras automaticamente a partir de dados do ambiente.
Comum em agentes inteligentes adaptativos, como chatbots, jogos ou sistemas de recomendação.

### Resumo

| Tipo de Árvore | Uso em Agente de IA | Complexidade |
|----------------|---------------------|-------------|
| Binária | Decisões simples (sim/não) | Baixa |
| Multi-ramo | Múltiplas ações possíveis | Média |
| Recursiva / Subárvore | Planejamento hierárquico | Média-Alta |
| Aprendizado (Decision Tree ML) | Agente adaptativo, aprende com dados | Alta |

Na prática, a árvore de decisão binária é o ponto de partida para agentes simples. À medida que o agente precisa planejar ou aprender, a árvore pode evoluir para subárvores e árvores de aprendizado.

---

## Implementação em C++

### Estrutura de Nó em C++

Cada nó pode ser representado como uma struct ou classe:

```cpp
struct Node {
    std::string condicao;  // pergunta ou condição
    Node* sim;             // ponteiro para nó se condição for verdadeira
    Node* nao;             // ponteiro para nó se condição for falsa
    std::string acaoFinal; // preenchido se for folha
};
```

### Percorrer a Árvore de Decisão

```cpp
void percorrer(Node* node) {
    if (!node) return;
    if (!node->acaoFinal.empty()) {
        std::cout << "Ação: " << node->acaoFinal << std::endl;
        return;
    }
    if (avaliar(node->condicao)) // função que retorna true/false
        percorrer(node->sim);
    else
        percorrer(node->nao);
}
```

### Exemplo Completo em C++

```cpp
#include <iostream>
#include <string>
#include <memory>

// Estrutura do nó da árvore de decisão
struct DecisionNode {
    std::string condition;
    std::string action;
    std::shared_ptr<DecisionNode> yesBranch;
    std::shared_ptr<DecisionNode> noBranch;
    
    DecisionNode(const std::string& cond, const std::string& act = "")
        : condition(cond), action(act) {}
};

// Função para avaliar condições (simplificada)
bool evaluateCondition(const std::string& condition) {
    if (condition == "Energia > 50") return true;
    if (condition == "Inimigo perto") return false;
    return false;
}

// Função recursiva para percorrer a árvore
void makeDecision(std::shared_ptr<DecisionNode> node) {
    if (!node) return;
    
    // Se nó folha (tem ação), executa
    if (!node->action.empty()) {
        std::cout << "Agente decide: " << node->action << std::endl;
        return;
    }
    
    // Avalia condição e segue pelo ramo apropriado
    if (evaluateCondition(node->condition)) {
        std::cout << "Condição '" << node->condition << "' = VERDADEIRO" << std::endl;
        makeDecision(node->yesBranch);
    } else {
        std::cout << "Condição '" << node->condition << "' = FALSO" << std::endl;
        makeDecision(node->noBranch);
    }
}

int main() {
    // Construindo a árvore de decisão
    auto root = std::make_shared<DecisionNode>("Energia > 50");
    
    auto energiaAlta = std::make_shared<DecisionNode>("Inimigo perto");
    auto energiaBaixa = std::make_shared<DecisionNode>("", "Descansar");
    
    auto atacar = std::make_shared<DecisionNode>("", "Atacar");
    auto explorar = std::make_shared<DecisionNode>("", "Explorar");
    auto procurarComida = std::make_shared<DecisionNode>("", "Procurar comida");
    
    // Montando a estrutura
    root->yesBranch = energiaAlta;
    root->noBranch = energiaBaixa;
    
    energiaAlta->yesBranch = atacar;
    energiaAlta->noBranch = explorar;
    
    std::cout << "=== Iniciando Sistema de Decisão do Agente ===" << std::endl;
    makeDecision(root);
    
    return 0;
}
```

---

## Agentes Simples (Reativos)

Agente Simples (ou Agente Reativo Simples) é o tipo mais básico de inteligência artificial. Ele funciona sob a lógica: "Se acontecer X, faça Y".

Ele não tem memória, não planeja o futuro e não entende o histórico do que aconteceu antes. Ele apenas olha para o estado atual do mundo e reage a ele usando regras pré-definidas (regras de condição-ação).

### Como ele funciona?

O ciclo de vida de um agente simples é:
1. **Percepção**: O sensor capta uma informação do ambiente agora
2. **Processamento**: O agente procura uma regra que combine com essa informação
3. **Ação**: O atuador executa a tarefa

### Exemplo Clássico: O Termostato

Imagine um termostato inteligente que controla o ar-condicionado:
- **Sensor**: Termômetro (lê a temperatura atual)
- **Regra 1**: Se temperatura > 25°C, então Ligar Ar
- **Regra 2**: Se temperatura <= 25°C, então Desligar Ar
- **Atuador**: Interruptor do aparelho

Ele não sabe se estava quente há 5 minutos; ele só sabe que, agora, está 26°C e precisa ligar.

### Exemplo em Código (C++)

```cpp
#include <iostream>
#include <string>

using namespace std;

struct Ambiente {
    float temperatura;
};

class AgenteTermostato {
public:
    void agir(Ambiente atual) {
        if (atual.temperatura > 25.0) {
            cout << "Agente: Ta quente (" << atual.temperatura << "C). Ligando o ar!" << endl;
        } else {
            cout << "Agente: Temperatura ok (" << atual.temperatura << "C). Ar desligado." << endl;
        }
    }
};

int main() {
    Ambiente sala = {28.5}; // Estado atual do mundo
    AgenteTermostato robo;

    robo.agir(sala); // O agente percebe e reage
    return 0;
}
```

### Limitações

O agente simples falha se o ambiente for complexo. Por exemplo: um carro autônomo não pode ser um agente simples, porque ele não pode apenas "frear se vir algo vermelho" (pode ser apenas o pôr do sol ou uma placa, não um semáforo). Ele precisa de contexto e memória.

---

## Arquitetura de Agentes de IA em C++

Diferente do ecossistema Python (focado em prototipagem rápida), a arquitetura em C++ é escolhida para sistemas que exigem baixa latência, segurança de memória e alta performance (como robótica, sistemas embarcados ou engines de jogos).

### Camadas da Arquitetura (O "Blueprint")

Uma estrutura moderna de agente em C++ geralmente segue estas camadas:

1. **Orquestrador (O Cérebro)**: É o loop principal (State Machine). Ele recebe o objetivo, consulta o LLM e decide qual "ferramenta" chamar. Em C++, isso é feito com máquinas de estado robustas para evitar comportamentos erráticos.
2. **Camada de Percepção (Contexto)**: Gerencia a memória de curto prazo (janela de contexto) e longo prazo (banco de vetores ou bancos NoSQL).
3. **Abstração de Modelos (LLM Wrapper)**: Interfaces para se comunicar com APIs (OpenAI/Anthropic via libcurl) ou modelos locais (usando llama.cpp ou TensorRT-LLM).
4. **Executor de Ações (Tools)**: Funções C++ puras que o agente pode chamar para interagir com o sistema operacional, sistema de arquivos ou hardware.

### Padrões de Design Fundamentais

Para criar agentes escaláveis em C++, aplicamos padrões clássicos:

- **Strategy Pattern**: Para alternar dinamicamente entre diferentes modelos de IA (ex: usar um modelo leve para tarefas simples e um pesado para raciocínio complexo).
- **Command Pattern**: Cada ação que o agente decide tomar é encapsulada em um objeto Command. Isso permite criar um log de auditoria, "desfazer" ações e validar a segurança antes da execução.
- **Observer Pattern**: Útil para sistemas multi-agentes, onde um agente "observa" as mudanças de estado feitas por outro e reage conforme necessário.

### Componentes Técnicos Essenciais

- **Gerenciamento de Memória**: O uso de std::shared_ptr e std::unique_ptr (RAII) é crítico para garantir que o histórico do chat e os dados de contexto não causem vazamentos de memória durante execuções longas.
- **Serialização (JSON)**: Agentes conversam via JSON. Bibliotecas como nlohmann/json são o padrão de ouro para C++ processar as instruções estruturadas da IA.
- **Concorrência**: Agentes de IA são intensivos em I/O (esperando respostas de rede). O uso de std::async ou bibliotecas como Asio permite que o agente continue processando ou monitorando o ambiente enquanto aguarda o LLM.

---

## Exemplo de Estrutura de Agente em C++

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Interface para as ferramentas (Tools) que o agente pode usar
class Tool {
public:
    virtual ~Tool() = default;
    virtual std::string getName() = 0;
    virtual std::string execute(const std::string& input) = 0;
};

// Exemplo de uma ferramenta real: Leitor de Arquivos
class FileReadTool : public Tool {
public:
    std::string getName() override { return "read_file"; }
    std::string execute(const std::string& path) override {
        // Simulação de leitura de arquivo
        return "Conteudo do arquivo " + path + ": [Lógica do sistema em C++]";
    }
};

// O Coração do Agente
class AIAgent {
private:
    std::vector<std::unique_ptr<Tool>> tools;
    
    // Simula a chamada ao LLM (OpenAI, Anthropic ou Llama.cpp)
    std::string callLLM(const std::string& prompt) {
        // Na vida real, aqui você usaria libcurl para enviar um JSON 
        // e receberia uma sugestão de ferramenta ou resposta final.
        if (prompt.find("ler") != std::string::npos) {
            return "TOOL: read_file(config.txt)";
        }
        return "FINAL: O sistema está configurado corretamente.";
    }

public:
    void addTool(std::unique_ptr<Tool> tool) {
        tools.push_back(std::move(tool));
    }

    void run(const std::string& task) {
        std::string currentPrompt = task;
        bool goalReached = false;

        std::cout << "--- Iniciando Tarefa: " << task << " ---\n";

        while (!goalReached) {
            // 1. THINK: Pergunta ao LLM o que fazer
            std::string response = callLLM(currentPrompt);

            // 2. ACT: Verifica se o LLM quer usar uma ferramenta
            if (response.substr(0, 5) == "TOOL:") {
                std::cout << "[Agente Pensou]: " << response << "\n";
                
                // 3. EXECUTE: O C++ executa a ação no mundo real
                std::string result = tools[0]->execute("config.txt");
                
                // 4. OBSERVE: Adiciona o resultado ao contexto e repete
                std::cout << "[Sistema Executou]: " << result << "\n";
                currentPrompt += "\nResultado da ferramenta: " + result;
            } 
            else {
                // FINAL: O objetivo foi atingido
                std::cout << "[Agente Finalizou]: " << response << "\n";
                goalReached = true;
            }
        }
    }
};

int main() {
    AIAgent meuAgente;
    meuAgente.addTool(std::make_unique<FileReadTool>());

    meuAgente.run("Por favor, verifique o que está escrito no arquivo config.txt");

    return 0;
}
```

---

## Recursos e Links Úteis

### Artigos e Tutoriais em Português

- **Como funciona o algoritmo Árvore de Decisão** - Didática Tech
  - https://didatica.tech/como-funciona-o-algoritmo-arvore-de-decisao/
  
- **Árvores de decisão: modelos de classificação e regressão** - Alura
  - https://www.alura.com.br/artigos/arvores-de-decisao
  
- **Árvores de Decisão - Introdução ao Machine Learning** - Bookdown
  - https://bookdown.org/jessicakubrusly/intr-machine-learning-i/_book/cap-arvores.html
  
- **Aula Árvores de Decisão (UFPE)** - PDF técnico com regras básicas
  - https://cin.ufpe.br/~if684/EC/aulas/Aula-arvores-decisao-SI.pdf

### Vídeos em Português

- **Árvore de Decisão - explicação conceitual**
  - https://www.youtube.com/watch?v=W7MfsE5av0c
  
- **A Árvore de Decisão - Aprendizado**
  - https://www.youtube.com/watch?v=aNrdgC0lIZ8

### Artigo em Inglês com Implementação

- **Decision tree implementation tutorial (conceito + lógica)**
  - https://www.bestdivision.com/questions/what-is-a-decision-tree-algorithm-in-cpp-and-how-is-it-implemented

- **Decision tree introduction example - GeeksforGeeks**
  - https://www.geeksforgeeks.org/decision-tree-introduction-example/

---

## Conclusão

Árvores de decisão são estruturas fundamentais para implementar agentes de IA em C++. Elas fornecem:

- **Clareza**: Estrutura visual fácil de entender
- **Flexibilidade**: Podem ser adaptadas para diferentes tipos de decisões
- **Performance**: Implementação eficiente em C++
- **Escalabilidade**: Podem evoluir de simples binárias para sistemas complexos com aprendizado

Combinadas com padrões de design modernos e boas práticas de C++, árvores de decisão formam a base para sistemas de IA robustos e autônomos.

---

## Próximos Passos

Para continuar aprendendo:

1. **Implemente sua própria árvore de decisão** usando os exemplos de código
2. **Estude padrões de design** adicionais (State, Factory, Observer)
3. **Explore bancos de dados vetoriais** para memória de longo prazo
4. **Integre com LLMs** usando llama.cpp ou APIs REST
5. **Aprenda sobre concorrência** para agentes multi-tarefas

O caminho para criar agentes de IA completos envolve dominar não apenas árvores de decisão, mas também arquitetura de software, gerenciamento de memória e integração com modelos de linguagem.
