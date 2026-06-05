# Minishell

## Project Overview

Minishell is a simplified implementation of a Unix shell inspired by Bash.

The goal is to understand how a shell works internally by implementing:

* Command execution
* Process creation and management
* Pipes
* Redirections
* Environment variables
* Signal handling
* Parsing and tokenization

Rather than simply executing commands, Minishell recreates the entire workflow that occurs when a user types a command into a terminal.

---

# Learning Objectives

The Minishell project teaches the following core Unix concepts:

## Process Management

Understanding how programs are executed through:

* `fork()`
* `execve()`
* `wait()`
* `waitpid()`

### Example

```bash
ls -la
```

The shell:

1. Creates a child process using `fork()`
2. Child executes `/bin/ls` using `execve()`
3. Parent waits for completion

````

---

## File Descriptors

Understanding standard streams:

```text
STDIN  = 0
STDOUT = 1
STDERR = 2
````

And how they can be redirected using:

* `open()`
* `dup2()`
* `close()`

### Example

```bash
echo hello > output.txt
```

The shell redirects `STDOUT` into a file.

---

## Inter-Process Communication

Understanding pipes:

```bash
ls | wc -l
```

Output from one process becomes input to another process.

Implemented using:

```c
pipe()
```

---

## Environment Variables

Managing shell environment variables such as:

```bash
PATH
HOME
USER
PWD
OLDPWD
```

Supporting:

```bash
export KEY=value
unset KEY
echo $KEY
```

---

## Signal Handling

Handling terminal signals correctly.

### Examples

```text
Ctrl+C -> SIGINT
Ctrl+\ -> SIGQUIT
```

Shell behavior should match Bash as closely as possible.

---

## Parsing

Transforming user input into executable structures.

Example:

```bash
cat file.txt | grep hello > output.txt
```

Must be interpreted as:

* Command 1: `cat file.txt`
* Pipe
* Command 2: `grep hello`
* Redirect output into `output.txt`

---

# Core Concepts

## REPL Loop

The shell operates in a continuous loop:

```text
Read
Evaluate
Print
Loop
```

Also known as:

```text
Prompt
↓
Read Input
↓
Parse
↓
Execute
↓
Wait
↓
Prompt Again
```

---

## Shell Lifecycle

Every command follows the same high-level workflow.

```text
User Input
    ↓
Tokenizer
    ↓
Syntax Validation
    ↓
Parser
    ↓
Expansion
    ↓
Executor
    ↓
Process Management
    ↓
Exit Status
    ↓
Prompt
```

---

# Architecture

## High-Level Architecture

```text
┌─────────────┐
│  Readline   │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Tokenizer  │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│ Syntax Check│
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   Parser    │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│ Expansions  │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Executor   │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│ Processes   │
└─────────────┘
```

---

# Workflow

## 1. Read Input

The shell displays a prompt:

```bash
minishell$
```

Input is read using:

```c
readline()
```

Example:

```bash
echo hello
```

Input received:

```c
"echo hello"
```

---

## 2. Tokenization

The tokenizer converts raw text into tokens.

Input:

```bash
echo hello | grep h > out.txt
```

Tokens:

```text
WORD       echo
WORD       hello
PIPE       |
WORD       grep
WORD       h
REDIR_OUT  >
WORD       out.txt
```

Tokenizer responsibility:

* Identify words
* Identify operators
* Preserve quotes
* Produce token list

---

## 3. Syntax Validation

Detect invalid command sequences.

Examples:

```bash
|
ls |
cat >
```

Should generate syntax errors before parsing.

Examples of checks:

* Pipe at beginning
* Pipe at end
* Missing redirection target
* Invalid operator sequence

---

## 4. Parsing

Convert token list into executable structures.

Example:

```bash
echo hello | grep h
```

Produces:

```text
Command 1
  args = ["echo", "hello"]

PIPE

Command 2
  args = ["grep", "h"]
```

Result is usually stored as:

```c
t_cmd
```

linked list.

---

## 5. Variable Expansion

Expand shell variables.

Environment:

```bash
USER=student
```

Input:

```bash
echo $USER
```

Expanded command:

```bash
echo student
```

Special variable:

```bash
echo $?
```

Returns the exit status of the previous command.

---

## 6. Redirection Processing

Handle:

```bash
<
>
>>
<<
```

Examples:

```bash
cat < input.txt
```

```bash
echo hello > output.txt
```

```bash
echo hello >> output.txt
```

```bash
cat << EOF
```

The parser stores redirections, and the executor applies them before execution.

---

## 7. Pipe Setup

Example:

```bash
cat file.txt | grep hello | wc -l
```

Pipeline:

```text
cat
 ↓
grep
 ↓
wc
```

Each pipe connects:

```text
stdout
    ↓
stdin
```

using:

```c
pipe()
```

---

## 8. Command Execution

Determine whether command is:

### Builtin

Examples:

```bash
cd
pwd
echo
env
export
unset
exit
```

or

### External Program

Examples:

```bash
ls
cat
grep
wc
```

---

## 9. Builtin Execution

Some builtins must run in the parent process.

Example:

```bash
cd /tmp
```

Running inside a child would not affect the shell's working directory.

Builtins commonly executed in parent:

```text
cd
export
unset
exit
```

---

## 10. External Program Execution

Execution workflow:

```text
fork()
   ↓
execve()
   ↓
waitpid()
```

Example:

```bash
ls
```

Process tree:

```text
Parent Shell
     │
     └── Child Process
             │
             └── execve("/bin/ls")
```

---

## 11. PATH Resolution

User enters:

```bash
ls
```

Shell searches:

```bash
PATH=/usr/bin:/bin:/usr/local/bin
```

Checks:

```text
/usr/bin/ls
/bin/ls
/usr/local/bin/ls
```

Until executable is found.

---

## 12. Exit Status Handling

Every command returns an exit status.

```text
0 = Success
Non-zero = Error
```

Stored internally:

```c
shell->last_status
```

Used for:

```bash
echo $?
```

---

## 13. Cleanup

After execution:

* Free tokens
* Free command structures
* Restore original file descriptors
* Reset temporary state

The shell then returns to the prompt.

---

# Suggested Module Layout

```text
src/
│
├── main/
│   └── minishell.c
│
├── lexer/
│   ├── tokenize.c
│   └── token_utils.c
│
├── parser/
│   ├── parser.c
│   ├── syntax.c
│   └── cmd_builder.c
│
├── expansion/
│   └── expand.c
│
├── executor/
│   ├── executor.c
│   ├── pipes.c
│   ├── redirections.c
│   └── path.c
│
├── builtins/
│   ├── cd.c
│   ├── echo.c
│   ├── env.c
│   ├── export.c
│   ├── unset.c
│   ├── pwd.c
│   └── exit.c
│
├── env/
│   └── env_utils.c
│
├── signals/
│   └── signals.c
│
└── utils/
    └── helpers.c
```

---

# Mental Model

Whenever the user enters:

```bash
cat file.txt | grep hello > output.txt
```

The shell should think:

```text
INPUT STRING
        ↓
TOKENIZE
        ↓
VALIDATE
        ↓
PARSE
        ↓
EXPAND VARIABLES
        ↓
BUILD COMMANDS
        ↓
SETUP REDIRECTIONS
        ↓
SETUP PIPES
        ↓
FORK PROCESSES
        ↓
EXECUTE COMMANDS
        ↓
WAIT FOR CHILDREN
        ↓
STORE EXIT STATUS
        ↓
DISPLAY PROMPT
```

This pipeline is the core of the Minishell project.
