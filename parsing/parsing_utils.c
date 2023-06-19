/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:25:42 by hyungseok         #+#    #+#             */
/*   Updated: 2023/06/19 19:45:45 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_extension_valid(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5 || !ft_strcmp(filename + len - 4, ".cub"))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	elements_filled(int elements_cnt[])
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (elements_cnt[i] != FILLED)
			return (0);
	}
	return (1);
}

void	check_comma(char *str)
{
	int	i;
	int	comma;

	i = -1;
	comma = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			comma++;
		else if (str[i] == '\n');
		else if (!(str[i] >= '0' && str[i] <= '9'))
			exit_error(ERR_ELEM_INVALID);
	}
	if (comma != 2)
		exit_error(ERR_ELEM_INVALID);
}

void	check_file_order(char *line)
{
	int	i;

	i = -1;
	if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
		||!ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3))
		return ;
	else if (!ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2))
		return ;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			exit_error(ERR_ELEM_INVALID);
	}
}

int	get_last(t_map *map)
{
	t_map	*tmp;
	int		i;

	tmp = map;
	i = -1;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	if (i < 2)
		exit_error(ERR_MAP_INVALID);
	return (i);
}
