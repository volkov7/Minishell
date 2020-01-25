/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:51:48 by jsance            #+#    #+#             */
/*   Updated: 2020/01/25 20:11:50 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_no_quote(char *str, char *quote)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (*quote == 0x0)
		{
			if (IS_QUOTE(str[i]))
			{
				*quote = str[i];
				continue ;
			}
			ft_putchar(str[i]);
		}
		else
		{
			if (str[i] == *quote)
			{
				*quote = 0x0;
				continue ;
			}
			ft_putchar(str[i]);
		}
	}
}

int		echo_builtin(t_data *data)
{
	size_t	i;
	size_t	n;
	char	quote;

	i = 0;
	n = 0;
	quote = 0x0;
	if (data->split_input[1] != NULL)
	{
		if (ft_strcmp(data->split_input[1], "-n") == 0)
		{
			i++;
			n = 1;
		}
		while (data->split_input[++i])
		{
			ft_put_no_quote(data->split_input[i], &quote);
			ft_putstr((data->split_input[i + 1]) ? " " : "");
		}
	}
	ft_putstr((n) ? "" : "\n");
	return (1);
}
