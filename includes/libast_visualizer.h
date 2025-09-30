/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libast_visualizer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:30:00 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 12:00:00 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBAST_VISUALIZER_H
# define LIBAST_VISUALIZER_H

# include <stdlib.h>
# include <stdio.h>

/* ============================================================================ */
/*                           BIBLIOTECA AST VISUALIZER                         */
/*                        Para integração com Minishell                        */
/* ============================================================================ */

/**
 * @brief Estrutura do nó da AST
 * Estrutura genérica para representar nós da árvore sintática abstrata
 */
typedef struct s_ast_node
{
    void                *data;          /* Dados do nó (comando, operador, etc.) */
    struct s_ast_node   *left;          /* Filho esquerdo */
    struct s_ast_node   *right;         /* Filho direito */
}   t_ast_node;

/**
 * @brief Handle para o visualizador
 * Estrutura opaca que mantém o estado interno do visualizador
 */
typedef struct s_ast_visualizer t_ast_visualizer;

/* ============================================================================ */
/*                              API PRINCIPAL                                  */
/* ============================================================================ */

/**
 * @brief Inicializa o visualizador de AST
 * @return Ponteiro para o visualizador ou NULL em caso de erro
 */
t_ast_visualizer *ast_visualizer_init(void);

/**
 * @brief Visualiza uma AST em uma janela gráfica
 * @param visualizer Visualizador inicializado
 * @param ast Árvore a ser visualizada
 * @param title Título da janela
 * @return 0 em sucesso, -1 em erro
 */
int ast_visualizer_show(t_ast_visualizer *visualizer, t_ast_node *ast, const char *title);

/**
 * @brief Libera recursos do visualizador
 * @param visualizer Visualizador a ser liberado
 */
void ast_visualizer_destroy(t_ast_visualizer *visualizer);

/* ============================================================================ */
/*                           CRIAÇÃO DE NODOS                                  */
/* ============================================================================ */

/**
 * @brief Cria um novo nó da AST
 * @param data Dados do nó (será copiado)
 * @return Novo nó ou NULL em caso de erro
 */
t_ast_node *ast_node_create(const char *data);

/**
 * @brief Cria um nó de comando
 * @param command String do comando
 * @return Novo nó de comando
 */
t_ast_node *ast_node_command(const char *command);

/**
 * @brief Cria um nó de pipe conectando dois nós
 * @param left Nó esquerdo
 * @param right Nó direito
 * @return Nó de pipe
 */
t_ast_node *ast_node_pipe(t_ast_node *left, t_ast_node *right);

/**
 * @brief Cria um nó de AND lógico (&&)
 * @param left Nó esquerdo
 * @param right Nó direito
 * @return Nó de AND
 */
t_ast_node *ast_node_and(t_ast_node *left, t_ast_node *right);

/**
 * @brief Cria um nó de OR lógico (||)
 * @param left Nó esquerdo
 * @param right Nó direito
 * @return Nó de OR
 */
t_ast_node *ast_node_or(t_ast_node *left, t_ast_node *right);

/**
 * @brief Cria um nó de redirecionamento
 * @param command Comando a ser redirecionado
 * @param redirect String de redirecionamento (>, >>, <, etc.)
 * @return Nó de redirecionamento
 */
t_ast_node *ast_node_redirect(t_ast_node *command, const char *redirect);

/* ============================================================================ */
/*                         FUNÇÕES DE CONVENIÊNCIA                             */
/* ============================================================================ */

/**
 * @brief Cria automaticamente um pipe entre dois comandos
 * @param cmd1 Primeiro comando
 * @param cmd2 Segundo comando
 * @return AST com pipe ou NULL em erro
 */
t_ast_node *ast_quick_pipe(const char *cmd1, const char *cmd2);

/**
 * @brief Cria automaticamente um AND entre dois comandos
 * @param cmd1 Primeiro comando
 * @param cmd2 Segundo comando
 * @return AST com AND ou NULL em erro
 */
t_ast_node *ast_quick_and(const char *cmd1, const char *cmd2);

/**
 * @brief Cria automaticamente um OR entre dois comandos
 * @param cmd1 Primeiro comando
 * @param cmd2 Segundo comando
 * @return AST com OR ou NULL em erro
 */
t_ast_node *ast_quick_or(const char *cmd1, const char *cmd2);

/* ============================================================================ */
/*                          GERENCIAMENTO DE MEMÓRIA                           */
/* ============================================================================ */

/**
 * @brief Libera uma AST completa
 * @param ast Raiz da árvore a ser liberada
 */
void ast_node_destroy(t_ast_node *ast);

/**
 * @brief Duplica uma AST
 * @param ast AST a ser duplicada
 * @return Nova AST ou NULL em erro
 */
t_ast_node *ast_node_duplicate(const t_ast_node *ast);

/* ============================================================================ */
/*                              UTILITÁRIOS                                    */
/* ============================================================================ */

/**
 * @brief Imprime a AST em formato textual (debug)
 * @param ast AST a ser impressa
 * @param depth Profundidade inicial (geralmente 0)
 */
void ast_node_print(const t_ast_node *ast, int depth);

/**
 * @brief Conta o número de nós na AST
 * @param ast AST a ser contada
 * @return Número de nós
 */
int ast_node_count(const t_ast_node *ast);

/**
 * @brief Calcula a altura da AST
 * @param ast AST a ser medida
 * @return Altura da árvore
 */
int ast_node_height(const t_ast_node *ast);

/* ============================================================================ */
/*                              EXEMPLOS DE USO                                */
/* ============================================================================ */

/**
 * @brief Cria um exemplo simples para teste
 * @return AST de exemplo
 */
t_ast_node *ast_create_example_simple(void);

/**
 * @brief Cria um exemplo complexo para teste
 * @return AST de exemplo complexo
 */
t_ast_node *ast_create_example_complex(void);

#endif