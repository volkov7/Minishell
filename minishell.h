/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:07:37 by jsance            #+#    #+#             */
/*   Updated: 2020/01/16 17:43:40 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "./libft/ft_printf.h"
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>

# define IS_QUOTE(c) (c == '"' || c == '\'')
# define PATH_MAX 1024

typedef struct	s_data
{
	char	**path;
	char	**copy_env;
	char	**split_input;
}				t_data;

char	*get_env(t_data *data, const char *searching);
void	running_signal_handler(int sig);

#endif