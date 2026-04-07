#pragma once

enum class StatusSaida {
    SUCESSO = 0,
    ERRO_NO_METODO = 1,
    ERRO_CONEXAO_REDE = 2,
    ERRO_MEMORIA_INSUFICIENTE = 3,
    ERRO_IF_ELSE = 4
};

inline int paraInt(StatusSaida s) {
    return static_cast<int>(s);
}
