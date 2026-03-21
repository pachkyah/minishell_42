*This project has been created as part of the 42 curriculum by kamelina[, ypachkou].*

# 🐚 Minishell

A simple UNIX shell implementation written in C as part of the 42 curriculum.
This project recreates core behaviors of bash, including command execution, environment management, and built-in commands.

---

## 📌 Features

* Execute commands with absolute, relative, or `$PATH` resolution
* Handle environment variables
* Support pipes (`|`)
* Input/output redirections:

  * `>` overwrite
  * `>>` append
  * `<` input
  * `<<` heredoc
* Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
* Built-in commands:

  * `echo`
  * `cd`
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`

---

## 🧠 Project Architecture

### 🔹 Environment Management

Environment variables are stored in a linked list:

```c
typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
} t_env;
```

### 🔹 `env_init`

The `env_init` function initializes the shell environment from `envp`.

#### Responsibilities:

* Iterate through `envp`
* Split each string into `key` and `value`
* Store them in a linked list

#### Example:

```c
t_env *env_init(char **envp)
{
    t_env *env = NULL;
    int i = 0;

    while (envp[i])
    {
        char *equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            char *key = ft_substr(envp[i], 0, equal - envp[i]);
            char *value = ft_strdup(equal + 1);
            env_add_back(&env, env_new(key, value));
            free(key);
            free(value);
        }
        i++;
    }
    return env;
}
```

---

## ⚙️ Compilation

```bash
make
```

Clean object files:

```bash
make clean
```

Full clean:

```bash
make fclean
```

Recompile:

```bash
make re
```

---

## ▶️ Usage

```bash
./minishell
```

Example:

```bash
minishell$ echo Hello World
Hello World
```

---

## 🔁 Execution Flow

1. Initialize environment (`env_init`)
2. Display prompt
3. Read user input
4. Parse input into tokens
5. Execute:

   * Builtins
   * External commands (via `execve`)
6. Loop until `exit`

---

## 🔧 Builtins Behavior

| Command  | Description              |
| -------- | ------------------------ |
| `echo`   | Print arguments          |
| `cd`     | Change directory         |
| `pwd`    | Print working directory  |
| `export` | Set environment variable |
| `unset`  | Remove variable          |
| `env`    | Display environment      |
| `exit`   | Exit shell               |

---

## ⚠️ Edge Cases Handled

* Empty input
* Invalid commands
* Missing files in redirection
* Pipes with multiple commands
* Signals during execution

---

## 🧪 Testing

You can test with:

```bash
ls | grep minishell
echo $HOME
cat < infile > outfile
```

---

## 📚 Allowed Functions

* `malloc`, `free`, `write`, `read`
* `fork`, `execve`, `wait`
* `open`, `close`, `dup`, `dup2`
* `signal`, `kill`
* `getcwd`, `chdir`
* `stat`, `lstat`
* `perror`, `strerror`

---

## 👨‍💻 Authors

* Your Name
* Partner Name

---

## 📄 License

This project is part of the 42 School curriculum and is intended for educational purposes.
