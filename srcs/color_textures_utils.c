/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:07:47 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/14 23:22:01 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_str_digits(char *rgb_string)
{
	int	i;

	i = 0;
	if (!rgb_string || !*rgb_string)
		return (0);
	while (rgb_string[i])
	{
		if (!ft_isdigit(rgb_string[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_rgb_strings(char **rgb_strings, int count)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (i < count)
	{
		trimmed = ft_strtrim(rgb_strings[i], " \t\n\r");
		if (!trimmed || !rgb_str_digits(trimmed))
		{
			free(trimmed);
			free_tab((void **)rgb_strings);
			return (0);
		}
		free(rgb_strings[i]);
		rgb_strings[i] = trimmed;
		i++;
	}
	return (1);
}

unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	int	r;
	int	g;
	int	b;

	if (!rgb_tab)
		return (err("Could not convert RGB to hex", 0));
	r = rgb_tab[0] & 0xff;
	g = rgb_tab[1] & 0xff;
	b = rgb_tab[2] & 0xff;
	return ((r << 16) | (g << 8) | b);
}

int	*convert_rgb(char **rgb_strings)
{
	int	i;
	int	*rgb;

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		err("Could not allocate memory", 0);
		return (0);
	}
	i = 0;
	while (rgb_strings[i])
	{
		rgb[i] = ft_atoi(rgb_strings[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_tab((void **)rgb_strings);
			free(rgb);
			return (0);
		}
		i++;
	}
	free_tab((void **)rgb_strings);
	return (rgb);
}

int	*parse_rgb(char *line)
{
	char	**rgb_strings;
	int		count;

	count = 0;
	rgb_strings = ft_split(line, ',');
	if (!rgb_strings)
		return (0);
	while (rgb_strings && rgb_strings[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_strings);
		return (0);
	}
	if (!check_rgb_strings(rgb_strings, count))
		return (0);
	return (convert_rgb(rgb_strings));
}
