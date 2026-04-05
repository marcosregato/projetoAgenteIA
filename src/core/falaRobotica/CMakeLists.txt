# CMakeLists.txt para core/falaRobotica/
add_library(falaRobotica SintetizadorVoz.cpp)

# Incluir headers
target_include_directories(falaRobotica PUBLIC ${CMAKE_SOURCE_DIR}/include)
if(ESPEAK_FOUND)
  target_include_directories(falaRobotica PUBLIC ${ESPEAK_INCLUDE_DIR})
  target_compile_definitions(falaRobotica PRIVATE HAS_ESPEAK=1)
else()
  target_compile_definitions(falaRobotica PRIVATE HAS_ESPEAK=0)
endif()

# Linkar dependências, se necessário
target_link_libraries(falaRobotica PRIVATE ${FLITE_LIB} ${FLITE_KAL_LIB} ${FLITE_SLT_LIB} ${FLITE_M_LIB})
if(ESPEAK_FOUND)
  target_link_libraries(falaRobotica PRIVATE ${ESPEAK_LIB})
endif()
