/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == 'P')
			{
				g->px = x;
				g->py = y;
			}
			if (g->map[y][x] == 'C')
				g->total++;
			x++;
		}
		y++;
	}
}

static char	**dup_map(char **map, int h)
{
	char	**copy;
	int		i;

	copy = ft_calloc(h + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < h)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (ft_array_free(copy), NULL);
		i++;
	}
	return (copy);
}

static int	unreachable(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strchr(map[i], 'C') || ft_strchr(map[i], 'E'))
			return (1);
		i++;
	}
	return (0);
}

static void	fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	fill(map, x + 1, y);
	fill(map, x - 1, y);
	fill(map, x, y + 1);
	fill(map, x, y - 1);
}

int	check_path(t_game *g)
{
	char	**copy;
	int		bad;

	copy = dup_map(g->map, g->h);
	if (!copy)
		return (fail("memory allocation failed"));
	fill(copy, g->px, g->py);
	bad = unreachable(copy);
	ft_array_free(copy);
	if (bad)
		return (fail("no valid path to every collectible and the exit"));
	return (0);
}
