/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ianibar <ianibar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:46:56 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 15:46:25 by ianibar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_create_node(char *token, t_type type)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (new_node)
	{
		new_node->token = token;
		new_node->type = type;
		new_node->expand = false;
		new_node->next = NULL;
	}
	return (new_node);
}

void	ft_add_to_node(t_token **head, t_token *new_node)
{
	t_token	*current;

	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	ft_newline(t_token **token)
{
	t_token	*new_node;

	new_node = ft_create_node(ft_strdup(""), newline);
	if (new_node)
		ft_add_to_node(token, new_node);
}

void	ft_merge(t_token **current)
{
	t_token	*temp;
	char	*merged_token;

	merged_token = ft_strjoin((*current)->token, (*current)->next->token);
	free((*current)->token);
	free((*current)->next->token);
	(*current)->token = merged_token;
	(*current)->type = word;
	temp = (*current)->next->next;
	(*current)->next = temp;
}

void	ft_merge_quotes(t_token **token_list)
{
	int		type1;
	int		type2;
	t_token	*current;

	current = *token_list;
	while (current != NULL && current->next != NULL)
	{
		type1 = current->type;
		type2 = current->next->type;
		if ((type1 == d_quote || type1 == word || type1 == dollar 
				|| type1 == s_quote) && (type2 == d_quote 
				|| type2 == word || type2 == s_quote || type2 == dollar))
		{
			ft_merge(&current);
		}
		else
			current = current->next;
	}
}
