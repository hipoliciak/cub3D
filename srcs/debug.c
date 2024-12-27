/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:05:32 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 17:07:55 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->file.map[y])
	{
		x = 0;
		while (game->file.map[y][x])
		{
			printf("%c", game->file.map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
	printf("Player position: %f, %f\n",
		game->player.pos_x, game->player.pos_y);
	printf("Player int position: %d, %d\n",
		(int)game->player.pos_x, (int)game->player.pos_y);
	printf("Player direction: %f, %f\n",
		game->player.dir_x, game->player.dir_y);
	printf("\n");
	return (0);
}
