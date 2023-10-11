/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_island_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:11:07 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/10/11 14:29:19 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_island1(char **board, t_map *tmp, int *x, int *y)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (tmp)
	{
		j = -1;
		len = ft_strlen(tmp->line);
		board[i] = malloc(sizeof(char) * (len + 1));
		while (++j < len)
		{
			board[i][j] = tmp->line[j];
			if (tmp->line[j] == '1')
			{
				*x = i;
				*y = j;
			}
		}
		board[i][j] = '\0';
		i++;
		tmp = tmp->next;
	}
	board[i] = NULL;
}

void	check_island2(char **board, int last)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < last + 1)
	{
		j = -1;
		len = ft_strlen(board[i]);
		while (++j < len)
		{
			if (board[i][j] != '2' && board[i][j] != ' ')
				exit_error(ERR_MAP_INVALID);
		}
	}
}
