/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:42:18 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/26 00:00:53 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer_ar.h"

static int ft_clean(t_data *data)
{
    if (data->img->img)
        mlx_destroy_image(data->mlx_ptr, data->img->img);
    if (data->img)
        free(data->img);
    if (data->mlx_win)
        mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    exit (0);
}
t_inic *ft_get_inic(t_inic *inic, int sign, int level)
{  
    if (inic->x2 == -1 || inic->y2 == -1)
    {
        if (sign)
            inic->x2 = inic->x1 + 150;
        else
            inic->x2 = inic->x1 - 150;
        inic->y2 = inic->y1 + 175; 
    }
    else
       {
       if (sign)
       {
            inic->x1 += 150;
            inic->x2 += 150; 
       } 
       else
       {
            inic->x1 -= 150;
            inic->x2 -= 150;
       }
       inic->y1 = 100 + (175 * level);
       inic->y2 = inic->y1 + (175 * level);
    }
    return (inic);
}
t_inic *new_inic(t_inic *inc)
{
    t_inic *inic;

    inic = (t_inic *)malloc(sizeof(t_inic));
    inic->x1 = inc->x1;
    inic->y1 = inc->y1;
    inic->x2 = inc->x2;
    inic->y2 = inc->y2;
    return (inic);
}
static void ft_draw_ast(t_data *data, t_ast *ast, int sign, int level)
{
   t_inic *inic;
    
    if (!ast)
        return ;
   (void)sign; 
   //inic = NULL;
   if (ast->left)
   {
        inic = ft_get_inic(new_inic(data->inic), 0, _SC_LEVEL3_CACHE_ASSOC);
        ft_draw_edge(data, inic);
        free(inic);
    //mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img,0 , 0));
   // sleep(3);
   }
    if (ast->right)
    {
        inic = ft_get_inic(new_inic(data->inic), 1, level);
        ft_draw_edge(data, inic);
        free(inic);
    }
    //mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img,0 , 0));
    //sleep(0.3);
     data->inic = ft_get_inic(data->inic, sign, level);
    ft_draw_circle(data, data->inic->y1, data->inic->x1);
    
    //ft_draw_ast(data, ast->left, 0, ++level);
    ft_draw_ast(data, ast->right, 1, ++level);
    //data->inic = ft_get_inic(data->inic, sign);
   
   // mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img,0 , 0); 
}
static int ft_draw(t_data *data)
{
    ft_creat_ast(data);
    ft_draw_background( data->img);
    ft_draw_ast(data, data->ast, 1, 0);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img,0 , 0);
    return (0);
}

static void ft_inic(t_data *data)
{
    data->img = (t_img *)malloc(sizeof(t_img));
    data->inic = (t_inic *)malloc(sizeof(t_inic));
    data->inic->x1 = (WIDTH / 2);
    data->inic->y1 = 100;
    data->inic->x2 = -1;
    data->inic->y2 = -1;
}
int main()
{
    t_data data;

    ft_inic(&data);
    
    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (1);
    data.img->img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
    data.img->addr = mlx_get_data_addr(data.img->img, &data.img->bpp, &data.img->size, &data.img->endian);
    data.mlx_win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "visuzlizer Binary Tree");
    ft_draw(&data);
    mlx_hook(data.mlx_win, 17, 0, ft_clean, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}

