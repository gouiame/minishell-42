/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:21:31 by ianibar           #+#    #+#             */
/*   Updated: 2023/10/22 17:34:54 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_built(t_cmd	*cmd, t_env	**env, int index, int *exit_status)
{
	if (index == 1)
		ft_export(cmd, env, exit_status);
	if (index == 2)
		ft_env(*env, cmd, exit_status);
	if (index == 3)
		ft_echo(cmd, exit_status);
	if (index == 7)
		ft_unset(env, cmd, exit_status);
	if (index == 5)
		ft_cd(*env, cmd, exit_status);
	if (index == 4)
		print_pwd(cmd, exit_status);
	if (index == 6)
		ft_exit(cmd, exit_status);
}

int	search_built(char *cmd)
{
	if (!my_strcmp(cmd, "export"))
		return (1);
	if (!my_strcmp(cmd, "env"))
		return (2);
	if (!my_strcmp(cmd, "echo"))
		return (3);
	if (!my_strcmp(cmd, "pwd"))
		return (4);
	if (!my_strcmp(cmd, "cd"))
		return (5);
	if (!my_strcmp(cmd, "exit"))
		return (6);
	if (!my_strcmp(cmd, "unset"))
		return (7);
	return (0);
}

int	ft_lstsize1(t_cmd *cmd)
{
	t_cmd	*t;
	int		i;

	i = 0;
	t = cmd;
	if (!t)
		return (0);
	while (t)
	{
		t = t->next;
		i++;
	}
	return (i);
}

char	**ft_convert_to_env(t_env *envs)
{
	t_env	*head;
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc((ft_lstsize(envs) + 1) * sizeof(char *));
	if (!new_env)
		exit(EXIT_FAILURE);
	head = envs;
	if (!head)
		return (NULL);
	while (i < ft_lstsize(envs))
	{
		new_env[i] = ft_strjoin(head->name, "=");
		new_env[i] = ft_strjoin(new_env[i], head->value);
		i++;
		head = head->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	execution(t_env **envs, t_cmd *cmd, int *exit_status)
{
	int		fds[2];
	pid_t	pid;
	t_cmd	*tmp;
	int		prev_fd;
	int		size;
	int		idx;
	int		status;
	char	**new_env;

	tmp = cmd;
	prev_fd = 0;
	size = ft_lstsize1(cmd);
	idx = 0;
	new_env = ft_convert_to_env(*envs);
	if (!cmd->next)
	{
		if (search_built(cmd->tab[0]) != 0)
			ft_built(cmd, envs, search_built(cmd->tab[0]), exit_status);
		else
		{
			pid = fork();
			if (!pid)
			{
				if (cmd->out_fd != 1)
					dup2(cmd->out_fd, 1);
				if (cmd->in_fd != 0)
					dup2(cmd->in_fd, 0);
				ft_execute_cmd(*envs, cmd, new_env);
				free_memory(new_env);
				exit(0);
			}
			status = 0;
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				*exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == 3)
					printf ("Quit : 3\n");
				*exit_status = 128 + WTERMSIG(status);
			}
		}
		return ;
	}
	while (cmd)
	{
		if (cmd->next)
			pipe(fds);
		pid = fork();
		if (pid == 0)
		{
			if (cmd->in_fd != 0)
				dup2(cmd->in_fd, 0);
			if (cmd->out_fd != 1)
				dup2(cmd->out_fd, 1);
			if (idx != 0 && cmd->in_fd == 0)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (idx != size - 1 && cmd->out_fd == 1)
				dup2(fds[1], 1);
			close(fds[0]);
			close(fds[1]);
			if (search_built(cmd->tab[0]) != 0)
				ft_built(cmd, envs, search_built(cmd->tab[0]), exit_status);
			else
			{
				ft_execute_cmd(*envs, cmd, new_env);
				exit(0);
			}
		}
		else
		{
			if (idx != 0)
				close(prev_fd);
			close(fds[1]); // Close write end of the pipe
			prev_fd = fds[0];
		}
		cmd = cmd->next;
		idx++;
	}
	status = 0;
	while (tmp)
	{
		wait(&status);
		tmp = tmp->next;
	}
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			printf ("Quit : 3\n");
		*exit_status = 128 + WTERMSIG(status);
	}
}
