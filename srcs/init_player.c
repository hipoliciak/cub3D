/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:37 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/21 19:02:13 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_position_is_valid(t_game *game, char **map)
{
	int	i;
	int	j;

	i = (int)game->player.pos_y;
	j = (int)game->player.pos_x;
	if (ft_strlen(map[i - 1]) < (size_t)j
		|| ft_strlen(map[i + 1]) < (size_t)j
		|| ft_isspace(map[i][j - 1])
		|| ft_isspace(map[i][j + 1])
		|| ft_isspace(map[i - 1][j])
		|| ft_isspace(map[i + 1][j]))
		return (1);
	return (0);
}

int	check_player_position(t_game *game, char **map)
{
	int	i;
	int	j;

	i = game->map.start_of_map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NEWS", map[i][j]))
			{
				game->player.pos_x = (double)j + 0.5;
				game->player.pos_y = (double)i + 0.5;
				game->player.dir = map[i][j];
				map[i][j] = 'P';
				game->player_count++;
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(game, map))
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
}
