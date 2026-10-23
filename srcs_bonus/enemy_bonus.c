/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	init_enemies(t_game *g)
{
	int	x;
	int	y;
	int	i;

	g->enemies = ft_calloc(g->n_enemy + 1, sizeof(t_enemy));
	if (!g->enemies)
		return (fail("memory allocation failed"));
	i = 0;
	y = -1;
	while (g->map[++y])
	{
		x = -1;
		while (g->map[y][++x])
		{
			if (g->map[y][x] != 'N')
				continue ;
			g->map[y][x] = '0';
			g->enemies[i].x = x;
			g->enemies[i].y = y;
			g->enemies[i++].dir = 1;
		}
	}
	return (0);
}

int	hit_enemy(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->n_enemy)
	{
		if (g->enemies[i].x == g->px && g->enemies[i].y == g->py)
			return (1);
		i++;
	}
	return (0);
}

static void	step_enemy(t_game *g, t_enemy *e)
{
	if (g->map[e->y][e->x + e->dir] != '0')
	{
		e->dir = -e->dir;
		return ;
	}
	e->x += e->dir;
	g->enemy->instances[e->id].x = e->x * TILE;
}

void	move_enemies(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->n_enemy)
	{
		step_enemy(g, &g->enemies[i]);
		i++;
	}
	if (hit_enemy(g))
		lose(g);
}
