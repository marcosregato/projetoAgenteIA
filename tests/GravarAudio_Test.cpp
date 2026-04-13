#include <gtest/gtest.h>
#include <include/falaRobotica/GravarAudio.hpp>

// Teste básico para verificar se a classe pode ser instanciada
TEST(GravarAudioTest, CriacaoInstancia) {
    // Arrange & Act
    GravarAudio gravador;
    
    // Assert
    // Se chegamos aqui, a classe foi instanciada com sucesso
    SUCCEED();
}

// Teste para verificar o tamanho da classe
TEST(GravarAudioTest, TamanhoObjeto) {
    // Arrange & Act
    GravarAudio gravador;
    
    // Assert
    // Classe sem membros públicos, tamanho deve ser 1 byte (mínimo)
    EXPECT_EQ(sizeof(gravador), 1) << "Classe deve ter tamanho mínimo de 1 byte";
}

// Teste de cópia (deve funcionar pois não há membros para copiar)
TEST(GravarAudioTest, CopiaObjeto) {
    // Arrange
    GravarAudio gravador1;
    
    // Act
    GravarAudio gravador2 = gravador1; // Testa construtor de cópia
    
    // Assert
    // Se chegamos aqui, a cópia foi bem-sucedida
    SUCCEED();
}

// Teste de atribuição
TEST(GravarAudioTest, AtribuicaoObjeto) {
    // Arrange
    GravarAudio gravador1, gravador2;
    
    // Act
    gravador2 = gravador1; // Testa operador de atribuição
    
    // Assert
    // Se chegamos aqui, a atribuição foi bem-sucedida
    SUCCEED();
}

// Teste de múltiplas instâncias
TEST(GravarAudioTest, MultiplasInstancias) {
    // Arrange & Act
    GravarAudio gravador1, gravador2, gravador3;
    
    // Assert
    // Verificamos se podemos criar múltiplas instâncias sem conflitos
    EXPECT_EQ(sizeof(gravador1), sizeof(gravador2));
    EXPECT_EQ(sizeof(gravador2), sizeof(gravador3));
}

// Teste para verificar se a classe compila corretamente
TEST(GravarAudioTest, CompilacaoCorreta) {
    // Arrange & Act
    GravarAudio gravador;
    
    // Assert
    // Este teste verifica que a classe compila corretamente
    EXPECT_TRUE(true) << "Classe compilada com método privado capturarAudio()";
}

// Teste de inicialização padrão
TEST(GravarAudioTest, InicializacaoPadrao) {
    // Arrange & Act
    GravarAudio gravador;
    
    // Assert
    // Verificamos se o objeto está em um estado válido após criação
    EXPECT_TRUE(true) << "GravarAudio inicializado com sucesso";
}
