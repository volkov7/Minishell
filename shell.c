/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:50:22 by jsance            #+#    #+#             */
/*   Updated: 2020/01/16 19:15:17 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(void)
{
	ft_putstr("$> ");
}

void	printenv(t_data *data)
{
	size_t	i;

	i = -1;
	while (data->copy_env[++i])
		ft_putendl((const char *)data->copy_env[i]);
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
	i = -1;
	while (env[++i])
	{
		(*data)->copy_env[i] = ft_strnew(ft_strlen(env[i]) + 1);
		ft_strcpy((*data)->copy_env[i], env[i]);
		if (ft_strncmp((const char *)(*data)->copy_env[i], "PATH", 4) == 0)
			(*data)->path = ft_strsplit((*data)->copy_env[i] + 5, ':');
	}
	(*data)->copy_env[i] = NULL;
}

void	get_file(const char *path, const char *input, char **file)
{
	size_t	len;
	
	len = ft_strlen(path) + ft_strlen(input) + 2;
	if (!(*file = ft_strnew(len)))
		exit(0);
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
					execve(file, data->split_input, data->copy_env);
			}
			else
				write(2, "minishell: permission denied: \n", 31);
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

int		echo_builtin(char *input, t_data *data)
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
	return(1);
}

char	*get_env(t_data *data, const char *searching)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(searching);
	while (data->copy_env[++i])
	{
		if (ft_strnequ(data->copy_env[i], searching, len))
			return (ft_strchr(data->copy_env[i], '=') + 1);
	}
	return (NULL);
}

size_t		find_env(t_data *data, const char *searching)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(searching);
	while (data->copy_env[++i])
	{
		if (ft_strnequ(data->copy_env[i], searching, len))
			return (i);
	}
	return (i);
}

void	update_env(const char *env_var, t_data *data, char *new_val)
{
	size_t	pos;
	
	pos = find_env(data, env_var);
	if (data->copy_env[pos])
	{
		free(data->copy_env[pos]);
		if (new_val)
			data->copy_env[pos] = ft_strjoin(env_var, new_val);
		else
			data->copy_env[pos] = ft_strjoin(env_var, NULL);
	}
}

void	print_path(t_data *data)
{
	char	*home;
	char	*oldpwd;
	size_t	len_home;
	size_t	len_oldpwd;
	char	*print_path;

	home = get_env(data, "HOME=");
	oldpwd = get_env(data, "OLDPWD=");
	len_home = ft_strlen((const char *)home);
	len_oldpwd = ft_strlen((const char *)oldpwd);
	if (!(print_path = ft_strnew(len_oldpwd - len_home + 1)))
		exit(0);
	ft_strcat(print_path, "~");
	ft_strcat(print_path, oldpwd + len_home);
	ft_putendl((const char *)print_path);
	free(print_path);
}

int		chg_dir(t_data *data, char *path, int print)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	if (!(chdir(path)))
	{
		if (print)
			print_path(data);
		update_env("OLDPWD=", data, cwd);
		getcwd(cwd, PATH_MAX);
		update_env("PWD=", data, cwd);
	}
	else
	{
		write(2, "cd: ", 4);
		if (access(path, F_OK) == -1)
			write(2, "no such file or directory: ", 27);
		else if (access(path, R_OK) == -1)
			write(2, "permission denied: ", 19);
		else
			write(2, "not a directory: ", 17);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
	return (1);
}

char	*path_replace(char *cwd, t_data *data)
{
	char	*tmp;
	size_t	len_cwd;
	size_t	rep_len;
	size_t	tmp_len;
	size_t	ind;

	if (!(tmp = ft_strstr(cwd, data->split_input[1])))
		return (NULL);
	tmp_len = ft_strlen((const char *)tmp);
	rep_len = ft_strlen((const char *)data->split_input[2]);
	len_cwd = ft_strlen((const char *)cwd);
	if (!(tmp = ft_strnew(len_cwd - 1 + rep_len)))
		exit (0);
	ind = len_cwd - tmp_len;
	ft_strncpy(tmp, cwd, ind);
	ft_strcat(tmp, data->split_input[2]);
	ft_strcat(tmp, cwd + ind + 1);
	return (tmp);
}

int		chk_two_args(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	int		ret;

	if (data->split_input[2])
	{
		if (data->split_input[3])
		{
			write(2, "cd: too many arguments\n", 23);
			return (1);
		}
		getcwd(cwd, PATH_MAX);
		if (!(tmp = path_replace(cwd, data)))
		{
			write(2, "cd: string not in pwd:", 22);
			write(2, data->split_input[1], ft_strlen(data->split_input[1]));
			write(2, "\n", 1);
			return (1);
		}
		ret = chg_dir(data, tmp, 0);
		free(tmp);
		return (ret);
	}
	return (0);
}

int		cd_builtin(t_data *data)
{
	char	*home;

	home = 	get_env(data, "HOME=");
	if (data->split_input[1] == NULL)
		return ((home && *home) ? chg_dir(data, home, 0) : 1);
	if (chk_two_args(data))
		return (1);
	else
	{
		if (ft_strcmp(data->split_input[1], "--") == 0)
			return ((home && *home) ? chg_dir(data, home, 0) : 1);
		else if (ft_strcmp(data->split_input[1], "-") == 0)
			return (chg_dir(data, get_env(data, "OLDPWD="), 1));
		return (chg_dir(data, data->split_input[1], 0));
	}
	return (1);
}

int		check_builtin(char *input, t_data *data)
{
	if (ft_strcmp(data->split_input[0], "echo") == 0)
		return (echo_builtin(input, data));
	else if (ft_strcmp(data->split_input[0], "cd") == 0)
		return (cd_builtin(data));
	else if (ft_strcmp(data->split_input[0], "env") == 0)
	{
		printenv(data);
		return (1);
	}
	return (0);
}

void	check_input(char *input, t_data *data)
{
	if (check_builtin(input, data));
	else
		try_exec(input, data);
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