/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volkker <volkker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 11:33:56 by jsance            #+#    #+#             */
/*   Updated: 2020/01/30 08:52:49 by volkker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "./libft.h"
# define BUFF_SIZE	7
# define FD_MAX		1024

int get_next_line(const int fd, char **line);

#endif
