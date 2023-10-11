/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:59 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/10/11 16:09:08 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

int	is_nsew(char c)
{
	return (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

void	check_path_valid(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		exit_error(ERR_ELEM_INVALID);
	}
	else
		close(fd);
}

void	check_cases(t_map *tmp, char c)
{
	if (tmp->prev && ft_strlen(tmp->prev->line) < ft_strlen(tmp->line)
		&& c == '0')
		exit_error(ERR_WALL_INVALID);
	if (tmp->next && ft_strlen(tmp->next->line) < ft_strlen(tmp->line)
		&& c == '0')
		exit_error(ERR_WALL_INVALID);
}
