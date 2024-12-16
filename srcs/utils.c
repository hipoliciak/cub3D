/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:31 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/16 21:24:35 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err(char *str, int code)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	return (code);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	ft_isspace_not_nl(int c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	count_map_lines(t_game *game, int map_start)
{
	int	i;
	int	j;

	game->map.start_of_map = map_start;
	i = map_start;
	while (game->map.map[i])
	{
		j = 0;
		while (ft_isspace_not_nl(game->map.map[i][j]))
			j++;
		if (game->map.map[i][j] == '1')
			i++;
		else
			return (err("Invalid map", 1));
	}
	game->map.end_of_map = i - 1;
	game->map.height = i - game->map.start_of_map;
	return (0);
}

int	is_surrounded_by_space_or_wall(char **map, int i, int j)
{
	if ((map[i - 1][j] == ' ' || map[i - 1][j] == '1'
		|| map[i - 1][j] == '\0')
		&& (map[i + 1][j] == ' ' || map[i + 1][j] == '1'
		|| map[i + 1][j] == '\0')
		&& (map[i][j - 1] == ' ' || map[i][j - 1] == '1'
		|| map[i][j - 1] == '\0')
		&& (map[i][j + 1] == ' ' || map[i][j + 1] == '1'
		|| map[i][j + 1] == '\0'))
		return (0);
	return (1);
}

int	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = game->map.start_of_map;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			printf("%c", game->map.map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
	printf("\n");
	printf("Player position: %f, %f\n", game->player.pos_x, game->player.pos_y);
	// printf("Player angle: %f\n", game->player.angle);
	printf("Player tile position: %d, %d\n",
		game->player.tile_x, game->player.tile_y);
	printf("\n");
	return (0);
}
