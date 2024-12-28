/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:09 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/28 02:03:58 by dmodrzej         ###   ########.fr       */
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

int	set_direction_textures(t_file *file, char *line, int i)
{
	char	*identifier;

	identifier = ft_substr(line, i, 2);
	if (!identifier)
		return (err("Malloc failed", 1));
	if (!ft_strncmp(identifier, "NO", 2) && !file->north_path)
		file->north_path = get_texture_path(line, i + 2);
	else if (!ft_strncmp(identifier, "SO", 2) && !file->south_path)
		file->south_path = get_texture_path(line, i + 2);
	else if (!ft_strncmp(identifier, "WE", 2) && !file->west_path)
		file->west_path = get_texture_path(line, i + 2);
	else if (!ft_strncmp(identifier, "EA", 2) && !file->east_path)
		file->east_path = get_texture_path(line, i + 2);
	else
	{
		free(identifier);
		return (err("Invalid texture", 1));
	}
	free(identifier);
	return (0);
}

int	set_color_textures(t_file *file, char *line, int i)
{
	if (!file->rgb_ceiling && line[i] == 'C')
	{
		file->rgb_ceiling = parse_rgb(line + i + 1);
		if (!file->rgb_ceiling)
			return (err("Invalid RGB ceiling color", 1));
	}
	else if (!file->rgb_floor && line[i] == 'F')
	{
		file->rgb_floor = parse_rgb(line + i + 1);
		if (!file->rgb_floor)
			return (err("Invalid RGB floor color", 1));
	}
	else
		return (err("Invalid RGB color", 1));
	return (0);
}

int	parse_line(t_game *game, char *line, int map_line_index)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && (is_space(line[i]) || line[i] == '\n'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	if (ft_isprint(line[i]) && !ft_strchr("NSWEFC", line[i]) && line[i] != '1')
		return (err("Invalid file line", 1));
	if (ft_strchr("NSWEFC", line[i]))
	{
		if (line[i + 1] && ft_strchr("OEA", line[i + 1]))
			return (set_direction_textures(&game->file, line, i));
		else if (line[i + 1] && is_space(line[i + 1]))
			return (set_color_textures(&game->file, line, i));
	}
	else if (line[i] && line[i] == '1' && !game->file.map_start)
		game->file.map_start = map_line_index;
	else if (line[i] && line[i] != '1' && game->file.map_start)
		return (err("Invalid map line", 1));
	return (0);
}

int	parse_file(t_game *game)
{
	int	i;
	int	ret;

	i = 0;
	while (game->file.file[i])
	{
		ret = parse_line(game, game->file.file[i], i);
		if (ret)
			return (ret);
		i++;
	}
	if (!game->file.map_start)
		return (err("No map", 1));
	if (copy_map(game))
		return (1);
	return (0);
}
