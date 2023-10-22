/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ianibar <ianibar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:18 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 15:49:59 by ianibar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_char_pos(char *str, char c, int pos)
{
	pos++;
	while (str[pos])
	{
		if (str[pos] == c)
			return (pos);
		(pos)++;
	}
	return (0);
}

void	ft_treat_single_quote(t_token **token_list, char *str, int *i)
{
	char	*token;
	t_token	*new_node;
	int		j;
	int		start;

	start = *i;
	j = 0;
	*i = ft_find_char_pos(str, '\'', *i);
	if (*i == 0)
		return ;
	token = malloc((*i - start + 2) * sizeof(char));
	if (token == NULL)
		exit(1);
	start++;
	while (start < *i)
		token[j++] = str[start++];
	token[j] = '\0';
	new_node = ft_create_node(token, word);
	if (new_node)
		ft_add_to_node(token_list, new_node);
}

void	ft_treat_double_quote(t_token **token_list, char *str, int *i)
{
	char	*token;
	t_token	*new_node;
	int		j;
	int		start;

	start = *i;
	j = 0;
	*i = ft_find_char_pos(str, '\"', *i);
	if (*i == 0)
		return ;
	token = malloc((*i - start + 2) * sizeof(char));
	if (token == NULL)
		exit(1);
	start++;
	while (start < *i)
		token[j++] = str[start++];
	token[j] = '\0';
	new_node = ft_create_node(token, d_quote);
	if (new_node)
		ft_add_to_node(token_list, new_node);
}

int	ft_len_of_word(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '|' && str[i] != '<'
			&& str[i] != '>' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\'' && str[i] != '\"' && (str[i] != '$' 
				&& str[i + 1] != '?'))
			i++;
		else
			break ;
	}
	return (i);
}

void	ft_treat_word(t_token **token_list, char *str, int *i)
{
	char	*token;
	t_token	*new_node;
	int		j;
	int		start;

	start = *i;
	j = 0;
	*i = ft_len_of_word(str, *i);
	token = malloc((*i - start + 2) * sizeof(char));
	if (token == NULL)
		exit(1);
	while (start < *i)
		token[j++] = str[start++];
	token[j] = '\0';
	new_node = ft_create_node(token, word);
	if (new_node)
		ft_add_to_node(token_list, new_node);
	*i -= 1 ;
}
