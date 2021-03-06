/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** mysh
*/

#include <stddef.h>

#ifndef MYSH_H_
#define MYSH_H_

// Enum

typedef enum state_s {
    ON,
    OFF
}state_t;

// | > < >> <<

typedef enum type_s {
    PIPE,
    D_RED,
    G_RED,
    D_D_RED,
    G_D_RED,
    NOTHING,
    ALLOC
}type_t;

// Linked List

typedef struct chain_s {
    char *name_env;
    char *env_value;
    struct chain_s *next;
}chain_t;

typedef struct list_s {
    chain_t *head;
}list_t;

typedef struct task_s {
    char **line;
    int pipe[2];
    type_t task_next;
    type_t task_prev;
    struct task_s *next;
    struct task_s *prev;
}task_t;

// Struct

typedef struct shell_s {
    state_t state;
    char **init_env;
    list_t env;
    char exit_value;
}shell_t;

typedef struct s_cmd
{
    char *funct;
    void (*fct_ptr)(shell_t *, char **);
} t_cmd;


// INITIALISATION

int init_env(char **envp, list_t *env);
int index_of_env(char *env);
char *get_env_name(char *env);
char *get_env_value(char *env);
int my_memset(char *str, int len);

// BUILTINS

void my_exit(shell_t *shell, char **args);
void my_env(shell_t *shell, char **args);
void my_unsetenv(shell_t *shell, char **args);
void my_setenv(shell_t *shell, char **args);
void my_cd(shell_t *shell, char **args);
void my_exe(shell_t *shell, char **args);

// SHELL FUNCTIONS

int shell_loop(shell_t *shell);
int concat_exe(shell_t *shell, char **old_args, char *path, char **envp);
int executable_this(char **envp, char *path, char **args, shell_t *shell);
int print_status(int status, shell_t *shell);

// ENV MANAGEMENT

int print_env(char **env);
int print_list_env(list_t *env);
int my_unset_list(shell_t *shell, char *to_unset);
int get_index_of_env(shell_t *shell, char *env);
void my_setenv_list(shell_t *shell, char **args);
void my_cd_list(shell_t *shell, char *path);
char *get_value_of_env(shell_t *shell, int index);
char **transform_env(list_t *env);
int get_length_of_env(list_t *env);

// USER INTERACTIONS

char *get_user_input(void);
int task_interpreter(char *input, shell_t *shell);

// PARSING

char **my_parse_shell(char *to_parse);
int clean_str(char *to_clean);
int my_matches(char *str, char *cmp);
int command_listing(char *cmd, char **args, shell_t *shell);

// PARSING TASK

int preload_task(char *line, task_t **task);
void free_task(task_t **task);
char *space_add(char *str, int to_free);
int in_quote(char *str, int len);
int is_task(char const *str);
type_t get_task(char const *str);
int set_task(task_t *task, char **separate, int current, int len);
int set_line(task_t *task, char **separate, int current, int len);
void free_task(task_t **task);
int verify_task(task_t **task);

// DIFF EXE

int simple_listing(char *cmd, char **args, shell_t *shell);
void simple_exe(shell_t *shell, char **args);
int prev_pipe(task_t *task, shell_t *shell);
int next_pipe(task_t *task, shell_t *shell);
int middle_pipe(task_t *task, shell_t *shell);
int prev_left_redir(task_t *task, shell_t *shell);
int prev_rigth_redir(task_t *task, shell_t *shell);
int prev_d_rigth_red(task_t *task, shell_t *shell);

// Dictionnary

static const t_cmd builtin[] = {{"env", &my_env},
                                {"unsetenv", &my_unsetenv},
                                {"setenv", &my_setenv},
                                {"cd", &my_cd},
                                {"*", &my_exe},
                                {"*", &simple_exe},
                                {NULL, NULL}};

#endif /* !MYSH_H_ */