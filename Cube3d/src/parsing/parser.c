/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:57:35 by jose-vda         #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	validate_extension(char *filename)
{
	if (!has_cub_extension(filename))
	{
		printf("Error\nInvalid extension (use .cub)\n");
		return (0);
	}
	return (1);
}

static int	open_map_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file\n");
		return (-1);
	}
	return (fd);
}

static int	check_identifiers_and_map(t_game *game, char **map_lines,
		int map_count, int *got)
{
	if (!got[0] || !got[1] || !got[2] || !got[3] || got[4] == 0 || got[5] == 0)
	{
		free_map_lines_arr(map_lines, map_count);
		printf("Error\nMissing identifier (NO, SO, EA, WE, F, C)\n");
		return (0);
	}
	if (map_count == 0)
	{
		free(map_lines);
		printf("Error\nEmpty map\n");
		return (0);
	}
	if (!build_game_map(game, map_lines, map_count))
		return (0);
	return (1);
}

int	parse_map(t_game *game, char *filename)
{
	int		fd;
	int		got[6];
	char	**map_lines;
	int		map_count;

	if (!validate_extension(filename))
		return (0);
	fd = open_map_file(filename);
	if (fd < 0)
		return (0);
	init_parse_state(game, got);
	map_lines = malloc(sizeof(char *) * 4096);
	if (!map_lines)
	{
		close(fd);
		return (0);
	}
	if (!read_file_loop(fd, game, got, map_lines, &map_count))
	{
		free_map_lines_arr(map_lines, map_count);
		close(fd);
		return (0);
	}
	close(fd);
	return (check_identifiers_and_map(game, map_lines, map_count, got));
}
