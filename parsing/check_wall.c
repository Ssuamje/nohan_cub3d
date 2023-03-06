/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:47:58 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/24 16:37:01 by hyungnoh         ###   ########.fr       */
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
			err_msg("error : wall not closed");
		len = ft_strlen(tmp->line) - 1;
		if (tmp->line[len] != '1')
			err_msg("error : wall not closed");
		i = -1;
		while (tmp->line[++i])
		{
			if (j == 0 || j == last)
			{
				if (tmp->line[i] != '1' && tmp->line[i] != ' ')
					err_msg("error : wall not closed");
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
	int		next_len;

	tmp = map;
	while (tmp)
	{
		len = ft_strlen(tmp->line) - 1;
		while (++i < len && j != 0 && j != last)
		{
			if (tmp->next)
			{
				next_len = ft_strlen(tmp->next->line) - 1;
				if (tmp->line[i] != '1' && tmp->line[i] != ' ' && i > next_len)
					err_msg("error : wall not closed");
			}
			if ((tmp->line[i] != '1' && tmp->line[i] != ' ') 
				&& (tmp->line[i - 1] == ' ' || tmp->line[i + 1] == ' '
				|| tmp->prev->line[i] == ' ' || tmp->next->line[i] == ' '))
				err_msg("error : wall not closed");
		}
		i = 0;
		j++;
		tmp = tmp->next;
	}
}

void	recursion(char **board, int x, int y, int last)
{
	int	len;
	int	prev_len;
	int	next_len;

	if (board[x][y] == '2')
		return ;
	board[x][y] = '2';
	len = ft_strlen(board[x]);
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

void	check_island(t_map *map, int i, int j, int last)
{
	t_map	*tmp;
	char	**board;
	int		len;
	int		x;
	int		y;

	x = 0;
	y = 0;
	tmp = map;
	board = malloc(sizeof(char *) * (last + 2));	
	while (tmp)
	{
		len = ft_strlen(tmp->line);
		board[i] = malloc(sizeof(char) * (len + 1));
		while (++j < len)
		{
			board[i][j] = tmp->line[j];
			if (tmp->line[j] == '1')
			{
				x = i;
				y = j;
			}
		}
		board[i][j] = '\0';
		j = -1;
		i++;
		tmp = tmp->next;
	}
	board[i] = NULL;
	recursion(board, x, y, last);
	i = -1;
	while (++i < last + 1)
	{
		j = -1;
		len = ft_strlen(board[i]);
		while (++j < len)
		{
			if (board[i][j] != '2' && board[i][j] != ' ')
				err_msg("error : island exists");
		}
	}
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
	check_island(map, 0, -1, last);
}
