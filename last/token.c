/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:29 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 17:45:10 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_treat_dollar(t_token **t, char *str, int *i)
{
	char	*token;
	t_token	*new_node;
	int		j;
	int		start;

	(*i)++;
	start = *i;
	j = 0;
	*i = ft_len_word(str, *i);
	token = malloc((*i - start + 2) * sizeof(char));
	if (token == NULL)
	{
		free(token);
		exit(1);
	}
	while (start < *i)
		token[j++] = str[start++];
	token[j] = '\0';
	new_node = ft_create_node(token, dollar);
	if (new_node)
		ft_add_to_node(t, new_node);
}

void	ft_treat_redirections(t_token **token, char *str, int *i)
{
	t_token	*new_node;	

	new_node = NULL;
	if (str[*i] == '>' && str[*i + 1] == '>' )
	{
		new_node = ft_create_node(ft_strdup(">>"), append);
		if (new_node)
			ft_add_to_node(token, new_node);
		(*i)++;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		new_node = ft_create_node(ft_strdup("<<"), heredoc);
		if (new_node)
			ft_add_to_node(token, new_node);
		(*i)++;
	}
}

void	ft_treat_symbols(t_token **token, char *str, int *i)
{
	t_token	*new_node;

	new_node = NULL;
	if (str[*i] == ' ' )
		new_node = ft_create_node(ft_strdup(" "), space);
	else if (str[*i] == '|' )
		new_node = ft_create_node(ft_strdup("|"), pipe_);
	else if ((str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '<' && str[*i + 1] == '<'))
		ft_treat_redirections(token, str, i);
	else if (str[*i] == '>')
		new_node = ft_create_node(ft_strdup(">"), output);
	else if (str[*i] == '<')
		new_node = ft_create_node(ft_strdup("<"), input);
	if (new_node)
		ft_add_to_node(token, new_node);
}

void	ft_handle_status(t_token **t, char *str, int *i, int *exit_)
{
	t_token	*new_node;

	(void)str;
	(*i)++;
	new_node = ft_create_node(ft_itoa(*exit_), word);
	if (new_node)
		ft_add_to_node(t, new_node);
}

void	ft_tokenize(char *str, t_token **token_list, int *exit_status)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(" \t\n\v\f\r", str[i]) != NULL)
			str[i] = ' ';
		if (ft_strchr("| <>", str[i]) != NULL)
			ft_treat_symbols(token_list, str, &i);
		else if (str[i] == '$' && str[i + 1] == '?')
			ft_handle_status(token_list, str, &i, exit_status);
		else if (str[i] == '\"' || str[i] == '\'')
			ft_treat_quotes(token_list, str, &i);
		else if (str[i] == '$')
		{
			ft_treat_dollar(token_list, str, &i);
			continue ;
		}
		else
			ft_treat_word(token_list, str, &i);
		i++;
	}
	if (str[i] == '\0')
		ft_newline(token_list);
}
