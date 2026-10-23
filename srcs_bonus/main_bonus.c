/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	fail(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (fail("usage: ./so_long_bonus <map.ber>"));
	ft_bzero(&g, sizeof(g));
	g.map = read_map(argv[1]);
	if (!g.map)
		return (1);
	if (validate_map(&g) || init_enemies(&g))
	{
		free_game(&g);
		return (1);
	}
	if (init_game(&g))
	{
		free_game(&g);
		return (1);
	}
	mlx_loop(g.mlx);
	free_game(&g);
	return (0);
}
