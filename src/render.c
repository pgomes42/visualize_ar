/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:58:45 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 11:26:49 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer_ar.h"

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x <= WIDTH && y <= HEIGHT && x >= 0 && y >= 0)
	{
		pixel = img->addr + (y * img->size + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

int ft_draw_circle(t_data *data, int start_y, int start_x, int radius, int color)
{
	int x;
	int y;
	int screen_x;
	int screen_y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (((x * x) + (y * y)) <= (radius * radius))
			{
				screen_x = start_x + x + data->offset_x;
				screen_y = start_y + y + data->offset_y;
				put_pixel_to_image(data->img, screen_x, screen_y, color);
			}
			x++;
		}
		y++;
	}
	return (0);
}
void ft_draw_thick_line(t_data *data, int x1, int y1, int x2, int y2, int thickness)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
	
	dx = abs(x2 - x1);
	dy = -abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx + dy;
	
	while (1)
	{
		ft_draw_circle(data, y1, x1, thickness / 2, 0xAAAAAA);
		if (x1 == x2 && y1 == y2)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}


int ft_draw_edge(t_data *data, t_inic *inic)
{
	t_line line;
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	
	line.vx = inic->x2 - inic->x1;
	line.vy = inic->y2 - inic->y1;
	line.dist = sqrt((line.vx * line.vx) + (line.vy * line.vy));
	if (line.dist == 0)
		return (0);
	line.ux = line.vx / line.dist;
	line.uy = line.vy / line.dist;
	start_x = (int)(inic->x1 + line.ux * R + 0.5);
	start_y = (int)(inic->y1 + line.uy * R + 0.5);
	end_x = (int)(inic->x2 - line.ux * R + 0.5);
	end_y = (int)(inic->y2 - line.uy * R + 0.5);
	ft_draw_thick_line(data, start_x, start_y, end_x, end_y, (R * 0.2));
	return (0);	
}

t_inic *ft_get_inic(t_inic *parent, int sign, int num_par) 
{
    t_inic *inic;

    inic = (t_inic *)malloc(sizeof(t_inic));
    if (sign < 2)
    {
        if (sign == 1)
        { 
            inic->x1 = parent->x1;
            inic->x2 = (inic->x1 + ((R + 10) * num_par)); 
        }
        else
        { 
            inic->x1 = parent->x1;
            inic->x2 = (inic->x1 - ((R + 10) * num_par));
        }
        inic->y1 = parent->y1;
            
    }
    else if (sign >= 2)
    {
        if(sign == 2)
        {
            inic->x1 = parent->x1 + ((R + 10) * num_par);
            inic->x2 = (inic->x1 + ((R + 10) * num_par));
        }
        else
        {
            inic->x1 = parent->x1 - ((R + 10) * num_par);
            inic->x2 = (inic->x1 - ((R + 10) * num_par));
        }
        inic->y1 = parent->y1 + (30 + R * 2);
    }
        inic->y2 = (inic->y1 +(30 + R * 2)); 
    
        return (inic);
}

int	ft_draw_background(t_img *img)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
				put_pixel_to_image(img, x, y, 0x00000F);
		}
	}
	return (0);
}

int key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	else if (keycode == KEY_LEFT)
		data->offset_x += MOVE_SPEED;
	else if (keycode == KEY_RIGHT)
		data->offset_x -= MOVE_SPEED;
	else if (keycode == KEY_UP)
		data->offset_y += MOVE_SPEED;
	else if (keycode == KEY_DOWN)
		data->offset_y -= MOVE_SPEED;
	else if (keycode == KEY_1)
	{
		if (data->ast)
			lib_clear_ast_internal(data->ast);
		data->ast = ast_create_example();
		printf("🎨 Exemplo 1: (ls -la | grep txt) && echo found\n");
	}
	else if (keycode == KEY_2)
	{
		if (data->ast)
			lib_clear_ast_internal(data->ast);
		data->ast = ast_create_colorful_example();
		printf("🎨 Exemplo 2: (cat file.txt | sort -r) || (echo error > log)\n");
	}
	else if (keycode == KEY_3)
	{
		
		if (data->ast)
			lib_clear_ast_internal(data->ast);
		data->ast = ast_create_complex_example();
		printf("🎨 Exemplo 3: find . -name *.c || (make && ./program)\n");
	}
	
	render_tree(data);
	return (0);
}

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
	return (0);
}

void render_tree(t_data *data)
{
	ft_draw_background(data->img);
	if (data->ast)
	{
		data->deleey = 0;
		ft_draw_ast(data, data->ast, data->inic);
		ft_draw_nodes(data, data->ast, data->inic);
		ft_put_str_ast(data, data->ast, data->inic);
	}
	
}
