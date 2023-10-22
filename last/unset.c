/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:25:16 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 17:30:42 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checking_unset(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_node(t_env *env)
{
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
	free(env);
}

void	ft_pop(t_env **env, char *name)
{
	t_env	*head;
	t_env	*temp;

	head = *env;
	if (!my_strcmp(head->name, name))
	{
		temp = head;
		*env = (*env)->next;
		return ;
	}
	while ((*env) && (*env)->next)
	{
		if ((*env)->next && !my_strcmp((*env)->next->name, name))
		{
			temp = (*env)->next;
			(*env)->next = (*env)->next->next;
			(*env) = head;
			return ;
		}
		(*env) = (*env)->next;
	}
	(*env) = head;
}

void	ft_unset(t_env **env, t_cmd *cmd, int *exit_status)
{
	int	i;

	i = 1;
	while (cmd->tab[i])
	{
		if (!checking_unset(cmd->tab[i]))
		{
			ft_putstr_fd("./minishell: unset: ", 2);
			ft_putstr_fd(cmd->tab[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			*exit_status = 1;
		}
		else
			ft_pop(env, cmd->tab[i]);
		i++;
	}
	*exit_status = 0;
}
