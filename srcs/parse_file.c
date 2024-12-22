/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:09 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/22 17:54:31 by dmodrzej         ###   ########.fr       */
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

int	set_direction_textures(t_texdata *texdata, char *line, int j)
{
	char	*identifier;

	identifier = ft_substr(line, j, 2);
	if (!identifier)
		return (1);
	if (!ft_strncmp(identifier, "NO", 2) && !texdata->north_path)
		texdata->north_path = get_texture_path(line, j + 2);
	else if (!ft_strncmp(identifier, "SO", 2) && !texdata->south_path)
		texdata->south_path = get_texture_path(line, j + 2);
	else if (!ft_strncmp(identifier, "WE", 2) && !texdata->west_path)
		texdata->west_path = get_texture_path(line, j + 2);
	else if (!ft_strncmp(identifier, "EA", 2) && !texdata->east_path)
		texdata->east_path = get_texture_path(line, j + 2);
	else
	{
		free(identifier);
		return (1);
	}
	free(identifier);
	return (0);
}

int	set_color_textures(t_texdata *texdata, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]) && line[j + 1] != ' ')
		return (2);
	if (!texdata->rgb_ceiling && line[j] == 'C')
	{
		texdata->rgb_ceiling = parse_rgb(line + j + 1);
		if (!texdata->rgb_ceiling)
			return (2);
	}
	else if (!texdata->rgb_floor && line[j] == 'F')
	{
		texdata->rgb_floor = parse_rgb(line + j + 1);
		if (!texdata->rgb_floor)
			return (2);
	}
	else
		return (2);
	return (0);
}

int	process_line_content(t_game *game, char **map, int i, int j)
{
	while (ft_isspace(map[i][j]))
		j++;
	if (ft_isprint(map[i][j]) && map[i][j] != ' ' && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1]) &&
			map[i][j + 1] != ' ' && !ft_isdigit(map[i][j]))
		{
			if (set_direction_textures(&game->texdata, map[i], j))
				return (err("Invalid texture", 2));
			return (-1);
		}
		else
		{
			if (set_color_textures(&game->texdata, map[i], j))
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
