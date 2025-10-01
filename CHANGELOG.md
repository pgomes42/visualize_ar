# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- 🎥 **Demonstration Video**: Complete visual showcase of AST Visualizer features
- 📁 **Demo Directory**: Professional demo materials and documentation
- 🎬 **Video Integration**: README updated with video showcase section
- 📊 **Project Status**: Comprehensive achievement tracking and metrics
- 📝 **Git Attributes**: Proper file handling configuration for repository
- Professional project documentation
- MIT License with educational provisions
- Comprehensive contribution guidelines

## [1.2.0] - 2024-12-19

### Added
- Complete minishell integration with builtin commands
- AST saving system for proper visualization workflow
- Builtin `ast_visualize` command for interactive AST viewing
- Professional project documentation and README
- MIT License with 42 School educational provisions
- Comprehensive API documentation with examples

### Fixed
- AST visualization workflow - now properly saves AST before visualization
- Function name conflicts between library and minishell
- Memory management issues in minishell integration
- Proper error handling for visualization commands

### Changed
- Improved builtin command implementation
- Enhanced user experience with proper workflow
- Better integration with minishell execution flow

## [1.1.0] - 2024-12-19

### Added
- Professional static library creation (`libast_visualizer.a`)
- Public API with comprehensive documentation
- Library-specific Makefile (`Makefile.lib`)
- Example programs for library usage
- Memory-safe library interface

### Enhanced
- Command text color changed to black for better readability
- Improved visual contrast in AST nodes
- Better color scheme for different command types

### Fixed
- Text rendering improvements
- Color display issues

## [1.0.0] - 2024-12-19

### Added
- Complete AST adapter system for automatic tree generation
- Color-coded visualization system with command type detection
- Interactive controls for switching between AST examples
- Real command display in AST nodes instead of generic text
- Memory management with proper malloc/free handling
- Type conversion from int-based to void* generic data handling

### Features
- **Color System**: Different colors for different command types
  - Commands: Blue (#0066CC)
  - Pipes: Green (#00AA00)
  - Redirections: Orange (#FF6600)
  - AND/OR operators: Purple (#9900CC)
  - Parentheses: Red (#CC0000)

- **Interactive Controls**:
  - Press '1', '2', '3' to switch between different AST examples
  - ESC to exit visualization
  - Real-time AST rendering with MinilibX

- **AST Examples**:
  1. Simple pipe command: `ls -l | grep .txt`
  2. Complex redirection: `cat file.txt > output.txt`
  3. Logical operators: `make && ./program || echo "failed"`

### Technical Improvements
- Generic void* data handling for flexible AST node content
- Automatic AST structure generation from command strings
- Command type detection and classification
- Memory-safe operations with proper cleanup
- Cross-platform compatibility (Linux focus)

### Documentation
- Comprehensive API documentation
- Usage examples and integration guides
- Professional README with badges and features
- Educational content for 42 School students

---

## Release Notes

### Version 1.2.0 - "Professional Integration"
This release marks the complete transformation of the AST Visualizer into a professional-grade tool with full minishell integration. Key achievements include proper workflow implementation, comprehensive documentation, and educational licensing for the 42 School community.

### Version 1.1.0 - "Library Foundation"
The library release establishes AST Visualizer as a reusable component with a clean public API, professional build system, and comprehensive documentation for developers.

### Version 1.0.0 - "Color Revolution"
The first major release introduces the color-coded visualization system, making AST structures immediately comprehensible through visual cues and interactive controls.

---

## Upgrade Guide

### From 1.1.x to 1.2.0
- Update your minishell integration to use the new builtin commands
- Use `ast_visualize` builtin instead of calling visualizer directly
- Ensure AST is properly saved before visualization

### From 1.0.x to 1.1.0
- Replace direct executable calls with library integration
- Update Makefile to use `Makefile.lib` for library builds
- Include `libast_visualizer.h` in your projects

### From 0.x to 1.0.0
- Update AST data types from `int` to `void*`
- Use new color-coded visualization functions
- Implement new interactive controls in your application

---

## Contributors

- **pgomes** - Project creator and main developer
- **42 School Community** - Testing, feedback, and educational support

---

## License

This project is licensed under the MIT License with additional educational provisions for 42 School use. See [LICENSE](LICENSE) for details.