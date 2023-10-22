/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:48:40 by cgouiame          #+#    #+#             */
/*   Updated: 2023/10/22 16:49:11 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *cmd)
{
	char	*str;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != '+' && cmd[i] != '=')
		i++;
	str = (char *)malloc(i + 1);
	i = 0;
	while (cmd[i] && cmd[i] != '+' && cmd[i] != '=')
	{
		str[i] = cmd[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
