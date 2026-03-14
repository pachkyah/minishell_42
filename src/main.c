#include "minishell.h"

//dummy main for testing

// Helper to quickly create a mock command node
t_cmd *utils_create_mock_cmd(char **args)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    cmd->args = args;
    cmd->redirs = NULL;
    cmd->fd_in = 0;
    cmd->fd_out = 1;
    cmd->next = NULL;
    return (cmd);
}

int main(int argc, char **argv, char **envp)
{
    t_data data;
    
    (void)argc;
    (void)argv;

    // 1. Setup Data & Env (You'll eventually need a real env-to-list converter)
    data.envp = envp; 
    data.last_exit = 0;

    // 2. MOCK PARSER: Manually creating "ls -l | grep .c"
    char *cmd1_args[] = {"ls", "-l", NULL};
    char *cmd2_args[] = {"grep", ".c", NULL};
    
    data.cmds = utils_create_mock_cmd(cmd1_args);
    data.cmds->next = utils_create_mock_cmd(cmd2_args);

    // 3. YOUR MISSION: The Executor
    // This is where you will spend the next few days.
    printf("--- Starting Execution ---\n");
    executor(&data);
    printf("--- Execution Finished ---\n");

    // 4. Cleanup (Partner will eventually write a proper free_cmds)
    free(data.cmds->next);
    free(data.cmds);

    return (0);
}