# 🎨 AST Visualizer - Advanced Tree Visualization Library

[![42 Project](https://img.shields.io/badge/42-Project-000000?style=flat&logo=42)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics](https://img.shields.io/badge/Graphics-MinilibX-green.svg)](https://github.com/42Paris/minilibx-linux)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Screenshots](#screenshots)
- [Installation](#installation)
- [Usage](#usage)
- [API Documentation](#api-documentation)
- [Integration Examples](#integration-examples)
- [Contributing](#contributing)
- [License](#license)

## 🎯 Overview

**AST Visualizer** is a professional-grade C library designed for **42 School projects**, specifically for visualizing Abstract Syntax Trees (AST) in **Minishell** implementations. This library provides both textual and interactive graphical representations of command parsing trees.

### 🏆 Project Goals
- ✅ **Educational**: Help students understand AST structures
- ✅ **Debug Tool**: Visual debugging for parser implementations  
- ✅ **Professional**: Clean, documented, and maintainable code
- ✅ **Performance**: Optimized for real-time visualization
- ✅ **Integration**: Easy integration with existing Minishell projects

## ✨ Features

### 🎨 Visual Features
- **Color-coded nodes** for different command types
- **Interactive navigation** with keyboard controls
- **Real-time AST generation** from command lines
- **Multiple visualization modes** (text and graphical)

### 🔧 Technical Features
- **Zero-dependency core** (except MinilibX for graphics)
- **Memory-safe** with automatic cleanup
- **Cross-compatible** with different Minishell implementations
- **Extensible API** for custom node types
- **Performance optimized** for large ASTs

### 🎮 Color Scheme
| Element | Color | Usage |
|---------|--------|--------|
| 🟢 **Commands** | Green | `ls`, `cat`, `echo`, etc. |
| 🔵 **Pipes** | Blue | `\|` operators |
| 🟡 **AND** | Gold | `&&` operators |
| 🟠 **OR** | Orange | `\|\|` operators |
| 🟣 **Redirections** | Pink | `>`, `>>`, `<` operators |

## 📸 Screenshots

### Command Pipeline Visualization
```
📋 Command: ls -la | grep .txt | head -5
📊 Nodes: 5 | Height: 3

└─ |
  └─ |
    └─ ls -la
    └─ grep .txt
  └─ head -5
```

### Conditional Command Structure
```
📋 Command: make clean && echo "done" || echo "error"
📊 Nodes: 5 | Height: 3

└─ ||
  └─ &&
    └─ make clean
    └─ echo "done"
  └─ echo "error"
```

## 🚀 Installation

### Prerequisites
- **GCC** or **Clang** compiler
- **Make** build system
- **X11 development libraries** (Linux)
- **MinilibX** (included)

### Quick Install
```bash
# Clone the repository
git clone https://github.com/pgomes42/visualize_ar.git
cd visualize_ar

# Build the library
make -f Makefile.lib

# Install to your Minishell project
make -f Makefile.lib install
```

### Manual Integration
```bash
# Copy library files
cp lib_ast/libast_visualizer.a your_minishell/lib/
cp includes/libast_visualizer.h your_minishell/includes/

# Add to your Makefile
LIBS += -last_visualizer -lmlx -lmlx_Linux -lX11 -lXext -lm
```

## 📚 Usage

### Basic Integration
```c
#include "libast_visualizer.h"

int main(void)
{
    t_ast_visualizer *viz = ast_visualizer_init();
    t_ast_node *ast = ast_quick_pipe("ls -la", "grep .txt");
    
    ast_visualizer_show(viz, ast, "My AST");
    
    ast_node_destroy(ast);
    ast_visualizer_destroy(viz);
    return (0);
}
```

### Minishell Integration
```c
// In your minishell main loop
while (1) {
    char *line = readline("minishell> ");
    t_ast_node *ast = parse_command_line(line);
    
    // Visualize on demand
    if (strcmp(line, "visualize") == 0)
        minishell_visualize_ast(&data);
    
    execute_ast(ast);
}
```

### Interactive Controls
- **⬅️➡️⬆️⬇️**: Navigate through the AST
- **ESC**: Close visualization window
- **Mouse**: Future zoom/pan functionality

## 📖 API Documentation

### Core Functions
```c
// Initialization
t_ast_visualizer *ast_visualizer_init(void);
void ast_visualizer_destroy(t_ast_visualizer *viz);

// Visualization
int ast_visualizer_show(t_ast_visualizer *viz, t_ast_node *ast, const char *title);

// Node Creation
t_ast_node *ast_node_create(const char *data);
t_ast_node *ast_node_pipe(t_ast_node *left, t_ast_node *right);
t_ast_node *ast_node_and(t_ast_node *left, t_ast_node *right);

// Quick Builders
t_ast_node *ast_quick_pipe(const char *cmd1, const char *cmd2);
t_ast_node *ast_quick_and(const char *cmd1, const char *cmd2);
```

### Memory Management
```c
// Cleanup
void ast_node_destroy(t_ast_node *ast);

// Utilities
int ast_node_count(const t_ast_node *ast);
int ast_node_height(const t_ast_node *ast);
void ast_node_print(const t_ast_node *ast, int depth);
```

## 🔗 Integration Examples

### Example 1: Simple Command
```bash
minishell$ echo "Hello, 42!"
minishell$ visualize
```
**Result**: Single green node with command text

### Example 2: Pipeline
```bash
minishell$ cat /etc/passwd | grep root | head -1
minishell$ visualize
```
**Result**: Tree structure with blue pipe nodes

### Example 3: Conditional Execution
```bash
minishell$ make clean && echo "success" || echo "failed"
minishell$ visualize
```
**Result**: Complex tree with gold and orange operators

## 📁 Project Structure

```
visualize_ar/
├── 📚 Documentation
│   ├── README.md                    # This file
│   ├── INSTALLATION.md              # Installation guide
│   ├── API_REFERENCE.md             # Complete API docs
│   └── EXAMPLES.md                  # Usage examples
├── 📦 Library Source
│   ├── src/
│   │   ├── libast_visualizer.c      # Main library implementation
│   │   ├── ast.c                    # AST manipulation functions
│   │   ├── render.c                 # Rendering engine
│   │   └── ast_adapter.c            # Type conversion utilities
│   └── includes/
│       ├── libast_visualizer.h      # Public API header
│       └── visualizer_ar.h          # Internal definitions
├── 🔧 Build System
│   ├── Makefile                     # Main application build
│   ├── Makefile.lib                 # Library build system
│   └── lib_ast/                     # Compiled library output
├── 🧪 Examples & Tests
│   ├── examples/
│   │   ├── test_lib.c               # Library usage examples
│   │   └── minishell_integration.c  # Integration examples
│   └── tests/                       # Unit tests (future)
├── 🎯 Minishell Integration
│   └── minishell/                   # Complete Minishell with integration
└── 📖 Documentation
    ├── INTEGRATION_COMPLETE.md      # Integration guide
    ├── COMO_USAR_AST.md             # Usage guide (PT)
    └── USO_EXATO.md                 # Exact usage guide (PT)
```

## 🏆 Achievements & Badges

### 🥇 Technical Excellence
- ✅ **Zero Memory Leaks** - Valgrind clean
- ✅ **42 Norminette** - Code style compliant
- ✅ **Cross-Platform** - Linux compatible
- ✅ **Performance Optimized** - Real-time rendering

### 🎯 Feature Completeness
- ✅ **Complete API** - All major functions implemented
- ✅ **Documentation** - Comprehensive guides and examples
- ✅ **Integration Ready** - Easy Minishell integration
- ✅ **Professional Grade** - Production-ready code

### 🔧 Build Quality
- ✅ **Automated Build** - Makefile system
- ✅ **Dependency Management** - Clean library linking
- ✅ **Error Handling** - Robust error management
- ✅ **Memory Safety** - Automatic cleanup

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md).

### Development Setup
```bash
git clone https://github.com/pgomes42/visualize_ar.git
cd visualize_ar
make -f Makefile.lib
./examples/test_lib
```

### Code Style
- Follow **42 School Norminette**
- Use **clear, descriptive names**
- **Document all public functions**
- **Test thoroughly**

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🎓 42 School Integration

This project was developed as an **educational tool** for **42 School** students working on **Minishell** projects. It demonstrates:

- **Advanced C programming** techniques
- **Graphics programming** with MinilibX
- **Data structure visualization**
- **Professional software development** practices

## 🙏 Acknowledgments

- **42 School** for the educational framework
- **MinilibX** development team
- **Open source community** for inspiration
- **Fellow 42 students** for feedback and testing

---

**Made with ❤️ for the 42 Community**

[![42](https://badge42.vercel.app/api/v2/cl6q2m1p7001109l9eayvdb7r/project/3379984)](https://github.com/JaeSeoKim/badge42)