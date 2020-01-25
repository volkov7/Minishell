/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:06:01 by jsance            #+#    #+#             */
/*   Updated: 2020/01/25 20:17:10 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_env(t_data **data, size_t len)
{
	char	**fresh;
	size_t	i;

	if (!(fresh = (char**)malloc(sizeof(char*) * len + 1)))
		exit(0);
	i = -1;
	while ((*data)->copy_env[++i])
	{
		if (!(fresh[i] = ft_strdup((*data)->copy_env[i])))
			exit(0);
		ft_strdel(&((*data)->copy_env[i]));
	}
	fresh[i] = NULL;
	fresh[i + 1] = NULL;
	free((*data)->copy_env);
	(*data)->copy_env = fresh;
}

char	*delete_quotes(char *new_value)
{
	int		i;
	size_t	count;
	size_t	len;
	char	*fresh;

	i = -1;
	count = 0;
	while (new_value[++i])
		if (IS_QUOTE(new_value[i]))
			count++;
	len = ft_strlen(new_value) - count;
	if (!(fresh = ft_strnew(len)))
		exit(0);
	i = -1;
	count = 0;
	while (new_value[++i])
	{
		if (IS_QUOTE(new_value[i]))
			continue ;
		fresh[count] = new_value[i];
		count++;
	}
	ft_strdel(&new_value);
	return (fresh);
}

int		setenv_builtin(t_data *data)
{
	if (data->split_input[1] == NULL)
	{
		write(2, "setenv: Too few arguments\n", 27);
		return (1);
	}
	else if (data->split_input[2] && data->split_input[3])
	{
		write(2, "setenv: Too many arguments\n", 28);
		return (1);
	}
	if (data->split_input[2])
		data->split_input[2] = delete_quotes(data->split_input[2]);
	update_env(data->split_input[1], data, data->split_input[2]);
	return (1);
}

void	remove_env(t_data *data, size_t pos, int i, int size)
{
	char	**fresh;

	if (data->copy_env[pos])
	{
		while (data->copy_env[size])
			size++;
		if (!(fresh = (char**)malloc(sizeof(char*) * size - 1)))
			exit(0);
		size = -1;
		while (data->copy_env[++i])
		{
			if (i == pos)
				ft_strdel(&(data->copy_env[i++]));
			if (!data->copy_env[i])
				break ;
			if (!(fresh[++size] = ft_strdup(data->copy_env[i])))
				exit(0);
			ft_strdel(&(data->copy_env[i]));
		}
		fresh[i - 1] = NULL;
		free(data->copy_env);
		data->copy_env = fresh;
	}
}

int		unsetenv_builtin(t_data *data)
{
	int		size;
	int		i;

	size = 0;
	i = -1;
	if (data->split_input[1] == NULL)
	{
		write(2, "unsetenv: Too few arguments\n", 29);
		return (1);
	}
	else if (data->split_input[2] && data->split_input[3])
	{
		write(2, "unsetenv: Too many arguments\n", 28);
		return (1);
	}
	remove_env(data, find_env(data, data->split_input[1]), i, size);
	return (1);
}
