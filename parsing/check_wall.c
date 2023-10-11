/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:47:58 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/10/11 16:59:51 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_side(t_map *map, int i, int j, int last)
{
	t_map	*tmp;
	int		len;

	tmp = map;
	while (tmp)
	{
		if (tmp->line[0] != '1' && tmp->line[0] != ' ')
			exit_error(ERR_WALL_INVALID);
		len = ft_strlen(tmp->line) - 1;
		if (tmp->line[len] != '1')
			exit_error(ERR_WALL_INVALID);
		i = -1;
		while (tmp->line[++i])
		{
			if (j == 0 || j == last)
			{
				if (tmp->line[i] != '1' && tmp->line[i] != ' ')
					exit_error(ERR_WALL_INVALID);
			}
		}
		j++;
		tmp = tmp->next;
	}
}

void	check_closed(t_map *map, int i, int j, int last)
{
	t_map	*tmp;
	int		len;

	tmp = map;
	while (tmp)
	{
		len = ft_strlen(tmp->line) - 1;
		while (++i < len && j != 0 && j != last)
		{
			check_cases(tmp, tmp->line[i], i);
			if (tmp->next)
			{
				if (tmp->line[i] != '1' && tmp->line[i] != ' '
					&& i > (int)ft_strlen(tmp->next->line) - 1)
					exit_error(ERR_WALL_INVALID);
			}
			if ((tmp->line[i] != '1' && tmp->line[i] != ' ')
				&& (tmp->line[i - 1] == ' ' || tmp->line[i + 1] == ' '
					|| tmp->prev->line[i] == ' ' || tmp->next->line[i] == ' '))
				exit_error(ERR_WALL_INVALID);
		}
		i = 0;
		j++;
		tmp = tmp->next;
	}
}

void	recursion(char **board, int x, int y, int last)
{
	int	prev_len;
	int	next_len;

	if (board[x][y] == '2')
		return ;
	board[x][y] = '2';
	if (x != 0)
		prev_len = ft_strlen(board[x - 1]);
	if (x != last)
		next_len = ft_strlen(board[x + 1]);
	if (x != 0 && y <= prev_len - 1 && board[x - 1][y] != ' ')
		recursion(board, x - 1, y, last);
	if (x != last && y <= next_len - 1 && board[x + 1][y] != ' ')
		recursion(board, x + 1, y, last);
	if (y != 0 && board[x][y - 1] != ' ')
		recursion(board, x, y - 1, last);
	if (board[x][y + 1] != '\0' && board[x][y + 1] != ' ')
		recursion(board, x, y + 1, last);
}

void	check_island(t_map *map, int i, int last)
{
	t_map	*tmp;
	char	**board;
	int		x;
	int		y;

	x = 0;
	y = 0;
	tmp = map;
	board = malloc(sizeof(char *) * (last + 2));
	check_island1(board, tmp, &x, &y);
	recursion(board, x, y, last);
	check_island2(board, last);
	i = -1;
	while (++i < last + 1)
		free(board[i]);
	free(board);
}

void	check_wall(t_map *map)
{
	int		last;

	last = get_last(map);
	check_side(map, -1, 0, last);
	check_closed(map, 0, 0, last);
	check_island(map, 0, last);
}
