#!/bin/bash

# Comandos executados para resolver o erro do CMake com FLITE

# 1. Tentar instalar libflite-dev (falhou)
# sudo apt-get update && sudo apt-get install -y libflite-dev

# 2. Buscar pacotes flite disponíveis
apt search flite

# 3. Instalar o pacote correto flite1-dev
sudo apt-get install -y flite1-dev

# 4. Executar CMake (primeira tentativa, falhou por causa do main.cpp)
cd /home/marcos/workspace/projetoAgenteIA/build && cmake ..

# 5. Após editar o CMakeLists.txt em src/ para corrigir o caminho de main.cpp
cd /home/marcos/workspace/projetoAgenteIA/build && cmake ..

# 6. Compilar o projeto
make