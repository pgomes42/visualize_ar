/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_adapter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:50:00 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 11:24:37 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer_ar.h"

/* ============================================================================ */
/*                        FUNÇÕES AUXILIARES PARA TIPOS                        */
/* ============================================================================ */

/**
 * Cria um ponteiro para inteiro (para manter compatibilidade)
 * @param value: valor inteiro
 * @return: ponteiro para o valor alocado
 */
void *create_int_data(int value)
{
    int *data;
    
    data = (int *)malloc(sizeof(int));
    if (!data)
        return (NULL);
    *data = value;
    return (data);
}

/**
 * Cria um ponteiro para string
 * @param str: string a ser copiada
 * @return: ponteiro para a string alocada
 */
void *create_string_data(const char *str)
{
    char *data;
    
    if (!str)
        return (NULL);
    data = (char *)malloc(strlen(str) + 1);
    if (!data)
        return (NULL);
    strcpy(data, str);
    return (data);
}

/* ============================================================================ */
/*                        FUNÇÕES DE CRIAÇÃO AUTOMÁTICA DE AST                 */
/* ============================================================================ */

/**
 * Cria um nó AST básico
 * @param data: ponteiro genérico para os dados do nó
 * @return: ponteiro para o novo nó AST
 */
t_ast *ast_create_node(void *data)
{
    t_ast *node;

    node = (t_ast *)malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

/**
 * Cria uma AST para comando simples
 * @param cmd_data: dados genéricos do comando
 * @return: ponteiro para a AST do comando
 */
t_ast *ast_create_command(void *cmd_data)
{
    return (ast_create_node(cmd_data));
}

/**
 * Cria uma AST para pipe (|)
 * @param left_cmd: comando da esquerda
 * @param right_cmd: comando da direita
 * @return: ponteiro para a AST do pipe
 */
t_ast *ast_create_pipe(t_ast *left_cmd, t_ast *right_cmd)
{
    t_ast *pipe_node;

    pipe_node = ast_create_node(create_string_data("|")); 
    if (!pipe_node)
        return (NULL);
    pipe_node->left = left_cmd;
    pipe_node->right = right_cmd;
    return (pipe_node);
}

/**
 * Cria uma AST para operador AND (&&)
 * @param left_expr: expressão da esquerda
 * @param right_expr: expressão da direita
 * @return: ponteiro para a AST do AND
 */
t_ast *ast_create_and(t_ast *left_expr, t_ast *right_expr)
{
    t_ast *and_node;

    and_node = ast_create_node(create_string_data("&&")); /* Operador AND */
    if (!and_node)
        return (NULL);
    and_node->left = left_expr;
    and_node->right = right_expr;/* Operador pipe */
    return (and_node);
}

/**
 * Cria uma AST para operador OR (||)
 * @param left_expr: expressão da esquerda
 * @param right_expr: expressão da direita
 * @return: ponteiro para a AST do OR
 */
t_ast *ast_create_or(t_ast *left_expr, t_ast *right_expr)
{
    t_ast *or_node;

    or_node = ast_create_node(create_string_data("||")); /* Operador OR */
    if (!or_node)
        return (NULL);
    or_node->left = left_expr;
    or_node->right = right_expr;
    return (or_node);
}

/**
 * Cria uma AST para redirecionamento
 * @param cmd: comando base
 * @param redirect_data: dados do redirecionamento
 * @return: ponteiro para a AST do redirecionamento
 */
t_ast *ast_create_redirect(t_ast *cmd, void *redirect_data)
{
    t_ast *redirect_node;

    (void)redirect_data; /* Suprimir warning de parâmetro não usado */
    redirect_node = ast_create_node(create_string_data(">")); /* Operador redirecionamento */
    if (!redirect_node)
        return (NULL);
    redirect_node->left = cmd;
    redirect_node->right = NULL; /* ou ponteiro para arquivo/target */
    return (redirect_node);
}

/**
 * Cria uma AST para subshell ()
 * @param inner_ast: AST interna do subshell
 * @return: ponteiro para a AST do subshell
 */
t_ast *ast_create_subshell(t_ast *inner_ast)
{
    t_ast *subshell_node;

    subshell_node = ast_create_node(create_string_data("()")); /* Operador subshell */
    if (!subshell_node)
        return (NULL);
    subshell_node->left = inner_ast;
    subshell_node->right = NULL;
    return (subshell_node);
}

/* ============================================================================ */
/*                        FUNÇÕES DE CRIAÇÃO AUTOMÁTICA PARA MINISHELL        */
/* ============================================================================ */

/**
 * Cria automaticamente uma AST para: cmd1 | cmd2
 * @param cmd1_data: dados do primeiro comando
 * @param cmd2_data: dados do segundo comando
 * @return: AST completa do pipe
 */
t_ast *ast_auto_pipe(void *cmd1_data, void *cmd2_data)
{
    t_ast *cmd1;
    t_ast *cmd2;

    cmd1 = ast_create_command(cmd1_data);
    cmd2 = ast_create_command(cmd2_data);
    if (!cmd1 || !cmd2)
    {
        if (cmd1) ft_clear_ast(cmd1);
        if (cmd2) ft_clear_ast(cmd2);
        return (NULL);
    }
    return (ast_create_pipe(cmd1, cmd2));
}

/**
 * Cria automaticamente uma AST para: cmd1 && cmd2
 * @param cmd1_data: dados do primeiro comando
 * @param cmd2_data: dados do segundo comando
 * @return: AST completa do AND/* Operador pipe */
 */
t_ast *ast_auto_and(void *cmd1_data, void *cmd2_data)
{
    t_ast *cmd1;
    t_ast *cmd2;

    cmd1 = ast_create_command(cmd1_data);
    cmd2 = ast_create_command(cmd2_data);
    if (!cmd1 || !cmd2)
    {
        if (cmd1) ft_clear_ast(cmd1);
        if (cmd2) ft_clear_ast(cmd2);
        return (NULL);
    }
    return (ast_create_and(cmd1, cmd2));
}

/**
 * Cria automaticamente uma AST para: cmd1 || cmd2
 * @param cmd1_data: dados do primeiro comando
 * @param cmd2_data: dados do segundo comando
 * @return: AST completa do OR
 */
t_ast *ast_auto_or(void *cmd1_data, void *cmd2_data)
{
    t_ast *cmd1;
    t_ast *cmd2;

    cmd1 = ast_create_command(cmd1_data);
    cmd2 = ast_create_command(cmd2_data);
    if (!cmd1 || !cmd2)
    {
        if (cmd1) ft_clear_ast(cmd1);
        if (cmd2) ft_clear_ast(cmd2);
        return (NULL);
    }
    return (ast_create_or(cmd1, cmd2));
}

/**
 * Cria automaticamente uma AST complexa: (cmd1 | cmd2) && cmd3
 * @param cmd1_data: dados do primeiro comando do pipe
 * @param cmd2_data: dados do segundo comando do pipe
 * @param cmd3_data: dados do comando final
 * @return: AST completa da expressão complexa
 */
t_ast *ast_auto_pipe_and(void *cmd1_data, void *cmd2_data, void *cmd3_data)
{
    t_ast *pipe_ast;
    t_ast *cmd3;

    pipe_ast = ast_auto_pipe(cmd1_data, cmd2_data);
    cmd3 = ast_create_command(cmd3_data);
    if (!pipe_ast || !cmd3)
    {
        if (pipe_ast) ft_clear_ast(pipe_ast);
        if (cmd3) ft_clear_ast(cmd3);
        return (NULL);
    }
    return (ast_create_and(pipe_ast, cmd3));
}

/**
 * Cria automaticamente uma AST complexa: cmd1 && (cmd2 | cmd3)
 * @param cmd1_data: dados do primeiro comando
 * @param cmd2_data: dados do primeiro comando do pipe
 * @param cmd3_data: dados do segundo comando do pipe
 * @return: AST completa da expressão complexa
 */
t_ast *ast_auto_and_pipe(void *cmd1_data, void *cmd2_data, void *cmd3_data)
{
    t_ast *cmd1;
    t_ast *pipe_ast;

    cmd1 = ast_create_command(cmd1_data);
    pipe_ast = ast_auto_pipe(cmd2_data, cmd3_data);
    if (!cmd1 || !pipe_ast)
    {
        if (cmd1) ft_clear_ast(cmd1);
        if (pipe_ast) ft_clear_ast(pipe_ast);
        return (NULL);
    }
    return (ast_create_and(cmd1, pipe_ast));
}

/* ============================================================================ */
/*                        FUNÇÕES DE UTILIDADE E DEMONSTRAÇÃO                  */
/* ============================================================================ */

/**
 * Cria uma AST de exemplo para demonstração
 * Cria: (ls -la | grep txt) && echo "found"
 * @return: AST de exemplo
 */
t_ast *ast_create_example(void)
{
    void *ls_data = create_string_data("ls -la");
    void *grep_data = create_string_data("grep txt");
    void *echo_data = create_string_data("echo found");
    
    return (ast_auto_pipe_and(ls_data, grep_data, echo_data));
}

/**
 * Cria uma AST colorida para demonstrar diferentes tipos
 * Cria: (cat file.txt | sort -r) || (echo "error" > log.txt)
 * @return: AST de exemplo colorida
 */
t_ast *ast_create_colorful_example(void)
{
    t_ast *left_pipe, *right_redirect, *result;
    t_ast *cat_cmd, *sort_cmd, *echo_cmd, *log_file;
    
    /* Lado esquerdo: cat file.txt | sort -r */
    cat_cmd = ast_create_command(create_string_data("cat file.txt"));
    sort_cmd = ast_create_command(create_string_data("sort -r"));
    left_pipe = ast_create_pipe(cat_cmd, sort_cmd);
    
    /* Lado direito: echo "error" > log.txt */
    echo_cmd = ast_create_command(create_string_data("echo error"));
    log_file = ast_create_command(create_string_data("log.txt"));
    right_redirect = ast_create_redirect(echo_cmd, create_string_data("log.txt"));
    right_redirect->right = log_file; /* Conectar arquivo */
    
    /* Conectar com OR: (cat | sort) || (echo > log) */
    result = ast_create_or(left_pipe, right_redirect);
    
    return (result);
}

/**
 * Cria uma AST de exemplo mais complexa
 * Cria: find . -name "*.c" || (make && ./program)
 * @return: AST de exemplo complexa
 */
t_ast *ast_create_complex_example(void)
{
    t_ast *cmd1;
    t_ast *and_part;
    void *cmd1_data = create_string_data("find . -name *.c");
    void *cmd2_data = create_string_data("make");
    void *cmd3_data = create_string_data("./program");

    cmd1 = ast_create_command(cmd1_data);
    and_part = ast_auto_and(cmd2_data, cmd3_data);
    if (!cmd1 || !and_part)
    {
        if (cmd1) ft_clear_ast(cmd1);
        if (and_part) ft_clear_ast(and_part);
        return (NULL);
    }
    return (ast_create_or(cmd1, and_part));
}

/**
 * Função de teste que cria e visualiza uma AST automaticamente
 * @param data: estrutura de dados do visualizador
 */
void ast_test_auto_creation(t_data *data)
{
    printf("🌳 Criando AST automaticamente...\n");
    
    /* Liberar AST anterior se existir */
    if (data->ast)
    {
        ft_clear_ast(data->ast);
        data->ast = NULL;
    }
    
    /* Criar nova AST automaticamente */
    data->ast = ast_create_example();
    
    if (data->ast)
    {
        printf("✅ AST criada com sucesso: (ls | grep) && echo\n");
        printf("   Root data: %s\n", data->ast->data ? "conjunto" : "NULL");
        if (data->ast->left)
            printf("   Left (pipe) presente\n");
        if (data->ast->right)
            printf("   Right (echo) presente\n");
    }
    else
    {
        printf("❌ Erro ao criar AST\n");
    }
}

/* ============================================================================ */
/*                        FUNÇÕES DE CORES PARA VISUALIZAÇÃO                  */
/* ============================================================================ */

/**
 * Determina a cor do nó baseada no tipo de comando
 * @param node: ponteiro para o nó AST
 * @return: cor em formato hexadecimal
 */
int get_node_color(t_ast *node)
{
    char *data_str;
    
    if (!node || !node->data)
        return (COLOR_DEFAULT);
    
    data_str = (char *)node->data;
    
    /* Identificar operadores */
    if (strcmp(data_str, "|") == 0)
        return (COLOR_PIPE);
    else if (strcmp(data_str, "&&") == 0)
        return (COLOR_AND);
    else if (strcmp(data_str, "||") == 0)
        return (COLOR_OR);
    else if (strcmp(data_str, ">") == 0 || strcmp(data_str, ">>") == 0 || 
             strcmp(data_str, "<") == 0 || strcmp(data_str, "<<") == 0)
        return (COLOR_REDIRECT);
    else if (strcmp(data_str, "()") == 0 || strcmp(data_str, "subshell") == 0)
        return (COLOR_SUBSHELL);
    /* Comandos normais */
    else
        return (COLOR_COMMAND);
}

/**
 * Determina a cor do texto baseada no tipo de comando
 * @param node: ponteiro para o nó AST
 * @return: cor do texto em formato hexadecimal
 */
int get_text_color(t_ast *node)
{
    char *data_str;
    
    if (!node || !node->data)
        return (TEXT_COLOR_DEFAULT);
    
    data_str = (char *)node->data;
    
    /* Operadores em amarelo */
    if (strcmp(data_str, "|") == 0 || strcmp(data_str, "&&") == 0 || 
        strcmp(data_str, "||") == 0 || strcmp(data_str, ">") == 0 || 
        strcmp(data_str, ">>") == 0 || strcmp(data_str, "<") == 0 || 
        strcmp(data_str, "<<") == 0)
        return (TEXT_COLOR_OP);
    /* Comandos em verde claro */
    else
        return (TEXT_COLOR_CMD);
}