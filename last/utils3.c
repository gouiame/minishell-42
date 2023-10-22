/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:41:11 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 17:42:45 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_create_token(char *str, t_token **t, int *exit_status)
{
	str = ft_strtrim(str, " \t\n\v\f\r");
	ft_tokenize(str, t, exit_status);
	ft_remove_spaces(t);
	ft_check_syntax(t, str, exit_status);
	free(str);
}

int	ft_arg_size(char **cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != NULL)
		i++;
	return (i);
}
