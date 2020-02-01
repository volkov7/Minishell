/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:50:29 by jsance            #+#    #+#             */
/*   Updated: 2020/02/01 13:58:35 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			sh_err("cd: no such file or directory: ", path);
		else if (access(path, R_OK) == -1)
			sh_err("cd: permission denied: ", path);
		else
			sh_err("cd: not a directory: ", path);
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
		exit(0);
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
			sh_err("cd: string not in pwd: ", data->split_input[1]);
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

	home = get_env(data, "HOME");
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
