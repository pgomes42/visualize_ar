/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:21:44 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/28 13:46:32 by pgomes           ###   ########.fr       */
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
   /* root->left->left = ft_new_node(++str);
    root->left->left->right = ft_new_node(++str);
    root->left->left->left = ft_new_node(++str);*/
//root->right = ft_new_node(++str);
    // root->right->left = ft_new_node(++str);
     //root->left->right = ft_new_node(++str);
     /*root->left->right->left = ft_new_node(++str);
       root->left->right->right = ft_new_node(++str);
       root->left->right->right->left = ft_new_node(++str);
       root->left->right->right->right = ft_new_node(++str);
     root->right->right = ft_new_node(++str);
     root->right->left = ft_new_node(++str);
    root->right->right->right = ft_new_node(++str);
      root->right->right->right->right = ft_new_node(++str);
     // root->right->right->right->right->right = ft_new_node(++str);
      
       root->right->right->left = ft_new_node(++str);
    */
    data->ast = root;
}