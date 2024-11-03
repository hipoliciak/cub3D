/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:51 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/03 01:27:49 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strncmp(&path[len - 4], ".cub", 4) != 0)
		return (0);
	return (1);
}

void	read_map(t_game *game, char *path)
{
	int		fd;
	char	*line;

	fd = open_map(path, game);
	line = get_next_line(fd);
	if (!line)
		end_game_with_message(game, "No map", 1);
	while (line)
	{
		game->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	game->map.map = malloc(sizeof(char *) * game->map.height + 1);
	if (!game->map.map)
		end_game_with_message(game, "Malloc error", 1);
	close(fd);
}

void	fill_map(t_game *game, char *path)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open_map(path, game);
	line = get_next_line(fd);
	while (line && i < game->map.height + 1)
	{
		game->map.map[i] = ft_strdup(line);
		if (!game->map.map[i])
			end_game_with_message(game, "Malloc error", 1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	check_characters(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x] != '\n' && game->map.map[y][x])
		{
			if (ft_strchr(" 01NEWS", game->map.map[y][x]) == NULL)
				end_game_with_message(game, "Invalid character in map", 1);
			x++;
		}
		y++;
	}
}

void	check_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (y == 0)
			{
				if (game->map.map[y][x] != '1')
					end_game_with_message(game, "Map not closed", 1);
			}
			if (y > 0 && y < game->map.height - 1)
			{
				while (game->map.map[y][x] == ' ' && game->map.map[y][x])
					x++;
				if (game->map.map[y][x] != '1')
					end_game_with_message(game, "Map not closed", 1);
				while (game->map.map[y][x] != ' ' && game->map.map[y][x])
					x++;
				if (game->map.map[y][x] != '1')
					end_game_with_message(game, "Map not closed", 1);
			}
			if (y == game->map.height - 1)
			{
				if (game->map.map[y][x] != '1')
					end_game_with_message(game, "Map not closed", 1);
			}
			x++;
		}
		y++;
	}
}
