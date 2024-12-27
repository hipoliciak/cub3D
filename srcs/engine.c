/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:56:17 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 17:05:55 by dmodrzej         ###   ########.fr       */
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

void	try_move(t_game *game, double target_x, double target_y)
{
	int	old_x;
	int	old_y;
	int	new_x;
	int	new_y;

	old_x = (int)game->player.pos_x;
	old_y = (int)game->player.pos_y;
	new_x = (int)target_x;
	new_y = (int)target_y;
	if (new_x != old_x || new_y != old_y)
	{
		if (game->file.map[new_y][new_x] == '0')
		{
			game->file.map[old_y][old_x] = '0';
			game->file.map[new_y][new_x] = 'P';
			game->player.pos_x = target_x;
			game->player.pos_y = target_y;
			draw_map(game);
		}
	}
	else
	{
		game->player.pos_x = target_x;
		game->player.pos_y = target_y;
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
