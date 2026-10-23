/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_game(t_game *g)
{
	ft_array_free(g->map);
	free(g->ids);
	if (g->mlx)
		mlx_terminate(g->mlx);
}

void	move_player(t_game *g, int dx, int dy)
{
	char	*cell;

	cell = &g->map[g->py + dy][g->px + dx];
	if (*cell == '1')
		return ;
	g->px += dx;
	g->py += dy;
	g->player->instances[0].x = g->px * TILE;
	g->player->instances[0].y = g->py * TILE;
	g->moves++;
	ft_printf("Moves: %d\n", g->moves);
	if (*cell == 'C')
	{
		*cell = '0';
		g->coll->instances[g->ids[g->py * g->w + g->px]].enabled = false;
		g->got++;
		g->exit_open->enabled = (g->got == g->total);
	}
	else if (*cell == 'E' && g->got == g->total)
		mlx_close_window(g->mlx);
}

void	on_key(mlx_key_data_t k, void *param)
{
	t_game	*g;

	g = param;
	if (k.action != MLX_PRESS)
		return ;
	if (k.key == MLX_KEY_ESCAPE)
		mlx_close_window(g->mlx);
	else if (k.key == MLX_KEY_W || k.key == MLX_KEY_UP)
		move_player(g, 0, -1);
	else if (k.key == MLX_KEY_S || k.key == MLX_KEY_DOWN)
		move_player(g, 0, 1);
	else if (k.key == MLX_KEY_A || k.key == MLX_KEY_LEFT)
		move_player(g, -1, 0);
	else if (k.key == MLX_KEY_D || k.key == MLX_KEY_RIGHT)
		move_player(g, 1, 0);
}
