/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:49:56 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 17:11:14 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *cmd)
{
	int		i;
	int		len;
	int		j;
	char	*value;	

	i = 0;
	j = 0;
	if (!ft_strchr(cmd, '='))
		return (0);
	while (cmd[i] && cmd[i] != '=')
		i++;
	i++;
	len = ft_strlen(cmd) - i + 1;
	value = malloc(len);
	while (i < ft_strlen(cmd))
		value[j++] = cmd[i++];
	value[j] = '\0';
	return (value);
}

char	*ft_strjoin2(char *s1, char *s2)
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
	free(s1);
	return (p);
}

void	join_value(t_env *env, char *name, char *value, int index)
{
	t_env	*head;
	char	*tmp;

	head = env;
	while (head)
	{
		if (!my_strcmp(head->name, name))
		{
			if (index == 1)
			{
				head->value = ft_strjoin2(head->value, value);
				free(value);
				return ;
			}
			else
			{
				tmp = head->value;
				head->value = value;
				free(tmp);
				return ;
			}
		}
		head = head->next;
	}
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*t;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	t = *lst;
	while (t->next != NULL)
		t = t->next;
	t->next = new;
}

t_env	*ft_lstnew(char *name, char *value)
{
	t_env	*t;

	t = malloc(sizeof(t_env));
	if (!t)
		return (NULL);
	t->name = name;
	t->value = value;
	t->index = 0;
	t->next = NULL;
	return (t);
}
