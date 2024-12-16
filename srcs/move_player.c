/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:51 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/15 18:58:31 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *p, double angle)
{
	double	tmp_dir_x;
	double	tmp_plane_x;

	tmp_dir_x = p->dir_x;
	tmp_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = tmp_dir_x * sin(angle) + p->dir_y * cos(angle);
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = tmp_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void	try_move(t_game *game, double new_x, double new_y)
{
	if (game->map.map[(int)new_y][(int)new_x] == '0')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

int	move_player(t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (p->key_state[0])
		try_move(game, p->pos_x + p->dir_x * MOVESPEED,
			p->pos_y + p->dir_y * MOVESPEED);
	if (p->key_state[1])
		try_move(game, p->pos_x - p->dir_x * MOVESPEED,
			p->pos_y - p->dir_y * MOVESPEED);
	if (p->key_state[2])
		try_move(game, p->pos_x + p->dir_y * MOVESPEED,
			p->pos_y - p->dir_x * MOVESPEED);
	if (p->key_state[3])
		try_move(game, p->pos_x - p->dir_y * MOVESPEED,
			p->pos_y + p->dir_x * MOVESPEED);
	if (p->key_state[4])
		rotate_player(p, -ROTSPEED);
	if (p->key_state[5])
		rotate_player(p, ROTSPEED);
	return (0);
}
