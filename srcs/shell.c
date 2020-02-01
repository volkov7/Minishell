/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:50:22 by jsance            #+#    #+#             */
/*   Updated: 2020/02/01 13:33:36 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(void)
{
	ft_putstr("$> ");
}

void	init_env(char **env, t_data **data)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	(*data)->copy_env = (char**)malloc(sizeof(char*) * i + 1);
	i = -1;
	while (env[++i])
	{
		(*data)->copy_env[i] = ft_strnew(ft_strlen(env[i]) + 1);
		ft_strcpy((*data)->copy_env[i], env[i]);
		if (ft_strncmp((const char *)(*data)->copy_env[i], "PATH=", 5) == 0)
			(*data)->path = ft_strsplit((*data)->copy_env[i] + 5, ':');
	}
	(*data)->copy_env[i] = NULL;
}

void	create_st(t_data **data)
{
	if (!(*data = (t_data*)malloc(sizeof(t_data))))
		exit(0);
	(*data)->path = NULL;
	(*data)->copy_env = NULL;
	(*data)->split_input = NULL;
}

int		isemptystr(char *str)
{
	int		i;
	int		min;
	int		max;

	i = -1;
	min = 33;
	max = 126;
	if (str)
	{
		while (str[++i])
		{
			if (str[i] >= min && str[i] <= max)
				return (0);
		}
	}
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;
	int		ret;
	char	**commands;

	create_st(&data);
	init_env(env, &data);
	while (1 && ret != -1)
	{
		signal(SIGINT, signal_handler);
		display_prompt();
		input = get_input(data);
		if (isemptystr(input))
		{
			ft_strdel(&input);
			continue ;
		}
		commands = ft_strsplit(input, ';');
		ret = exec_commands(commands, data);
		free(input);
		clean_commands(&commands);
	}
	clean_data(&data, 1);
	return (0);
}
