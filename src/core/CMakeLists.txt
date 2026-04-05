# CMakeLists.txt para core/
add_subdirectory(utils)
add_subdirectory(arquivo)
add_subdirectory(agente)
add_subdirectory(falaRobotica)

add_library(core inference_engine.cpp)

# Incluir headers
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Linkar dependências, se necessário
target_link_libraries(core PRIVATE core_utils arquivo agente falaRobotica llama ${OpenCV_LIBS})
