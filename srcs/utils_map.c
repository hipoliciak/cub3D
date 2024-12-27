/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 20:05:18 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 22:40:05 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_map_lines(char **file, int map_start)
{
	int	i;

	i = 0;
	while (file[i + map_start])
		i++;
	return (i);
}

int	copy_map(t_game *game)
{
	int		i;
	int		map_lines;
	char	*line_copy;

	map_lines = count_map_lines(game->file.file, game->file.map_start);
	if (map_lines == 0)
		return (err("No map", 1));
	game->file.map_height = map_lines;
	game->file.map = malloc(sizeof(char *) * (map_lines + 1));
	if (!game->file.map)
		return (err("Could not allocate memory", 1));
	i = 0;
	while (i < map_lines)
	{
		line_copy = ft_strdup(game->file.file[i + game->file.map_start]);
		if (!line_copy)
		{
			free_tab((void **)game->file.map);
			return (err("Could not allocate memory", 1));
		}
		game->file.map[i] = line_copy;
		i++;
	}
	game->file.map[i] = NULL;
	return (0);
}
