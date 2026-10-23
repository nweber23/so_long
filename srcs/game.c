/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

static int	load_images(t_game *g)
{
	g->floor = load(g, "textures/floor.png");
	g->wall = load(g, "textures/wall.png");
	g->exit_closed = load(g, "textures/exit.png");
	g->exit_open = load(g, "textures/exit_open.png");
	g->coll = load(g, "textures/collectible.png");
	g->player = load(g, "textures/player.png");
	if (!g->floor || !g->wall || !g->exit_closed || !g->exit_open
		|| !g->coll || !g->player)
		return (fail("cannot load textures"));
	return (0);
}

static int	draw_cell(t_game *g, int x, int y)
{
	char	c;
	int		id;

	c = g->map[y][x];
	if (mlx_image_to_window(g->mlx, g->floor, x * TILE, y * TILE) < 0)
		return (1);
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
	else
		id = 0;
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
	if (mlx_image_to_window(g->mlx, g->player, g->px * TILE, g->py * TILE) < 0)
		return (fail("cannot draw the player"));
	return (0);
}

int	init_game(t_game *g)
{
	g->mlx = mlx_init(g->w * TILE, g->h * TILE, "so_long", false);
	if (!g->mlx)
		return (fail((char *)mlx_strerror(mlx_get_errno())));
	g->ids = ft_calloc(g->w * g->h, sizeof(int));
	if (!g->ids)
		return (fail("memory allocation failed"));
	if (load_images(g) || draw_map(g))
		return (1);
	mlx_key_hook(g->mlx, on_key, g);
	return (0);
}
