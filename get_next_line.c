/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:47:31 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:47:32 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

static int	get_line(t_line *tline, char **line)
{
	char	*next;

	if (!ft_strlen(tline->str))
		return (0);
	if (!tline->newline)
	{
		*line = tline->str;
		tline->str = ft_strnew(0);
		return (1);
	}
	next = ft_strchr(tline->str, '\n');
	*next++ = '\0';
	*line = ft_strdup(tline->str);
	ft_strcpy(tline->str, next);
	tline->newline--;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	char				*buff;
	char				*tmp;
	int					ret;
	static t_line		tline;

	if (tline.str == NULL)
		tline.str = ft_strnew(0);
	while (!tline.newline)
	{
		buff = ft_strnew(BUFF_SIZE);
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			return (get_line(&tline, line));
		tline.newline = ft_strcchar(buff, '\n');
		tmp = ft_strjoin(tline.str, buff);
		free(tline.str);
		tline.str = tmp;
		free(buff);
	}
	return (get_line(&tline, line));
}
