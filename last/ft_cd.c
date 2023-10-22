/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 01:33:42 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 17:24:23 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (!my_strcmp("HOME", head->name))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

int	check_env(t_env *env, char *str)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (!my_strcmp(head->name, str))
			return (1);
		head = head->next;
	}
	return (0);
}

void	ft_cd(t_env *env, t_cmd *cmd, int *exit_status)
{
	char	*current;
	char	*new_pwd;
	int		flags;

	flags = 0;
	current = ft_pwd();
	if (!cmd->tab[1])
	{
		if (chdir(get_home(env)))
			ft_putstr_fd("ash: cd: HOME not set\n", 2);
		else
			flags = 1;
	}
	else if (chdir(cmd->tab[1]))
	{
		if (access(cmd->tab[1], F_OK) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmd->tab[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			*exit_status = 1;
			return ;
		}
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmd->tab[1], 2);
			ft_putstr_fd(": Not a directory\n", 2);
			*exit_status = 1;
			return ;
		}
	}
	else
		flags = 1;
	if (flags)
	{
		if (check_env(env, "OLDPWD"))
		{
			if (!check_env(env, "PWD"))
				join_value(env, "OLDPWD", "", 0);
			else
				join_value(env, "OLDPWD", current, 0);
		}
		new_pwd = ft_pwd();
		if (check_env(env, "PWD"))
			join_value(env, "PWD", new_pwd, 0);
	}
	*exit_status = 0;
}
