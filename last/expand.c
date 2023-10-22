/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:05:18 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 16:44:57 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_value(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (current->name && ft_strcmp(key, current->name) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*p;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = malloc(len);
	if (p == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		p[i++] = s2[j++];
	}
	p[i] = '\0';
	return (p);
}

void	ft_process_dollar(char **new_token, char *str, int *i, t_env *env)
{
	char	*word_;
	char	*value;
	int		start;
	char	current_char[2];

	if (str[*i] == '$')
	{
		(*i)++;
		start = *i;
		while (str[*i] && !ft_strchr(" \t\n\v\f\r$\"|><'-", str[*i]))
			(*i)++;
		word_ = ft_substr(str, start, *i - start);
		value = ft_find_value(word_, env);
		*new_token = ft_strjoin(*new_token, value);
		free(word_);
	}
	else
	{
		current_char[0] = str[*i];
		current_char[1] = '\0';
		*new_token = ft_strjoin(*new_token, current_char);
		(*i)++;
	}
}

void	ft_handle_dollar_quotes(t_token *token_list, t_env *env)
{
	t_token	*current;
	char	*new_token;
	char	*str;
	int		i;

	current = token_list;
	while (current != NULL)
	{
		if (current->type == d_quote && ft_strchr(current->token, '$'))
		{
			new_token = ft_strdup("");
			str = current->token;
			i = 0;
			while (str[i])
			{
				ft_process_dollar(&new_token, str, &i, env);
			}
			free(current->token);
			current->token = new_token;
			current->type = word;
		}
		current = current->next;
	}
}

char	*ft_check_expand(t_token *token_list, t_env *env)
{
	t_token	*current;
	char	*key;
	char	*value;
	char	*tmp;

	current = token_list;
	while (current != NULL) 
	{
		if (current->type == d_quote && ft_strchr(current->token, '$'))
			ft_handle_dollar_quotes(current, env);
		else if (current->type == heredoc)
		{
			tmp = current->next->token;
			current->token = ft_strjoin("$", tmp);
			current = current->next;
		}
		else if (current->type == dollar)
		{
			key = current->token;
			value = ft_find_value(key, env);
			free(current->token);
			current->token = ft_strdup(value);
			current->type = word;
		}
		current = current->next;
	}
	return (value);
}
