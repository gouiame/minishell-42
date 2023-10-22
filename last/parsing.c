/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ianibar <ianibar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:29:58 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 16:05:36 by ianibar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_first_cmd(char **cmd_arg, t_redir *redirections)
{
	t_cmd	*first_cmd;
	int		size;
	int		i;

	i = 0;
	first_cmd = malloc(sizeof(t_cmd));
	first_cmd->tab = NULL;
	first_cmd->in_fd = 0;
	first_cmd->out_fd = 1;
	if (cmd_arg != NULL)
	{
		size = ft_arg_size(cmd_arg);
		first_cmd->tab = malloc(sizeof(char *) * (size + 1));
		while (cmd_arg[i] != NULL)
		{
			first_cmd->tab[i] = ft_strdup(cmd_arg[i]);
			i++;
		}
		first_cmd->tab[i] = NULL;
	}
	first_cmd->redir = redirections;
	first_cmd->next = NULL;
	return (first_cmd);
}

void	ft_add_cmd(t_cmd *cmd, char **cmd_arg, t_redir *redirections)
{
	t_cmd	*new_cmd;
	int		size;
	int		i;

	i = 0;
	new_cmd = cmd;
	while (new_cmd->next != NULL)
		new_cmd = new_cmd->next;
	new_cmd->next = malloc(sizeof(t_cmd));
	new_cmd->next->tab = NULL;
	new_cmd->next->in_fd = 0;
	new_cmd->next->out_fd = 1;
	if (cmd_arg != NULL)
	{
		size = ft_arg_size(cmd_arg);
		new_cmd->next->tab = malloc(sizeof(char *) * (size + 1));
		while (cmd_arg[i] != NULL)
		{
			new_cmd->next->tab[i] = ft_strdup(cmd_arg[i]);
			i++;
		}
		new_cmd->next->tab[i] = NULL;
	}
	new_cmd->next->redir = redirections;
	new_cmd->next->next = NULL;
}

void	ft_set_cmd(t_parse *var)
{
	int	i;

	i = 0;
	if (var->cmd == NULL)
	{
		var->cmd = ft_first_cmd(var->cmd_arg, var->redir);
		(free_memory(var->cmd_arg), var->cmd_arg = NULL);
		var->redir = NULL;
	}
	else
	{
		ft_add_cmd(var->cmd, var->cmd_arg, var->redir);
		(free_memory(var->cmd_arg), var->cmd_arg = NULL);
		var->redir = NULL;
	}
}

void	ft_get_cmd_arg(t_parse *var)
{
	t_token	*token;
	int		i;

	var->cmd_arg = NULL;
	var->size = 0;
	i = 0;
	token = var->token;
	while (token->type != pipe_ && token->type != newline)
	{
		if (token->type == word || token->type == s_quote
			|| token->type == d_quote)
			var->size++;
		token = token->next;
	}
	ft_malloc_cmd_arg(var);
}

t_cmd	*ft_first_cmd_red(int fd_in, int fd_out)
{
	t_cmd	*first_cmd;

	first_cmd = malloc(sizeof(t_cmd));
	first_cmd->tab = NULL;
	first_cmd->in_fd = fd_in;
	first_cmd->out_fd = fd_out;
	first_cmd->next = NULL;
	return (first_cmd);
}
