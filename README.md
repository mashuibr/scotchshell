# C++ Shell Implementation

A learning project to understand how shells work by building one from scratch in C++.

**Author:** Ibrahim Shah  
**Started:** 07/07/26

---

## 📋 Project Overview

This project implements a basic interactive shell in C++ similar to bash/sh. It parses user commands, executes built-in operations, shows a dynamic prompt, and handles simple command-line arguments. This is an educational journey into understanding shell architecture and design patterns.

**Current Status:** Basic implementation with core shell loop, built-in commands, and prompt customization

---

## 🏗️ Architecture

### Core Components

```
┌─────────────────────────────────────────────────┐
│         Shell Loop (main.cpp)                   │
│  - Infinite loop for command input              │
│  - Colored prompt rendering                     │
│  - Input parsing (command + arguments)          │
└──────────────┬──────────────────────────────────┘
               │
               ▼
┌─────────────────────────────────────────────────┐
│    Command Router (commandRedirect)             │
│  - Routes commands to appropriate handlers      │
│  - Implements built-in commands                 │
│  - Handles unknown commands                     │
└──────────────┬──────────────────────────────────┘
               │
      ┌────────┼────────┐
      ▼        ▼        ▼
    echo      pwd      ls      cd      exit
   commands.cpp (Implementation details)
```

### File Structure

- **main.cpp** - Shell loop, input parsing, command routing
- **command.h** - Function declarations for command handlers
- **commands.cpp** - Implementation of built-in commands and prompt logic
- **compile.sh** - Build script

### Data Flow

1. User enters: `echo hello world`
2. `getline()` reads input → `"echo hello world"`
3. String parsing finds first space at index 5
4. Split into: command=`"echo"`, argument=`"hello world"`
5. `commandRedirect()` routes to `executeEcho()`
6. Output printed, loop continues with the updated prompt path

---

## 📚 Learning Roadmap & Progress

### ✅ Completed (Phase 1: Foundation)
- [x] Interactive shell loop with continuous input handling
- [x] Basic command parsing (command + single argument string)
- [x] Command routing/dispatcher pattern
- [x] Built-in commands: `echo`, `pwd`, `ls`, `cd`, `exit`
- [x] Colored prompt output (`\033[36m` and `\033[33m` ANSI codes)
- [x] Prompt path shortened to `~` when inside `HOME`
- [x] Unknown command feedback
- [x] Basic compilation setup

### 🔄 Current Focus (Phase 2: Expansion)
- [ ] Multiple arguments parsing (argv-style)
- [ ] Quoted string support
- [ ] stdin/stdout redirection (`>`, `<`, `>>`)
- [ ] Pipes (`|`) between commands
- [ ] Background execution (`&`)
- [ ] Command history
- [ ] Safer error handling around system calls

### 📋 Future Work (Phase 3: Advanced)
- [ ] Environment variables (`$PATH`, `$HOME`, etc.)
- [ ] Script file execution
- [ ] Wildcards and globbing (`*`, `?`)
- [ ] Signal handling (Ctrl+C, Ctrl+Z)
- [ ] More built-in commands (`cat`, `mkdir`, `rm`, etc.)
- [ ] Command lookup in `PATH`
- [ ] Error handling and validation

### 🎓 Planned Learning Topics
- Process creation with `fork()` and `exec()`
- File descriptor manipulation
- Buffer management and memory safety
- Signal handling in Unix
- String tokenization techniques

---

## 💡 What I've Learned

### C++ Concepts Applied
- **String handling**: `getline()`, `substr()`, `find()` for parsing
- **ANSI escape codes**: Terminal color manipulation with `\033[36m` and `\033[33m` sequences
- **Standard library**: `<iostream>`, `<string>`, `<unistd.h>`
- **Branching-based dispatch**: Command routing using `if` / `else if`
- **Buffer management**: Fixed-size buffers with `getcwd()`
- **Directory traversal**: Listing entries with `opendir()` / `readdir()`
- **Directory changes**: Updating the working directory with `chdir()`

### Shell Design Insights
1. **Simplicity first**: A shell is just a loop that reads → parses → executes
2. **Command dispatching**: Router pattern cleanly separates concerns
3. **Input parsing**: String manipulation is fundamental to shell functionality
4. **System calls**: Direct OS interaction via functions like `getcwd()` and `chdir()`
5. **Prompt state matters**: The current working directory is part of the shell experience

### Development Workflow
- Iterative feature addition with recompilation
- The importance of simple build scripts
- Keeping headers clean and minimal
- Updating documentation as the shell grows helps keep the project honest

---

## ⚠️ Common Mistakes & Solutions

### 1. **Fixed-Size Buffers Without Bounds Checking**
```cpp
// ❌ WRONG - Buffer overflow risk
char buffer[100];
getcwd(buffer, 100);

// ✅ BETTER - Check result, consider dynamic allocation
char buffer[256];
if (getcwd(buffer, sizeof(buffer)) == nullptr) {
    perror("getcwd failed");
}

// ✅ BEST - Use modern C++ with string
char buffer[256];
std::string cwd;
if (getcwd(buffer, sizeof(buffer)) != nullptr) {
    cwd = buffer;
}
```

**Why:** Buffer overflows are security vulnerabilities. Always check return values.

---

