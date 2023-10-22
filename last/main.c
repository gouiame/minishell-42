/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:47:32 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 17:27:10 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_parse(char *str, t_env *envs, int *exit_status)
{
	t_token	*token_list;

	token_list = NULL;
	if (ft_handle_quotes_error(str, token_list, exit_status) == 0)
		return (NULL);
	ft_create_token(str, &token_list, exit_status);
	if (token_list != NULL)
	{
		ft_check_expand(token_list, envs);
		ft_merge_quotes(&token_list);
		ft_handle_redirections(&token_list);
	}
	return (token_list);
}

void	ft_write_exit(void)
{
	printf ("exit\n");
	exit (0);
}

int	main(int ac, char **av, char **env)
{
	t_env	*envs;
	char	*str;
	t_cmd	*cmd_list;
	t_token	*token_list;
	int		exit_status;

	(void)ac;
	(void)av;
	envs = NULL;
	exit_status = 0;
	g_exit_st = 0;
	ft_init_env(&envs, env);
	while (1)
	{
		ft_handle_signals();
		str = readline("minishell$> ");
		if (g_exit_st)
		{
			exit_status = g_exit_st;
			g_exit_st = 0;
		}
		token_list = NULL;
		if (str == NULL)
			ft_write_exit();
		if (*str)
			add_history(str);
		token_list = ft_parse(str, envs, &exit_status);
		cmd_list = ft_parsing(token_list, envs);
		if (cmd_list && cmd_list->tab)
			execution(&envs, cmd_list, &exit_status);
		while (cmd_list)
		{
			if (cmd_list->in_fd != 0)
				close(cmd_list->in_fd);
			if (cmd_list->out_fd != 1)
				close(cmd_list->out_fd);
			cmd_list = cmd_list->next;
		}
		ft_free(token_list, cmd_list, str);
	}
}
