/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:05:47 by sanan             #+#    #+#             */
/*   Updated: 2023/10/12 16:36:19 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * draw_start, draw_end는 draw_vertical에서 사용되는데,
 * draw_start는 화면의 중앙에서 line_height의 절반만큼 위로 올라간 지점이고,
 * draw_end는 화면의 중앙에서 line_height의 절반만큼 아래로 내려간 지점이다.
 * 이를 통해, draw_start와 draw_end 사이의 범위에 색을 채워넣는다.
 * draw_start가 0보다 작으면 0으로, draw_end가 SCREEN_HEIGHT보다 크면 SCREEN_HEIGHT-1로
 * 지정한다. (draw_end가 SCREEN_HEIGHT가 되면, 이미지의 끝을 넘어가기 때문에)
 * 이후에 draw_vertical에서 draw_start와 draw_end 사이의 범위에 색을 채워넣는다.
 * (draw_start와 draw_end는 이미지의 y좌표이다.)
 * 그리는 방향이 y = 0에서 아래로 y값이 더해지는 것이므로, start->end가 위에서 아래로다.
*/
void	set_draw_range(t_game *game)
{
	game->line_height = (int)(SCREEN_HEIGHT / game->perp_wall_dist);
	game->draw_start = -game->line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->draw_end >= SCREEN_HEIGHT)
		game->draw_end = SCREEN_HEIGHT - 1;
}

/**
 * 텍스쳐를 그리기 위한 계산을 한다.
 * img_data는 mlx img로서 이미지의 시작 주소이다. 우리는 이 img에 color를 채워서 뿌린다.
 * img_line_size는 이미지의 가로 크기다.
 * bits_per_pixel은 이미지의 한 픽셀을 표현하는데 필요한 바이트 수다.
 * unsigned int의 크기인 4바이트를 기준으로 점프해서, 해당 xpm에 있는 color를 지정한다.
*/
void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img_data + (y * game->img_line_size + \
	x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_vertical(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < game->draw_start)
	{
		put_pixel(game, x, y, game->ceiling);
		y++;
	}
	while (y < game->draw_end)
	{
		put_pixel(game, x, y, game->color);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		put_pixel(game, x, y, game->floor);
		y++;
	}
}
