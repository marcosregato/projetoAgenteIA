# Encontrar arquivos de teste
file(GLOB TEST_SOURCES "*.cpp" "*/*.cpp")

# Criar executável de testes
add_executable(unit_tests ${TEST_SOURCES})

# Incluir diretório de headers
target_include_directories(unit_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${rapidjson_SOURCE_DIR}/include
)

# Linkar com Catch2 e dependências
target_link_libraries(unit_tests PRIVATE 
    Catch2::Catch2WithMain
    core
    utils
    core_utils
    falaRobotica
    llama
    ${OpenCV_LIBS}
    ${FLITE_LIB}
    ${FLITE_KAL_LIB}
    ${FLITE_M_LIB}
)

# Descobrir testes automaticamente
include(Catch)
catch_discover_tests(unit_tests)
