/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:08:01 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/10/24 13:34:22 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	elements_cnt_init(int elements_cnt[])
{
	int	i;

	i = -1;
	while (++i < 6)
		elements_cnt[i] = UNFILLED;
}

void	check_path(t_info *info, char *line, int elements_cnt[])
{
	if (!ft_strncmp("NO ", line, 3))
	{
		elements_cnt[0] += FILLED;
		put_path_if_valid(&info->north_path, line, elements_cnt[0]);
		check_path_valid(info->north_path);
	}
	else if (!ft_strncmp("SO ", line, 3))
	{
		elements_cnt[1] += FILLED;
		put_path_if_valid(&info->south_path, line, elements_cnt[1]);
		check_path_valid(info->south_path);
	}
	else if (!ft_strncmp("WE ", line, 3))
	{
		elements_cnt[2] += FILLED;
		put_path_if_valid(&info->west_path, line, elements_cnt[2]);
		check_path_valid(info->west_path);
	}
	else if (!ft_strncmp("EA ", line, 3))
	{
		elements_cnt[3] += FILLED;
		put_path_if_valid(&info->east_path, line, elements_cnt[3]);
		check_path_valid(info->east_path);
	}
}

void	check_f_rgb(t_info *info, char *line, int elements_cnt[])
{
	char	**tmp_rgb;
	int		i;

	i = -1;
	if (!ft_strncmp("F ", line, 2))
	{
		if (++elements_cnt[4] > FILLED)
			exit_error(ERR_ELEM_INVALID);
		check_comma(line + 2);
		tmp_rgb = ft_split(line + 2, ',');
		if (tmp_rgb[3] != NULL)
			exit_error(ERR_ELEM_INVALID);
		while (++i < 3)
		{
			info->f_rgb[i] = ft_atoi(tmp_rgb[i]);
			if (info->f_rgb[i] < 0 || info->f_rgb[i] > 255)
				exit_error(ERR_ELEM_INVALID);
		}
		i = -1;
		while (++i < 3)
			free(tmp_rgb[i]);
		free(tmp_rgb);
	}
}

void	check_c_rgb(t_info *info, char *line, int elements_cnt[])
{
	char	**tmp_rgb;
	int		i;

	i = -1;
	if (!ft_strncmp("C ", line, 2))
	{
		if (++elements_cnt[5] > FILLED)
			exit_error(ERR_ELEM_INVALID);
		check_comma(line + 2);
		tmp_rgb = ft_split(line + 2, ',');
		if (tmp_rgb[3] != NULL)
			exit_error(ERR_ELEM_INVALID);
		while (++i < 3)
		{
			info->c_rgb[i] = ft_atoi(tmp_rgb[i]);
			if (info->c_rgb[i] < 0 || info->c_rgb[i] > 255)
				exit_error(ERR_ELEM_INVALID);
		}
		i = -1;
		while (++i < 3)
			free(tmp_rgb[i]);
		free(tmp_rgb);
	}
}

void	elements_init(t_info *info)
{
	int		elements_cnt[6];
	char	*line;

	elements_cnt_init(elements_cnt);
	while (READ_ELEMENTS)
	{
		line = get_next_line(info->fd);
		if (line == NO_MORE_TO_READ)
		{
			free(line);
			break ;
		}
		check_file_order(line);
		check_path(info, line, elements_cnt);
		check_f_rgb(info, line, elements_cnt);
		check_c_rgb(info, line, elements_cnt);
		if (elements_filled(elements_cnt))
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (!elements_filled(elements_cnt))
		exit_error(ERR_ELEM_LACK);
}
