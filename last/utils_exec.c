/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:49:21 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 16:49:46 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (!my_strcmp(head->name, "PATH"))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

char	**my_env(t_env *env)
{
	int		i;
	int		len;
	char	**tab;
	char	*str;
	t_env	*head;

	head = env;
	i = 0;
	len = 0;
	if (env)
		len = ft_lstsize(env);
	tab = (char **)malloc(len + 1);
	while (head)
	{
		if (head->value)
		{
			str = ft_strjoin(head->name, "=");
			tab[i] = ft_strjoin(str, head->value);
		}
		else
			tab[i] = head->name;
		i++;
		head = head->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_comparing(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == 'c' || str[0] == 'C') && (str[1] == 'l' \
	|| str[1] == 'L') && (str[2] == 'e' || str[2] == 'E') && \
	(str[3] == 'a' || str[3] == 'A') && (str[4] == 'r' || str[4] == 'R'))
		return (1);
	return (0);
}

void	ft_clear(void)
{
	setenv ("TERM", "xterm-256color", 1);
	system ("clear");
	exit (0);
}

void	ft_execute_cmd(t_env *envs, t_cmd *cmd, char **env)
{
	char	**tab;
	char	*str;
	int		i;

	i = 0;
	if (ft_comparing(cmd->tab[0]))
	{
		if (check_env(envs, "PATH"))
			ft_clear();
		else
			ft_putstr_fd("No such file or directory\n", 2);
		exit(127);
	}
	if (check_env(envs, "PATH"))
	{
		tab = ft_split(get_path(envs), ':');
		if (!tab)
			return ;
		if (ft_strchr(cmd->tab[0], '/'))
		{
			execve(cmd->tab[0], cmd->tab, env);
			perror("-->");
			if (access(cmd->tab[0], F_OK))
				exit(127);
			exit(126);
			return ;
		}
		else
		{
			while (tab[i])
			{
				str = ft_strjoin(tab[i], "/");
				if (!access(ft_strjoin(str, cmd->tab[0]), F_OK))
					execve(ft_strjoin(str, cmd->tab[0]), cmd->tab, env);
				i++;
			}
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->tab[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
}
