cmake_minimum_required(VERSION 3.29)
project(linguagem_maximus C)

set(CMAKE_C_STANDARD 11)

# Adiciona o executável e os arquivos necessários
add_executable(linguagem_maximus
        main.c
        lexico.c
)

# Inclui os diretórios que contêm os cabeçalhos
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
