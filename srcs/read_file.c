/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:24 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/26 22:39:16 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	get_number_of_lines(char *path)
// {
// 	int		fd;
// 	char	*line;
// 	int		line_count;

// 	line_count = 0;
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	else
// 	{
// 		line = get_next_line(fd);
// 		while (line != NULL)
// 		{
// 			line_count++;
// 			free(line);
// 			line = get_next_line(fd);
// 		}
// 		close(fd);
// 	}
// 	return (line_count);
// }

// void	fill_map(t_game *game)
// {
// 	char	*line;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	line = get_next_line(game->map.fd);
// 	while (line != NULL)
// 	{
// 		i = 0;
// 		while (line[i] != '\0' && line[i] != '\n')
// 			i++;
// 		line[i] = '\0';
// 		game->map.map[j] = ft_strdup(line);
// 		free(line);
// 		if (!game->map.map[j])
// 		{
// 			err("Could not allocate memory", 1);
// 			free_tab((void **)game->map.map);
// 			return ;
// 		}
// 		line = get_next_line(game->map.fd);
// 		j++;
// 	}
// 	game->map.map[j] = NULL;
// }

// int	read_file(t_game *game, char *path)
// {
// 	int	line_count;

// 	line_count = get_number_of_lines(path);
// 	game->map.map = malloc(sizeof(char *) * (line_count + 1));
// 	if (!(game->map.map))
// 		return (err("Could not allocate memory", 1));
// 	game->map.fd = open(path, O_RDONLY);
// 	if (game->map.fd < 0)
// 	{
// 		free(game->map.map);
// 		return (1);
// 	}
// 	else
// 	{
// 		fill_map(game);
// 		close(game->map.fd);
// 	}
// 	return (0);
// }

int	get_number_of_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_count);
}

int	fill_map(t_game *game, int fd)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] != '\0' && line[i] != '\n')
			i++;
		line[i] = '\0';
		game->map.map[j] = ft_strdup(line);
		free(line);
		if (!game->map.map[j])
		{
			err("Could not allocate memory", 1);
			free_tab((void **)game->map.map);
			return (1);
		}
		line = get_next_line(fd);
		j++;
	}
	game->map.map[j] = NULL;
	return (0);
}

int	read_file(t_game *game, char *path)
{
	int	fd;
	int	line_count;

	line_count = get_number_of_lines(path);
	if (line_count < 0)
		return (err("Could not read the file", 1));
	game->map.map = malloc(sizeof(char *) * (line_count + 1));
	if (!game->map.map)
		return (err("Could not allocate memory", 1));
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(game->map.map);
		return (err("Could not open the file", 1));
	}
	if (fill_map(game, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
