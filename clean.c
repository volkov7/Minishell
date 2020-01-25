/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:08:15 by jsance            #+#    #+#             */
/*   Updated: 2020/01/25 18:15:32 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_commands(char ***commands)
{
	int		i;

	i = -1;
	while ((*commands)[++i])
		free((*commands)[i]);
	free(*commands);
}

void	clean_data(t_data **data, int flag)
{
	size_t	i;

	if (flag)
	{
		i = -1;
		while ((*data)->path[++i])
			ft_strdel(&(*data)->path[i]);
		free((*data)->path);
		i = -1;
		while ((*data)->copy_env[++i])
			ft_strdel(&(*data)->copy_env[i]);
		free((*data)->copy_env);
	}
	else
	{
		i = -1;
		while ((*data)->split_input[++i])
			ft_strdel(&(*data)->split_input[i]);
		free((*data)->split_input);
	}
	if (flag)
		free(*data);
}

void	create_clean_path(t_data *data, char ***path, int clean)
{
	int		i;

	i = -1;
	if (clean)
	{
		while ((*path)[++i])
			ft_strdel(&((*path)[i]));
		free(*path);
	}
	else
	{
		*path = NULL;
		while (data->copy_env[++i])
		{
			if (ft_strncmp((const char *)data->copy_env[i], "PATH=", 5) == 0)
				*path = ft_strsplit(data->copy_env[i] + 5, ':');
		}
	}
}
