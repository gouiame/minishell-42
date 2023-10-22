/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:35 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 16:52:09 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc ((ft_strlen(s1) + 1) * sizeof(char));
	if (p == NULL)
		return (0);
	if (!s1)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;
	int		len_s;

	i = 0;
	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		str = malloc(ft_strlen(s + start) * sizeof(char) + 1);
	else
		str = malloc(len * sizeof(char) + 1);
	if (str == NULL )
		return (NULL);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_len_word(char *str, int i)
{
	while (str[i] != '\0' && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| (str[i] == '_')))
	{
		i++;
	}
	return (i);
}

static size_t	words_counter(char const *str, char c)
{
	size_t	counter;
	int		i;

	i = 0;
	counter = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if ((str[i] == c && str[i + 1] != c) || str[i + 1] == '\0' )
			counter++;
		i++;
	}
	return (counter);
}

char	**ft_split(char *s, char c)
{
	size_t	i;
	char	**split;
	size_t	j;
	size_t	wordstart;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	split = (char **) malloc ((words_counter(s, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (i < words_counter(s, c) && s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		wordstart = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		split[i] = ft_substr(s, wordstart, j - wordstart);
		if (split[i++] == NULL)
			return (free_memory(split));
	}
	split[i] = NULL;
	return (split);
}
