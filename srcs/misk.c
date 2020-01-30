/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:05:43 by jsance            #+#    #+#             */
/*   Updated: 2020/01/25 20:09:45 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	running_signal_handler(int sig)
{
	write(1, "\n", 1);
}

void	signal_handler(int sig)
{
	write(1, "\n", 1);
	display_prompt();
}

void	shell_err(const char *err, char *file)
{
	write(2, err, ft_strlen(err));
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
}

void	found_len(t_data *data, size_t *len)
{
	int		i;
	int		j;
	int		start;

	i = -1;
	while (data->split_input[++i])
	{
		j = -1;
		start = 0;
		while (data->split_input[i][++j])
		{
			if (data->split_input[i][j] != '\\' || start == 1)
			{
				(*len)++;
				start = 0;
				continue ;
			}
			start = 1;
		}
		if (start != 1)
			break ;
		(*len)++;
	}
}

void	create_full_path(t_data *data, char **path)
{
	int		i;
	int		j;
	int		k;
	int		start;

	i = -1;
	k = -1;
	while (data->split_input[++i])
	{
		j = -1;
		start = 0;
		while (data->split_input[i][++j])
		{
			if (data->split_input[i][j] != '\\' || start == 1)
			{
				(*path)[++k] = data->split_input[i][j];
				start = 0;
				continue ;
			}
			start = 1;
		}
		if (start != 1)
			break ;
		(*path)[++k] = ' ';
	}
}
