/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ianibar <ianibar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:02:27 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 16:05:48 by ianibar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(t_token *token, int *fd_in, int *fd_out, t_env *env)
{
	char	*delimiter;

	if (token->type == input)
		*fd_in = open(token->next->token, O_RDONLY);
	if (token->type == output)
		*fd_out = open(token->token, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (token->type == append)
		*fd_out = open(token->token, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (token->type == heredoc)
	{
		delimiter = token->token;
		*fd_in = open("/tmp/.tmp_her", O_CREAT | O_WRONLY | O_TRUNC, 0666);
		ft_read_heredoc(*fd_in, delimiter, env);
		close(*fd_in);
		*fd_in = open("/tmp/.tmp_her", O_RDONLY, 0666);
	}
}

t_cmd	*ft_parsing(t_token *tokens_list, t_env *env)
{
	t_parse	var;
	int		in_fd;
	int		out_fd;
	t_cmd	*tmp;

	ft_init_var(&var, tokens_list);
	while (var.token != NULL)
	{
		if ((var.token->type == word || var.token->type == s_quote
				|| var.token->type == d_quote) && !var.cmd_arg)
		{
			in_fd = 0;
			out_fd = 1;
			ft_get_cmd_arg(&var);
		}
		if (var.token->type == pipe_ || var.token->type == newline)
		{
			ft_set_cmd(&var);
			if (in_fd != 0 || out_fd != 1)
			{
				tmp = var.cmd;
				while (var.cmd->next)
					var.cmd = var.cmd->next;
				var.cmd->in_fd = in_fd;
				var.cmd->out_fd = out_fd;
				var.cmd = tmp;
			}
		}
		if (var.token->type == input
			|| var.token->type == output
			|| var.token->type == append
			|| var.token->type == heredoc)
		{
			open_files(var.token, &in_fd, &out_fd, env);
		}
		var.token = var.token->next;
	}
	return (var.cmd);
}
