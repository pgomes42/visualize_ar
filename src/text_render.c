/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:45:00 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 12:00:00 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer_ar.h"

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