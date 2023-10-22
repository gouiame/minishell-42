/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:00:05 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 17:25:45 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env, t_cmd *cmd, int *exit_status)
{
	t_env	*head;

	head = env;
	if (!head)
		return ;
	if (cmd->tab[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->tab[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		*exit_status = 127;
	}
	while (head)
	{
		if (head->value)
		{
			ft_putstr_fd(head->name, cmd->out_fd);
			ft_putstr_fd("=", cmd->out_fd);
			ft_putstr_fd(head->value, cmd->out_fd);
			ft_putstr_fd("\n", cmd->out_fd);
		}
		head = head->next;
	}
}

void	ft_init_indexing(t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		head->index = 0;
		head = head->next;
	}
}

void	ft_indexing(t_env *env)
{
	t_env	*head;
	t_env	*tmp;
	int		env_len;
	int		i;

	ft_init_indexing(env);
	env_len = ft_lstsize(env);
	i = 0;
	while (1)
	{
		tmp = env;
		head = env;
		while (head)
		{
			if ((my_strcmp(head->name, tmp->name) == -1 
					|| tmp->index) && head->index == 0)
				tmp = head;
			head = head->next;
		}
		tmp->index = i + 1;
		if (i + 1 >= env_len)
			break ;
		i++;
	}
}

int	checking_export(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (j < i)
	{
		if (str[j] == '+')
		{
			if (j + 1 != i)
				return (0);
		}
		if (!ft_isalpha(str[j]) && str[j] != '_' 
			&& !ft_isdigit(str[j]) && str[j] != '+')
			return (0);
		j++;
	}
	return (1);
}
