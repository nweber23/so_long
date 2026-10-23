/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static mlx_image_t	*load(t_game *g, char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(path);
	if (!tex)
		return (NULL);
	img = mlx_texture_to_image(g->mlx, tex);
	mlx_delete_texture(tex);
	return (img);
}

int	load_images(t_game *g)
{
	g->floor = load(g, "textures/floor.png");
	g->wall = load(g, "textures/wall.png");
	g->exit_closed = load(g, "textures/exit.png");
	g->exit_open = load(g, "textures/exit_open.png");
	g->tex_player = mlx_load_png("textures/bonus/player_sheet.png");
	g->tex_coll = mlx_load_png("textures/bonus/collectible_sheet.png");
	g->tex_enemy = mlx_load_png("textures/bonus/enemy_sheet.png");
	g->player = mlx_new_image(g->mlx, TILE, TILE);
	g->coll = mlx_new_image(g->mlx, TILE, TILE);
	g->enemy = mlx_new_image(g->mlx, TILE, TILE);
	if (!g->floor || !g->wall || !g->exit_closed || !g->exit_open
		|| !g->tex_player || !g->tex_coll || !g->tex_enemy
		|| !g->player || !g->coll || !g->enemy)
		return (fail("cannot load textures"));
	set_frame(g->player, g->tex_player, 0);
	set_frame(g->coll, g->tex_coll, 0);
	set_frame(g->enemy, g->tex_enemy, 0);
	return (0);
}

static int	draw_cell(t_game *g, int x, int y)
{
	char	c;
	int		id;

	c = g->map[y][x];
	if (mlx_image_to_window(g->mlx, g->floor, x * TILE, y * TILE) < 0)
		return (1);
	id = 0;
	if (c == '1')
		id = mlx_image_to_window(g->mlx, g->wall, x * TILE, y * TILE);
	else if (c == 'E')
	{
		id = mlx_image_to_window(g->mlx, g->exit_closed, x * TILE, y * TILE);
		if (id >= 0)
			id = mlx_image_to_window(g->mlx, g->exit_open, x * TILE, y * TILE);
	}
	else if (c == 'C')
	{
		id = mlx_image_to_window(g->mlx, g->coll, x * TILE, y * TILE);
		g->ids[y * g->w + x] = id;
	}
	return (id < 0);
}

static int	draw_map(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->h)
	{
		x = 0;
		while (x < g->w)
		{
			if (draw_cell(g, x, y))
				return (fail("cannot draw the map"));
			x++;
		}
		y++;
	}
	g->exit_open->enabled = false;
	return (0);
}

int	init_game(t_game *g)
{
	int	i;

	g->mlx = mlx_init(g->w * TILE, g->h * TILE, "so_long", false);
	if (!g->mlx)
		return (fail((char *)mlx_strerror(mlx_get_errno())));
	g->ids = ft_calloc(g->w * g->h, sizeof(int));
	if (!g->ids || load_images(g) || draw_map(g))
		return (1);
	i = 0;
	while (i < g->n_enemy)
	{
		g->enemies[i].id = mlx_image_to_window(g->mlx, g->enemy,
				g->enemies[i].x * TILE, g->enemies[i].y * TILE);
		i++;
	}
	if (mlx_image_to_window(g->mlx, g->player, g->px * TILE, g->py * TILE) < 0)
		return (fail("cannot draw the player"));
	draw_hud(g);
	mlx_key_hook(g->mlx, on_key, g);
	mlx_loop_hook(g->mlx, on_frame, g);
	return (0);
}
