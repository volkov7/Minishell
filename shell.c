/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:50:22 by jsance            #+#    #+#             */
/*   Updated: 2020/01/13 15:58:15 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(void)
{
	ft_printf("$> ");
}

char	*get_input(void)
{
	char	*input;

	input = NULL;
	get_next_line(0, &input);
	if (ft_strcmp((const char *)input, "exit") == 0)
		exit(0);
	return (input);
}

void	init_env(char **env, t_data **data)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	(*data)->copy_env = (char**)malloc(sizeof(char*) * i + 1);
	i = 0;
	while (env[i])
	{
		(*data)->copy_env[i] = (char*)malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		ft_strcpy((*data)->copy_env[i], env[i]);
		if (ft_strncmp((const char *)(*data)->copy_env[i], "PATH", 4) == 0)
			(*data)->path = ft_strsplit((*data)->copy_env[i] + 5, ':');
		i++;
	}
	(*data)->copy_env[i] = NULL;
}

void	get_file(const char *path, const char *input, char **file)
{
	size_t	len;
	
	len = ft_strlen((const char *)path) + ft_strlen(input) + 2;
	*file = (char*)malloc(sizeof(char)* len);
	ft_bzero(*file, len);
	ft_strcat(*file, path);
	ft_strcat(*file, "/");
	ft_strcat(*file, input);
	(*file)[len] = '\0';
}

void	go_exec(char *path, const char *input, t_data *data)
{
	pid_t		father;
	char		*file;
	int			status;
	struct stat	st;

	get_file(path, data->split_input[0], &file);
	if (lstat(file, &st) != -1)
	{
		if (st.st_mode & S_IFREG)
		{
			if (st.st_mode & S_IXUSR)
			{
				father = fork();
				if (father > 0)
					wait(&status);
				if (father == 0)
					execve(file, (data->split_input), data->copy_env);
			}
			else
				write(2, "minishell: permission denied: ", 30);
		}
	}
	free(file);
}

void	try_exec(const char *input, t_data *data)
{
	DIR				*dir;
    struct dirent	*dp;
	size_t			i;
	int				flag;

	i = -1;
	flag = 1;
	while (data->path[++i] && flag)
	{
		if ((dir = opendir(data->path[i])) == NULL)
		{
			closedir(dir);
			continue ;
		}
		while ((dp = readdir(dir)) != NULL)
		{
			if (ft_strcmp(dp->d_name, data->split_input[0]) == 0)
			{
				go_exec(data->path[i], input, data);
				flag = 0;
			}
		}
		closedir(dir);
	}
}

void	create_st(t_data **data)
{
	if (!(*data = (t_data*)malloc(sizeof(t_data))))
		exit(0);
	(*data)->path = NULL;
	(*data)->copy_env = NULL;
	(*data)->split_input = NULL;
}

void	clean_data(t_data **data, int flag)
{
	size_t	i;

	if (flag)
	{
		i = -1;
		while ((*data)->path[++i])
			free((*data)->path[i]);
		free((*data)->path);
		i = -1;
		while ((*data)->copy_env[++i])
			free((*data)->copy_env[i]);
		free((*data)->copy_env);
	}
	i = -1;
	while ((*data)->split_input[++i])
		free((*data)->split_input[i]);
	free((*data)->split_input);
	if (flag)
		free(*data);
}

int		go_echo(char *input, t_data *data)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (data->split_input[1] != NULL)
	{
		if (ft_strcmp(data->split_input[1], "-n") == 0)
		{
			i++;
			n = 1;
		}
		while (data->split_input[++i])
			ft_printf("%s ", data->split_input[i]);	
	}
	ft_printf((n) ? "" : "\n");
	return(1);
}

int		check_builtin(char *input, t_data *data)
{
	if (ft_strcmp(data->split_input[0], "echo") == 0)
		return (go_echo(input, data));
	return (0);
}

void	check_input(char *input, t_data *data)
{
	check_builtin(input, data);
	// try_exec(input, data);
}

int		main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;

	input = NULL;
	create_st(&data);
	init_env(env, &data);
	while (1)
	{
		display_prompt();
		input = get_input();
		if (ft_strchr((const char *)input, ';') != NULL)
			data->split_input = ft_strsplit(input, ';'); // Можно потом сплитить по пробелу, чтобы получить для кажой функции свои аргументы
		else
			data->split_input = ft_strsplit(input, ' ');
		check_input(input, data);
		free(input);
		clean_data(&data, 0);
	}
	clean_data(&data, 1);
	return (0);
}