# 🤝 Contributing to AST Visualizer

Thank you for your interest in contributing to the AST Visualizer project! This guide will help you get started.

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Process](#development-process)
- [Coding Standards](#coding-standards)
- [Submitting Changes](#submitting-changes)
- [Bug Reports](#bug-reports)
- [Feature Requests](#feature-requests)

## 🎯 Code of Conduct

This project follows the 42 School community standards:

- ✅ **Be respectful** and inclusive
- ✅ **Help fellow students** learn and grow
- ✅ **Share knowledge** constructively
- ✅ **Follow academic integrity** guidelines

## 🚀 Getting Started

### Prerequisites
- GCC or Clang compiler
- Make build system
- Git for version control
- Basic knowledge of C programming
- Familiarity with MinilibX (helpful)

### Setup Development Environment
```bash
# Fork the repository
git clone https://github.com/pgomes42/visualize_ar.git
cd visualize_ar

# Create development branch
git checkout -b feature/your-feature-name

# Build and test
make -f Makefile.lib
./examples/test_lib
```

## 🔄 Development Process

### 1. Choose Your Contribution Type

#### 🐛 Bug Fixes
- Check existing issues first
- Create issue if not exists
- Reference issue in commit message

#### ✨ New Features
- Discuss in issues first
- Follow API design principles
- Add tests and documentation

#### 📚 Documentation
- Improve clarity and examples
- Add missing API documentation
- Fix typos and formatting

#### 🎨 UI/UX Improvements
- Color scheme enhancements
- Better visual layouts
- Improved user experience

### 2. Development Workflow

```bash
# Start with updated main branch
git checkout main
git pull origin main

# Create feature branch
git checkout -b feature/your-feature

# Make changes
# ... your development work ...

# Test thoroughly
make -f Makefile.lib clean
make -f Makefile.lib
./examples/test_lib

# Commit with clear message
git add .
git commit -m "feat: add interactive zoom functionality"

# Push and create PR
git push origin feature/your-feature
```

## 📝 Coding Standards

### 42 Norminette Compliance
All code must pass 42 Norminette checks:

```bash
# Check your files
norminette src/*.c includes/*.h
```

### Code Style Guidelines

#### Functions
```c
/**
 * @brief Brief description of function
 * @param param1 Description of parameter
 * @return Description of return value
 */
int	function_name(int param1, char *param2)
{
	int	result;
	
	if (!param2)
		return (-1);
	
	result = some_calculation(param1);
	return (result);
}
```

#### Headers
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: YYYY/MM/DD HH:MM:SS by pgomes           #+#    #+#             */
/*   Updated: YYYY/MM/DD HH:MM:SS by pgomes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
```

#### Variable Naming
- Use **snake_case** for variables and functions
- Use **descriptive names**
- Avoid abbreviations unless obvious

#### Memory Management
- **Always check malloc** return values
- **Free all allocated memory**
- **Set pointers to NULL** after freeing
- **Use valgrind** to check for leaks

### API Design Principles

#### Public Functions
- Clear, consistent naming
- Comprehensive error handling
- Full documentation
- Memory safety

#### Private Functions
- Static keyword for internal functions
- Clear internal documentation
- Consistent with public API style

## 🧪 Testing

### Manual Testing
```bash
# Build library
make -f Makefile.lib

# Test basic functionality
./examples/test_lib

# Test minishell integration
cd minishell && make && ./minishell
```

### Memory Testing
```bash
# Check for memory leaks
valgrind --leak-check=full ./examples/test_lib
```

### Performance Testing
```bash
# Test with large ASTs
# Create large command sequences
# Monitor memory usage
```

## 📤 Submitting Changes

### Pull Request Process

1. **Update Documentation**
   - Update README if needed
   - Add API documentation
   - Include usage examples

2. **Test Thoroughly**
   - Manual testing
   - Memory leak testing
   - Cross-platform testing

3. **Commit Message Format**
   ```
   type(scope): brief description
   
   Longer description if needed.
   
   Fixes #issue-number
   ```

   Types:
   - `feat`: New feature
   - `fix`: Bug fix
   - `docs`: Documentation
   - `style`: Code style changes
   - `refactor`: Code refactoring
   - `test`: Adding tests
   - `chore`: Maintenance tasks

4. **Pull Request Template**
   ```markdown
   ## Description
   Brief description of changes
   
   ## Type of Change
   - [ ] Bug fix
   - [ ] New feature
   - [ ] Documentation update
   - [ ] Code refactoring
   
   ## Testing
   - [ ] Tested manually
   - [ ] No memory leaks
   - [ ] Norminette compliant
   
   ## Screenshots (if applicable)
   ```

## 🐛 Bug Reports

Use the issue template:

```markdown
**Bug Description**
Clear description of the bug

**Steps to Reproduce**
1. Step one
2. Step two
3. Step three

**Expected Behavior**
What should happen

**Actual Behavior**
What actually happens

**Environment**
- OS: [e.g., Ubuntu 20.04]
- Compiler: [e.g., GCC 9.4.0]
- Make version: [e.g., GNU Make 4.2.1]

**Additional Context**
Any other relevant information
```

## ✨ Feature Requests

Use the feature request template:

```markdown
**Feature Description**
Clear description of the proposed feature

**Problem it Solves**
What problem does this feature address?

**Proposed Solution**
How should this feature work?

**Alternatives Considered**
Other solutions you've considered

**Additional Context**
Mockups, examples, references
```

## 🏆 Recognition

Contributors will be recognized in:
- README.md contributors section
- Git commit history
- Release notes
- Project documentation

### Contribution Levels

#### 🥉 **Contributor**
- First contribution merged
- Bug fixes or small improvements

#### 🥈 **Regular Contributor**
- Multiple contributions
- Feature implementations
- Documentation improvements

#### 🥇 **Core Contributor**
- Significant feature additions
- Architecture improvements
- Mentoring other contributors

## 📞 Getting Help

### 42 School Students
- Ask in your campus Slack
- Discuss with peers
- Reach out to pedagogy team

### General Questions
- Create an issue with the "question" label
- Check existing documentation first
- Be specific about your problem

### Real-time Help
- 42 School Discord channels
- Campus study groups
- Peer programming sessions

## 🎯 Priority Areas

We especially welcome contributions in:

### High Priority
- 🐛 **Bug fixes**
- 📚 **Documentation improvements**
- 🧪 **Test coverage**
- 🔧 **Performance optimizations**

### Medium Priority
- ✨ **New visualization features**
- 🎨 **UI/UX improvements**
- 🔌 **Integration enhancements**
- 📱 **Cross-platform support**

### Low Priority
- 🎁 **Nice-to-have features**
- 🔬 **Experimental features**
- 🎪 **Advanced visualizations**

---

**Thank you for contributing to AST Visualizer! 🎉**

Together, we're building tools that help the entire 42 community learn and grow.

Happy coding! 👨‍💻👩‍💻