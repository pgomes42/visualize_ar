/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libast_visualizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:30:00 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 12:00:00 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libast_visualizer.h"
#include "visualizer_ar.h"
#include <string.h>

/* ============================================================================ */
/*                          ESTRUTURA INTERNA                                  */
/* ============================================================================ */

struct s_ast_visualizer
{
    void    *mlx_ptr;
    int     initialized;
};

/* ============================================================================ */
/*                           FUNÇÕES INTERNAS                                  */
/* ============================================================================ */

static char *ft_strdup_safe(const char *str)
{
    char *new_str;
    int len, i;
    
    if (!str)
        return (NULL);
    
    len = strlen(str);
    new_str = malloc(len + 1);
    if (!new_str)
        return (NULL);
    
    i = 0;
    while (i < len)
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
    return (new_str);
}

static t_ast *convert_to_internal_ast(const t_ast_node *external_ast)
{
    t_ast *internal_ast;
    
    if (!external_ast)
        return (NULL);
    
    internal_ast = malloc(sizeof(t_ast));
    if (!internal_ast)
        return (NULL);
    
    internal_ast->data = ft_strdup_safe((const char *)external_ast->data);
    internal_ast->left = convert_to_internal_ast(external_ast->left);
    internal_ast->right = convert_to_internal_ast(external_ast->right);
    
    return (internal_ast);
}

/* ============================================================================ */
/*                              API PRINCIPAL                                  */
/* ============================================================================ */

t_ast_visualizer *ast_visualizer_init(void)
{
    t_ast_visualizer *visualizer;
    
    visualizer = malloc(sizeof(t_ast_visualizer));
    if (!visualizer)
        return (NULL);
    
    visualizer->mlx_ptr = mlx_init();
    if (!visualizer->mlx_ptr)
    {
        free(visualizer);
        return (NULL);
    }
    
    visualizer->initialized = 1;
    return (visualizer);
}

int ast_visualizer_show(t_ast_visualizer *visualizer, t_ast_node *ast, const char *title)
{
    t_data data;
    t_ast *internal_ast;
    char *window_title;
    
    if (!visualizer || !visualizer->initialized || !ast)
        return (-1);
    
    /* Preparar título */
    window_title = ft_strdup_safe(title ? title : "AST Visualizer");
    if (!window_title)
        return (-1);
    
    /* Converter AST externa para formato interno */
    internal_ast = convert_to_internal_ast(ast);
    if (!internal_ast)
    {
        free(window_title);
        return (-1);
    }
    
    /* Inicializar estrutura de dados */
    data.img = malloc(sizeof(t_img));
    data.inic = malloc(sizeof(t_inic));
    if (!data.img || !data.inic)
    {
        if (data.img) free(data.img);
        if (data.inic) free(data.inic);
        lib_clear_ast_internal(internal_ast);
        free(window_title);
        return (-1);
    }
    
    data.mlx_ptr = visualizer->mlx_ptr;
    data.ast = internal_ast;
    data.inic->x1 = (WIDTH / 2);
    data.inic->y1 = 100;
    data.inic->x2 = -1;
    data.inic->y2 = -1;
    data.offset_x = 0;
    data.offset_y = 0;
    data.deleey = 1;
    
    /* Criar janela e imagem */
    data.img->img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
    if (!data.img->img)
    {
        free(data.img);
        free(data.inic);
        lib_clear_ast_internal(internal_ast);
        free(window_title);
        return (-1);
    }
    
    data.img->addr = mlx_get_data_addr(data.img->img, &data.img->bpp, &data.img->size, &data.img->endian);
    data.mlx_win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, window_title);
    if (!data.mlx_win)
    {
        mlx_destroy_image(data.mlx_ptr, data.img->img);
        free(data.img);
        free(data.inic);
        lib_clear_ast_internal(internal_ast);
        free(window_title);
        return (-1);
    }
    
    /* Mostrar instruções */
    printf("🎨 === AST VISUALIZER LIBRARY === 🎨\n");
    printf("📋 Controles:\n");
    printf("   ⬅️➡️⬆️⬇️ - Mover visualização\n");
    printf("   ESC - Fechar janela\n");
    printf("🎨 Cores: 🟢Comandos 🔵Pipe 🟡AND 🟠OR 🟣Redirect\n\n");
    
    /* Desenhar AST */
    ft_draw_background(data.img);
    mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.img->img, 0, 0);
    ft_draw_ast(&data, data.ast, data.inic);
    ft_draw_nodes(&data, data.ast, data.inic);
    ft_put_str_ast(&data, data.ast, data.inic);
    
    /* Configurar hooks */
    mlx_hook(data.mlx_win, 17, 0, close_window, &data);
    mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
    
    /* Iniciar loop */
    mlx_loop(data.mlx_ptr);
    
    /* Limpeza */
    if (data.img->img)
        mlx_destroy_image(data.mlx_ptr, data.img->img);
    if (data.img)
        free(data.img);
    if (data.mlx_win)
        mlx_destroy_window(data.mlx_ptr, data.mlx_win);
    free(data.inic);
    lib_clear_ast_internal(internal_ast);
    free(window_title);
    
    return (0);
}

void ast_visualizer_destroy(t_ast_visualizer *visualizer)
{
    if (!visualizer)
        return;
    
    if (visualizer->mlx_ptr && visualizer->initialized)
        mlx_destroy_display(visualizer->mlx_ptr);
    
    free(visualizer);
}

/* ============================================================================ */
/*                           CRIAÇÃO DE NODOS                                  */
/* ============================================================================ */

