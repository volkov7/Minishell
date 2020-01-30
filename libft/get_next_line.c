/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:10:42 by jsance            #+#    #+#             */
/*   Updated: 2019/09/21 15:40:23 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		new_line(char **line, char **fds, int fd)
{
	int				len;
	char			*tmp;

	len = 0;
	while (fds[fd][len] != '\n' && fds[fd][len] != '\0')
		len++;
	if (fds[fd][len] == '\n')
	{
		*line = ft_strsub(fds[fd], 0, len);
		tmp = ft_strdup(fds[fd] + len + 1);
		ft_strdel(&fds[fd]);
		fds[fd] = tmp;
		if (!(fds[fd][0]))
			ft_strdel(&fds[fd]);
	}
	else if (fds[fd][len] == '\0')
	{
		*line = ft_strdup(fds[fd]);
		ft_strdel(&fds[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char			*tmp;
	char			*buff;
	static char		*fds[FD_MAX];
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	buff = ft_strnew(BUFF_SIZE + 1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!fds[fd])
			fds[fd] = ft_strnew(0);
		tmp = ft_strjoin(fds[fd], buff);
		ft_strdel(&fds[fd]);
		fds[fd] = tmp;
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	free(buff);
	if (ret < 0)
		return (-1);
	if (ret == 0 && !fds[fd])
		return (0);
	return (new_line(line, fds, fd));
}
