/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:30:00 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 12:00:00 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libast_visualizer.h"
#include <stdio.h>

/**
 * @brief Exemplo de uso da biblioteca AST Visualizer
 * 
 * Este arquivo demonstra como usar a biblioteca libast_visualizer
 * para visualizar árvores sintáticas abstratas no seu minishell.
 */

void test_simple_example(void)
{
    t_ast_visualizer *visualizer;
    t_ast_node *ast;
    
    printf("\n=== TESTE 1: Exemplo Simples ===\n");
    printf("Comando: ls -la | grep .txt\n");
    
    /* Inicializar visualizador */
    visualizer = ast_visualizer_init();
    if (!visualizer)
    {
        printf("❌ Erro ao inicializar visualizador\n");
        return;
    }
    
    /* Criar AST simples */
    ast = ast_create_example_simple();
    if (!ast)
    {
        printf("❌ Erro ao criar AST\n");
        ast_visualizer_destroy(visualizer);
        return;
    }
    
    /* Mostrar informações */
    printf("📊 Estatísticas da AST:\n");
    printf("   Nós: %d\n", ast_node_count(ast));
    printf("   Altura: %d\n", ast_node_height(ast));
    
    printf("\n📋 Estrutura da AST:\n");
    ast_node_print(ast, 0);
    
    /* Visualizar */
    printf("\n🎨 Abrindo visualizador... (ESC para fechar)\n");
    ast_visualizer_show(visualizer, ast, "Exemplo Simples: ls -la | grep .txt");
    
    /* Limpeza */
    ast_node_destroy(ast);
    ast_visualizer_destroy(visualizer);
}

void test_complex_example(void)
{
    t_ast_visualizer *visualizer;
    t_ast_node *ast;
    
    printf("\n=== TESTE 2: Exemplo Complexo ===\n");
    printf("Comando: (cat file.txt | sort) && echo sorted\n");
    
    /* Inicializar visualizador */
    visualizer = ast_visualizer_init();
    if (!visualizer)
    {
        printf("❌ Erro ao inicializar visualizador\n");
        return;
    }
    
    /* Criar AST complexa */
    ast = ast_create_example_complex();
    if (!ast)
    {
        printf("❌ Erro ao criar AST\n");
        ast_visualizer_destroy(visualizer);
        return;
    }
    
    /* Mostrar informações */
    printf("📊 Estatísticas da AST:\n");
    printf("   Nós: %d\n", ast_node_count(ast));
    printf("   Altura: %d\n", ast_node_height(ast));
    
    printf("\n📋 Estrutura da AST:\n");
    ast_node_print(ast, 0);
    
    /* Visualizar */
    printf("\n🎨 Abrindo visualizador... (ESC para fechar)\n");
    ast_visualizer_show(visualizer, ast, "Exemplo Complexo: (cat | sort) && echo");
    
    /* Limpeza */
    ast_node_destroy(ast);
    ast_visualizer_destroy(visualizer);
}

