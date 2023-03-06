/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:08:01 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/03/06 15:44:33 by hyungnoh         ###   ########.fr       */
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
		info->north_path = ft_linedup(line + 3);
		elements_cnt[0]	+= FILLED;
	}
	else if (!ft_strncmp("SO ", line, 3))
	{
		info->south_path = ft_linedup(line + 3);
		elements_cnt[1] += FILLED;
	}
	else if (!ft_strncmp("WE ", line, 3))
	{
		info->west_path = ft_linedup(line + 3);
		elements_cnt[2] += FILLED;
	}
	else if (!ft_strncmp("EA ", line, 3))
	{
		info->east_path = ft_linedup(line + 3);
		elements_cnt[3] += FILLED;
	}
}

void	check_f_rgb(t_info *info, char *line, int elements_cnt[])
{
	char	**tmp_rgb;
	int		i;

	i = -1;
	if (!ft_strncmp("F ", line, 2))
	{
		check_comma(line + 2);
		tmp_rgb = ft_split(line + 2, ',');
		if (tmp_rgb[3] != NULL)
			err_msg("error : improper elements");
		while (++i < 3)
		{
			info->f_rgb[i] = ft_atoi(tmp_rgb[i]);
			if (info->f_rgb[i] < 0 || info->f_rgb[i] > 255)
				err_msg("error : improper elements");
		}
		i = -1;
		while (++i < 3)
			free(tmp_rgb[i]);
		free(tmp_rgb);
		elements_cnt[4]	+= FILLED;
	}
}

void	check_c_rgb(t_info *info, char *line, int elements_cnt[])
{
	char	**tmp_rgb;
	int		i;

	i = -1;
	if (!ft_strncmp("C ", line, 2))
	{
		check_comma(line + 2);
		tmp_rgb = ft_split(line + 2, ',');
		if (tmp_rgb[3] != NULL)
			err_msg("error : improper elements");
		while (++i < 3)
		{
			info->c_rgb[i] = ft_atoi(tmp_rgb[i]);
			if (info->c_rgb[i] < 0 || info->c_rgb[i] > 255)
				err_msg("error : improper elements");
		}
		i = -1;
		while (++i < 3)
			free(tmp_rgb[i]);
		free(tmp_rgb);
		elements_cnt[5]	+= FILLED;
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
		err_msg("error : not enough elements");
}
