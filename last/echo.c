/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:16:25 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 17:40:34 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	if (!str[1])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd, int *exit_status)
{
	int	i;
	int	flags1;
	int	flags2;

	i = 1;
	flags1 = 1;
	flags2 = 0;
	if (cmd->tab[1] && check_n(cmd->tab[1]))
		flags1 = 0;
	if (!flags1)
		i = 2;
	if (cmd->tab[1])
	{
		while (cmd->tab[i])
		{
			if (!check_n(cmd->tab[i]) || flags2)
			{
				flags2 = 1;
				if (flags2)
				{
					ft_putstr_fd(cmd->tab[i], cmd->out_fd);
					if (cmd->tab[i + 1])
						write(cmd->out_fd, " ", 1);
				}
			}
			i++;
		}
	}
	if (flags1)
		write(cmd->out_fd, "\n", 1);
	*exit_status = 0;
}
