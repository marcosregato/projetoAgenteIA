# Encontrar arquivos de teste
file(GLOB TEST_SOURCES "*.cpp" "*/*.cpp")

# Criar executável de testes unitários (excluindo test_voice_engines)
list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test_voice_engines.cpp")
add_executable(unit_tests ${TEST_SOURCES})

# Criar executável de testes de voz
add_executable(test_voice_engines test_voice_engines.cpp)
add_executable(test_voice_simple test_voice_simple.cpp)
add_executable(test_image_processor test_image_processor.cpp)
add_executable(run_tests run_tests.cpp)

# Incluir diretório de headers para unit_tests
target_include_directories(unit_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${rapidjson_SOURCE_DIR}/include
)

# Incluir diretório de headers para test_voice_engines
target_include_directories(test_voice_engines PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${rapidjson_SOURCE_DIR}/include
)

# Incluir diretório de headers para test_voice_simple
target_include_directories(test_voice_simple PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${rapidjson_SOURCE_DIR}/include
)

# Incluir diretório de headers para run_tests
target_include_directories(run_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${rapidjson_SOURCE_DIR}/include
)

# Linkar unit_tests com Catch2 e dependências
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

# Linkar test_voice_engines com dependências
target_link_libraries(test_voice_engines PRIVATE 
    core
    utils
    core_utils
    falaRobotica
    arquivo
    agente
    llama
    ${OpenCV_LIBS}
    ${FLITE_LIB}
    ${FLITE_KAL_LIB}
    ${FLITE_M_LIB}
)

# Linkar run_tests com dependências
target_link_libraries(run_tests PRIVATE 
    core
    utils
    core_utils
    falaRobotica
    arquivo
    agente
    llama
    ${OpenCV_LIBS}
    ${FLITE_LIB}
    ${FLITE_KAL_LIB}
    ${FLITE_M_LIB}
)

# Descobrir testes unitários automaticamente
include(Catch)
catch_discover_tests(unit_tests)