### 2. **Incorrect String Parsing Edge Cases**
```cpp
// ❌ WRONG - Doesn't handle multiple spaces
size_t index = instruction.find(' ');
command = instruction.substr(0, index);
argument = instruction.substr(index + 1);

// Problem: "echo  multiple  spaces" breaks unexpectedly

// ✅ BETTER - Handle empty input
size_t index = instruction.find(' ');
if(index == string::npos){
    command = instruction;
    argument = "";
} else {
    command = instruction.substr(0, index);
    argument = instruction.substr(index + 1);
}

// ✅ BEST - Tokenize properly with vector
std::vector<std::string> parseCommand(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while(iss >> token) tokens.push_back(token);
    return tokens;
}
```

**Why:** Edge cases like empty input or multiple spaces cause crashes or unexpected behavior.

---

### 3. **Not Handling Command Not Found**
```cpp
// ❌ WRONG - No feedback for unknown commands
if(command == "echo") { executeEcho(argument); }
if(command == "pwd") { executePwd(); }
// If command doesn't match, nothing happens!

// ✅ BETTER - Add fallback handler
if(command == "echo") { executeEcho(argument); }
else if(command == "pwd") { executePwd(); }
else if(command == "exit") { exit(0); }
else if(command != "") {
    std::cout << "Command not found: " << command << std::endl;
}
```

**Why:** User feedback matters. Silence is confusing.

---

### 4. **Not Trimming Whitespace**
```cpp
// ❌ WRONG - Input with leading/trailing spaces fails
" echo hello" → command = " echo" (space included!)

// ✅ BETTER - Trim before parsing
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n");
    size_t end = str.find_last_not_of(" \t\n");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

instruction = trim(instruction);
```

**Why:** Users naturally add extra spaces; robust parsing handles this gracefully.

---

### 5. **Memory Leaks with Dynamic Allocation**
```cpp
// ❌ WRONG - When you eventually use dynamic allocation
char* buffer = new char[256];
getcwd(buffer, 256);
// No delete[] - memory leak!

// ✅ BETTER - Use RAII (Resource Acquisition Is Initialization)
std::vector<char> buffer(256);
getcwd(buffer.data(), buffer.size());
// Automatic cleanup when vector goes out of scope
```

**Why:** C++ requires explicit memory management. Use STL containers for safety.

---

### 6. **Not Checking System Call Return Values**
```cpp
// ❌ WRONG - Assume success
char buffer[100];
getcwd(buffer, 100);  // Ignore return value!

// ✅ BETTER - Check for errors
char buffer[100];
if (getcwd(buffer, 100) == nullptr) {
    perror("getcwd");  // Print system error message
    return;
}
```

**Why:** System calls can fail (permissions, path too long, etc.). Always check return values.

---

### 7. **Using Raw Pointers for String Data**
```cpp
// ❌ WRONG - Risky pointer usage
char* result = getcwd(buffer, 100);
// result points to buffer, but is easily misused

// ✅ BETTER - Use std::string immediately
char buffer[256];
std::string cwd;
if (getcwd(buffer, sizeof(buffer)) != nullptr) {
    cwd = buffer;  // Safe copy to string
    std::cout << cwd << std::endl;
}
```

**Why:** `std::string` handles memory safely; raw pointers are error-prone.

---

### 8. **Assuming `cd` Should Print the New Path Only on Success**
```cpp
// ❌ WRONG - No feedback or unclear failure handling
if (chdir(path.c_str()) != 0) {
    // ignored
}

// ✅ BETTER - Report the error clearly
if (chdir(path.c_str()) != 0) {
    perror("chdir failed");
}
```

**Why:** Directory changes affect shell state, so clear feedback is important when the operation fails.

---

## 🚀 How to Build & Run

### Prerequisites
- GCC compiler (`g++`)
- Standard C++ libraries
- Linux/Unix environment

### Compilation
```bash
chmod +x compile.sh
./compile.sh
```

Or manually:
```bash
g++ main.cpp commands.cpp -o shell
./shell
```

### Usage
```bash
mashu@scotch: echo hello
hello

mashu@scotch: pwd
/home/mashu/Developer/cpp/shell

mashu@scotch: ls
command.h
commands.cpp
compile.sh
main.cpp
shell
rough-work

mashu@scotch: cd rough-work
Changed directory to: rough-work

mashu@scotch: pwd
/home/mashu/Developer/cpp/shell/rough-work

mashu@scotch: exit
```

---

## 📝 Next Steps

1. **Improve parsing**: Handle multiple arguments and quoted strings
2. **Add more commands**: Implement `cat`, `mkdir`, `rm`
3. **Error handling**: Graceful error messages and exit codes
4. **Process execution**: Use `fork()` and `exec()` for external programs
5. **Redirection**: Implement `>`, `<`, `>>` for file I/O

---

## 🔗 References & Resources

- **Unix System Programming**: Understanding `fork()`, `exec()`, `getcwd()`
- **C++ String Library**: `<string>`, `<sstream>` for parsing
- **POSIX API**: Standard Unix/Linux system calls
- **Shell Scripting**: Bash man pages for specification reference

---

## 📌 Notes

- This is a learning project—production shells handle many more edge cases
- Modern C++ encourages using `std::string` over C-style strings
- Error handling will become crucial as complexity increases
- Consider future refactoring with command pattern or strategy pattern

