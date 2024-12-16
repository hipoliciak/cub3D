/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:31 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/16 01:24:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	find_biggest_len(t_map *map, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(map->map[i]);
	while (map->map[i] != NULL)
	{
		if (ft_strlen(map->map[i]) > biggest_len)
			biggest_len = ft_strlen(map->map[i]);
		i++;
	}
	return (biggest_len);
}

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
