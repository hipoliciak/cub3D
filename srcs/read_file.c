/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:24 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/21 18:34:40 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_number_of_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

void	fill_tab(int row, t_game *game)
{
	char	*line;
	int		i;

	line = get_next_line(game->map.fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] != '\0' && line[i] != '\n')
			i++;
		line[i] = '\0';
		game->map.map[row] = ft_strdup(line);
		free(line);
		if (!game->map.map[row])
		{
			err("Could not allocate memory", 1);
			free_tab((void **)game->map.map);
			return ;
		}
		line = get_next_line(game->map.fd);
		row++;
	}
	game->map.map[row] = NULL;
}

int	read_file(char *path, t_game *game)
{
	int		row;

	row = 0;
	game->map.line_count = get_number_of_lines(path);
	game->map.map = malloc(sizeof(char *) * (game->map.line_count + 1));
	if (!(game->map.map))
		return (err("Could not allocate memory", 1));
	game->map.fd = open(path, O_RDONLY);
	if (game->map.fd < 0)
	{
		free(game->map.map);
		return (1);
	}
	else
	{
		fill_tab(row, game);
		close(game->map.fd);
	}
	return (0);
}
