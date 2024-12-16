/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:09 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/16 01:07:38 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	set_direction_textures(t_tex *textures, char *line, int j)
{
	char	*identifier;

	identifier = ft_substr(line, j, 2);
	if (!identifier)
		return (1);
	if (!ft_strncmp(identifier, "NO", 2) && !textures->north)
		textures->north = get_texture_path(line, j + 2);
	else if (!ft_strncmp(identifier, "SO", 2) && !textures->south)
		textures->south = get_texture_path(line, j + 2);
	else if (!ft_strncmp(identifier, "WE", 2) && !textures->west)
		textures->west = get_texture_path(line, j + 2);
	else if (!ft_strncmp(identifier, "EA", 2) && !textures->east)
		textures->east = get_texture_path(line, j + 2);
	else
	{
		free(identifier);
		return (1);
	}
	free(identifier);
	return (0);
}

int	set_color_textures(t_tex *textures, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]) && line[j + 1] != ' ')
		return (2);
	if (!textures->ceiling && line[j] == 'C')
	{
		textures->ceiling = parse_rgb(line + j + 1);
		if (!textures->ceiling)
			return (2);
		else
			textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	}
	else if (!textures->floor && line[j] == 'F')
	{
		textures->floor = parse_rgb(line + j + 1);
		if (!textures->floor)
			return (2);
		else
			textures->hex_floor = convert_rgb_to_hex(textures->floor);
	}
	else
		return (2);
	return (0);
}

int	process_line_content(t_game *game, char **mapf, int i, int j)
{
	while (mapf[i][j] == ' ' || mapf[i][j] == '\t' || mapf[i][j] == '\n')
		j++;
	if (ft_isprint(mapf[i][j]) && mapf[i][j] != ' ' && !ft_isdigit(mapf[i][j]))
	{
		if (mapf[i][j + 1] && ft_isprint(mapf[i][j + 1]) &&
			mapf[i][j + 1] != ' ' && !ft_isdigit(mapf[i][j]))
		{
			if (set_direction_textures(&game->texture, mapf[i], j))
				return (err("Invalid texture", 2));
			return (-1);
		}
		else
		{
			if (set_color_textures(&game->texture, mapf[i], j))
				return (err("Invalid RGB color", 2));
			return (-1);
		}
	}
	else if (ft_isdigit(mapf[i][j]))
	{
		game->map.start_of_map = i;
		while (game->map.map[i])
			i++;
		if (i == game->map.start_of_map)
			return (err("Invalid map", 2));
		game->map.end_of_map = i - 1;
		game->map.height = i - game->map.start_of_map;
		return (0);
	}
	return (1);
}

int	parse_file(t_game *game, char **mapf)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (mapf[i])
	{
		j = 0;
		while (mapf[i][j])
		{
			ret = process_line_content(game, mapf, i, j);
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
