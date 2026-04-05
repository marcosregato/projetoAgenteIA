# CMakeLists.txt para core/utils/
add_library(core_utils LogSistema.cpp VerificarArquivo.cpp)

# Incluir headers
target_include_directories(core_utils PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Linkar dependências, se necessário
target_link_libraries(core_utils PRIVATE ${OpenCV_LIBS})