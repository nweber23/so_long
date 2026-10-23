/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:18:50 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*read_file(int fd)
{
	char	*all;
	char	*line;
	char	*tmp;

	all = ft_strdup("");
	line = get_next_line(fd);
	while (all && line)
	{
		tmp = ft_strjoin(all, line);
		free(all);
		free(line);
		all = tmp;
		line = get_next_line(fd);
	}
	free(line);
	return (all);
}

static int	has_ber_extension(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	return (len > 4 && !ft_strcmp(path + len - 4, ".ber"));
}

char	**read_map(char *path)
{
	int		fd;
	char	*all;
	char	**map;

	if (!has_ber_extension(path))
		return (fail("map file must have the .ber extension"), NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (fail("cannot open map file"), NULL);
	all = read_file(fd);
	close(fd);
	if (!all || !*all)
		return (free(all), fail("empty or unreadable map"), NULL);
	if (all[0] == '\n' || ft_strnstr(all, "\n\n", ft_strlen(all)))
		return (free(all), fail("map contains an empty line"), NULL);
	map = ft_split(all, '\n');
	free(all);
	if (!map)
		fail("memory allocation failed");
	return (map);
}
