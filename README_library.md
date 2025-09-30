# 🎨 AST Visualizer Library

Uma biblioteca para visualizar Árvores Sintáticas Abstratas (AST) desenvolvida especificamente para integração com projetos Minishell da 42.

## 📋 Características

- ✅ **API Simples**: Interface fácil de usar com funções intuitivas
- ✅ **Colorido**: Visualização com cores para diferentes tipos de nós
- ✅ **Interativo**: Controles de navegação com teclado
- ✅ **Memória Segura**: Gerenciamento automático de memória
- ✅ **Portável**: Compilação limpa em sistemas Linux

## 🎨 Sistema de Cores

- 🟢 **Verde**: Comandos simples (`ls`, `cat`, `echo`, etc.)
- 🔵 **Azul**: Operador pipe (`|`)
- 🟡 **Dourado**: Operador AND lógico (`&&`)
- 🟠 **Laranja**: Operador OR lógico (`||`)
- 🟣 **Rosa**: Redirecionamentos (`>`, `>>`, `<`)

## 🚀 Instalação Rápida

### 1. Compilar a Biblioteca

```bash
# Entrar no diretório do visualizador
cd visualize_ar

# Compilar a biblioteca
make -f Makefile.lib

# Verificar se foi criada
ls lib_ast/libast_visualizer.a
```

### 2. Instalar no Minishell

```bash
# Instalar automaticamente no diretório do minishell
make -f Makefile.lib install

# Ou copiar manualmente
cp lib_ast/libast_visualizer.a ../minishell/lib/
cp includes/libast_visualizer.h ../minishell/includes/
```

## 📖 Como Usar no Minishell

### 1. Incluir Header

```c
#include "libast_visualizer.h"
```

### 2. Exemplo Básico

```c
#include "libast_visualizer.h"

int main(void)
{
    t_ast_visualizer *visualizer;
    t_ast_node *ast;
    
    // Inicializar visualizador
    visualizer = ast_visualizer_init();
    if (!visualizer)
        return (1);
    
    // Criar AST simples: ls -la | grep .txt
    ast = ast_quick_pipe("ls -la", "grep .txt");
    if (!ast)
    {
        ast_visualizer_destroy(visualizer);
        return (1);
    }
    
    // Visualizar
    ast_visualizer_show(visualizer, ast, "Meu Minishell - AST");
    
    // Limpeza
    ast_node_destroy(ast);
    ast_visualizer_destroy(visualizer);
    
    return (0);
}
```

### 3. Compilar com a Biblioteca

```bash
cc -Wall -Wextra -Werror meu_minishell.c \
   -Iincludes \
   -Llib_ast -last_visualizer \
   -Llib/minilibx-linux -lmlx -lmlx_Linux \
   -lX11 -lXext -lm \
   -o minishell
```

## 🔧 API Completa

### Inicialização

```c
// Inicializar visualizador
t_ast_visualizer *ast_visualizer_init(void);

// Mostrar AST
int ast_visualizer_show(t_ast_visualizer *visualizer, 
                       t_ast_node *ast, 
                       const char *title);

// Destruir visualizador
void ast_visualizer_destroy(t_ast_visualizer *visualizer);
```

### Criação de Nós

```c
// Criar nó genérico
t_ast_node *ast_node_create(const char *data);

// Criar nós específicos
t_ast_node *ast_node_command(const char *command);
t_ast_node *ast_node_pipe(t_ast_node *left, t_ast_node *right);
t_ast_node *ast_node_and(t_ast_node *left, t_ast_node *right);
t_ast_node *ast_node_or(t_ast_node *left, t_ast_node *right);
t_ast_node *ast_node_redirect(t_ast_node *command, const char *redirect);
```

### Funções Rápidas

```c
// Criar pipes rapidamente
t_ast_node *ast_quick_pipe(const char *cmd1, const char *cmd2);
t_ast_node *ast_quick_and(const char *cmd1, const char *cmd2);
t_ast_node *ast_quick_or(const char *cmd1, const char *cmd2);
```

### Gerenciamento de Memória

```c
// Liberar AST
void ast_node_destroy(t_ast_node *ast);

// Duplicar AST
t_ast_node *ast_node_duplicate(const t_ast_node *ast);
```

### Utilitários

```c
// Debug - imprimir AST em texto
void ast_node_print(const t_ast_node *ast, int depth);

// Estatísticas
int ast_node_count(const t_ast_node *ast);
int ast_node_height(const t_ast_node *ast);
```

## 🎮 Controles da Interface

- **⬅️➡️⬆️⬇️**: Mover visualização
- **ESC**: Fechar janela
- **Mouse**: Navegação (futuro)

## 📝 Exemplos Práticos

