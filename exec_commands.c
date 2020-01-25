/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:59:17 by jsance            #+#    #+#             */
/*   Updated: 2020/01/25 20:02:31 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_builtin(t_data *data)
{
	if (ft_strcmp(data->split_input[0], "exit") == 0)
		return (-1);
	else if (ft_strcmp(data->split_input[0], "echo") == 0)
		return (echo_builtin(data));
	else if (ft_strcmp(data->split_input[0], "cd") == 0)
		return (cd_builtin(data));
	else if (ft_strcmp(data->split_input[0], "setenv") == 0)
		return (setenv_builtin(data));
	else if (ft_strcmp(data->split_input[0], "unsetenv") == 0)
		return (unsetenv_builtin(data));
	else if (ft_strcmp(data->split_input[0], "env") == 0)
	{
		printenv(data);
		return (1);
	}
	return (0);
}

int		parsing_input(t_data *data, int *flag)
{
	char		*full_path;
	size_t		len;
	struct stat	st;

	len = 0;
	found_len(data, &len);
	full_path = ft_strnew(len + 1);
	create_full_path(data, &full_path);
	if (!(ft_strchr((const char *)full_path, '/')))
	{
		ft_strdel(&full_path);
		return (0);
	}
	if (lstat(full_path, &st) != -1)
		go_exec(full_path, data, flag, 1);
	else
		shell_err("minishell: no such file or directory: ", full_path);
	ft_strdel(&full_path);
	return (1);
}

int		check_input(t_data *data)
{
	int		ret;
	int		flag;

	ret = check_builtin(data);
	flag = 1;
	if (ret == 1 || try_exec(data, &flag) == 1)
		return (1);
	else if (ret == -1)
		return (-1);
	else if (parsing_input(data, &flag))
		return (1);
	else
		shell_err("minishell: command not found: ", data->split_input[0]);
	return (0);
}

int		exec_commands(char **commands, t_data *data)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	while (commands[++i])
	{
		data->split_input = ft_strsplit(commands[i], ' ');
		ret = check_input(data);
		clean_data(&data, 0);
		if (ret == -1)
			break ;
	}
	return (ret);
}
