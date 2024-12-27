/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:24 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 22:55:12 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_number_of_lines(char *path)
{
	char	*line;
	int		fd;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
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

int	fill_file(t_game *game, int fd)
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
		game->file.file[j] = ft_strdup(line);
		free(line);
		if (!game->file.file[j])
		{
			err("Could not allocate memory", 1);
			free_tab((void **)game->file.file);
			return (1);
		}
		line = get_next_line(fd);
		j++;
	}
	game->file.file[j] = NULL;
	return (0);
}

int	copy_file(t_game *game, char *path)
{
	int	fd;
	int	line_count;

	if (is_cub_file(path))
		return (err("Not a .cub file", 1));
	line_count = get_number_of_lines(path);
	if (line_count <= 0)
		return (err("Empty file", 1));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err("Could not open the file", 1));
	game->file.file = malloc(sizeof(char *) * (line_count + 1));
	if (!game->file.file)
	{
		close(fd);
		return (err("Could not allocate memory", 1));
	}
	if (fill_file(game, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
