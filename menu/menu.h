#ifndef MENU_H
#define MENU_H

#include "../file/file.h"

// Exibe o cabeçalho do menu
// Pré-condições: Nenhuma
// Pós-condições: O cabeçalho do menu é exibido no console
void header_menu();

// Cadastra um novo produto
// Pré-condições: Nenhuma
// Pós-condições: Um novo produto é cadastrado
void cadastrarProduto(ARQUIVOS files);

// Remove um produto existente
// Pré-condições: O produto a ser removido deve existir no cadastro
// Pós-condições: O produto é removido do cadastro
void removerProduto();

// Atualiza o preço de um produto
// Pré-condições: O produto a ser atualizado deve existir no cadastro
// Pós-condições: O preço do produto é atualizado
void atualizarPreco();

// Atualiza o estoque de um produto
// Pré-condições: O produto a ser atualizado deve existir no cadastro
// Pós-condições: O estoque do produto é atualizado
void atualizarEstoque();

// Imprime as informações de um produto específico
// Pré-condições: O produto cujas informações serão impressas deve existir no cadastro
// Pós-condições: As informações do produto são impressas no console
void imprimirInformacoes(ARQUIVOS files);

// Imprime a lista de todos os produtos cadastrados
// Pré-condições: Nenhuma
// Pós-condições: A lista de todos os produtos é impressa no console
void imprimirListaProdutos();

// Imprime a árvore de produtos
// Pré-condições: Nenhuma
// Pós-condições: A árvore de produtos é impressa no console
void imprimirArvore();

// Imprime a lista de nós livres do arquivo de índices
// Pré-condições: Nenhuma
// Pós-condições: A lista de nós livres do arquivo de índices é impressa no console
void imprimirListaLivresIndices();

// Imprime a lista de registros livres do arquivo de dados
// Pré-condições: Nenhuma
// Pós-condições: A lista de registros livres do arquivo de dados é impressa no console
void imprimirListaLivresDados();

// Realiza operações em lote a partir de um arquivo de texto
// Pré-condições: O arquivo de texto contendo as operações em lote deve existir e estar formatado corretamente
// Pós-condições: As operações em lote são executadas
void realizarOperacoesEmLote();

// Exibe o menu principal e processa a escolha do usuário
// Pré-condições: Nenhuma
// Pós-condições: O usuário escolhe uma opção do menu e a operação correspondente é executada
void menu_principal(ARQUIVOS files);

#endif // MENU_H
