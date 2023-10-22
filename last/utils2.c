/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:51:33 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 17:49:45 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (c == '\0')
		return (&str[len]);
	if (!str)
		return (NULL);	
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*p;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[i] && ft_strchr(set, s1[len]))
		len--;
	p = ft_substr(s1, i, (len - i) + 1);
	return (p);
}

void	ft_treat_quotes(t_token **token, char *str, int *i)
{
	if (str[*i] == '\"')
		ft_treat_double_quote(token, str, i);
	else if (str[*i] == '\'')
		ft_treat_single_quote(token, str, i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
