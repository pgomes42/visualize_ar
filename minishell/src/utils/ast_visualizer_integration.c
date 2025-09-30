/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_visualizer_integration.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:00:00 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 12:00:00 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libast_visualizer.h"

/* ============================================================================ */
/*                        INTEGRAÇÃO COM MINISHELL                             */
/* ============================================================================ */

/**
 * @brief Converte o tipo t_type do minishell para string
 */
static char *get_type_string(t_type type)
{
    switch (type)
    {
        case T_COMAND:
            return ("COMMAND");
        case T_PIPE:
            return ("|");
        case T_IN_REDIR:
            return ("<");
        case T_OUT_APP_REDIR:
            return (">>");
        case T_OUT_SUB_REDIR:
            return (">");
        case T_HERODUC:
            return ("<<");
        default:
            return ("UNKNOWN");
    }
}

/**
 * @brief Converte a estrutura t_ast do minishell para t_ast_node da biblioteca
 */
static t_ast_node *convert_minishell_ast_to_lib(t_ast *minishell_ast)
{
    t_ast_node *lib_node;
    char *node_data;
    
    if (!minishell_ast)
        return (NULL);
    
    /* Determinar o dado do nó baseado no tipo */
    if (minishell_ast->type == T_COMAND)
    {
        /* Para comandos, usar o valor do comando */
        node_data = minishell_ast->value;
    }
    else
    {
        /* Para operadores, usar a string do tipo */
        node_data = get_type_string(minishell_ast->type);
    }
    
    /* Criar nó da biblioteca */
    lib_node = ast_node_create(node_data);
    if (!lib_node)
        return (NULL);
    
    /* Converter filhos recursivamente */
    lib_node->left = convert_minishell_ast_to_lib(minishell_ast->left);
    lib_node->right = convert_minishell_ast_to_lib(minishell_ast->right);
    
    return (lib_node);
}

/**
 * @brief Duplica uma AST do minishell para armazenamento
 */
static t_ast *duplicate_minishell_ast(t_ast *original)
{
    t_ast *copy;
    
    if (!original)
        return (NULL);
    
    copy = malloc(sizeof(t_ast));
    if (!copy)
        return (NULL);
    
    copy->type = original->type;
    copy->value = original->value ? ft_strdup(original->value) : NULL;
    copy->args = original->args; /* Compartilhado - não duplicar */
    copy->argv = original->argv; /* Compartilhado - não duplicar */
    copy->nb_args = original->nb_args;
    copy->left = duplicate_minishell_ast(original->left);
    copy->right = duplicate_minishell_ast(original->right);
    
    return (copy);
}

/**
 * @brief Libera AST duplicada
 */
static void free_duplicated_ast(t_ast *ast)
{
    if (!ast)
        return;
    
    free_duplicated_ast(ast->left);
    free_duplicated_ast(ast->right);
    
    if (ast->value)
        free(ast->value);
    
    free(ast);
}

/**
 * @brief Salva AST atual para visualização posterior
 */
void minishell_save_ast_for_visualization(t_data *data)
{
    if (!data || !data->ast || !data->line)
        return;
    
    /* Não salvar se for comando de visualização */
    if (ft_strncmp(data->line, "visualize", 9) == 0 ||
        ft_strncmp(data->line, "debug_ast", 9) == 0 ||
        ft_strncmp(data->line, "show_ast", 8) == 0)
        return;
    
    /* Liberar AST anterior se existir */
    if (data->last_ast_for_visualizer)
    {
        free_duplicated_ast(data->last_ast_for_visualizer);
        data->last_ast_for_visualizer = NULL;
    }
    
    /* Liberar comando anterior se existir */
    if (data->last_command_for_visualizer)
    {
        free(data->last_command_for_visualizer);
        data->last_command_for_visualizer = NULL;
    }
    
    /* Salvar nova AST e comando */
    data->last_ast_for_visualizer = duplicate_minishell_ast(data->ast);
    if (data->line)
        data->last_command_for_visualizer = ft_strdup(data->line);
}

