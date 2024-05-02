#include <stdio.h>
#include "file/file.h"
#include "menu/menu.h"

// adicione comentários no seguinte formato:
// Descreva o que a função faz
// Pré-condições: o que é necessário para que a função possa ser chamada
// Pós-condição: o que a função deve retornar

// Função principal do programa.
// Pré-condição: nenhuma.
// Pós-condição: O programa é executado, interagindo com o usuário por meio do menu principal.
//               Os arquivos são abertos e verificados para garantir a consistência do sistema.
//               Ao final, os arquivos são fechados antes da conclusão do programa.
int main() {
    // Estrutura para armazenar os arquivos necessários.
    ARQUIVOS files;

    // Verifica a existência e integridade dos arquivos, abrindo-os se necessário.
    verificar_arquivos(&files);

    // Executa a função com as opções do menu disponíveis
    menu_principal(files);

    // Fecha os arquivos ao final da execução do programa.
    fechar_arquivos(&files);

    // Indica a conclusão bem-sucedida do programa.
    return 0;
}
