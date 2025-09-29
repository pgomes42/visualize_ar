/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:21:44 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/29 12:43:41 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer_ar.h"

static t_ast *ft_new_node(int data)
{
    t_ast *new;

    new = (t_ast *)malloc(sizeof(t_ast));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return (new);
}

void ft_clear_ast(t_ast *ast)
{
    if (!ast)
        return;
    ft_clear_ast(ast->left);
    ft_clear_ast(ast->right);
    free(ast);
    ast = NULL;
}

int ft_get_num_parent(t_ast *ast, int i)
{
    if (!ast)
        return (i);
    ft_get_num_parent(ast->left, i + 1);
    return (ft_get_num_parent(ast->right, i + 1));
}
void ft_creat_ast(t_data *data)
{
    t_ast *root;
    int str;

    str = 0;
    root = ft_new_node(++str);
    root->left = ft_new_node(++str);
    root->left->left = ft_new_node(++str);
    root->left->left->right = ft_new_node(++str);
    root->left->left->left = ft_new_node(++str);
root->right = ft_new_node(++str);
    root->right->left = ft_new_node(++str);
     /*root->left->right = ft_new_node(++str);
     root->left->right->left = ft_new_node(++str);
       root->left->right->right = ft_new_node(++str);
       root->left->right->right->left = ft_new_node(++str);
       root->left->right->right->right = ft_new_node(++str);
     root->right->right = ft_new_node(++str);
     root->right->left = ft_new_node(++str);
    root->right->right->right = ft_new_node(++str);
      root->right->right->right->right = ft_new_node(++str);
      root->right->right->right->right->right = ft_new_node(++str);*/
      
       //root->right->right->left = ft_new_node(++str);
    
    data->ast = root;
}

void ft_draw_nodes(t_data *data, t_ast *ast, t_inic *inic)
{
    t_inic *inic_tmp;
    int num_par;
    
    if (!ast)
        return ; 
    num_par = ft_get_num_parent(ast, 0);
    ft_draw_circle(data, inic->y1, inic->x1, R, 0xFFFAAF);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img, 0 , 0);
    inic_tmp = NULL;     
    inic_tmp = ft_get_inic(inic, 3, num_par);
    ft_draw_nodes(data, ast->left, inic_tmp);
    free(inic_tmp);
    inic_tmp = ft_get_inic(inic, 2, num_par);
    ft_draw_nodes(data, ast->right, inic_tmp);
    free(inic_tmp);
}
void ft_draw_ast(t_data *data, t_ast *ast, t_inic *inic)
{
    t_inic *inic_tmp;
    int num_par;
    
    if (!ast)
        return ; 
    num_par = ft_get_num_parent(ast, 0);
    ft_draw_circle(data, inic->y1, inic->x1, R, 0xFFFAAF);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img,0 , 0);
    sleep(data->deleey);
    inic_tmp = NULL;     
    if (ast->left)
    {
        inic_tmp = ft_get_inic(inic, 0, num_par);
        
        ft_draw_edge(data, inic_tmp); 
        mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img,0 , 0);
        sleep(data->deleey);
        free(inic_tmp);
    }   
    if (ast->right)
    { 
        inic_tmp = ft_get_inic(inic, 1, num_par); 
        ft_draw_edge(data, inic_tmp); 
        mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img->img,0 , 0);
        sleep(data->deleey);
        free(inic_tmp); 
    }   
    inic_tmp = ft_get_inic(inic, 3, num_par);
    ft_draw_ast(data, ast->left, inic_tmp);
    free(inic_tmp);
    inic_tmp = ft_get_inic(inic, 2, num_par);
    ft_draw_ast(data, ast->right, inic_tmp);
    free(inic_tmp);
}