/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <MLX42/MLX42.h>
# include "libft.h"

# define TILE 32

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	int			*ids;
	int			w;
	int			h;
	int			px;
	int			py;
	int			total;
	int			got;
	int			moves;
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t	*exit_closed;
	mlx_image_t	*player;
	mlx_image_t	*coll;
	mlx_image_t	*exit_open;
}	t_game;

char	**read_map(char *path);
int		validate_map(t_game *g);
int		check_path(t_game *g);
void	find_player(t_game *g);
int		fail(char *msg);
int		init_game(t_game *g);
void	move_player(t_game *g, int dx, int dy);
void	on_key(mlx_key_data_t k, void *param);
void	free_game(t_game *g);

#endif
