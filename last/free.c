/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:45:49 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 17:35:00 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*prev;

	while (cmd_list)
	{
		free_memory(cmd_list->tab);
		if (cmd_list->redir)
		{
			free(cmd_list->redir->filename);
			free(cmd_list->redir);
		}
		prev = cmd_list;
		cmd_list = cmd_list->next;
		free(prev);
	}
}

void	ft_free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->token);
		free(tmp);
	}
}

void	ft_free(t_token *token_list, t_cmd *cmd_list, char *str)
{
	ft_free_token_list(token_list);
	ft_free_cmd_list(cmd_list);
	free(str);
}

char	**free_memory(char **p)
{
	int	i;

	i = 0;
	if (p == NULL)
		return (NULL);
	while (p[i])
	{
		free (p[i]);
		i++;
	}
	free (p);
	return (NULL);
}

void	ft_remove_spaces(t_token **token_list)
{
	t_token	*current;
	t_token	*temp;

	current = *token_list;
	while (current && current->next)
	{
		if (current->type == pipe_ || current->type == input
			|| current->type == output || current->type == heredoc
			|| current->type == append)
		{
			while (current->next && current->next->type == space)
			{
				temp = current->next;
				current->next = temp->next;
				free (temp->token);
				free (temp);
			}
		}
		current = current->next;
	}
}
