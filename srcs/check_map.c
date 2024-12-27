/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:06:57 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 23:22:38 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_end(char **map, int map_length)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_length)
	{
		j = 0;
		while (map[i][j] && is_space(map[i][j]))
			j++;
		if (map[i][j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	check_map_inside(char **map, int i, int j, int k)
{
	while (map[i][k] && is_space(map[i][k]))
		k++;
	while (map[i][k] && k < j)
	{
		if (map[i][k] != '1')
			return (1);
		while (map[i][k] && !is_space(map[i][k]))
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
				return (3);
			k++;
		}
	}
	return (0);
}

int	check_map_top_bottom(char **map, int i, int j)
{
	while (map[i][j] && is_space(map[i][j]))
		j++;
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	check_map_content(char **map)
{
	int	i;
	int	j;
	int	k;
	int	ret;

	if (check_map_top_bottom(map, 0, 0))
		return (3);
	i = 1;
	while (map[i])
	{
		j = ft_strlen(map[i]);
		k = 0;
		ret = check_map_inside(map, i, j, k);
		if (ret == 1)
			return (1);
		else if (ret == 2)
			return (2);
		else if (ret == 3)
			return (3);
		else
			i++;
	}
	if (check_map_top_bottom(map, i - 1, 0))
		return (3);
	return (0);
}

int	check_map(t_game *game)
{
	if (game->file.map_height < 3)
		return (err("Map too small", 1));
	if (check_map_end(game->file.map, game->file.map_height))
		return (err("There is a line after map end", 1));
	if (check_map_content(game->file.map) == 1)
		return (err("Invalid map side border", 1));
	if (check_map_content(game->file.map) == 2)
		return (err("Invalid map elements", 1));
	if (check_map_content(game->file.map) == 3)
		return (err("Invalid map top or bottom border", 1));
	if (check_player_position(game, game->file.map))
		return (err("Invalid player position", 1));
	if (game->player.dir == '\0')
		return (err("Player not initialized", 1));
	if (game->file.player_count != 1)
		return (err("Wrong number of players", 1));
	return (0);
}
