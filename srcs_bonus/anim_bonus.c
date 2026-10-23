/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_frame(mlx_image_t *img, mlx_texture_t *tex, int frame)
{
	uint32_t	row;
	uint32_t	line;

	line = TILE * 4;
	row = 0;
	while (row < TILE)
	{
		ft_memcpy(img->pixels + row * line,
			tex->pixels + (row * tex->width + frame * TILE) * 4, line);
		row++;
	}
}

void	draw_hud(t_game *g)
{
	char	*num;
	char	*text;

	if (g->hud)
		mlx_delete_image(g->mlx, g->hud);
	num = ft_itoa(g->moves);
	text = ft_strjoin("Moves: ", num);
	free(num);
	if (!text)
		return ;
	g->hud = mlx_put_string(g->mlx, text, 6, 6);
	free(text);
}

void	on_frame(void *param)
{
	t_game	*g;

	g = param;
	if (g->over)
		return ;
	g->anim_time += g->mlx->delta_time;
	g->enemy_time += g->mlx->delta_time;
	if (g->anim_time >= ANIM_DELAY)
	{
		g->anim_time = 0;
		g->frame++;
		set_frame(g->player, g->tex_player, g->frame % 4);
		set_frame(g->coll, g->tex_coll, g->frame % 4);
		set_frame(g->enemy, g->tex_enemy, g->frame % 2);
	}
	if (g->enemy_time >= ENEMY_DELAY)
	{
		g->enemy_time = 0;
		move_enemies(g);
	}
}
