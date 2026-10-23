/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	check_chars(t_game *g)
{
	int	x;
	int	y;

	g->w = ft_strlen(g->map[0]);
	y = 0;
	while (g->map[y])
	{
		if ((int)ft_strlen(g->map[y]) != g->w)
			return (fail("map is not rectangular"));
		x = 0;
		while (g->map[y][x])
		{
			if (!ft_strchr("01CENP", g->map[y][x]))
				return (fail("invalid character in map"));
			x++;
		}
		y++;
	}
	g->h = y;
	return (0);
}

static int	check_walls(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->w)
	{
		if (g->map[0][i] != '1' || g->map[g->h - 1][i] != '1')
			return (fail("map is not surrounded by walls"));
		i++;
	}
	i = 0;
	while (i < g->h)
	{
		if (g->map[i][0] != '1' || g->map[i][g->w - 1] != '1')
			return (fail("map is not surrounded by walls"));
		i++;
	}
	return (0);
}

static int	count_char(char **map, char c)
{
	int	n;
	int	i;
	int	j;

	n = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				n++;
			j++;
		}
		i++;
	}
	return (n);
}

static int	check_counts(t_game *g)
{
	if (count_char(g->map, 'P') != 1)
		return (fail("map needs exactly one player (P)"));
	if (count_char(g->map, 'E') != 1)
		return (fail("map needs exactly one exit (E)"));
	if (count_char(g->map, 'C') < 1)
		return (fail("map needs at least one collectible (C)"));
	return (0);
}

int	validate_map(t_game *g)
{
	if (check_chars(g) || check_walls(g) || check_counts(g))
		return (1);
	find_player(g);
	return (check_path(g));
}
