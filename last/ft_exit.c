/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:12:41 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 17:17:02 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *st)
{
	int	i;
	int	r;
	int	nb;

	r = 1;
	nb = 0;
	i = 0;
	while ((st[i] >= 9 && st[i] <= 13) || st[i] == ' ')
		i++;
	if (st[i] == '+' || st[i] == '-')
	{
		if (st[i] == '-')
			r = -1;
		i++;
	}
	while (st[i] >= '0' && st[i] <= '9')
	{
		nb = (nb * 10) + (st[i] - '0');
		i++;
	}
	return (nb * r);
}

int	ft_isnum(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == '-')
		i++;
	while (cmd[i])
	{
		if (cmd[i] < '0' || cmd[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, int *exit_status)
{
	int	i;

	i = 0;
	if (!cmd->tab[1])
	{
		printf("exit\n");
		exit(1);
	}
	if (ft_isnum(cmd->tab[1]))
	{
		if (cmd->tab[2])
			printf ("minishell: exit: too many arguments\n");
		else
		{
			printf("exit\n");
			exit (ft_atoi(cmd->tab[1]) % 256);
		}
		*exit_status = 1;
	}
	else
	{
		printf("minishell: exit: %s: numeric argument required", cmd->tab[1]);
		exit(255);
	}
	return (0);
}
