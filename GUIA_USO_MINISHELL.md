# 🎨 GUIA PRÁTICO: Como Usar o Visualizador AST no Minishell

## 🚀 Início Rápido

### 1. Executar o Minishell
```bash
cd /home/pgomes/Cadete/visualize_ar/minishell
./minishell
```

### 2. Comandos Básicos com Visualização

#### A. Comando Simples
```bash
minishell$ ls -la
# Execute o comando normalmente
# Depois visualize:
minishell$ visualize
```

#### B. Comando com Pipe
```bash
minishell$ ls -la | grep .txt
# Após executar, visualize:
minishell$ visualize
```

#### C. Comando com AND (&&)
```bash
minishell$ make && echo "sucesso"
minishell$ visualize
```

#### D. Comando com OR (||)
```bash
minishell$ false || echo "erro tratado"
minishell$ visualize
```

## 🎯 Formas de Visualizar

### Método 1: Comando Builtin `visualize`
```bash
minishell$ [qualquer comando]
minishell$ visualize
```
- ✅ Mais comum e direto
- ✅ Funciona com qualquer comando anterior
- ✅ Mostra estatísticas detalhadas

### Método 2: Comandos de Debug Automático
```bash
minishell$ debug_ast
# OU
minishell$ show_ast
```
- ✅ Detecta automaticamente
- ✅ Usa a última AST criada

### Método 3: Palavra-chave especial
```bash
minishell$ visualize_command
```
- ✅ Funciona imediatamente

## 📊 O que Você Verá

### Informações Exibidas:
```
🎨 === VISUALIZADOR DE AST MINISHELL === 🎨
📋 Comando: ls -la | grep .txt
📊 Nós na AST: 3
📏 Altura da AST: 2

📋 Estrutura da AST (texto):
└─ |
  └─ ls -la
  └─ grep .txt

🎨 Abrindo visualizador gráfico... (ESC para fechar)
```

### Interface Gráfica:
- **🟢 Verde**: Comandos simples (`ls`, `cat`, `echo`)
- **🔵 Azul**: Operador pipe (`|`)
- **🟡 Dourado**: Operador AND (`&&`)
- **🟠 Laranja**: Operador OR (`||`)
- **🟣 Rosa**: Redirecionamentos (`>`, `>>`, `<`)

## 🎮 Controles da Interface

### Navegação:
- **⬅️**: Mover para esquerda
- **➡️**: Mover para direita
- **⬆️**: Mover para cima
- **⬇️**: Mover para baixo
- **ESC**: Fechar janela

## 💡 Exemplos Práticos

### Exemplo 1: Pipeline Simples
```bash
minishell$ cat /etc/passwd | head -5 | grep root
minishell$ visualize
```
**Resultado**: AST com 2 pipes conectando 3 comandos

### Exemplo 2: Condicional com AND
```bash
minishell$ cd /tmp && ls -la
minishell$ visualize
```
**Resultado**: AST mostrando estrutura condicional

### Exemplo 3: Fallback com OR
```bash
minishell$ comando_inexistente || echo "comando falhou"
minishell$ visualize
```
**Resultado**: AST com estrutura de fallback

### Exemplo 4: Redirecionamento
```bash
minishell$ echo "teste" > arquivo.txt
minishell$ visualize
```
**Resultado**: AST mostrando redirecionamento de saída

### Exemplo 5: Comando Complexo
```bash
minishell$ (find . -name "*.c" | wc -l) && echo "arquivos C contados"
minishell$ visualize
```
**Resultado**: AST complexa com subshell, pipe e AND

## 🔍 Debug Durante Desenvolvimento

### Para Desenvolvedores:
Se você quiser adicionar visualização automática durante o desenvolvimento:

1. **Edite `src/main.c`**
2. **Descomente a linha:**
   ```c
   /* minishell_auto_visualize_complex_ast(&data); */
   ```
3. **Recompile:**
   ```bash
   make clean && make
   ```

Agora ASTs complexas (>3 nós) perguntarão automaticamente se você quer visualizar.

## 🛠️ Comandos de Teste

### Sequência de Testes Completa:
```bash
# Teste 1: Comando simples
minishell$ echo "Hello World"
minishell$ visualize

# Teste 2: Pipe simples
minishell$ ls | head -3
minishell$ visualize

# Teste 3: Pipe duplo
minishell$ cat /etc/passwd | grep root | wc -l
minishell$ visualize

# Teste 4: AND condicional
minishell$ true && echo "sucesso"
minishell$ visualize

# Teste 5: OR fallback
minishell$ false || echo "falhou"
minishell$ visualize

# Teste 6: Redirecionamento
minishell$ echo "teste" > /tmp/teste.txt
minishell$ visualize

# Teste 7: Comando complexo
minishell$ ls -la | grep ".txt" && echo "encontrados"
minishell$ visualize
```

## 📋 Interpretação dos Resultados

### Estatísticas:
- **Nós**: Número total de elementos na AST
- **Altura**: Profundidade máxima da árvore

### Estrutura Textual:
```
└─ |                    # Nó raiz (pipe)
  └─ ls -la            # Filho esquerdo (comando)
  └─ grep .txt         # Filho direito (comando)
```

### Cores na Interface Gráfica:
- **Verde**: Folhas da árvore (comandos executáveis)
- **Azul/Dourado/Laranja**: Nós intermediários (operadores)
- **Rosa**: Redirecionamentos

## ⚠️ Troubleshooting

### Problema: "Nenhuma AST disponível"
**Solução**: Execute um comando antes de usar `visualize`
```bash
minishell$ ls        # Execute algo primeiro
minishell$ visualize # Agora funciona
```

### Problema: Interface não abre
**Solução**: Verificar ambiente gráfico
```bash
# Se usando SSH:
ssh -X usuario@servidor

# Ou definir DISPLAY:
export DISPLAY=:0
```

### Problema: Comando não reconhecido
**Solução**: Verificar se foi compilado corretamente
```bash
make clean && make
```

## 🎯 Casos de Uso Avançados

### 1. Análise de Performance
Use para entender como comandos complexos são estruturados:
```bash
minishell$ find . -type f -name "*.c" | xargs grep -l "main" | head -10
minishell$ visualize
```

### 2. Debug de Parser
Verifique se seu parser está criando a AST correta:
```bash
minishell$ comando_complicado && (echo ok || echo erro)
minishell$ visualize
```

### 3. Educacional
Entenda precedência de operadores:
```bash
minishell$ cmd1 || cmd2 && cmd3
minishell$ visualize
# vs
minishell$ (cmd1 || cmd2) && cmd3
minishell$ visualize
```

## 📚 Referência Rápida

### Comandos Disponíveis:
| Comando | Função |
|---------|--------|
| `visualize` | Visualiza última AST |
| `debug_ast` | Debug automático |
| `show_ast` | Sinônimo de debug_ast |

### Cores dos Nós:
| Cor | Elemento |
|-----|----------|
| 🟢 Verde | Comandos |
| 🔵 Azul | Pipe (\|) |
| 🟡 Dourado | AND (&&) |
| 🟠 Laranja | OR (\|\|) |
| 🟣 Rosa | Redirect (>, <) |

### Controles:
| Tecla | Ação |
|-------|------|
| ⬅️➡️⬆️⬇️ | Navegar |
| ESC | Fechar |

---

## 🚀 Começe Agora!

1. **Abra o minishell**: `./minishell`
2. **Execute um comando**: `ls -la | grep .txt`
3. **Visualize**: `visualize`
4. **Explore**: Use as setas para navegar, ESC para fechar

**Divirta-se explorando suas ASTs! 🎨✨**