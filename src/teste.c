/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:59:11 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/25 18:59:12 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minilibx-linux/mlx.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>


#define WIDTH 800
#define HEIGHT 600
#define R 40            /* raio dos nós */
#define THICKNESS 12    /* espessura da aresta */

typedef struct s_img {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_img;

typedef struct s_data {
    void    *mlx;
    void    *win;
    t_img   *img; /* nota: ponteiro para encaixar com put_pixel_to_image(data->img, ...) */
} t_data;

/* escreve um pixel na imagem (seguro contra fora de limites) */
void put_pixel_to_image(t_img *img, int x, int y, int color)
{
    if (!img)
        return;
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    char *dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

/* Bresenham: linha básica */
void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2)
{
    int dx, dy, err, sx, sy, e2;

    dx = abs(x2 - x1);
    sx = (x1 < x2) ? 1 : -1;
    dy = -abs(y2 - y1);
    sy = (y1 < y2) ? 1 : -1;
    err = dx + dy;
    while (1)
    {
        put_pixel_to_image(data->img, x1, y1, 0x00AAAAAA);
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

/* círculo preenchido (mais eficiente que varrer um quadrado) */
void draw_filled_circle(t_data *data, int xc, int yc, int r, int color)
{
    for (int dy = -r; dy <= r; dy++)
    {
        int dx_limit = (int)floor(sqrt((double)(r * r - dy * dy)));
        for (int dx = -dx_limit; dx <= dx_limit; dx++)
            put_pixel_to_image(data->img, xc + dx, yc + dy, color);
    }
}

/* desenha uma aresta "grossa" entre bordas de dois círculos
   (calcula o deslocamento perpendicular e desenha várias linhas paralelas) */
int ft_draw_edge(t_data *data, int x1, int y1, int x2, int y2)
{
    float vx = (float)(x2 - x1);
    float vy = (float)(y2 - y1);
    float dist = sqrtf(vx * vx + vy * vy);
    if (dist == 0.0f)
        return (0);

    float ux = vx / dist;   /* unidade direção */
    float uy = vy / dist;

    /* perpendicular unitário */
    float px = -uy;
    float py = ux;

    /* desenhar várias linhas deslocadas na perpendicular */
    int half = THICKNESS / 2;
    for (int i = -half; i <= half; i++)
    {
        int ofx = (int)roundf(px * i);
        int ofy = (int)roundf(py * i);

        int sx1 = (int)roundf(x1 + ux * R) + ofx;
        int sy1 = (int)roundf(y1 + uy * R) + ofy;
        int sx2 = (int)roundf(x2 - ux * R) + ofx;
        int sy2 = (int)roundf(y2 - uy * R) + ofy;

        ft_draw_line(data, sx1, sy1, sx2, sy2);
    }
    return (0);
}

/* handler de tecla (ESC fecha) */
int key_hook(int keycode, t_data *data)
{
    (void)data;
    if (keycode == 65307) /* XK_Escape no X11 */
        exit(0);
    return (0);
}

int main(void)
{
    t_data data_local;
    t_img *img;

    data_local.mlx = mlx_init();
    if (!data_local.mlx)
        return (1);
    data_local.win = mlx_new_window(data_local.mlx, WIDTH, HEIGHT, "Arvore binaria (exemplo)");
    if (!data_local.win)
        return (1);

    img = (t_img *)malloc(sizeof(t_img));
    if (!img)
        return (1);
    img->img = mlx_new_image(data_local.mlx, WIDTH, HEIGHT);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    data_local.img = img;

    /* --- desenhar exemplo: A (top) -> B e C (baixo) --- */
    int ax = WIDTH / 2, ay = 120;
    int bx = WIDTH / 2 - 180, by = 360;
    int cx = WIDTH / 2 + 180, cy = 360;

    /* fundo (preenche com preto) */
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel_to_image(data_local.img, x, y, 0x00000000);

    /* nós (círculos preenchidos) */
    draw_filled_circle(&data_local, ax, ay, R, 0x00FF5555); /* A vermelho */
    draw_filled_circle(&data_local, bx, by, R, 0x0055FF55); /* B verde */
    draw_filled_circle(&data_local, cx, cy, R, 0x005555FF); /* C azul */

    /* arestas grossas */
    ft_draw_edge(&data_local, ax, ay, bx, by);
    ft_draw_edge(&data_local, ax, ay, cx, cy);

    /* enviar para a janela */
    mlx_put_image_to_window(data_local.mlx, data_local.win, img->img, 0, 0);

    mlx_key_hook(data_local.win, key_hook, &data_local);
    mlx_loop(data_local.mlx);

    free(img);
    return (0);
}

