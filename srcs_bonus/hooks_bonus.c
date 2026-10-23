/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_game(t_game *g)
{
	ft_array_free(g->map);
	free(g->ids);
	free(g->enemies);
	if (g->tex_player)
		mlx_delete_texture(g->tex_player);
	if (g->tex_coll)
		mlx_delete_texture(g->tex_coll);
	if (g->tex_enemy)
		mlx_delete_texture(g->tex_enemy);
	if (g->mlx)
		mlx_terminate(g->mlx);
}

void	lose(t_game *g)
{
	g->over = 1;
	ft_printf("You lose!\n");
	mlx_put_string(g->mlx, "YOU LOSE - press ESC", g->w * TILE / 2 - 90,
		g->h * TILE / 2);
}

static void	pickup(t_game *g, char *cell)
{
	*cell = '0';
	g->coll->instances[g->ids[g->py * g->w + g->px]].enabled = false;
	g->got++;
	g->exit_open->enabled = (g->got == g->total);
}

void	move_player(t_game *g, int dx, int dy)
{
	char	*cell;

	cell = &g->map[g->py + dy][g->px + dx];
	if (g->over || *cell == '1')
		return ;
	g->px += dx;
	g->py += dy;
	g->player->instances[0].x = g->px * TILE;
	g->player->instances[0].y = g->py * TILE;
	g->moves++;
	ft_printf("Moves: %d\n", g->moves);
	draw_hud(g);
	if (*cell == 'C')
		pickup(g, cell);
	if (hit_enemy(g))
		lose(g);
	else if (*cell == 'E' && g->got == g->total)
	{
		ft_printf("You won in %d moves!\n", g->moves);
		mlx_close_window(g->mlx);
	}
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
