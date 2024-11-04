/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:51 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/04 20:55:03 by piotr            ###   ########.fr       */
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

bool line_validation(char *line)
{
	int i;
	if(line[0] == '\n')
		return false;
	i = 0;
	while(line[i])
	{
		if(ft_strchr(" 01NEWS\n", line[i]) == NULL)
			return false;	
		i++;
	}
	return true;
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
		if(line_validation(line))
			game->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	// potential problem may lie in below line, i increased from +1 to +3 alloc size. ATM is fine
	game->map.map = malloc(sizeof(char *) * (game->map.height + 3));
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
		if(line_validation(line) && (i < game->map.height + 1))
		{
			game->map.map[i] = ft_strdup(line);
			if (!game->map.map[i])
				end_game_with_message(game, "Malloc error", 1);
			i++;
		}

		free(line);
		line = get_next_line(fd);
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
			// TO CHECK: I think \n is missing here it should be " 01NEWS\n":
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
