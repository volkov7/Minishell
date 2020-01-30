/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:24:27 by jsance            #+#    #+#             */
/*   Updated: 2020/01/25 20:12:59 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printenv(t_data *data)
{
	int		i;

	i = -1;
	while (data->copy_env[++i])
		ft_putendl((const char *)data->copy_env[i]);
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

size_t	find_env(t_data *data, const char *searching)
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

char	*found_env(char *input, t_data *data, size_t i, size_t *env_len)
{
	char	*env;
	char	*found;
	size_t	k;

	*env_len = 0;
	k = i;
	while (ft_isalpha(input[++k]) || input[k] == '_')
		(*env_len)++;
	if (!(env = ft_strnew(*env_len)))
		exit(0);
	ft_strncpy(env, (const char *)input + i + 1, *env_len);
	found = get_env(data, env);
	ft_strdel(&env);
	return (found);
}
