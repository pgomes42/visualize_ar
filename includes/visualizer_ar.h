/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_ar.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:17:43 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 11:23:25 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_AR_H
# define VISUALIZER_AR_H

# define R  40 
# define WIDTH  1200
# define HEIGHT  900
# define Y2 175
# define X2 150

/* Teclas de movimento */
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_ESC 65307

/* Teclas para alternar exemplos */
# define KEY_1 49
# define KEY_2 50
# define KEY_3 51


# define MOVE_SPEED 50

/* ============================================================================ */
/*                               CORES PARA AST                                */
/* ============================================================================ */

/* Cores para nós de comandos */
# define COLOR_COMMAND     0x00FF00    /* Verde - comandos simples */
# define COLOR_PIPE        0x0080FF    /* Azul - operador pipe */
# define COLOR_AND         0xFFD700    /* Dourado - operador && */
# define COLOR_OR          0xFF8000    /* Laranja - operador || */
# define COLOR_REDIRECT    0xFF0080    /* Rosa - redirecionamentos */
# define COLOR_SUBSHELL    0x8000FF    /* Roxo - subshells */
# define COLOR_DEFAULT     0xFFFFFF    /* Branco - padrão */

/* Cores para texto */
# define TEXT_COLOR_CMD    0x000000    /* Preto para comandos */
# define TEXT_COLOR_OP     0xFFFF00    /* Amarelo para operadores */
# define TEXT_COLOR_DEFAULT 0xFFFFFF   /* Branco para outros */


# include "../lib/minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>

typedef struct s_ast
{
    void *data;
    struct s_ast *left;
    struct s_ast *right;  
    
}   t_ast;

typedef struct s_img
{
    void *img;
    char *addr;
    int size;
    int bpp;
    int endian;
        
}   t_img;

typedef struct s_line
{
    float vx;
	float vy;
	float ux;
	float uy;
	float dist;
	float px;
	float py;
    
} t_line;

typedef struct s_inic
{
    int x1;
    int y1;
    int x2;
    int y2;
} t_inic;
typedef struct s_data
{
    t_img *img;
    t_inic *inic;
    t_ast *ast;
    void    *mlx_win;
    void    *mlx_ptr;
    int     offset_x;
    int     offset_y;
    int     deleey;
    
}   t_data;

int ft_get_num_parent(t_ast *ast, int i);
void ft_clear_ast(t_ast *ast);
void ft_creat_ast(t_data *data);
int ft_draw_circle(t_data *data, int start_y, int start_x, int radius, int color);
int	ft_draw_background(t_img *img);
int ft_draw_edge(t_data *data, t_inic *inic);
void ft_draw_thick_line(t_data *data, int x1, int y1, int x2, int y2, int thickness);
int key_hook(int keycode, t_data *data);
int close_window(t_data *data);
void render_tree(t_data *data);
void ft_draw_ast(t_data *data, t_ast *ast, t_inic *inic);
void ft_put_str_ast(t_data *data, t_ast *ast, t_inic *inic);
t_inic *ft_get_inic(t_inic *parent, int sign, int num_par);
void ft_draw_nodes(t_data *data, t_ast *ast, t_inic *inic);

/* ============================================================================ */
/*                        FUNÇÕES DE CRIAÇÃO AUTOMÁTICA DE AST                 */
/* ============================================================================ */

/* Funções básicas de criação */
t_ast *ast_create_node(void *data);
t_ast *ast_create_command(void *cmd_data);
t_ast *ast_create_pipe(t_ast *left_cmd, t_ast *right_cmd);
t_ast *ast_create_and(t_ast *left_expr, t_ast *right_expr);
t_ast *ast_create_or(t_ast *left_expr, t_ast *right_expr);
t_ast *ast_create_redirect(t_ast *cmd, void *redirect_data);
t_ast *ast_create_subshell(t_ast *inner_ast);

/* Funções automáticas para Minishell */
t_ast *ast_auto_pipe(void *cmd1_data, void *cmd2_data);
t_ast *ast_auto_and(void *cmd1_data, void *cmd2_data);
t_ast *ast_auto_or(void *cmd1_data, void *cmd2_data);
t_ast *ast_auto_pipe_and(void *cmd1_data, void *cmd2_data, void *cmd3_data);
t_ast *ast_auto_and_pipe(void *cmd1_data, void *cmd2_data, void *cmd3_data);

/* Funções de exemplo e teste */
t_ast *ast_create_example(void);
t_ast *ast_create_colorful_example(void);
t_ast *ast_create_complex_example(void);
void ast_test_auto_creation(t_data *data);

/* Funções helper para criação de dados */
void *create_int_data(int value);
void *create_string_data(const char *str);

/* Funções para cores baseadas em tipos */
int get_node_color(t_ast *node);
int get_text_color(t_ast *node);

#endif
