/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:50:22 by jsance            #+#    #+#             */
/*   Updated: 2020/01/12 19:07:46 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include "./libft/ft_printf.h"
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

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

char	**init_env(char **env, char ***path)
{
	size_t	i;
	char	**copy_env;

	i = 0;
	while (env[i])
		i++;
	copy_env = (char**)malloc(sizeof(char*) * i + 1);
	i = 0;
	while (env[i])
	{
		copy_env[i] = (char*)malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		ft_strcpy(copy_env[i], env[i]);
		if (ft_strncmp((const char *)copy_env[i], "PATH", 4) == 0)
			*path = ft_strsplit(copy_env[i] + 5, ':');
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

void	go_exec(char *path, const char *input, char **argv, char **copy_env)
{
	pid_t	father;
	char	*file;
	size_t	len;
	int		status;

	len = ft_strlen((const char *)path) + ft_strlen(input) + 2;
	file = (char*)malloc(sizeof(char)* len);
	ft_bzero(file, len);
	ft_strcat(file, path);
	ft_strcat(file, "/");
	ft_strcat(file, input);
	file[len] = '\0';
	father = fork();
	if (father > 0)
		wait(&status);
	if (father == 0)
		execve(file, argv, copy_env);
	free(file);
}

void	try_exec(char **path, const char *input, char **argv, char **copy_env)
{
	DIR				*dir;
    struct dirent	*dp;
	size_t			i;
	int				flag;

	i = -1;
	flag = 1;
	while (path[++i] && flag)
	{
		if ((dir = opendir(path[i])) == NULL)
		{
			ft_printf("Something wrong with direcrory check try_exec function");
			exit(0);
		}
		while ((dp = readdir(dir)) != NULL)
		{
			if (ft_strcmp(dp->d_name, input) == 0)
			{
				go_exec(path[i], input, argv, copy_env);
				flag = 0;
			}
		}
		closedir(dir);
	}
}

int		main(int argc, char **argv, char **env)
{
	char	*input;
	char	**copy_env;
	char	**path;

	input = NULL;
	copy_env = init_env(env, &path);
	while (1)
	{
		display_prompt();
		input = get_input();
		try_exec(path, input, argv, copy_env);
		free(input);
	}
	return (0);
}