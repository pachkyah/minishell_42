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
# include "libft.h"

/* ================= MACROS ================= */

# define SUCCESS 0
# define ERROR 1

/* --- Redirection Types --- */
typedef enum e_redir_type
{
	RED_IN,      // <
	RED_OUT,     // >
	RED_APPEND,  // >>
	RED_HEREDOC  // <<
} t_redir_type;

/* --- Structures --- */

typedef struct s_redir
{
    char            *file;      // Filename or Heredoc delimiter
    t_redir_type	type;      // REDIR_IN, REDIR_OUT, etc.
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

/* Environment list */
typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

/* Shell state */
typedef struct s_shell {
	char	**env;
	int		last_status;
} t_shell;

/* Token types */
typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR
} t_token_type;

/* Token structure */
typedef struct s_token {
	char			*value;
	t_token_type	type;
	struct s_token	*next;
} t_token;

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

/* ================= SSIGNALS ================= */
void    init_signals(void);

// Parser (Your Partner)
int			parse_input(char *line, t_data *data);
void		free_cmds(t_cmd *cmds);
char		*get_cmd_path(char *cmd, char **envp);
t_token		*tokenize(char *line);
t_token		*ft_new_token(char *value, t_token_type type);
void		ft_token_add_back(t_token **head, t_token *new);
void		free_tokens(t_token *head);

/* ================= EXECUTOR ================= */
int     executor(t_data *data);
void    handle_redirections(t_cmd *cmd);
char    *find_path(char *cmd, char **envp);

/* ================= BUILTINS ================= */
int		is_builtin(char *cmd);
void	exec_builtin(t_cmd *cmd, t_data *data);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_shell *shell);
int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, t_shell *shell);
int		builtin_exit(char **args, t_shell *shell);

/* ================= ENV ================= */

t_env	*env_init(char **envp);
char	*env_get(t_env *env, char *key);
void	env_set(t_env **env, char *key, char *value);
void	env_unset(t_env **env, char *key);
char	*get_env_value(char *var_name, t_shell *shell);
char	*expand_variables(char *input, t_shell *shell);

/* ================= UTILS ================= */

void     error_msg(char *msg);
void     free_split(char **arr);

#endif