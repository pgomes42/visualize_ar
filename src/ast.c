/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:21:44 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/25 21:53:43 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer_ar.h"

static t_ast *ft_new_node(void *data)
{
    t_ast *new;

    new = (t_ast *)malloc(sizeof(t_ast));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return (new);
}

void ft_creat_ast(t_data *data)
{
    t_ast *root;
    char *str;

    str ="no";
    root = ft_new_node(str);
    root->left = ft_new_node(str);
     root->left->left = ft_new_node(str);
     root->right = ft_new_node(str);
     root->left->right = ft_new_node(str);
     root->right->right = ft_new_node(str);
    data->ast = root;
}