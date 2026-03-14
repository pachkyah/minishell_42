#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/* --- Redirection Types --- */
# int    REDIR_IN        1  // <
# int    REDIR_OUT       2  // >
# int    APPEND          3  // >>
# int    HEREDOC         4  // <<

/* --- Structures --- */

typedef struct s_redir
{
    char            *file;      // Filename or Heredoc delimiter
    int             type;      // REDIR_IN, REDIR_OUT, etc.
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **args;     // ["ls", "-la", NULL]
    t_redir         *redirs;    // Linked list of all < > >> << for this command
    int             fd_in;      // Final resolved input FD (default 0)
    int             fd_out;     // Final resolved output FD (default 1)
    struct s_cmd    *next;      // Next command if a '|' exists
}   t_cmd;

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef struct s_data
{
    t_cmd           *cmds;      // The list of commands to execute
    t_env           *env_list;  // Linked list of environment variables
    char            **envp;     // Array version of env (for execve)
    int             last_exit;  // Exit status of last command ($?)
    int             stdin_bak;  // Backup of original STDIN
    int             stdout_bak; // Backup of original STDOUT
}   t_data;

/* --- Function Prototypes --- */

// Signals (You)
void    init_signals(void);

// Parser (Your Partner)
int     parse_input(char *line, t_data *data);
void    free_cmds(t_cmd *cmds);

// Executor (You)
int     executor(t_data *data);
void    handle_redirections(t_cmd *cmd);
char    *find_path(char *cmd, char **envp);

// Builtins (Shared)
int     is_builtin(char *cmd);
void    exec_builtin(t_cmd *cmd, t_data *data);

#endif