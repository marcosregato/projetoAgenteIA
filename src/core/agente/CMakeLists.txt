# CMakeLists.txt para core/agente/
add_library(agente Agente.cpp)

# Incluir headers
target_include_directories(agente PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Linkar dependências, se necessário
target_link_libraries(agente PRIVATE utils)