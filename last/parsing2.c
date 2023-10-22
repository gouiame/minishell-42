/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ianibar <ianibar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:51:27 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 15:56:33 by ianibar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_intlen(long c)
{
	int	i;

	i = 0;
	if (c <= 0)
	{
		i++;
	}
	while (c != 0)
	{
		c = c / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	nb = n;
	len = ft_intlen(nb);
	if (nb == 0)
		return (ft_strdup("0"));
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * (-1);
	}
	str[len--] = '\0';
	while (nb > 0)
	{
		str[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	return (str);
}

void	ft_malloc_cmd_arg(t_parse *var)
{
	t_token	*token;
	int		i;

	i = 0;
	token = var->token;
	var->cmd_arg = malloc(sizeof(char *) * (var->size + 1));
	while (i < var->size)
	{
		if (token->type == word || token->type == s_quote
			|| token->type == d_quote)
			var->cmd_arg[i++] = ft_strdup(token->token);
		token = token->next;
	}
	var->cmd_arg[i] = NULL;
}

void	ft_init_var(t_parse *var, t_token *tokens_list)
{
	var->token = tokens_list;
	var->redir = NULL;
	var->cmd_arg = NULL;
	var->cmd = NULL;
	var->size = 0;
}

void	ft_set_redir(t_parse *var, t_token *token)
{
	t_redir	*redirection;
	t_redir	*temp;

	redirection = malloc(sizeof(t_redir));
	redirection->type = token->type;
	redirection->filename = ft_strdup(token->token);
	redirection->next = NULL;
	temp = var->redir;
	if (!temp)
	{
		var->redir = redirection;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = redirection;
}
