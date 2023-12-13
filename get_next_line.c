/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:21:58 by mnachit           #+#    #+#             */
/*   Updated: 2023/12/13 13:29:22 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_read(int fd, char *buf, char **str)
{
	char	*tmp;
	ssize_t	i;

	if (!*str || !ft_strchr(*str, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		while (i > 0)
		{
			buf[i] = '\0';
			if (!*str)
				*str = ft_substr(buf, 0, i);
			else
			{
				tmp = *str;
				*str = ft_strjoin(*str, buf);
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

static char	*ft_finish(char **str)
{
	char	*rja3;
	char	*tmp;
	int		i;
	int		j;

	if (!*str)
		return (NULL);
	if (!ft_strchr(*str, '\n'))
	{
		rja3 = ft_substr(*str, 0, ft_strlen(*str));
		ft_free(*&str);
		return (rja3);
	}
	i = ft_strlen(*str);
	j = ft_strlen(ft_strchr(*str, '\n'));
	rja3 = ft_substr(*str, 0, i - j + 1);
	tmp = *str;
	*str = ft_substr(ft_strchr(*str, '\n'), 1, j - 1);
	free(tmp);
	if (**str == '\0')
		ft_free(*&str);
	return (rja3);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buf;

	if (BUFFER_SIZE < 1 || BUFFER_SIZE > 4294967295)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (fd == -1)
	{
		free(buf);
		return (NULL);
	}
	ft_read(fd, buf, &str);
	return (ft_finish(&str));
}
