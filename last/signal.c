/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ianibar <ianibar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:44:03 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 15:53:04 by ianibar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	handler_sig(int signum)
{
	(void)signum;
	if (waitpid(-1, NULL, WNOHANG))
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_st = 1;
	}
}

void	ft_handle_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &handler_sig);
	signal(SIGQUIT, SIG_IGN);
}
