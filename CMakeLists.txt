cmake_minimum_required(VERSION 3.14)
project(projetoAgenteIA CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")

include(FetchContent)


# --- 1. Encontrar dependências do sistema ---
# Tentar encontrar OpenCV no sistema
find_package(OpenCV QUIET COMPONENTS core imgproc imgcodecs highgui videoio face)

if(NOT OpenCV_FOUND)
  message(STATUS "OpenCV não encontrado no sistema. Baixando e compilando OpenCV...")
  
  # Baixar OpenCV usando FetchContent
  FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG 4.6.0
  )
  
  # Baixar OpenCV contrib (opcional, para funcionalidades extras)
  FetchContent_Declare(
    opencv_contrib
    GIT_REPOSITORY https://github.com/opencv/opencv_contrib.git
    GIT_TAG 4.6.0
  )
  
  # Configurar variáveis para o build do OpenCV
  set(OPENCV_EXTRA_MODULES_PATH ${opencv_contrib_SOURCE_DIR}/modules CACHE PATH "Path to OpenCV contrib modules")
  set(BUILD_opencv_face ON CACHE BOOL "Build face module")
  set(BUILD_opencv_highgui ON CACHE BOOL "Build highgui module")
  set(BUILD_opencv_videoio ON CACHE BOOL "Build videoio module")
  set(BUILD_opencv_imgcodecs ON CACHE BOOL "Build imgcodecs module")
  set(BUILD_opencv_imgproc ON CACHE BOOL "Build imgproc module")
  set(BUILD_opencv_core ON CACHE BOOL "Build core module")
  set(BUILD_TESTS OFF CACHE BOOL "Build tests")
  set(BUILD_PERF_TESTS OFF CACHE BOOL "Build performance tests")
  set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples")
  set(BUILD_DOCS OFF CACHE BOOL "Build documentation")
  set(WITH_CUDA OFF CACHE BOOL "Build with CUDA support")
  set(WITH_OPENMP ON CACHE BOOL "Build with OpenMP support")
  
  # Baixar e configurar OpenCV
  FetchContent_MakeAvailable(opencv)
  FetchContent_MakeAvailable(opencv_contrib)
  
  # Encontrar novamente após o download
  find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs highgui videoio face)
endif()

# Verificação final do OpenCV
if(OpenCV_FOUND)
  message(STATUS "OpenCV encontrado: versão ${OpenCV_VERSION}")
  message(STATUS "OpenCV include: ${OpenCV_INCLUDE_DIRS}")
  message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
else()
  message(FATAL_ERROR "OpenCV não encontrado mesmo após tentativa de download!")
endif()
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
  message(STATUS "eSpeak-ng não encontrado no sistema. Baixando e compilando eSpeak-ng...")
  
  # Baixar eSpeak-ng usando FetchContent
  FetchContent_Declare(
    espeak-ng
    GIT_REPOSITORY https://github.com/espeak-ng/espeak-ng.git
    GIT_TAG master
  )
  
  # Configurar variáveis para o build do eSpeak-ng
  set(BUILD_TESTS OFF CACHE BOOL "Build tests")
  set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")
  set(USE_ASYNC OFF CACHE BOOL "Use async audio")
  
  # Baixar e configurar eSpeak-ng
  FetchContent_MakeAvailable(espeak-ng)
  
  # Tentar encontrar novamente após o download
  find_path(ESPEAK_INCLUDE_DIR
    NAMES speak_lib.h
    PATHS ${espeak-ng_SOURCE_DIR}/include
    NO_DEFAULT_PATH
  )
  find_library(ESPEAK_LIB
    NAMES espeak-ng
    PATHS ${espeak-ng_SOURCE_DIR}/lib
    NO_DEFAULT_PATH
  )
  
  if(ESPEAK_INCLUDE_DIR AND ESPEAK_LIB)
    set(ESPEAK_FOUND TRUE)
    message(STATUS "eSpeak-ng baixado e compilado com sucesso!")
    message(STATUS "eSpeak-ng include: ${ESPEAK_INCLUDE_DIR}")
    message(STATUS "eSpeak-ng lib: ${ESPEAK_LIB}")
    add_definitions(-DHAS_ESPEAK=1)
  else()
    message(WARNING "Falha ao baixar e compilar eSpeak-ng. Português por eSpeak ficará desativado.")
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

# whisper.cpp (reconhecimento de fala)
FetchContent_Declare(
  whisper.cpp
  GIT_REPOSITORY https://github.com/ggerganov/whisper.cpp
  GIT_TAG        master
)
FetchContent_MakeAvailable(whisper.cpp)

# --- 3. Configuração de Testes ---
enable_testing()

# --- 4. Adicionar a lista de Modelos para download ---
set(MODEL_LIST
    "Llama-3.2-1B-Instruct-Q4_K_M.gguf|https://huggingface.co"
    "Phi-3.5-mini-instruct-Q4_K_M.gguf|https://huggingface.co"
    "qwen2.5-0.5b-instruct-q5_k_m.gguf|https://huggingface.co"
    "lbfmodel.yaml|https://raw.githubusercontent.com/k_sh_sh/face_landmark_detection/master/lbfmodel.yaml"
    "base.en.bin|https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-base.en.bin"
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
