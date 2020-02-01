/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:14:16 by jsance            #+#    #+#             */
/*   Updated: 2020/02/01 13:53:36 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
