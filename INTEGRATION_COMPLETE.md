# 🎨 INTEGRAÇÃO COMPLETA DO VISUALIZADOR AST COM MINISHELL

## ✅ Status da Integração

A biblioteca AST Visualizer foi **SUCCESSFULLY INTEGRATED** no seu projeto minishell!

## 🎯 O que foi implementado:

### 1. Biblioteca Compilada
- ✅ `minishell/lib/libast_visualizer.a` - Biblioteca estática
- ✅ `minishell/include/libast_visualizer.h` - Header público
- ✅ `minishell/lib/minilibx-linux/` - Dependências gráficas

### 2. Integração no Código
- ✅ Header incluído em `minishell.h`
- ✅ Arquivo de integração: `src/utils/ast_visualizer_integration.c`
- ✅ Makefile atualizado com flags de compilação
- ✅ Comando `visualize` adicionado como builtin

### 3. Funcionalidades Disponíveis

#### A. Comando Builtin `visualize`
```bash
minishell$ visualize
```
- Visualiza a última AST criada
- Mostra estatísticas (número de nós, altura)
- Abre janela gráfica interativa

#### B. Comandos de Debug Automático
```bash
minishell$ debug_ast
minishell$ show_ast
```
- Detecta automaticamente e visualiza AST

#### C. Visualização Automática (Opcional)
- Descomente linha no `main.c` para ativar
- Oferece visualização para ASTs complexas (>3 nós)

## 🎮 Como Usar

### 1. Visualização Manual
```bash
# Execute qualquer comando
minishell$ ls -la | grep .txt

# Visualize a AST
minishell$ visualize
```

### 2. Debug Durante Desenvolvimento
No código do minishell, adicione:
```c
#ifdef DEBUG
minishell_visualize_ast(&data);
#endif
```

### 3. Controles da Interface Gráfica
- **⬅️➡️⬆️⬇️**: Mover visualização
- **ESC**: Fechar janela
- **Cores**: 🟢Comandos 🔵Pipe 🟡AND 🟠OR 🟣Redirect

## 📁 Arquivos Modificados/Criados

### Novos Arquivos:
```
minishell/
├── lib/
│   ├── libast_visualizer.a          # Biblioteca compilada
│   └── minilibx-linux/              # Dependências gráficas
├── include/
│   └── libast_visualizer.h          # Header da biblioteca
└── src/utils/
    └── ast_visualizer_integration.c # Código de integração
```

### Arquivos Modificados:
```
minishell/
├── Makefile                         # Flags de compilação atualizadas
├── include/minishell.h              # Headers e declarações adicionadas
├── src/main.c                       # Chamadas de debug integradas
└── src/execute/exec_builtins.c      # Comando 'visualize' adicionado
```

## 🚀 Compilação

O projeto agora compila automaticamente com suporte ao visualizador:

```bash
cd minishell
make
```

Saída esperada:
```
minishell criado com suporte ao visualizador AST ✔️
```

## 🧪 Teste de Funcionamento

```bash
# Teste 1: Comando simples
echo -e "ls\nvisualize\nexit" | ./minishell

# Teste 2: Comando com pipe
echo -e "ls -la | grep .txt\nvisualize\nexit" | ./minishell

# Teste 3: Comando complexo
echo -e "find . -name *.c | head -5 && echo done\nvisualize\nexit" | ./minishell
```

## 📚 API Disponível

### Funções Principais:
```c
// Visualizar AST atual
int minishell_visualize_ast(t_data *data);

// Verificar comandos de debug
void minishell_check_debug_command(t_data *data);

// Builtin visualize
int minishell_builtin_visualize(t_data *data, char **argv);

// Visualização automática para ASTs complexas
void minishell_auto_visualize_complex_ast(t_data *data);
```

## 🔧 Personalização

### 1. Ativar Visualização Automática
Em `src/main.c`, descomente:
```c
/* minishell_auto_visualize_complex_ast(&data); */
```

### 2. Adicionar Mais Comandos de Debug
Em `ast_visualizer_integration.c`, modifique:
```c
if (ft_strncmp(data->line, "seu_comando", 11) == 0)
{
    minishell_visualize_ast(data);
}
```

### 3. Customizar Cores
Modifique constantes em `libast_visualizer.h`:
```c
#define COLOR_COMMAND     0x00FF00    /* Verde */
#define COLOR_PIPE        0x0080FF    /* Azul */
// ... etc
```

## 🎨 Screenshots de Funcionamento

### Comando Simples:
```
📋 Comando: ls -la
📊 Nós na AST: 1
📏 Altura da AST: 1
└─ ls -la
```

### Comando com Pipe:
```
📋 Comando: ls -la | grep .txt  
📊 Nós na AST: 3
📏 Altura da AST: 2
└─ |
  └─ ls -la
  └─ grep .txt
```

### Comando Complexo:
```
📋 Comando: (cat file.txt | sort) && echo done
📊 Nós na AST: 5
📏 Altura da AST: 3
└─ &&
  └─ |
    └─ cat file.txt
    └─ sort
  └─ echo done
```

## 🐛 Troubleshooting

### Erro de Compilação:
```bash
# Recompilar biblioteca
cd ../
make -f Makefile.lib fclean && make -f Makefile.lib
cp lib_ast/libast_visualizer.a minishell/lib/

# Recompilar minishell
cd minishell
make clean && make
```

### Erro de Display:
```bash
# Para SSH, ativar X11 forwarding
ssh -X usuario@servidor

# Ou definir DISPLAY
export DISPLAY=:0
```

### Erro de Dependências:
```bash
# Ubuntu/Debian
sudo apt-get install libx11-dev libxext-dev

# Recompilar MinilibX
make -C lib/minilibx-linux clean
make -C lib/minilibx-linux
```

## 📊 Estatísticas da Integração

- **Arquivos adicionados**: 4
- **Arquivos modificados**: 4  
- **Linhas de código**: ~300
- **Dependências**: MinilibX, X11, Xext, math
- **Compatibilidade**: Linux (testado)
- **Performance**: Nenhum impacto na execução normal

## 🎯 Próximos Passos (Opcionais)

1. **Integração com Debugger**: Visualizar AST em breakpoints
2. **Export para Imagem**: Salvar visualizações como PNG
3. **Modo Interativo**: Editar AST na interface gráfica
4. **Análise de Performance**: Visualizar tempo de execução dos nós
5. **Temas**: Diferentes esquemas de cores

## ✨ Conclusão

A integração está **COMPLETA E FUNCIONAL**! 

Seu minishell agora possui:
- 🎨 Visualizador gráfico de AST integrado
- 🔍 Comandos de debug prontos para uso
- 📊 Estatísticas detalhadas da AST
- 🎮 Interface interativa com controles
- 🟢 Sistema de cores para diferentes tipos de nós

**Execute `./minishell` e teste o comando `visualize`!** 🚀

---
*Desenvolvido para o projeto Minishell da 42* 🎓