/**
 * @brief Visualiza a AST salva anteriormente
 */
int minishell_visualize_saved_ast(t_data *data)
{
    t_ast_visualizer *visualizer;
    t_ast_node *lib_ast;
    char title[256];
    int result;
    
    if (!data || !data->last_ast_for_visualizer)
    {
        printf("❌ Nenhuma AST anterior disponível para visualização\n");
        printf("💡 Execute um comando primeiro, depois use 'visualize'\n");
        return (-1);
    }
    
    /* Inicializar visualizador */
    visualizer = ast_visualizer_init();
    if (!visualizer)
    {
        printf("❌ Erro ao inicializar visualizador\n");
        return (-1);
    }
    
    /* Converter AST salva para formato da biblioteca */
    lib_ast = convert_minishell_ast_to_lib(data->last_ast_for_visualizer);
    if (!lib_ast)
    {
        printf("❌ Erro ao converter AST\n");
        ast_visualizer_destroy(visualizer);
        return (-1);
    }
    
    /* Criar título personalizado */
    if (data->last_command_for_visualizer && strlen(data->last_command_for_visualizer) < 200)
        snprintf(title, sizeof(title), "Minishell AST: %s", data->last_command_for_visualizer);
    else
        snprintf(title, sizeof(title), "Minishell AST Visualizer");
    
    /* Mostrar informações da AST */
    printf("\n🎨 === VISUALIZADOR DE AST MINISHELL === 🎨\n");
    printf("📋 Comando anterior: %s\n", data->last_command_for_visualizer ? data->last_command_for_visualizer : "(vazio)");
    printf("📊 Nós na AST: %d\n", ast_node_count(lib_ast));
    printf("📏 Altura da AST: %d\n", ast_node_height(lib_ast));
    
    printf("\n📋 Estrutura da AST (texto):\n");
    ast_node_print(lib_ast, 0);
    
    /* Visualizar */
    printf("\n🎨 Abrindo visualizador gráfico... (ESC para fechar)\n");
    result = ast_visualizer_show(visualizer, lib_ast, title);
    
    /* Limpeza */
    ast_node_destroy(lib_ast);
    ast_visualizer_destroy(visualizer);
    
    if (result == 0)
        printf("✅ Visualização concluída\n");
    else
        printf("❌ Erro na visualização\n");
    
    return (result);
}

/**
 * @brief Função de conveniência para debug - NÃO MAIS USADA
 */
void minishell_check_debug_command(t_data *data)
{
    /* Função removida para evitar conflitos com o builtin visualize */
    (void)data;
}

/**
 * @brief Adiciona função de visualização como builtin
 */
int minishell_builtin_visualize(t_data *data, char **argv)
{
    (void)argv; /* Não usar argumentos por enquanto */
    
    printf("🎨 Executando visualizador de AST...\n");
    
    return (minishell_visualize_saved_ast(data));
}

/**
 * @brief Versão automática - visualiza sempre que há uma AST complexa
 */
void minishell_auto_visualize_complex_ast(t_data *data)
{
    int node_count;
    t_ast_node *lib_ast;
    
    if (!data || !data->last_ast_for_visualizer)
        return;
    
    /* Converter temporariamente para contar nós */
    lib_ast = convert_minishell_ast_to_lib(data->last_ast_for_visualizer);
    if (!lib_ast)
        return;
    
    node_count = ast_node_count(lib_ast);
    
    /* Se a AST é complexa (mais de 3 nós), oferecer visualização */
    if (node_count > 3)
    {
        printf("\n🤔 AST complexa detectada (%d nós). Visualizar? (y/n): ", node_count);
        
        char response[10];
        if (fgets(response, sizeof(response), stdin) && 
            (response[0] == 'y' || response[0] == 'Y'))
        {
            ast_node_destroy(lib_ast);
            minishell_visualize_saved_ast(data);
            return;
        }
    }
    
    ast_node_destroy(lib_ast);
}