t_ast_node *ast_node_create(const char *data)
{
    t_ast_node *node;
    
    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    
    node->data = ft_strdup_safe(data);
    node->left = NULL;
    node->right = NULL;
    
    return (node);
}

t_ast_node *ast_node_command(const char *command)
{
    return (ast_node_create(command));
}

t_ast_node *ast_node_pipe(t_ast_node *left, t_ast_node *right)
{
    t_ast_node *pipe_node;
    
    pipe_node = ast_node_create("|");
    if (!pipe_node)
        return (NULL);
    
    pipe_node->left = left;
    pipe_node->right = right;
    
    return (pipe_node);
}

t_ast_node *ast_node_and(t_ast_node *left, t_ast_node *right)
{
    t_ast_node *and_node;
    
    and_node = ast_node_create("&&");
    if (!and_node)
        return (NULL);
    
    and_node->left = left;
    and_node->right = right;
    
    return (and_node);
}

t_ast_node *ast_node_or(t_ast_node *left, t_ast_node *right)
{
    t_ast_node *or_node;
    
    or_node = ast_node_create("||");
    if (!or_node)
        return (NULL);
    
    or_node->left = left;
    or_node->right = right;
    
    return (or_node);
}

t_ast_node *ast_node_redirect(t_ast_node *command, const char *redirect)
{
    t_ast_node *redirect_node;
    
    redirect_node = ast_node_create(redirect);
    if (!redirect_node)
        return (NULL);
    
    redirect_node->left = command;
    redirect_node->right = NULL;
    
    return (redirect_node);
}

/* ============================================================================ */
/*                         FUNÇÕES DE CONVENIÊNCIA                             */
/* ============================================================================ */

t_ast_node *ast_quick_pipe(const char *cmd1, const char *cmd2)
{
    t_ast_node *left, *right;
    
    left = ast_node_command(cmd1);
    right = ast_node_command(cmd2);
    
    if (!left || !right)
    {
        if (left) ast_node_destroy(left);
        if (right) ast_node_destroy(right);
        return (NULL);
    }
    
    return (ast_node_pipe(left, right));
}

t_ast_node *ast_quick_and(const char *cmd1, const char *cmd2)
{
    t_ast_node *left, *right;
    
    left = ast_node_command(cmd1);
    right = ast_node_command(cmd2);
    
    if (!left || !right)
    {
        if (left) ast_node_destroy(left);
        if (right) ast_node_destroy(right);
        return (NULL);
    }
    
    return (ast_node_and(left, right));
}

t_ast_node *ast_quick_or(const char *cmd1, const char *cmd2)
{
    t_ast_node *left, *right;
    
    left = ast_node_command(cmd1);
    right = ast_node_command(cmd2);
    
    if (!left || !right)
    {
        if (left) ast_node_destroy(left);
        if (right) ast_node_destroy(right);
        return (NULL);
    }
    
    return (ast_node_or(left, right));
}

/* ============================================================================ */
/*                          GERENCIAMENTO DE MEMÓRIA                           */
/* ============================================================================ */

void ast_node_destroy(t_ast_node *ast)
{
    if (!ast)
        return;
    
    ast_node_destroy(ast->left);
    ast_node_destroy(ast->right);
    
    if (ast->data)
        free(ast->data);
    
    free(ast);
}

t_ast_node *ast_node_duplicate(const t_ast_node *ast)
{
    t_ast_node *new_node;
    
    if (!ast)
        return (NULL);
    
    new_node = ast_node_create((const char *)ast->data);
    if (!new_node)
        return (NULL);
    
    new_node->left = ast_node_duplicate(ast->left);
    new_node->right = ast_node_duplicate(ast->right);
    
    return (new_node);
}

/* ============================================================================ */
/*                              UTILITÁRIOS                                    */
/* ============================================================================ */

void ast_node_print(const t_ast_node *ast, int depth)
{
    int i;
    
    if (!ast)
        return;
    
    for (i = 0; i < depth; i++)
        printf("  ");
    
    printf("└─ %s\n", ast->data ? (char *)ast->data : "(null)");
    
    if (ast->left || ast->right)
    {
        ast_node_print(ast->left, depth + 1);
        ast_node_print(ast->right, depth + 1);
    }
}

int ast_node_count(const t_ast_node *ast)
{
    if (!ast)
        return (0);
    
    return (1 + ast_node_count(ast->left) + ast_node_count(ast->right));
}

int ast_node_height(const t_ast_node *ast)
{
    int left_height, right_height;
    
    if (!ast)
        return (0);
    
    left_height = ast_node_height(ast->left);
    right_height = ast_node_height(ast->right);
    
    return (1 + (left_height > right_height ? left_height : right_height));
}

/* ============================================================================ */
/*                              EXEMPLOS DE USO                                */
/* ============================================================================ */

t_ast_node *ast_create_example_simple(void)
{
    /* Cria: ls -la | grep .txt */
    return (ast_quick_pipe("ls -la", "grep .txt"));
}

t_ast_node *ast_create_example_complex(void)
{
    /* Cria: (cat file.txt | sort) && echo "sorted" */
    t_ast_node *pipe_part, *command_part;
    
    pipe_part = ast_quick_pipe("cat file.txt", "sort");
    command_part = ast_node_command("echo sorted");
    
    if (!pipe_part || !command_part)
    {
        if (pipe_part) ast_node_destroy(pipe_part);
        if (command_part) ast_node_destroy(command_part);
        return (NULL);
    }
    
    return (ast_node_and(pipe_part, command_part));
}