/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:07:37 by jsance            #+#    #+#             */
/*   Updated: 2020/01/13 14:22:54 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct	s_data
{
	char	**path;
	char	**copy_env;
	char	**split_input;
}				t_data;

#include "get_next_line.h"
#include "./libft/ft_printf.h"
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#endif