cmake_minimum_required(VERSION 3.27)
project(trabalho_aed_3_bruna_andre C)

set(CMAKE_C_STANDARD 99)

add_executable(trabalho_aed_3_bruna_andre main.c
        cabecalho_dados.c
        cabecalho_indices.c
        lote.h
        lote.c
        produto.h
        produto_atualizacao.c
        produto_impressao.c
        produto_insercao.c
        produto_remocao.c
        file.c
        menu.c
        produto_insercao.h
        produto_remocao.h
        produto_atualizacao.h
        produto_impressao.h
        menu.c
        arvore_utils.c
        arvore_utils.h
)
