/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:39 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 17:48:32 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_create_node_env(char *var, char *val)
{
	t_env	*head;

	head = (t_env *)malloc(sizeof(t_env));
	head->name = ft_strdup(var);
	head->value = ft_strdup(val);
	head->index = 0;
	head->next = NULL;
	return (head);
}

void	ft_add_node_env(t_env *envs, char *var, char *val)
{
	t_env	*current;

	current = envs;
	while (current->next != NULL)
		current = current->next;
	current->next = (t_env *)malloc(sizeof(t_env));
	current->next->name = ft_strdup(var);
	current->next->value = ft_strdup(val);
	current->next->index = 0;
	current->next->next = NULL;
}

void	if_not_env(t_env **envs)
{
	char	*value;

	value = ft_pwd();
	*envs = ft_create_node_env("PWD", value);
	ft_add_node_env(*envs, "SHLVL", "1");
	ft_add_node_env(*envs, "OLDPWD", NULL);
}

void	ft_init_env(t_env **envs, char **env)
{
	char	**str;
	char	*pos;
	int		i;

	i = 0;
	if (env[0])
	{
		str = ft_split(env[0], '=');
		*envs = ft_create_node_env(str[0], str[1]);
		i = 1;
		while (env[i++])
		{
			pos = ft_strchr(env[i], '=');
			if (pos != NULL)
			{
				*pos = '\0';
				ft_add_node_env(*envs, env[i], pos + 1);
			}
		}
		free_memory(str);
	}
	else
		if_not_env(envs);
}
