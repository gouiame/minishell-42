/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 21:23:12 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 17:23:48 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_val(char *cmd, t_env **env)
{
	int		i;
	char	*name;

	i = 0;
	name = get_name(cmd);
	if (is_exsisting(*env, name))
	{
		if (get_value(cmd) && ft_strchr(cmd, '+'))
			join_value(*env, name, get_value(cmd), 1);
		else if (get_value(cmd))
			join_value(*env, name, get_value(cmd), 2);
	}
	else
	{
		if (get_value(cmd))
			ft_lstadd_back(env, ft_lstnew(name, get_value(cmd)));
		else
			ft_lstadd_back(env, ft_lstnew(name, NULL));
	}
}

void	add_export(t_cmd *cmd, t_env **env, int *exit_status)
{
	int	i;

	i = 1;
	while (cmd->tab[i])
	{
		if (!checking_export(cmd->tab[i]))
		{
			ft_putstr_fd ("minishell: export: ", 2);
			ft_putstr_fd(cmd->tab[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			*exit_status = 1;
		}
		else
			new_val(cmd->tab[i], env);
		i++;
	}
}

void	ft_export(t_cmd	*cmd, t_env	**env, int *exit_status)
{
	if (cmd->tab[1])
		add_export(cmd, env, exit_status);
	else
		print_export(*env, cmd);
}

void	print_export(t_env *env, t_cmd *cmd)
{
	while (env)
	{
		if (!env->value)
		{
			ft_putstr_fd("declare -x ", cmd->out_fd);
			ft_putstr_fd(env->name, cmd->out_fd);
			ft_putstr_fd("\n", cmd->out_fd);
		}
		else
		{
			ft_putstr_fd("declare -x ", cmd->out_fd);
			ft_putstr_fd(env->name, cmd->out_fd);
			write (cmd->out_fd, "=\"", 2);
			ft_putstr_fd(env->value, cmd->out_fd);
			write (cmd->out_fd, "\"", 1);
			ft_putstr_fd("\n", cmd->out_fd);
		}
		env = env->next;
	}
}

int	is_exsisting(t_env *env, char *name)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (ft_strlen(name) == ft_strlen(head->name)
			&& !my_strcmp(head->name, name))
			return (1);
		head = head->next;
	}
	return (0);
}
