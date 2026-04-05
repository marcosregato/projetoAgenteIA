#ifndef LOGSISTEMA_H_INCLUDED
#define LOGSISTEMA_H_INCLUDED

#include <string>

class LogSistema{

public:
    int criarArquivoLog();
    int logInfo(const std::string &mensagem);
    int logError(const std::string &mensagem);
    int logDebug(const std::string &mensagem);

private:
    int writeEntry(const std::string &nivel, const std::string &mensagem);
};

#endif
