/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_ar.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:17:43 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/25 21:48:58 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_AR_H
# define VISUALIZER_AR_H

# define R  70 
# define WIDTH  900
# define HEIGHT  700
# define Y2 175
# define X2 150


# include "../lib/minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

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
    int x2;
    int y1;
    int y2;
} t_inic;
typedef struct s_data
{
    t_img *img;
    t_inic *inic;
    t_ast *ast;
    void    *mlx_win;
    void    *mlx_ptr;
    
    
}   t_data;

void ft_creat_ast(t_data *data);
int ft_draw_circle(t_data *data, int start_y, int start_x);
int	ft_draw_background(t_img *img);
int ft_draw_edge(t_data *data, t_inic *inic);
#endif
