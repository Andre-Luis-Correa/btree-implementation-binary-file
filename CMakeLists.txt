cmake_minimum_required(VERSION 3.27)
project(trabalho_aed_3_bruna_andre C)

set(CMAKE_C_STANDARD 99)

add_executable(trabalho_aed_3_bruna_andre main.c
        cabecalho/cabecalho_dados.c
        cabecalho/cabecalho_indices.c
        lote/lote.h
        lote/lote.c
        utils/mainB.c
        produto/produto.h
        atualizacao/produto_atualizacao.c
        impressao/produto_impressao.c
        insercao/produto_insercao.c
        remocao/produto_remocao.c
        file/file.c
        menu/menu.c
        insercao/produto_insercao.h
        remocao/produto_remocao.h
        atualizacao/produto_atualizacao.h
        impressao/produto_impressao.h
        menu/menu.c
        utils/arvore_utils.c
        utils/arvore_utils.h
        utils/exemplo_rem.c
        utils/exemploooremocao.c)
