# 🎨 COMO EXECUTAR COMANDOS E DESENHAR A AST

## 🚀 Passo a Passo Completo

### 1. Abrir o Minishell
```bash
cd /home/pgomes/Cadete/visualize_ar/minishell
./minishell
```

### 2. Executar Comando + Visualizar AST

#### ✅ MÉTODO PRINCIPAL (Recomendado):

```bash
# Passo 1: Execute qualquer comando
minishell$ ls -la | grep .txt

# Passo 2: Visualize a AST
minishell$ visualize
```

**O que acontece:**
1. ✅ Comando é executado normalmente
2. ✅ AST é criada internamente
3. ✅ `visualize` mostra a estrutura da AST
4. ✅ Janela gráfica abre com a visualização

## 📋 Exemplos Práticos

### Exemplo 1: Comando Simples
```bash
minishell$ echo "Hello World"
# Resultado: Hello World

minishell$ visualize
# Resultado: 
📊 Nós na AST: 1
📏 Altura da AST: 1
└─ echo "Hello World"
```

### Exemplo 2: Pipeline (Pipe)
```bash
minishell$ ls -la | head -5
# Resultado: primeiras 5 linhas de ls -la

minishell$ visualize
# Resultado:
📊 Nós na AST: 3
📏 Altura da AST: 2
└─ |
  └─ ls -la
  └─ head -5
```

### Exemplo 3: Comando Condicional (AND)
```bash
minishell$ make clean && echo "limpeza concluída"
# Resultado: executa make clean, se sucesso executa echo

minishell$ visualize
# Resultado:
📊 Nós na AST: 3
📏 Altura da AST: 2
└─ &&
  └─ make clean
  └─ echo "limpeza concluída"
```

### Exemplo 4: Fallback (OR)
```bash
minishell$ comando_inexistente || echo "comando falhou"
# Resultado: comando falha, executa echo

minishell$ visualize
# Resultado:
📊 Nós na AST: 3
📏 Altura da AST: 2
└─ ||
  └─ comando_inexistente
  └─ echo "comando falhou"
```

### Exemplo 5: Pipeline Complexo
```bash
minishell$ cat /etc/passwd | grep root | wc -l
# Resultado: conta linhas com "root"

minishell$ visualize
# Resultado:
📊 Nós na AST: 5
📏 Altura da AST: 3
└─ |
  └─ |
    └─ cat /etc/passwd
    └─ grep root
  └─ wc -l
```

## 🎨 Interface Gráfica

### O que você verá:
1. **Janela gráfica** abre automaticamente
2. **Nós coloridos** representam diferentes elementos:
   - 🟢 **Verde**: Comandos
   - 🔵 **Azul**: Pipes (|)
   - 🟡 **Dourado**: AND (&&)
   - 🟠 **Laranja**: OR (||)
   - 🟣 **Rosa**: Redirecionamentos

3. **Controles**:
   - ⬅️➡️⬆️⬇️: Navegar pela AST
   - **ESC**: Fechar janela

## 🔄 Fluxo de Trabalho Típico

```bash
# 1. Abrir minishell
./minishell

# 2. Loop de trabalho:
minishell$ [seu_comando]        # Execute comando
minishell$ visualize            # Veja a AST
# [Janela gráfica abre, explore, pressione ESC]

minishell$ [outro_comando]      # Execute outro comando  
minishell$ visualize            # Veja nova AST
# [Repita quantas vezes quiser]

minishell$ exit                 # Sair
```

## 🧪 Sequência de Teste Completa

Execute estes comandos em sequência para ver diferentes tipos de AST:

```bash
# Comando 1: Simples
minishell$ pwd
minishell$ visualize

# Comando 2: Com argumentos
minishell$ ls -la
minishell$ visualize

# Comando 3: Pipe simples
minishell$ ls | head -3
minishell$ visualize

# Comando 4: Pipe duplo
minishell$ cat /etc/passwd | grep root | head -1
minishell$ visualize

# Comando 5: AND condicional
minishell$ true && echo "sucesso"
minishell$ visualize

# Comando 6: OR fallback
minishell$ false || echo "falhou"
minishell$ visualize

# Comando 7: Redirecionamento
minishell$ echo "teste" > /tmp/arquivo.txt
minishell$ visualize

# Comando 8: Complexo
minishell$ (ls *.c | wc -l) && echo "arquivos contados"
minishell$ visualize
```

## 💡 Dicas Importantes

### ✅ Fazer:
- Execute qualquer comando ANTES de usar `visualize`
- Use `visualize` logo após o comando para ver sua AST
- Explore a interface gráfica com as setas
- Feche com ESC quando terminar de explorar

### ❌ Não fazer:
- Não use `visualize` sem executar comando antes
- Não feche a janela clicando no X (use ESC)
- Não tente visualizar comandos internos que não criam AST

## 🐛 Solução de Problemas

### Problema: "Nenhuma AST disponível"
```bash
# Solução: Execute um comando primeiro
minishell$ ls        # Execute algo
minishell$ visualize # Agora funciona
```

### Problema: Interface não abre
```bash
# Solução 1: Verificar DISPLAY (para SSH)
export DISPLAY=:0

# Solução 2: Usar X11 forwarding
ssh -X usuario@servidor
```

### Problema: Comando não reconhecido
```bash
# Solução: Recompilar
make clean && make
```

## 🎯 Casos de Uso Avançados

### Debug de Parser:
```bash
minishell$ comando | muito | complexo && echo ok
minishell$ visualize
# Verifique se a precedência está correta
```

### Análise de Performance:
```bash
minishell$ find . -name "*.c" | xargs grep main | head -10
minishell$ visualize
# Veja como o pipeline é estruturado
```

### Estudo de Precedência:
```bash
minishell$ cmd1 && cmd2 || cmd3
minishell$ visualize
# vs
minishell$ cmd1 && (cmd2 || cmd3)
minishell$ visualize
# Compare as estruturas
```

---

## 🚀 RESUMO RÁPIDO:

1. **Abra**: `./minishell`
2. **Execute**: `[qualquer comando]`
3. **Visualize**: `visualize`
4. **Explore**: Use setas na interface gráfica
5. **Feche**: Pressione ESC
6. **Repita**: Para outros comandos

**É isso! Agora você pode visualizar qualquer AST do seu minishell! 🎨✨**