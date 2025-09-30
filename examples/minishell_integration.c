/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_integration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:50:00 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/30 11:50:00 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libast_visualizer.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Exemplo de integração simples com Minishell
 * 
 * Este arquivo mostra como integrar facilmente a biblioteca
 * AST Visualizer no seu projeto Minishell.
 */

/* ============================================================================ */
/*                         FUNÇÃO PRINCIPAL DE DEBUG                           */
/* ============================================================================ */

/**
 * @brief Função de debug para visualizar AST no minishell
 * 
 * Adicione esta função ao seu minishell para visualizar
 * qualquer AST durante o desenvolvimento/debug.
 * 
 * @param ast AST criada pelo seu parser
 * @param command_line Linha de comando original (para título)
 */
void minishell_debug_ast(t_ast_node *ast, const char *command_line)
{
    t_ast_visualizer *visualizer;
    char title[256];
    
    if (!ast)
    {
        printf("⚠️  AST é NULL - nada para visualizar\n");
        return;
    }
    
    printf("🔍 DEBUG: Visualizando AST...\n");
    
    /* Mostrar estatísticas */
    printf("📊 Estatísticas:\n");
    printf("   └─ Nós: %d\n", ast_node_count(ast));
    printf("   └─ Altura: %d\n", ast_node_height(ast));
    
    /* Mostrar estrutura em texto */
    printf("📋 Estrutura:\n");
    ast_node_print(ast, 0);
    
    /* Preparar título */
    if (command_line)
        snprintf(title, sizeof(title), "Minishell Debug: %s", command_line);
    else
        snprintf(title, sizeof(title), "Minishell Debug");
    
    /* Inicializar visualizador */
    visualizer = ast_visualizer_init();
    if (!visualizer)
    {
        printf("❌ Erro ao inicializar visualizador\n");
        return;
    }
    
    /* Mostrar visualização */
    printf("🎨 Abrindo janela... (ESC para fechar)\n");
    ast_visualizer_show(visualizer, ast, title);
    
    /* Limpeza */
    ast_visualizer_destroy(visualizer);
    printf("✅ Visualização concluída\n");
}

/* ============================================================================ */
/*                       FUNÇÕES DE CONVERSÃO PARA MINISHELL                  */
/* ============================================================================ */

/**
 * @brief Converte linha de comando simples em AST
 * 
 * Esta é uma função de exemplo. No seu minishell, você
 * provavelmente já tem um parser mais sofisticado.
 */
t_ast_node *parse_simple_command(const char *command_line)
{
    t_ast_node *ast = NULL;
    
    /* Exemplo: detectar pipes simples */
    if (strstr(command_line, " | "))
    {
        /* Dividir em cmd1 e cmd2 (implementação simplificada) */
        char *pipe_pos = strstr(command_line, " | ");
        char cmd1[256], cmd2[256];
        
        /* Extrair primeiro comando */
        int len1 = pipe_pos - command_line;
        strncpy(cmd1, command_line, len1);
        cmd1[len1] = '\0';
        
        /* Extrair segundo comando */
        strcpy(cmd2, pipe_pos + 3);
        
        /* Criar AST */
        ast = ast_quick_pipe(cmd1, cmd2);
    }
    /* Exemplo: detectar AND */
    else if (strstr(command_line, " && "))
    {
        char *and_pos = strstr(command_line, " && ");
        char cmd1[256], cmd2[256];
        
        int len1 = and_pos - command_line;
        strncpy(cmd1, command_line, len1);
        cmd1[len1] = '\0';
        
        strcpy(cmd2, and_pos + 4);
        
        ast = ast_quick_and(cmd1, cmd2);
    }
    /* Exemplo: detectar OR */
    else if (strstr(command_line, " || "))
    {
        char *or_pos = strstr(command_line, " || ");
        char cmd1[256], cmd2[256];
        
        int len1 = or_pos - command_line;
        strncpy(cmd1, command_line, len1);
        cmd1[len1] = '\0';
        
        strcpy(cmd2, or_pos + 4);
        
        ast = ast_quick_or(cmd1, cmd2);
    }
    /* Comando simples */
    else
    {
        ast = ast_node_command(command_line);
    }
    
    return (ast);
}

/* ============================================================================ */
/*                              EXEMPLO DE USO                                 */
/* ============================================================================ */

int main(void)
{
    t_ast_node *ast;
    char command_line[256];
    
    printf("🐚 === EXEMPLO DE INTEGRAÇÃO MINISHELL === 🐚\n");
    printf("\nEste exemplo mostra como integrar o visualizador no seu minishell.\n");
    printf("Digite um comando para visualizar (ou 'exit' para sair):\n\n");
    
    while (1)
    {
        printf("minishell> ");
        fflush(stdout);
        
        if (!fgets(command_line, sizeof(command_line), stdin))
            break;
        
        /* Remover newline */
        command_line[strcspn(command_line, "\n")] = '\0';
        
        /* Verificar saída */
        if (strcmp(command_line, "exit") == 0)
            break;
        
        if (strlen(command_line) == 0)
            continue;
        
        /* Parsear comando */
        ast = parse_simple_command(command_line);
        if (!ast)
        {
            printf("❌ Erro ao parsear comando\n");
            continue;
        }
        
        /* Visualizar AST */
        minishell_debug_ast(ast, command_line);
        
        /* Limpeza */
        ast_node_destroy(ast);
    }
    
    printf("👋 Saindo...\n");
    return (0);
}

/* ============================================================================ */
/*                         COMO INTEGRAR NO SEU MINISHELL                      */
/* ============================================================================ */

/*

1. COPIAR ARQUIVOS:
   - Copie lib_ast/libast_visualizer.a para o diretório lib do seu minishell
   - Copie includes/libast_visualizer.h para o diretório includes do seu minishell

2. MODIFICAR MAKEFILE:
   Adicione estas linhas ao seu Makefile:
   
   LIBS += -Llib -last_visualizer -lmlx -lmlx_Linux -lX11 -lXext -lm
   INCLUDES += -Iincludes

3. INCLUIR NO CÓDIGO:
   Adicione no início dos seus arquivos .c:
   
   #include "libast_visualizer.h"

4. ADICIONAR FUNÇÃO DE DEBUG:
   Copie a função minishell_debug_ast() acima para o seu código.

5. USAR DURANTE DESENVOLVIMENTO:
   No seu parser, adicione:
   
   // t_ast_node *my_ast = parse_your_command(command_line);
   
   // Para debug durante desenvolvimento:
   #ifdef DEBUG
   minishell_debug_ast(my_ast, command_line);
   #endif

6. COMPILAR:
   cc -Wall -Wextra -Werror -DDEBUG *.c -Iincludes -Llib -last_visualizer -lmlx -lmlx_Linux -lX11 -lXext -lm -o minishell

7. EXEMPLO DE INTEGRAÇÃO:
   
   // No seu main loop do minishell:
   while (1)
   {
       char *line = readline("minishell> ");
       t_ast_node *ast = parse_command_line(line);
       
       #ifdef DEBUG
       minishell_debug_ast(ast, line);
       #endif
       
       execute_ast(ast);
       ast_node_destroy(ast);
       free(line);
   }

*/