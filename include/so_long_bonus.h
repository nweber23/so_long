/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <fcntl.h>
# include <MLX42/MLX42.h>
# include "libft.h"

# define TILE 32
# define ANIM_DELAY 0.2
# define ENEMY_DELAY 0.4

typedef struct s_enemy
{
	int	x;
	int	y;
	int	dir;
	int	id;
}	t_enemy;

typedef struct s_game
{
	mlx_t			*mlx;
	char			**map;
	int				*ids;
	t_enemy			*enemies;
	int				n_enemy;
	int				w;
	int				h;
	int				px;
	int				py;
	int				total;
	int				got;
	int				moves;
	int				over;
	int				frame;
	double			anim_time;
	double			enemy_time;
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_image_t		*exit_closed;
	mlx_image_t		*exit_open;
	mlx_image_t		*player;
	mlx_image_t		*coll;
	mlx_image_t		*enemy;
	mlx_image_t		*hud;
	mlx_texture_t	*tex_player;
	mlx_texture_t	*tex_coll;
	mlx_texture_t	*tex_enemy;
}	t_game;

char	**read_map(char *path);
int		validate_map(t_game *g);
int		check_path(t_game *g);
void	find_player(t_game *g);
int		fail(char *msg);
int		init_game(t_game *g);
int		load_images(t_game *g);
int		init_enemies(t_game *g);
int		hit_enemy(t_game *g);
void	move_enemies(t_game *g);
void	move_player(t_game *g, int dx, int dy);
void	on_key(mlx_key_data_t k, void *param);
void	on_frame(void *param);
void	set_frame(mlx_image_t *img, mlx_texture_t *tex, int frame);
void	draw_hud(t_game *g);
void	lose(t_game *g);
void	free_game(t_game *g);

#endif
