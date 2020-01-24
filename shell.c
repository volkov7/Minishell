/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:50:22 by jsance            #+#    #+#             */
/*   Updated: 2020/01/22 17:48:25 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(void)
{
	ft_putstr("$> ");
}

void	printenv(t_data *data)
{
	int		i;

	i = -1;
	while (data->copy_env[++i])
		ft_putendl((const char *)data->copy_env[i]);
}

char	*tildejoin(char *input, char *home, size_t index)
{
	size_t	len;
	char	*fresh;

	len = ft_strlen((const char *)input) - 1 + ft_strlen(home);
	if (!(fresh = ft_strnew(len)))
		exit(0);
	ft_strncat(fresh, input, index);
	ft_strcat(fresh, (const char *)home);
	ft_strcat(fresh, (const char *)input + index + 1);
	ft_strdel(&input);
	return (fresh);
}

char	*tilde_exp(char *input, t_data *data)
{
	char	*fresh;
	char	*home;
	size_t	i;

	home = get_env(data, "HOME");
	i = 0;
	while (input[i] && input[i] != '~')
		i++;
	if (home != NULL)
	{
		if ((input[i] == '~' && input[i + 1] == '/' && input[i + 2] != '~')
			|| (input[i] == '~' && input[i + 1] == '\0'))
			return (tildejoin(input, home, i));
	}
	if (!(fresh = ft_strdup((const char *)input)))
		exit(0);
	ft_strdel(&input);
	return (fresh);
}

size_t	get_len(char *input, size_t	i)
{
	size_t	len;

	len = 0;
	while (ft_isalpha(input[++i]) || input[i] == '_')
		len++;
	return (len);
}

char	*found_env(char *input, t_data *data, size_t i, size_t *env_len)
{
	char	*env;
	char	*found;

	*env_len = get_len(input, i);
	if (!(env = ft_strnew(*env_len)))
		exit(0);
	ft_strncpy(env, (const char *)input + i + 1, *env_len);
	found = get_env(data, env);
	ft_strdel(&env);
	return (found);
}

char	*dollar_exp(char *input, t_data *data)
{
	char	*fresh;
	size_t	i;
	size_t	len;
	size_t	env_len;
	char	*found;

	i = 0;
	while (input[i] && input[i] != '$')
		i++;
	if (input[i] == '$' && input[i + 1] && input[i + 1] != '$')
	{
		found = found_env(input, data, i, &env_len);
		len = ft_strlen(input) - env_len - 1 + ft_strlen(found);
		if (!(fresh = ft_strnew(len)))
			exit(0);
		ft_strncpy(fresh, (const char *)input, i);
		ft_strcat(fresh, (const char *)found);
		ft_strcat(fresh, (const char *)input + i + env_len + 1);
		ft_strdel(&input);
		return (fresh);
	}
	return (input);
}

void	change_whitespaces(char **str)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\n' || (*str)[i] == '\t')
			(*str)[i] = ' ';
		i++;
	}
}

char	*get_input(t_data *data)
{
	char	*input;
	char	*tmp;

	input = NULL;
	get_next_line(0, &input);
	tmp = ft_strtrim((const char *)input);
	change_whitespaces(&tmp);
	ft_strdel(&input);
	input = tmp;
	if (strchr(input, '~') != NULL)
		input = tilde_exp(input, data);
	if (strchr(input, '$') != NULL)
		input = dollar_exp(input, data);
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
		if (ft_strncmp((const char *)(*data)->copy_env[i], "PATH=", 5) == 0)
			(*data)->path = ft_strsplit((*data)->copy_env[i] + 5, ':');
	}
	(*data)->copy_env[i] = NULL;
}

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

void	shell_err(const char *err, char *file)
{
	write(2, err, ft_strlen(err));
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
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
	return(1);
}

char	*get_env(t_data *data, const char *searching)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(searching, "=");
	len = ft_strlen(tmp);
	while (data->copy_env[++i])
	{
		if (ft_strnequ(data->copy_env[i], tmp, len))
		{
			ft_strdel(&tmp);
			return (ft_strchr(data->copy_env[i], '=') + 1);
		}
	}
	ft_strdel(&tmp);
	return (NULL);
}

size_t		find_env(t_data *data, const char *searching)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(searching, "=");
	len = ft_strlen((const char *)tmp);
	while (data->copy_env[++i])
	{
		if (ft_strnequ(data->copy_env[i], tmp, len))
		{
			ft_strdel(&tmp);
			return (i);
		}
	}
	ft_strdel(&tmp);
	return (i);
}

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

void	update_env(const char *env_var, t_data *data, char *new_val)
{
	size_t	pos;
	char	*tmp;
	
	pos = find_env(data, env_var);
	tmp = ft_strjoin("=", new_val);
	if (data->copy_env[pos])
	{
		free(data->copy_env[pos]);
		if (new_val)
			data->copy_env[pos] = ft_strjoin(env_var, tmp);
		else
			data->copy_env[pos] = ft_strjoin(env_var, "=");
	}
	else
	{
		realloc_env(&data, pos + 1);
		if (new_val)
			data->copy_env[pos] = ft_strjoin(env_var, tmp);
		else
			data->copy_env[pos] = ft_strjoin(env_var, "=");
	}
	ft_strdel(&tmp);
}

void	print_path(t_data *data)
{
	char	*home;
	char	*oldpwd;
	size_t	len_home;
	size_t	len_oldpwd;
	char	*print_path;

	home = get_env(data, "HOME");
	oldpwd = get_env(data, "OLDPWD");
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
		update_env("OLDPWD", data, cwd);
		getcwd(cwd, PATH_MAX);
		update_env("PWD", data, cwd);
	}
	else
	{
		if (access(path, F_OK) == -1)
			shell_err("cd: no such file or directory: ", path);
		else if (access(path, R_OK) == -1)
			shell_err("cd: permission denied: ", path);
		else
			shell_err("cd: not a directory: ", path);
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
			shell_err("cd: string not in pwd: ", data->split_input[1]);
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

	home = 	get_env(data, "HOME");
	if (data->split_input[1] == NULL)
		return ((home && *home) ? chg_dir(data, home, 0) : 1);
	if (chk_two_args(data))
		return (1);
	else
	{
		if (ft_strcmp(data->split_input[1], "--") == 0)
			return ((home && *home) ? chg_dir(data, home, 0) : 1);
		else if (ft_strcmp(data->split_input[1], "-") == 0)
			return (chg_dir(data, get_env(data, "OLDPWD"), 1));
		return (chg_dir(data, data->split_input[1], 0));
	}
	return (1);
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
				ft_strdel(&(data->copy_env[i++]));;
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

void	clean_commands(char ***commands)
{
	int		i;

	i = -1;
	while ((*commands)[++i])
		free((*commands)[i]);
	free(*commands);
}

int		isemptystr(char *str)
{
	int		i;
	int		min;
	int		max;

	i = -1;
	min = 33;
	max = 126;
	while (str[++i])
	{
		if (str[i] >= min && str[i] <= max)
			return (0);
	}
	return (1);
}

void	running_signal_handler(int sig)
{
	write(1, "\n", 1);
}

void	signal_handler(int sig)
{
	write(1, "\n", 1);
	display_prompt();
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
		ret = exec_commands(commands ,data);
		free(input);
		clean_commands(&commands);
	}
	clean_data(&data, 1);
	return (0);
}