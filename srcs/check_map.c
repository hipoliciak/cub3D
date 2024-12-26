/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:06:57 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/26 23:22:25 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_inside(char **map, int i, int j, int k)
{
	while (map[i][k] && is_space(map[i][k]))
		k++;
	while (map[i][k] && k < j)
	{
		if (map[i][k] != '1')
			return (1);
		while (map[i][k] && map[i][k] != ' ')
		{
			if (!ft_strchr("10NEWS", map[i][k]))
				return (2);
			k++;
		}
		if (map[i][k - 1] != '1')
			return (1);
		while (map[i][k] && is_space(map[i][k]))
		{
			if (is_surrounded_by_space_or_wall(map, i, k))
				return (1);
			k++;
		}
	}
	return (0);
}

int	check_map_top_bottom(char **map, int i, int j)
{
	while (is_space(map[i][j]))
		j++;
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	check_map_content(t_map *map)
{
	int	i;
	int	j;
	int	k;
	int	ret;

	if (check_map_top_bottom(map->map, map->start_of_map, 0))
		return (1);
	i = map->start_of_map + 1;
	while (i < map->end_of_map)
	{
		j = ft_strlen(map->map[i]);
		k = 0;
		ret = check_map_inside(map->map, i, j, k);
		if (ret == 1)
			return (1);
		else if (ret == 2)
			return (2);
		else
			i++;
	}
	if (check_map_top_bottom(map->map, map->end_of_map, 0))
		return (1);
	return (0);
}

int	check_map(t_game *game)
{
	if (game->map.start_of_map == 0)
		return (err("Map not found", 1));
	if (check_map_content(&game->map) == 1)
		return (err("Invalid map borders", 1));
	if (check_map_content(&game->map) == 2)
		return (err("Invalid map elements", 1));
	if ((game->map.end_of_map - game->map.start_of_map) < 3)
		return (err("Map too small", 1));
	if (check_player_position(game, game->map.map))
		return (err("Invalid player position", 1));
	if (game->player.dir == '\0')
		return (err("Player not initialized", 1));
	if (game->map.player_count != 1)
		return (err("Wrong number of players", 1));
	return (0);
}
