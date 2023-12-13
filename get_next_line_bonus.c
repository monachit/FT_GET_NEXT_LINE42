/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 05:25:37 by mnachit           #+#    #+#             */
/*   Updated: 2023/12/13 14:37:38 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_read(int fd, char *buf, char **str)
{
	char	*tmp;
	ssize_t	i;

	if (!str[fd] || !ft_strchr(str[fd], '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		while (i > 0)
		{
			buf[i] = '\0';
			if (!str[fd])
				str[fd] = ft_substr(buf, 0, i);
			else
			{
				tmp = str[fd];
				str[fd] = ft_strjoin(str[fd], buf);
				free(tmp);
			}
			if (ft_strchr(buf, '\n'))
				break ;
			i = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
}

static void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

static char	*ft_finish(char **str, int fd)
{
	char	*rja3;
	char	*tmp;
	int		i;
	int		j;

	if (!str[fd])
		return (NULL);
	if (!ft_strchr(str[fd], '\n'))
	{
		rja3 = ft_substr(str[fd], 0, ft_strlen(str[fd]));
		ft_free(&str[fd]);
		return (rja3);
	}
	i = ft_strlen(str[fd]);
	j = ft_strlen(ft_strchr(str[fd], '\n'));
	rja3 = ft_substr(str[fd], 0, i - j + 1);
	tmp = str[fd];
	str[fd] = ft_substr(ft_strchr(str[fd], '\n'), 1, j - 1);
	free(tmp);
	if (*str[fd] == '\0')
		ft_free(&str[fd]);
	return (rja3);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*buf;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > 4294967295)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (fd == -1 || read(fd, buf, 0) == -1)
	{
		free(buf);
		return (NULL);
	}
	ft_read(fd, buf, str);
	return (ft_finish(str, fd));
}