void test_manual_creation(void)
{
    t_ast_visualizer *visualizer;
    t_ast_node *cmd1, *cmd2, *cmd3, *pipe_node, *and_node, *final_ast;
    
    printf("\n=== TESTE 3: Criação Manual ===\n");
    printf("Comando: find . -name *.c | wc -l && echo contado\n");
    
    /* Inicializar visualizador */
    visualizer = ast_visualizer_init();
    if (!visualizer)
    {
        printf("❌ Erro ao inicializar visualizador\n");
        return;
    }
    
    /* Criar nós manualmente */
    cmd1 = ast_node_command("find . -name *.c");
    cmd2 = ast_node_command("wc -l");
    cmd3 = ast_node_command("echo contado");
    
    if (!cmd1 || !cmd2 || !cmd3)
    {
        printf("❌ Erro ao criar comandos\n");
        if (cmd1) ast_node_destroy(cmd1);
        if (cmd2) ast_node_destroy(cmd2);
        if (cmd3) ast_node_destroy(cmd3);
        ast_visualizer_destroy(visualizer);
        return;
    }
    
    /* Criar pipe */
    pipe_node = ast_node_pipe(cmd1, cmd2);
    if (!pipe_node)
    {
        printf("❌ Erro ao criar pipe\n");
        ast_node_destroy(cmd1);
        ast_node_destroy(cmd2);
        ast_node_destroy(cmd3);
        ast_visualizer_destroy(visualizer);
        return;
    }
    
    /* Criar AND */
    and_node = ast_node_and(pipe_node, cmd3);
    if (!and_node)
    {
        printf("❌ Erro ao criar AND\n");
        ast_node_destroy(pipe_node);
        ast_node_destroy(cmd3);
        ast_visualizer_destroy(visualizer);
        return;
    }
    
    final_ast = and_node;
    
    /* Mostrar informações */
    printf("📊 Estatísticas da AST:\n");
    printf("   Nós: %d\n", ast_node_count(final_ast));
    printf("   Altura: %d\n", ast_node_height(final_ast));
    
    printf("\n📋 Estrutura da AST:\n");
    ast_node_print(final_ast, 0);
    
    /* Visualizar */
    printf("\n🎨 Abrindo visualizador... (ESC para fechar)\n");
    ast_visualizer_show(visualizer, final_ast, "Criação Manual: find | wc && echo");
    
    /* Limpeza */
    ast_node_destroy(final_ast);
    ast_visualizer_destroy(visualizer);
}

void test_quick_functions(void)
{
    t_ast_visualizer *visualizer;
    t_ast_node *ast;
    
    printf("\n=== TESTE 4: Funções Rápidas ===\n");
    printf("Comando: make clean || echo erro\n");
    
    /* Inicializar visualizador */
    visualizer = ast_visualizer_init();
    if (!visualizer)
    {
        printf("❌ Erro ao inicializar visualizador\n");
        return;
    }
    
    /* Usar função rápida */
    ast = ast_quick_or("make clean", "echo erro");
    if (!ast)
    {
        printf("❌ Erro ao criar AST com função rápida\n");
        ast_visualizer_destroy(visualizer);
        return;
    }
    
    /* Mostrar informações */
    printf("📊 Estatísticas da AST:\n");
    printf("   Nós: %d\n", ast_node_count(ast));
    printf("   Altura: %d\n", ast_node_height(ast));
    
    printf("\n📋 Estrutura da AST:\n");
    ast_node_print(ast, 0);
    
    /* Visualizar */
    printf("\n🎨 Abrindo visualizador... (ESC para fechar)\n");
    ast_visualizer_show(visualizer, ast, "Função Rápida: make clean || echo erro");
    
    /* Limpeza */
    ast_node_destroy(ast);
    ast_visualizer_destroy(visualizer);
}

int main(void)
{
    int choice;
    
    printf("🎨 === TESTE DA BIBLIOTECA AST VISUALIZER === 🎨\n");
    printf("\nEste programa demonstra como usar a biblioteca libast_visualizer\n");
    printf("para visualizar ASTs no seu minishell.\n");
    
    printf("\nEscolha um teste:\n");
    printf("1. Exemplo simples (ls | grep)\n");
    printf("2. Exemplo complexo ((cat | sort) && echo)\n");
    printf("3. Criação manual (find | wc && echo)\n");
    printf("4. Funções rápidas (make || echo)\n");
    printf("0. Sair\n");
    
    printf("\nDigite sua escolha: ");
    scanf("%d", &choice);
    
    switch (choice)
    {
        case 1:
            test_simple_example();
            break;
        case 2:
            test_complex_example();
            break;
        case 3:
            test_manual_creation();
            break;
        case 4:
            test_quick_functions();
            break;
        case 0:
            printf("👋 Saindo...\n");
            break;
        default:
            printf("❌ Escolha inválida\n");
            break;
    }
    
    return (0);
}