### Exemplo 1: Pipe Simples
```c
// ls -la | grep .txt
t_ast_node *ast = ast_quick_pipe("ls -la", "grep .txt");
ast_visualizer_show(visualizer, ast, "Pipe Simples");
```

### Exemplo 2: Comando com AND
```c
// make && ./programa
t_ast_node *ast = ast_quick_and("make", "./programa");
ast_visualizer_show(visualizer, ast, "Build e Execute");
```

### Exemplo 3: AST Complexa
```c
// (cat file.txt | sort) && echo "sorted"
t_ast_node *pipe_part = ast_quick_pipe("cat file.txt", "sort");
t_ast_node *echo_part = ast_node_command("echo sorted");
t_ast_node *final_ast = ast_node_and(pipe_part, echo_part);

ast_visualizer_show(visualizer, final_ast, "AST Complexa");
```

### Exemplo 4: OR com Fallback
```c
// comando_principal || echo "erro"
t_ast_node *ast = ast_quick_or("comando_principal", "echo erro");
ast_visualizer_show(visualizer, ast, "Comando com Fallback");
```

## 🧪 Testar a Biblioteca

```bash
# Compilar exemplo de teste
make -f Makefile.lib example

# Executar teste
./example_ast
```

## 📁 Estrutura de Arquivos

```
visualize_ar/
├── includes/
│   ├── libast_visualizer.h    # Header público da biblioteca
│   └── visualizer_ar.h        # Header interno
├── src/
│   ├── libast_visualizer.c    # Implementação da API pública
│   ├── ast.c                  # Funções de AST
│   ├── render.c               # Funções de renderização
│   └── ast_adapter.c          # Funções auxiliares
├── lib_ast/
│   ├── libast_visualizer.a    # Biblioteca compilada
│   └── obj/                   # Objetos da biblioteca
├── examples/
│   └── test_lib.c             # Exemplo de uso
├── Makefile.lib               # Makefile da biblioteca
└── README_library.md          # Esta documentação
```

## 🔧 Troubleshooting

### Erro de Compilação MinilibX
```bash
# Instalar dependências no Ubuntu/Debian
sudo apt-get install libx11-dev libxext-dev

# Recompilar MinilibX
make -C lib/minilibx-linux clean
make -C lib/minilibx-linux
```

### Erro de Linking
```bash
# Verificar se as flags estão corretas
-Llib_ast -last_visualizer -Llib/minilibx-linux -lmlx -lmlx_Linux -lX11 -lXext -lm
```

### Erro de Display
```bash
# Se estiver usando SSH, habilitar X11 forwarding
ssh -X usuario@servidor

# Ou definir DISPLAY
export DISPLAY=:0
```

## 🎯 Integração com Minishell

### No seu parser de minishell:

```c
// Quando criar a AST do comando
t_ast_node *create_ast_from_tokens(t_token *tokens)
{
    t_ast_node *ast = NULL;
    
    // Seu código de parsing aqui...
    // Por exemplo, detectar pipes:
    if (has_pipe(tokens))
    {
        char *cmd1 = extract_command_before_pipe(tokens);
        char *cmd2 = extract_command_after_pipe(tokens);
        ast = ast_quick_pipe(cmd1, cmd2);
    }
    // Detectar AND:
    else if (has_and(tokens))
    {
        char *cmd1 = extract_command_before_and(tokens);
        char *cmd2 = extract_command_after_and(tokens);
        ast = ast_quick_and(cmd1, cmd2);
    }
    // Comando simples:
    else
    {
        char *cmd = extract_simple_command(tokens);
        ast = ast_node_command(cmd);
    }
    
    return (ast);
}

// Função de debug para mostrar AST
void debug_show_ast(t_ast_node *ast)
{
    t_ast_visualizer *visualizer;
    
    if (!ast)
        return;
    
    visualizer = ast_visualizer_init();
    if (!visualizer)
        return;
    
    printf("🔍 Debug: Mostrando AST...\n");
    ast_node_print(ast, 0);  // Print em texto
    
    ast_visualizer_show(visualizer, ast, "Minishell Debug - AST");
    
    ast_visualizer_destroy(visualizer);
}
```

## 📚 Recursos Adicionais

- **Header público**: `includes/libast_visualizer.h`
- **Exemplo completo**: `examples/test_lib.c`
- **Makefile**: `Makefile.lib`

## 👥 Suporte

Para dúvidas ou problemas:
1. Verificar a documentação no header `libast_visualizer.h`
2. Executar o exemplo: `make -f Makefile.lib example && ./example_ast`
3. Verificar dependências do MinilibX

---
*Desenvolvido para projetos Minishell da 42* 🚀