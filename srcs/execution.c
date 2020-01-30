/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:54:04 by jsance            #+#    #+#             */
/*   Updated: 2020/01/25 20:15:16 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_file(const char *path, const char *input, char **file, int cur_dir)
{
	size_t	len;

	if (cur_dir)
	{
		len = ft_strlen(path) + 1;
		if (!(*file = ft_strnew(len)))
			exit(0);
		ft_strcpy(*file, path);
	}
	else
	{
		len = ft_strlen(path) + ft_strlen(input) + 2;
		if (!(*file = ft_strnew(len)))
			exit(0);
		ft_strcat(*file, path);
		ft_strcat(*file, "/");
		ft_strcat(*file, input);
		(*file)[len] = '\0';
	}
}

void	go_exec(char *path, t_data *data, int *flag, int cur_dir)
{
	pid_t		father;
	char		*file;
	int			status;
	struct stat	st;

	signal(SIGINT, running_signal_handler);
	get_file(path, data->split_input[0], &file, cur_dir);
	*flag = 0;
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
					execve(file, data->split_input, data->copy_env);
			}
			else
				shell_err("minishell: permission denied: ", data->split_input[0]);
		}
	}
	free(file);
}

int		try_exec(t_data *data, int *flag)
{
	DIR				*dir;
	struct dirent	*dp;
	size_t			i;
	char			**path;

	i = -1;
	create_clean_path(data, &path, 0);
	if (path)
	{
		while (path[++i] && *flag)
		{
			if ((dir = opendir(path[i])) == NULL)
				continue ;
			while ((dp = readdir(dir)) != NULL)
				if (ft_strcmp(dp->d_name, data->split_input[0]) == 0)
					go_exec(path[i], data, flag, 0);
			(void)closedir(dir);
		}
		create_clean_path(data, &path, 1);
	}
	return ((*flag == 1) ? 0 : 1);
}
