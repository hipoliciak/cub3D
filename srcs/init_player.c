/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:37 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/16 01:20:00 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_position_is_valid(t_game *game, char **mapf_tab)
{
	int	i;
	int	j;

	i = (int)game->player.pos_y;
	j = (int)game->player.pos_x;
	if (ft_strlen(mapf_tab[i - 1]) < (size_t)j
		|| ft_strlen(mapf_tab[i + 1]) < (size_t)j
		|| ft_isspace(mapf_tab[i][j - 1])
		|| ft_isspace(mapf_tab[i][j + 1])
		|| ft_isspace(mapf_tab[i - 1][j])
		|| ft_isspace(mapf_tab[i + 1][j]))
		return (1);
	return (0);
}

int	check_player_position(t_game *game, char **mapf_tab)
{
	int	i;
	int	j;

	if (game->player.dir == '0')
		return (1);
	i = 0;
	while (mapf_tab[i])
	{
		j = 0;
		while (mapf_tab[i][j])
		{
			if (ft_strchr("NEWS", mapf_tab[i][j]))
			{
				game->player.pos_x = (double)j + 0.5;
				game->player.pos_y = (double)i + 0.5;
				mapf_tab[i][j] = 'P';
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(game, mapf_tab))
		return (1);
	return (0);
}

void	init_player_north_south(t_player *player)
{
	if (player->dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else
		return ;
}

void	init_player_east_west(t_player *player)
{
	if (player->dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (player->dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else
		return ;
}

void	init_player(t_player *player)
{
	player->dir = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->key_state[0] = 0;
	player->key_state[1] = 0;
	player->key_state[2] = 0;
	player->key_state[3] = 0;
	player->key_state[4] = 0;
	player->key_state[5] = 0;
}
