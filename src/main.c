/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:42:18 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 11:23:22 by pgomes           ###   ########.fr       */
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
    free(data->inic);
    lib_clear_ast_internal(data->ast);
    exit (0);
}

void ft_put_str_ast(t_data *data, t_ast *ast, t_inic *inic)
{
    t_inic *inic_tmp;
    int num_par;
    char *text_to_show;
    int text_color;
    
    if (!ast)
        return ; 
        
    /* Determina o texto a mostrar baseado no tipo de dados */
    if (ast->data)
        text_to_show = (char *)ast->data;
    else
        text_to_show = "NULL";
    
    /* Determina a cor baseada no tipo de comando */
    text_color = get_text_color(ast);
        
    num_par = ft_get_num_parent(ast, 0);
    mlx_string_put(data->mlx_ptr, data->mlx_win, inic->x1 - 10 + data->offset_x, inic->y1 + data->offset_y, text_color, text_to_show);
    inic_tmp = ft_get_inic(inic, 3, num_par);
    ft_put_str_ast(data, ast->left, inic_tmp);
    free(inic_tmp);
    inic_tmp = ft_get_inic(inic, 2, num_par);
    ft_put_str_ast(data, ast->right, inic_tmp);
    free(inic_tmp);    
}

static int ft_draw(t_data *data)
{
    /* Usar função automática para criar AST */
    if (!data->ast)
    {
        printf("🎨 Criando AST colorida para demonstração...\n");
        data->ast = ast_create_colorful_example();
        if (!data->ast)
        {
            printf("❌ Erro ao criar AST automaticamente\n");
            return (1);
        }
        printf("✅ AST criada: (cat file.txt | sort -r) || (echo error > log.txt)\n");
    }
    
    ft_draw_background(data->img);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img, 0, 0);
 
    ft_draw_ast(data, data->ast, data->inic);
    ft_draw_nodes(data, data->ast, data->inic);
    ft_put_str_ast(data, data->ast, data->inic);
    return (0);
}

static void ft_inic(t_data *data)
{
    data->img = (t_img *)malloc(sizeof(t_img));
    data->inic = (t_inic *)malloc(sizeof(t_inic));
    if (!data->img || !data->inic)
    {
        if (data->img)
            free(data->img);
        if (data->inic)
            free(data->inic);
        exit(1);
    }
    data->mlx_ptr = NULL;
    data->mlx_win = NULL;
    data->img->img = NULL;
    data->ast = NULL;  /* Inicializar ast como NULL */
    data->inic->x1 = (WIDTH / 2);
    data->inic->y1 = 100;
    data->inic->x2 = -1;
    data->inic->y2 = -1;
    data->offset_x = 0;
    data->offset_y = 0;
    data->deleey = 1;
}
int main()
{
    t_data data;

    ft_inic(&data);
    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
    {
        free(data.img);
        free(data.inic);
        return (1);
    }
    
    /* Mostrar instruções de uso */
    printf("🎨 === VISUALIZADOR DE AST COM CORES === 🎨\n");
    printf("📋 Instruções:\n");
    printf("   1️⃣  - Exemplo simples: (ls -la | grep txt) && echo found\n");
    printf("   2️⃣  - Exemplo colorido: (cat file.txt | sort -r) || (echo error > log)\n");
    printf("   3️⃣  - Exemplo complexo: find . -name *.c || (make && ./program)\n");
    printf("   ⬅️➡️⬆️⬇️ - Mover visualização\n");
    printf("   ESC - Sair\n");
    printf("🎨 Cores: 🟢Comandos 🔵Pipe 🟡AND 🟠OR 🟣Redirect\n\n");
    
    data.img->img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
    if (!data.img->img)
    {
        free(data.img);
        free(data.inic);
        return (1);
    }
    data.img->addr = mlx_get_data_addr(data.img->img, &data.img->bpp, &data.img->size, &data.img->endian);
    data.mlx_win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "visuzlizer Binary Tree");
    if (!data.mlx_win)
    {
        mlx_destroy_image(data.mlx_ptr, data.img->img);
        free(data.img);
        free(data.inic);
        return (1);
    }
    ft_draw(&data);
    mlx_hook(data.mlx_win, 17, 0, ft_clean, &data);
    mlx_hook(data.mlx_win, 2, 1L<<0, key_hook, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}

