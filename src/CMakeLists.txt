# CMakeLists.txt para src/
add_subdirectory(core)
add_subdirectory(utils)

# Criar executável principal
add_executable(projetoAgenteIA main.cpp)

# Incluir diretório de headers
target_include_directories(projetoAgenteIA PRIVATE ${CMAKE_SOURCE_DIR}/include ${rapidjson_SOURCE_DIR}/include)

# Linkar com bibliotecas dos submódulos e externas
target_link_libraries(projetoAgenteIA PRIVATE core utils core_utils falaRobotica llama ${OpenCV_LIBS} ${FLITE_LIB} ${FLITE_KAL_LIB} ${FLITE_M_LIB})