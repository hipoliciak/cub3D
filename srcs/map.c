/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:51 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/02 01:05:35 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map(t_game *game, char *path)
{
	int		fd;
	char	*line;

	fd = open_map(path, game);
	line = get_next_line(fd);
	if (!line)
		end_game_with_message(game, "No map", 1);
	if (ft_strchr(line, '\n') != 0)
		line = split_line(line);
	game->map.width = ft_strlen(line);
	while (line)
	{
		game->map.height++;
		free(line);
		line = get_next_line(fd);
		if (ft_strchr(line, '\n') != 0)
			line = split_line(line);
	}
	close(fd);
}

void	fill_map(t_game *game, char *path)
{
	int		fd;
	char	*line;
	int		i;

	if (game->map.height <= 3 || game->map.width <= 3)
		end_game_with_message(game, "Map too small", 1);
	fd = open_map(path, game);
	game->map.map = malloc(game->map.height * sizeof(char *));
	if (!game->map.map)
		end_game_with_message(game, "Malloc error", 1);
	i = 0;
	while (i < game->map.height)
	{
		line = get_next_line(fd);
		game->map.map[i] = malloc((game->map.width + 1) * sizeof(char));
		if (!game->map.map[i])
			end_game_with_message(game, "Malloc error", 1);
		ft_strlcpy(game->map.map[i], line, game->map.width + 1);
		free(line);
		i++;
	}
	close(fd);
}

void	validate_elements(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (ft_strchr("01NEWS", game->map.map[i][j]) == NULL)
				end_game_with_message(game, "Invalid element on the map", 1);
			j++;
		}
		i++;
	}
}

void	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (i == 0 || i == game->map.height)
			{
				if (game->map.map[i][j] != '1')
					end_game_with_message(game, "Invalid wall", 1);
			}
			if (j == 0 || j == game->map.width - 1)
			{
				if (game->map.map[i][j] != '1')
					end_game_with_message(game, "Invalid wall", 1);
			}
			j++;
		}
		i++;
	}
}
