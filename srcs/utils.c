/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:31 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/21 19:05:49 by dmodrzej         ###   ########.fr       */
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
			return (err("There is something after the map", 1));
	}
	game->map.end_of_map = i - 1;
	game->map.height = i - game->map.start_of_map;
	return (0);
}

int	is_surrounded_by_space_or_wall(char **map, int i, int j)
{
	if ((map[i - 1][j] == ' ' || map[i - 1][j] == '1'
		|| map[i - 1][j] == '\n' || map[i - 1][j] == '\0')
		&& (map[i + 1][j] == ' ' || map[i + 1][j] == '1'
		|| map[i + 1][j] == '\n' || map[i + 1][j] == '\0')
		&& (map[i][j - 1] == ' ' || map[i][j - 1] == '1'
		|| map[i][j - 1] == '\n' || map[i][j - 1] == '\0')
		&& (map[i][j + 1] == ' ' || map[i][j + 1] == '1'
		|| map[i][j + 1] == '\n' || map[i][j + 1] == '\0'))
		return (0);
	return (1);
}
