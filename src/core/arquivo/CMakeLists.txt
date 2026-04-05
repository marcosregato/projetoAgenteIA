# CMakeLists.txt para core/arquivo/
add_library(arquivo ManipularArquivo.cpp)

# Incluir headers
target_include_directories(arquivo PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Suprimir warnings de deprecated iterator do RapidJSON
target_compile_options(arquivo PRIVATE -Wno-deprecated-declarations)

# Linkar dependências, se necessário
# target_link_libraries(arquivo PRIVATE ...)