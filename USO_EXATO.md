# 🎯 COMO USAR EXATAMENTE - GUIA DEFINITIVO

## 🚀 PASSO A PASSO EXATO

### 1. NAVEGUE PARA O DIRETÓRIO
```bash
cd /home/pgomes/Cadete/visualize_ar/minishell
```

### 2. EXECUTE O MINISHELL
```bash
./minishell
```
**Resultado esperado:**
```
minishell$
```

### 3. EXECUTE UM COMANDO (QUALQUER UM)
```bash
minishell$ ls
```
**Resultado:** Lista os arquivos do diretório

### 4. VISUALIZE A AST
```bash
minishell$ visualize
```
**Resultado esperado:**
```
🎨 === VISUALIZADOR DE AST MINISHELL === 🎨
📋 Comando: ls
📊 Nós na AST: 1
📏 Altura da AST: 1

📋 Estrutura da AST (texto):
└─ ls

🎨 Abrindo visualizador gráfico... (ESC para fechar)
```

### 5. JANELA GRÁFICA ABRE
- Uma janela com círculo verde aparece
- Texto "ls" dentro do círculo
- Use setas para navegar
- Pressione ESC para fechar

---

## 📋 EXEMPLOS EXATOS COM RESULTADOS

### EXEMPLO 1: Comando Simples
```bash
minishell$ echo "hello"
hello
minishell$ visualize
```
**Você verá:**
- 📊 1 nó, altura 1
- 🟢 Círculo verde com "echo hello"

### EXEMPLO 2: Pipe
```bash
minishell$ ls | head -3
# (mostra primeiras 3 linhas)
minishell$ visualize
```
**Você verá:**
- 📊 3 nós, altura 2
- 🔵 Círculo azul "|" no topo
- 🟢 Dois círculos verdes: "ls" e "head -3"

### EXEMPLO 3: AND
```bash
minishell$ echo "test" && echo "ok"
test
ok
minishell$ visualize
```
**Você verá:**
- 📊 3 nós, altura 2
- 🟡 Círculo dourado "&&" no topo
- 🟢 Dois círculos verdes: "echo test" e "echo ok"

### EXEMPLO 4: Pipeline Complexo
```bash
minishell$ cat /etc/passwd | grep root | head -1
# (mostra primeira linha com root)
minishell$ visualize
```
**Você verá:**
- 📊 5 nós, altura 3
- Estrutura em árvore com múltiplos pipes

---

## ⚡ SEQUÊNCIA COMPLETA DE TESTE

**Execute EXATAMENTE isso:**

```bash
# 1. Entre no diretório
cd /home/pgomes/Cadete/visualize_ar/minishell

# 2. Execute o minishell
./minishell

# 3. No prompt do minishell, digite cada comando seguido de visualize:

# Teste 1
minishell$ pwd
minishell$ visualize

# Teste 2  
minishell$ ls -la
minishell$ visualize

# Teste 3
minishell$ echo "hello" | cat
minishell$ visualize

# Teste 4
minishell$ true && echo "success"
minishell$ visualize

# 5. Para sair
minishell$ exit
```

---

## 🎨 O QUE VOCÊ VERÁ EXATAMENTE

### Na interface de texto:
```
🎨 === VISUALIZADOR DE AST MINISHELL === 🎨
📋 Comando: ls | head -3
📊 Nós na AST: 3
📏 Altura da AST: 2

📋 Estrutura da AST (texto):
└─ |
  └─ ls
  └─ head -3

🎨 Abrindo visualizador gráfico... (ESC para fechar)
```

### Na janela gráfica:
1. **Janela preta** abre
2. **Círculos coloridos** aparecem:
   - 🔵 Azul no topo com "|"
   - 🟢 Verde à esquerda com "ls"
   - 🟢 Verde à direita com "head -3"
3. **Linhas** conectam os círculos
4. **Controles:**
   - ⬅️ Move para esquerda
   - ➡️ Move para direita
   - ⬆️ Move para cima
   - ⬇️ Move para baixo
   - **ESC** fecha a janela

---

## ❗ IMPORTANTES NOTAS PRÁTICAS

### ✅ FAZER:
1. **SEMPRE** execute um comando ANTES de `visualize`
2. **AGUARDE** a janela gráfica carregar completamente
3. **USE** as setas para explorar se a AST for grande
4. **PRESSIONE ESC** para fechar (não clique no X)

### ❌ NÃO FAZER:
1. **NÃO** use `visualize` sem comando anterior
2. **NÃO** feche a janela clicando (use ESC)
3. **NÃO** execute vários `visualize` seguidos

### 🔧 SE DER ERRO:
```bash
# Se aparecer "Nenhuma AST disponível":
minishell$ ls        # Execute qualquer comando primeiro
minishell$ visualize # Agora funciona

# Se a janela não abrir:
export DISPLAY=:0    # Configure o display
```

---

## 📱 DEMONSTRAÇÃO INTERATIVA

**Cole este bloco completo no terminal:**

```bash
cd /home/pgomes/Cadete/visualize_ar/minishell && cat << 'EOF' | ./minishell
echo "=== DEMO COMPLETA ==="
echo "Comando 1: Simples"
pwd
visualize
echo "Comando 2: Com pipe"
ls | head -2
visualize
echo "Comando 3: Com AND"
echo "test" && echo "ok"
visualize
echo "=== FIM DEMO ==="
exit
EOF
```

---

## 🎯 RESULTADO FINAL ESPERADO

Após seguir os passos, você deve conseguir:

1. ✅ Executar qualquer comando no minishell
2. ✅ Digitar `visualize` e ver estatísticas da AST
3. ✅ Ver a janela gráfica com círculos coloridos
4. ✅ Navegar pela AST com as setas
5. ✅ Fechar com ESC e voltar ao prompt
6. ✅ Repetir para outros comandos

**Se tudo isso funcionar, a integração está perfeita! 🎉**