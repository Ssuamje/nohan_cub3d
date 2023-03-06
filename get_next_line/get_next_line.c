/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:40:42 by hyungseok         #+#    #+#             */
/*   Updated: 2023/02/20 13:08:47 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define BUFFER_SIZE 1024
#define OPEN_MAX 10240

static char	*pile_up(int fd, char *pile)
{
	char		*buffer;
	ssize_t		rbyte;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	rbyte = BUFFER_SIZE;
	while (rbyte && !ft_strchr(pile, '\n'))
	{
		rbyte = read(fd, buffer, BUFFER_SIZE);
		if (rbyte == -1)
		{
			free(buffer);
			free(pile);
			return (NULL);
		}
		buffer[rbyte] = '\0';
		if (pile == NULL)
			pile = ft_strdup(buffer);
		else
			pile = ft_strjoin(pile, buffer);
	}
	free(buffer);
	return (pile);
}

static char	*allocate(char *pile, ssize_t i)
{
	char	*tmp;

	if (ft_strchr(pile, '\n'))
		tmp = (char *)malloc(sizeof(char) * (i + 2));
	else
		tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*get_line(char *pile)
{
	char	*tmp;
	ssize_t	i;

	i = 0;
	if (pile[i] == '\0')
		return (NULL);
	while (pile[i] != '\0' && pile[i] != '\n')
		i++;
	tmp = allocate(pile, i);
	if (!tmp)
		return (NULL);
	i = 0;
	while (pile[i] != '\0' && pile[i] != '\n')
	{
		tmp[i] = pile[i];
		i++;
	}
	if (pile[i] == '\n')
	{
		tmp[i] = pile[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static char	*reset(char *pile)
{
	char	*tmp;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	while (pile[i] != '\0' && pile[i] != '\n')
		i++;
	if (pile[i] == '\0' || (pile[i] == '\n' && pile[i + 1] == '\0'))
	{
		free(pile);
		return (NULL);
	}
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(pile) - i));
	if (!tmp)
	{
		free(pile);
		return (NULL);
	}
	i++;
	j = 0;
	while (pile[i] != '\0')
		tmp[j++] = pile[i++];
	tmp[j] = '\0';
	free(pile);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*pile[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	pile[fd] = pile_up(fd, pile[fd]);
	if (!pile[fd])
		return (NULL);
	line = get_line(pile[fd]);
	pile[fd] = reset(pile[fd]);
	return (line);
}
