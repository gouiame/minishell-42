/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:42 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 17:44:09 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_quotes_error(char *str, t_token *t, int *exit_status)
{
	int	double_q;
	int	single_q;
	int	i;

	(void)t;
	i = 0;
	single_q = 0;
	double_q = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			double_q++;
		else if (str[i] == '\'')
			single_q++;
		i++;
	}
	if (single_q % 2 != 0 || double_q % 2 != 0)
	{
		*exit_status = 258;
		perror("unclosed quotes");
		return (0);
	}
	return (1);
}

int	ft_check_errors(t_token *token)
{
	while (token->next != NULL)
	{
		if ((token->type == input || token->type == output 
				|| token->type == heredoc || token->type == append)
			&& (token->next->type == pipe_ || token->next->type == output
				|| token->next->type == heredoc || token->next->type == append
				|| token->next->type == input))
			return (0);
		if (token->type == pipe_ && token->next->type == pipe_)
			return (0);
		token = token->next;
	}
	return (1);
}

int	ft_syntax_error(t_token *token, char *str)
{
	t_token	*last_token;

	(void)str;
	last_token = token;
	if (token->type == pipe_)
		return (0);
	if ((token->type == input || token->type == output 
			|| token->type == heredoc || token->type == append)
		&& (token->next == NULL || token->next->type == newline))
		return (0);
	if (ft_check_errors(token) == 0)
		return (0);
	while (token->next != NULL)
	{
		last_token = token;
		token = token->next;
	}
	if (last_token->type == input || last_token->type == output
		|| last_token->type == heredoc || last_token->type == append
		|| last_token->type == pipe_)
		return (0);
	return (1);
}

void	ft_check_syntax(t_token **t, char *str, int *exit_status)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_syntax_error(*t, str) == 0)
		{
			*exit_status = 258;
			*t = NULL;
			perror("Syntax error");
			return ;
		}
		i++;
	}
}
