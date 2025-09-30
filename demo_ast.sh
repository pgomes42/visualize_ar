#!/bin/bash

# Script para demonstrar o uso do visualizador AST no minishell

echo "🎨 === DEMONSTRAÇÃO DO VISUALIZADOR AST === 🎨"
echo ""
echo "Executando minishell com comandos de exemplo..."
echo ""

cd /home/pgomes/Cadete/visualize_ar/minishell

# Sequência de comandos para demonstrar
cat << 'EOF' | ./minishell
echo "=== EXEMPLO 1: Comando Simples ==="
ls -la
visualize

echo "=== EXEMPLO 2: Comando com Pipe ==="
ls -la | grep .txt
visualize

echo "=== EXEMPLO 3: Comando com AND ==="
echo "teste" && echo "sucesso"
visualize

echo "=== EXEMPLO 4: Comando com OR ==="
false || echo "falhou como esperado"
visualize

echo "=== EXEMPLO 5: Pipeline Complexo ==="
cat /etc/passwd | head -3 | grep root
visualize

echo "=== FIM DA DEMONSTRAÇÃO ==="
exit
EOF

echo ""
echo "✅ Demonstração concluída!"