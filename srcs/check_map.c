/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:06:57 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/16 01:05:27 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_elements(t_game *game, char **map)
{
	int	i;
	int	j;

	i = game->map.start_of_map;
	game->player.dir = '0';
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (ft_isspace_not_nl(map[i][j]))
				j++;
			if (!(ft_strchr("10NEWS", map[i][j])))
				return (1);
			if (ft_strchr("NEWS", map[i][j]) && game->player.dir != '0')
				return (1);
			if (ft_strchr("NEWS", map[i][j]) && game->player.dir == '0')
				game->player.dir = map[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_top_bottom(char **map, int i, int j)
{
	if (!map || !map[i] || !map[i][j])
		return (1);
	while (ft_isspace_not_nl(map[i][j]))
		j++;
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	check_map_borders(t_map *map)
{
	int	i;
	int	j;
	int	k;

	if (check_map_top_bottom(map->map, map->start_of_map, 0))
		return (1);
	i = map->start_of_map + 1;
	while (i < map->end_of_map - 1)
	{
		k = 0;
		while (ft_isspace_not_nl(map->map[i][k]))
			k++;
		j = ft_strlen(map->map[i]) - 1;
		if (map->map[i][k] != '1' && map->map[i][k] != ' ')
			return (1);
		if (map->map[i][j] != '1' && map->map[i][j] != ' ')
			return (1);
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
	if (check_map_borders(&game->map))
		return (err("Invalid map borders", 1));
	if (game->map.height < 3)
		return (err("Map too small", 1));
	if (check_map_elements(game, game->map.map))
		return (err("Invalid map elements", 1));
	if (check_player_position(game, game->map.map))
		return (err("Invalid player position", 1));
	if (game->map.map[game->map.end_of_map + 1] != NULL)
		return (err("There is something after the map", 1));
	return (0);
}
