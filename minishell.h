/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:07:37 by jsance            #+#    #+#             */
/*   Updated: 2020/01/25 20:24:02 by jsance           ###   ########.fr       */
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
	char		**path;
	char		**copy_env;
	char		**split_input;
}				t_data;

/*
	cd_builtin.c
*/
int				chg_dir(t_data *data, char *path, int print);
int				cd_builtin(t_data *data);

/*
 *	environment.c
*/
void			printenv(t_data *data);
char			*get_env(t_data *data, const char *searching);
char			*found_env(char *input, t_data *data, size_t i,
												size_t *env_len);
size_t			find_env(t_data *data, const char *searching);
void			update_env(const char *env_var, t_data *data, char *new_val);

/*
 *			get_input.c
*/
void			change_whitespaces(char **str);
char			*dollar_exp(char *input, t_data *data);
char			*tilde_exp(char *input, t_data *data);
char			*get_input(t_data *data);

/*
 *			clean.c
*/
void			clean_commands(char ***commands);
void			clean_data(t_data **data, int flag);
void			create_clean_path(t_data *data, char ***path, int clean);

/*
 *	set_unset_env.c
*/
int				unsetenv_builtin(t_data *data);
int				setenv_builtin(t_data *data);
void			realloc_env(t_data **data, size_t len);

/*
 *	echo_builtin.c
*/
int				echo_builtin(t_data *data);
void			ft_put_no_quote(char *str, char *quote);

/*
 *	execution.c
*/
int				try_exec(t_data *data, int *flag);
void			go_exec(char *path, t_data *data, int *flag, int cur_dir);

/*
 *	exec_commands.c
*/
int				check_builtin(t_data *data);
int				exec_commands(char **commands, t_data *data);

/*
 *	misk.c
*/
void			shell_err(const char *err, char *file);
void			found_len(t_data *data, size_t *len);
void			create_full_path(t_data *data, char **path);
void			signal_handler(int sig);
void			running_signal_handler(int sig);

void			display_prompt(void);

#endif
