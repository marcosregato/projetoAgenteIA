# Seleção de Motor de Voz (SintetizadorVoz)

## Visão Geral

O sistema agora suporta dois motores de síntese de voz:
- **Flite**: Para síntese em inglês
- **eSpeak-ng**: Para síntese em português

## Enum MotorVoz

```cpp
enum class MotorVoz {
    FLITE,      // Usa Flite (inglês)
    ESPEAK_NG   // Usa eSpeak-ng (português)
};
```

## Construtores

### Construtor Padrão
```cpp
SintetizadorVoz tts; // Usa Flite por padrão
```

### Construtor com Motor Específico
```cpp
SintetizadorVoz tts(MotorVoz::ESPEAK_NG); // Usa eSpeak-ng
```

## Métodos Principais

### setMotorVoz()
Define qual motor de voz usar:
```cpp
tts.setMotorVoz(MotorVoz::FLITE);      // Mudar para Flite
tts.setMotorVoz(MotorVoz::ESPEAK_NG);   // Mudar para eSpeak-ng
```

### getMotorAtual()
Retorna o motor atualmente selecionado:
```cpp
MotorVoz motor = tts.getMotorAtual();
if (motor == MotorVoz::ESPEAK_NG) {
    std::cout << "Usando eSpeak-ng" << std::endl;
}
```

### inicializar()
Inicializa o motor selecionado:
```cpp
bool sucesso = tts.inicializar();
if (sucesso) {
    std::cout << "Motor inicializado com sucesso!" << std::endl;
}
```

### Métodos de Fala

#### falar()
Usa o motor selecionado automaticamente:
```cpp
tts.falar("Hello World"); // Se Flite estiver ativo, fala em inglês
tts.falar("Olá Mundo");  // Se eSpeak-ng estiver ativo, fala em português
```

#### falarIngles()
Força o uso do Flite (independentemente do motor selecionado):
```cpp
tts.falarIngles("Hello! This is English text.");
```

#### falarPortugues()
Força o uso do eSpeak-ng (independentemente do motor selecionado):
```cpp
tts.falarPortugues("Olá! Este é texto em português.");
```

## Exemplo de Uso Completo

```cpp
#include "falaRobotica/SintetizadorVoz.h"

int main() {
    // Criar sintetizador com Flite (padrão)
    SintetizadorVoz tts;
    tts.inicializar();
    
    // Falar em inglês com Flite
    tts.falar("Hello! This is Flite speaking.");
    
    // Mudar para eSpeak-ng
    tts.setMotorVoz(MotorVoz::ESPEAK_NG);
    tts.inicializar();
    
    // Falar em português com eSpeak-ng
    tts.falar("Olá! Este é o eSpeak-ng falando.");
    
    // Verificar motor atual
    if (tts.getMotorAtual() == MotorVoz::ESPEAK_NG) {
        std::cout << "Motor atual: eSpeak-ng" << std::endl;
    }
    
    return 0;
}
```

## Comportamento

- **Mudança de Motor**: Quando `setMotorVoz()` é chamado, os estados de inicialização são resetados
- **Inicialização Automática**: Os métodos de fala chamam `inicializar()` automaticamente se necessário
- **Verificação de Motor**: Métodos específicos verificam se o motor correto está selecionado
- **Fallback**: Se um motor não estiver disponível, mensagens de erro são registradas

## Logs

O sistema registra informações detalhadas sobre:
- Inicialização dos motores
- Mudanças de motor
- Erros de inicialização
- Falhas na síntese

## Dependências

- **Flite**: Requer `libflite-dev` e bibliotecas de voz
- **eSpeak-ng**: Requer `espeak-ng-dev` e bibliotecas de áudio
- **Configuração Automática**: O CMake baixa e compila dependências se não encontradas
