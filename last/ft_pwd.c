/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:16:57 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 17:25:20 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd(t_cmd *cmd, int *exit_status)
{
	char	*direct;

	direct = ft_pwd();
	if (direct)
	{
		ft_putstr_fd(direct, cmd->out_fd);
		free(direct);
	}
	*exit_status = 0;
}

char	*ft_pwd(void)
{
	char	*cwd;
	char	*direct;

	cwd = malloc(1024);
	direct = getcwd(cwd, 1024);
	if (!direct)
		return (NULL);
	return (cwd);
}
