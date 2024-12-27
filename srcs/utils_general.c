/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:09:31 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 22:05:23 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err(char *str, int code)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	return (code);
}

int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_surrounded_by_space_or_wall(char **map, int i, int j)
{
	if (map[i - 1] && (map[i - 1][j] == ' ' || map[i - 1][j] == '1'
		|| map[i - 1][j] == '\n' || map[i - 1][j] == '\0')
		&& (map[i][j - 1] == ' ' || map[i][j - 1] == '1'
		|| map[i][j - 1] == '\n' || map[i][j - 1] == '\0')
		&& (map[i][j + 1] == ' ' || map[i][j + 1] == '1'
		|| map[i][j + 1] == '\n' || map[i][j + 1] == '\0'))
		return (0);
	return (1);
}
