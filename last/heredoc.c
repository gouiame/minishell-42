/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ianibar <ianibar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:35:06 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 16:14:34 by ianibar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*p;

	i = 0;
	j = 0;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = malloc(len);
	if (p == NULL)
		return (NULL);
	while (s1[i++] != '\0')
		p[i] = s1[i];
	while (s2[j] != '\0')
	{
		p[i++] = s2[j++];
	}
	p[i] = '\0';
	return (p);
}

char	*ft_expanded(char *line, t_env *env)
{
	char	*tmp;
	char	*final_line;
	int		i;
	int		j;

	final_line = NULL;
	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] != '\0' && line[i] != '$')
		{
			i++;
			j++;
		}
		if (j != 0)
		{
			tmp = ft_substr(line, i - j, j);
			final_line = ft_strjoin1(final_line, tmp);
			j = 0;
		}
		if (line[i] == '$')
		{
			i++;
			j = 0;
			while (line[i] && line[i] != '$' && line[i] != ' ')
			{
				i++;
				j++;
			}
			tmp = ft_find_value(ft_substr(line, i - j, j), env);
			final_line = ft_strjoin1(final_line, tmp);
			j = 0;
		}
	}
	return (final_line);
}

void	ft_read_heredoc(int fd, char *delimiter, t_env *env)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if ((line != NULL && ft_strcmp(line, delimiter) == 0) || !line)
			break ;
		expanded_line = ft_expanded(line, env);
		ft_putstr_fd(expanded_line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}
