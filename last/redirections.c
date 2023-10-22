/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ianibar <ianibar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:23:55 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 15:55:44 by ianibar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_switch_type(t_token **token_list, t_token *current, t_token *prev)
{
	t_token	*temp;
	t_token	*to_remove;

	if (current->next)
		current->next->type = current->type;
	to_remove = current;
	if (prev != NULL)
	{
		prev->next = current->next;
		current = prev->next;
	}
	else 
	{
		temp = *token_list;
		*token_list = current->next;
		current = *token_list;
	}
}

void	ft_handle_redirections(t_token **token_list)
{
	t_token	*current;
	t_token	*prev;

	prev = NULL;
	current = *token_list;
	while (current != NULL && current->next != NULL)
	{
		if ((current->type == input || current->type == output
				|| current->type == append || current->type == heredoc) 
			&& (current->next->type == word || current->next->type == d_quote))
		{
			ft_switch_type(token_list, current, prev);
		}
		else
			prev = current;
		if (current)
			current = current->next;
	}
}
