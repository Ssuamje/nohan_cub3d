/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:35:33 by hyungseok         #+#    #+#             */
/*   Updated: 2023/10/11 13:51:30 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_msg_by_errno(int errno)
{
	if (errno == ERR_ELEM_INVALID)
		return ("Error: Invalid elements\n");
	if (errno == ERR_ELEM_LACK)
		return ("Error: Elements are not fulfilled\n");
	if (errno == ERR_MAP_FILE)
		return ("Error: Map file is not valid\n");
	if (errno == ERR_MAP_INVALID)
		return ("Error: Invalid map\n");
	if (errno == ERR_MAP_INVALID_PLAYER)
		return ("Error: Invalid player in map\n");
	if (errno == ERR_ARG)
		return ("Error: Invalid arguments\n");
	if (errno == ERR_WALL_INVALID)
		return ("Error: Wall is invalid\n");
	return (NULL);
}

void	exit_error(int errno)
{
	printf("%s", get_msg_by_errno(errno));
	exit(1);
}
