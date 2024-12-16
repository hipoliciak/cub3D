/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:06:57 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/16 21:21:47 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_inside(char **map, int i, int j, int k)
{
	while (ft_isspace_not_nl(map[i][k]))
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
		while (ft_isspace_not_nl(map[i][k]) && map[i][k])
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

int	check_map_content(t_map *map)
{
	int	i;
	int	j;
	int	k;

	if (check_map_top_bottom(map->map, map->start_of_map, 0))
		return (1);
	i = map->start_of_map + 1;
	j = ft_strlen(map->map[i]);
	while (i < map->end_of_map)
	{
		k = 0;
		if (check_map_inside(map->map, i, j, k) == 1)
			return (1);
		else if (check_map_inside(map->map, i, j, k) == 2)
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
	if (game->map.height < 3)
		return (err("Map too small", 1));
	if (check_player_position(game, game->map.map))
		return (err("Invalid player position", 1));
	return (0);
}
