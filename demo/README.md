# 🎥 Demo Videos

Este diretório contém vídeos demonstrativos do **AST Visualizer** em ação.

## 📹 Vídeos Disponíveis

### 1. **Demonstração Principal** 
- **Arquivo**: `ast_visualizer_demo.mp4` ou `ast_visualizer_demo.gif`
- **Duração**: ~2-3 minutos
- **Conteúdo**: 
  - Compilação e execução do projeto
  - Integração com minishell
  - Visualização de diferentes tipos de AST
  - Comandos interativos e navegação

### 2. **Tutorial de Uso**
- **Arquivo**: `tutorial_uso.mp4` ou `tutorial_uso.gif` 
- **Duração**: ~1-2 minutos
- **Conteúdo**:
  - Como compilar o projeto
  - Como usar o comando `ast_visualize`
  - Exemplos práticos de comandos

## 🚀 Como Usar os Vídeos

### Para Desenvolvedores
1. Assista ao vídeo principal para entender o funcionamento
2. Use o tutorial para aprender a implementação
3. Consulte o README.md para detalhes técnicos

### Para Estudantes da 42
1. Veja como o visualizador funciona na prática
2. Entenda como integrar em seus projetos
3. Use como referência para seus próprios projetos

## 📱 Formatos Suportados

### Vídeo Completo (MP4)
- **Vantagens**: Qualidade alta, áudio incluído
- **Uso**: Apresentações, documentação detalhada
- **Tamanho**: Maior (~10-50MB)

### GIF Animado
- **Vantagens**: Reprodução automática, compatível com GitHub
- **Uso**: README, documentação rápida
- **Tamanho**: Menor (~5-15MB)

### Terminal Recording (ASCIInema)
- **Vantagens**: Tamanho mínimo, interativo
- **Uso**: Documentação técnica
- **Tamanho**: Muito pequeno (~1-2MB)

## 🔧 Como Adicionar Novos Vídeos

### 1. Gravação
```bash
# Para gravar terminal (asciinema)
asciinema rec demo_terminal.cast

# Para converter para GIF
# Use ferramentas como ffmpeg ou online converters
```

### 2. Otimização
```bash
# Reduzir tamanho do vídeo
ffmpeg -i input.mp4 -vf "scale=1280:720" -c:v libx264 -crf 23 output.mp4

# Converter para GIF
ffmpeg -i input.mp4 -vf "fps=10,scale=800:-1:flags=lanczos" output.gif
```

### 3. Adição ao Git
```bash
# Adicionar ao repositório
git add demo/
git commit -m "feat: add demonstration video"
git push
```

## 📋 Checklist para Vídeos

### ✅ Qualidade Técnica
- [ ] Resolução adequada (mínimo 720p)
- [ ] Áudio claro (se aplicável)
- [ ] Duração apropriada (2-5 minutos)
- [ ] Tamanho otimizado para Git

### ✅ Conteúdo
- [ ] Demonstra funcionalidades principais
- [ ] Mostra integração com minishell
- [ ] Inclui comandos práticos
- [ ] Explica conceitos importantes

### ✅ Apresentação
- [ ] Terminal limpo e organizado
- [ ] Comandos claramente visíveis
- [ ] Ritmo adequado para acompanhar
- [ ] Resultados bem demonstrados

## 🎯 Melhores Práticas

### Gravação
1. **Prepare o ambiente**: Terminal limpo, diretório correto
2. **Planeje a sequência**: Liste os comandos a executar
3. **Teste antes**: Execute uma vez para verificar funcionamento
4. **Grave com calma**: Velocidade adequada para acompanhar

### Edição
1. **Corte partes desnecessárias**: Remoção de erros ou pausas longas
2. **Adicione títulos**: Identifique seções do vídeo
3. **Otimize tamanho**: Balance qualidade e tamanho do arquivo
4. **Teste reprodução**: Verifique em diferentes dispositivos

---

## 📞 Suporte

Se tiver dúvidas sobre os vídeos ou como usar o AST Visualizer:

- Consulte o [README.md](../README.md) principal
- Veja os [exemplos](../examples/) de código
- Crie uma issue no repositório

**Aproveite as demonstrações! 🎉**