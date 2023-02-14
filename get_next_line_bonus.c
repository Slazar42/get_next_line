/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:03:10 by slazar            #+#    #+#             */
/*   Updated: 2022/12/22 22:15:56 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*my_filter(char *save)
{
	char	*fil;
	int		i;

	i = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (!save[i])
		fil = malloc (i + 1);
	else
		fil = malloc (i + 2);
	if (!fil)
		return (0);
	i = 0;
	while (save[i] != '\n' && save[i])
	{
		fil[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		fil[i++] = '\n';
	fil[i] = '\0';
	return (fil);
}

char	*my_filter_cut(char *save)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (save[i] == '\n')
		i++;
	p = malloc(my_strlen(save) - i + 1);
	while (save[i])
		p[j++] = save[i++];
	p[j] = '\0';
	free(save);
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*buffer;
	int			readed;
	char		*fil;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!my_strchr(save[fd], '\n'))
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
			break ;
		buffer[readed] = '\0';
		save[fd] = my_strjoin(save[fd], buffer);
	}
	free(buffer);
	if (my_strlen(save[fd]) > 0 && readed >= 0)
	{
		fil = my_filter(save[fd]);
		save[fd] = my_filter_cut(save[fd]);
		return (fil);
	}
	free(save[fd]);
	return (save[fd] = 0);
}
