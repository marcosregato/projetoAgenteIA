# CMakeLists.txt para utils/
add_library(utils image_processor.cpp)

# Incluir headers
target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS})

# Linkar dependências
target_link_libraries(utils PRIVATE ${OpenCV_LIBS})