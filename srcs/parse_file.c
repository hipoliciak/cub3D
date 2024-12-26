/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:09 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/26 23:21:24 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && is_space(line[j]))
		j++;
	len = j;
	while (line[len] && !is_space(line[len]))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && !is_space(line[j]) && line[j] != '\n')
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && is_space(line[j]))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	set_direction_textures(t_map *map, char *line, int j)
{
	char	*identifier;

	identifier = ft_substr(line, j, 2);
	if (!identifier)
		return (1);
	if (!ft_strncmp(identifier, "NO", 2) && !map->north_path)
		map->north_path = get_texture_path(line, j + 2);
	else if (!ft_strncmp(identifier, "SO", 2) && !map->south_path)
		map->south_path = get_texture_path(line, j + 2);
	else if (!ft_strncmp(identifier, "WE", 2) && !map->west_path)
		map->west_path = get_texture_path(line, j + 2);
	else if (!ft_strncmp(identifier, "EA", 2) && !map->east_path)
		map->east_path = get_texture_path(line, j + 2);
	else
	{
		free(identifier);
		return (1);
	}
	free(identifier);
	return (0);
}

int	set_color_textures(t_map *map, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]) && !is_space(line[j + 1]))
		return (2);
	if (!map->rgb_ceiling && line[j] == 'C')
	{
		map->rgb_ceiling = parse_rgb(line + j + 1);
		if (!map->rgb_ceiling)
			return (2);
	}
	else if (!map->rgb_floor && line[j] == 'F')
	{
		map->rgb_floor = parse_rgb(line + j + 1);
		if (!map->rgb_floor)
			return (2);
	}
	else
		return (2);
	return (0);
}

int	process_line_content(t_game *game, char **map, int i, int j)
{
	while (map[i][j] && (is_space(map[i][j]) || map[i][j] == '\n'))
		j++;
	if (ft_isprint(map[i][j]) && !is_space(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
			&& !is_space(map[i][j + 1]) && !ft_isdigit(map[i][j + 1]))
		{
			if (set_direction_textures(&game->map, map[i], j))
				return (err("Invalid texture", 2));
			return (-1);
		}
		else
		{
			if (set_color_textures(&game->map, map[i], j))
				return (err("Invalid RGB color", 2));
			return (-1);
		}
	}
	else if (ft_isdigit(map[i][j]))
	{
		if (count_map_lines(game, i))
			return (2);
		return (0);
	}
	return (1);
}

int	parse_file(t_game *game)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			ret = process_line_content(game, game->map.map, i, j);
			if (ret == -1)
				break ;
			else if (ret == 2)
				return (1);
			else if (ret != 1)
				return (ret);
			j++;
		}
		i++;
	}
	return (0);
}
