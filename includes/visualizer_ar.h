/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_ar.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:17:43 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/29 12:39:16 by pgomes           ###   ########.fr       */
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


# define MOVE_SPEED 50


# include "../lib/minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>

typedef struct s_ast
{
    int data;
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
#endif
