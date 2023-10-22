/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:31:55 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 17:45:00 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

int	g_exit_st;

typedef struct s_env
{
	char			*value;
	char			*name;
	int				index;
	struct s_env	*next;
}t_env;

typedef enum s_type
{
	word,
	pipe_,
	input,
	output,
	heredoc,
	append,
	d_quote,
	s_quote,
	space,
	dollar,
	newline,
}t_type;

typedef struct s_token
{
	char			*token;
	t_type			type;
	bool			expand;
	int				fd_;
	struct s_token	*next;
	struct s_token	*prev;
}t_token;

typedef struct s_redir
{
	char			*filename;
	t_type			type;
	struct s_redir	*next;
}t_redir;

typedef struct s_cmd
{
	char			**tab;
	t_redir			*redir;
	int				in_fd;
	int				out_fd;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_parse{
	t_token	*token;
	t_cmd	*cmd;
	t_redir	*redir;
	char	**cmd_arg;
	int		size;
}t_parse;

char			**ft_split(char *s, char c);
char			**free_memory(char **p);
char			*ft_strdup(char *s1);
int				ft_strlen(char *str);
char			*ft_itoa(int n);
char			*ft_substr(char *s, int start, int len);
char			*ft_strchr(char *str, char c);
char			*ft_strtrim(char *s1, char *set);
int				ft_syntax_error(t_token *token, char *str);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strjoin(char *s1, char *s2);
void			ft_create_token(char *str, t_token **t, int *exit_status);
int				ft_len_word(char *str, int i);
void			ft_remove_spaces(t_token **token_list);
void			ft_treat_single_quote(t_token **token_list, char *str, int *i);
void			ft_treat_double_quote(t_token **token_list, char *str, int *i);
void			ft_treat_word(t_token **token_list, char *str, int *i);
int				ft_len_of_word(char *str, int i);
void			ft_treat_quotes(t_token **token, char *str, int *i);
void			ft_add_to_node(t_token **head, t_token *new_node);
t_token			*ft_create_node(char *token, t_type type);
void			ft_newline(t_token **token);
void			ft_init_env(t_env **envs, char **env);
char			*ft_check_expand(t_token *token_list, t_env *env);
void			ft_read_heredoc(int fd, char *delimiter, t_env *env);
void			ft_treat_heredoc(t_token **token_list, char *str, int *i);
void			ft_handle_redirections(t_token **token_list);
void			ft_handle_heredoc(t_token *token_list, char *str);
int				ft_handle_quotes_error(char *str, t_token *t, int *exit_status);
void			ft_merge_quotes(t_token **token_list);
t_cmd			*ft_parsing(t_token *tokens_list, t_env *env);
int				ft_arg_size(char **cmd_arg);
void			ft_malloc_cmd_arg(t_parse *var);
void			ft_init_var(t_parse *var, t_token *tokens_list);
void			ft_set_redir(t_parse *var, t_token *token);
void			ft_check_syntax(t_token **t, char *str, int *exit_status);
void			ft_handle_signals(void);
void			ft_handle_status(t_token **t, char *str, int *i, int *exit_);
void			ft_free(t_token *token_list, t_cmd *cmd_list, char *str);
void			ft_tokenize(char *str, t_token **token_list, int *exit_status);

		///////////////*********execution*********////////////////

void			ft_env(t_env *env, t_cmd *cmd, int *exit_status);
void			ft_indexing(t_env *env);
void			ft_export(t_cmd	*cmd, t_env	**env, int *exit_status);
void			ft_echo(t_cmd *cmd, int *exit_status);
void			ft_built(t_cmd	*cmd, t_env	**env, int index, int *exit_status);
int				search_built(char *cmd);
void			execution(t_env **envs, t_cmd *cmd, int *exit_status);
int				my_strcmp(char *str1, char *str2);
int				checking_export(char *str);
int				ft_isdigit( int arg );
void			print_export(t_env *env, t_cmd *cmd);
int				ft_lstsize(t_env *lst);
char			*get_name(char *cmd);
int				is_exsisting(t_env *env, char *name);
void			new_val(char *cmd, t_env **env);
void			join_value(t_env *env, char *name, char *value, int index);
char			*get_value(char *cmd);
void			ft_unset(t_env **env, t_cmd *cmd, int *exit_status);
int				ft_isalpha(int c);
void			ft_cd(t_env *env, t_cmd *cmd, int *exit_status);
char			*ft_pwd(void);
void			ft_set_cmd(t_parse *var);
void			ft_get_cmd_arg(t_parse *var);
void			print_pwd(t_cmd *cmd, int *exit_status);
int				check_env(t_env *env, char *str);
int				ft_exit(t_cmd *cmd, int *exit_status);
void			ft_lstadd_back(t_env **lst, t_env *new);
t_env			*ft_lstnew(char *name, char *value);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
char			*ft_find_value(char *key, t_env *env);
void			ft_write_exit(void);
void			ft_clear(void);
void			ft_printing(t_cmd *cmd, int i);
void			ft_execute_cmd(t_env *envs, t_cmd *cmd, char **env);
#endif
