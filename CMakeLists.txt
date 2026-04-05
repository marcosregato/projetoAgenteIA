cmake_minimum_required(VERSION 3.14)
project(projetoAgenteIA CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# --- 1. Encontrar dependências do sistema ---
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs highgui videoio face)
find_library(FLITE_LIB flite REQUIRED)
find_library(FLITE_KAL_LIB flite_cmu_us_kal)
find_library(FLITE_SLT_LIB flite_cmu_us_slt REQUIRED)
find_library(FLITE_M_LIB m REQUIRED)

find_path(ESPEAK_INCLUDE_DIR
  NAMES speak_lib.h
  PATH_SUFFIXES espeak-ng espeak
  PATHS /usr /usr/local /opt/homebrew
)
find_library(ESPEAK_LIB
  NAMES espeak-ng espeak
  PATHS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu /usr/lib64
)
if(ESPEAK_INCLUDE_DIR AND ESPEAK_LIB)
  set(ESPEAK_FOUND TRUE)
  message(STATUS "Encontrado espeak-ng: include=${ESPEAK_INCLUDE_DIR}, lib=${ESPEAK_LIB}")
  add_definitions(-DHAS_ESPEAK=1)
else()
  set(ESPEAK_FOUND FALSE)
  if(NOT ESPEAK_INCLUDE_DIR)
    message(WARNING "Espeak-ng header não encontrado. Português por eSpeak ficará desativado.")
  endif()
  if(NOT ESPEAK_LIB)
    message(WARNING "Biblioteca espeak-ng não encontrada.")
  endif()
endif()

# --- 2. Download das Dependências ---

# Catch2 (biblioteca de teste unitário)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# RapidJSON (biblioteca JSON)
FetchContent_Declare(
  rapidjson
  GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
  GIT_TAG master
)
FetchContent_MakeAvailable(rapidjson)

# llama.cpp (integração de modelo de IA)
FetchContent_Declare(
  llama.cpp
  GIT_REPOSITORY https://github.com/ggml-org/llama.cpp
  GIT_TAG        master
)
FetchContent_MakeAvailable(llama.cpp)

# --- 3. Configuração de Testes ---
enable_testing()

# --- 4. Adicionar a lista de Modelos para download ---
set(MODEL_LIST
    "Llama-3.2-1B-Instruct-Q4_K_M.gguf|https://huggingface.co"
    "Phi-3.5-mini-instruct-Q4_K_M.gguf|https://huggingface.co"
    "qwen2.5-0.5b-instruct-q5_k_m.gguf|https://huggingface.co"
)

set(MODEL_DIR "${CMAKE_BINARY_DIR}/models")
file(MAKE_DIRECTORY ${MODEL_DIR})

foreach(MODEL_ENTRY IN LISTS MODEL_LIST)
    string(REPLACE "|" ";" MODEL_PAR "${MODEL_ENTRY}")
    list(GET MODEL_PAR 0 MODEL_NAME)
    list(GET MODEL_PAR 1 MODEL_URL)
    
    set(DEST_PATH "${MODEL_DIR}/${MODEL_NAME}")

    if(NOT EXISTS "${DEST_PATH}")
        message(STATUS "Baixando modelo: ${MODEL_NAME}...")
        file(DOWNLOAD "${MODEL_URL}" "${DEST_PATH}"
             SHOW_PROGRESS
             TIMEOUT 1200
             STATUS DOWNLOAD_STATUS
        )
        list(GET DOWNLOAD_STATUS 0 ERR_CODE)
        if(NOT ERR_CODE EQUAL 0)
            message(WARNING "Falha ao baixar ${MODEL_NAME}. Erro: ${ERR_CODE}")
        endif()
    else()
        message(STATUS "Modelo já existe: ${MODEL_NAME}")
    endif()
endforeach()

# --- 5. Adicionar subdireórios ---
add_subdirectory(src)
add_subdirectory(tests)
