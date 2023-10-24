/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:59 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/10/24 13:31:09 by sanan            ###   ########.fr       */
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

void	check_cases(t_map *tmp, char c, int i)
{
	if (tmp->prev && (int)ft_strlen(tmp->prev->line) < i + 1
		&& c != '1')
		exit_error(ERR_WALL_INVALID);
	if (tmp->next && (int)ft_strlen(tmp->next->line) < i + 1
		&& c != '1')
		exit_error(ERR_WALL_INVALID);
}

void	put_path_if_valid(char **path_ptr, char *line, int elements_cnt)
{
	if (elements_cnt > FILLED)
		exit_error(ERR_ELEM_INVALID);
	else
		*path_ptr = ft_linedup(line + 3);
}
