/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:58:45 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/26 09:23:41 by pgomes           ###   ########.fr       */
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

int ft_draw_circle(t_data *data, int start_y, int start_x)
{
	int x;
	int y;
	
	y = -R ;
	while (y <= R)
	{		
			x = -R;
			while (x <= R)
			{
				if (((x * x) + (y * y)) <= ( R * R))
					put_pixel_to_image(data->img, start_x + x, start_y + y, 0xFFFAAF);
				x++;
			}
			y++;
	}
		return (0);
}
void ft_draw_line(t_data *data, t_inic *inic)
{
	t_inic lines;
	int err;
	int e2;
	
	lines.x1 = abs(inic->x2 - inic->x1);
	lines.y1 = -abs(inic->y2 - inic->y1);
	lines.x2 = -1;
	lines.y2 = -1;
	if (inic->x1 < inic->x2)
		lines.x2 = 1;
	if(inic->y1 < inic->y2)
		lines.y2 = 1;
	err = lines.x1 + lines.y1;
	while (1)
	{
		put_pixel_to_image(data->img, inic->x1 , inic->y1 , 0xAAAAAA);
		if (inic->x1 == inic->x2 && inic->y1 == inic->y2)
			break;
		e2 = 2 * err;
		if(e2 >= lines.y1)
		{
			err += lines.y1;
			inic->x1 += lines.x2;
		}
		if(e2 <= lines.x1)
		{
			err += lines.x1;
			inic->y1 += lines.y2;
		}
	}
	
}

int ft_draw_edge(t_data *data, t_inic *inic)
{
	t_line line;
	t_inic temp_inic;
	int i;
		
	line.vx = inic->x2 - inic->x1;
	line.vy = inic->y2 - inic->y1;
	line.dist = sqrt((line.vx * line.vx) + (line.vy * line.vy));
	line.ux = line.vx / line.dist;
	line.uy = line.vy / line.dist;
	line.px = -line.uy;
	line.py = line.ux;
	i = -6;
	while (++i <= 5)
	{
		temp_inic.x1 = (inic->x1 + line.ux * R) + line.px * i;
		temp_inic.y1 = (inic->y1 + line.uy * R) + line.py * i;
		temp_inic.x2 = (inic->x2 - line.ux * R) + line.px * i;
		temp_inic.y2 = (inic->y2 - line.uy * R) + line.py * i;
		ft_draw_line(data, &temp_inic);
	}
	return (0);	
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
				put_pixel_to_image(img, x, y, 0xFFFFFF);
		}
	}
	return (0);
}
