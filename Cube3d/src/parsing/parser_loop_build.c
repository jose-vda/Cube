/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_loop_build.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	compute_map_width(t_game *game, char **map_lines, int map_count)
{
	int	i;

	game->map_width = 0;
	i = 0;
	while (i < map_count)
	{
		if (ft_strlen(map_lines[i]) > game->map_width)
			game->map_width = ft_strlen(map_lines[i]);
		i++;
	}
}

static int	alloc_and_fill_map(t_game *game, char **map_lines, int map_count)
{
	int	i;

	game->map = malloc(sizeof(char *) * (map_count + 1));
	if (!game->map)
	{
		free_tex_paths(game);
		free_map_lines_arr(map_lines, map_count);
		return (0);
	}
	i = 0;
	while (i < map_count)
	{
		game->map[i] = map_lines[i];
		i++;
	}
	game->map[map_count] = NULL;
	free(map_lines);
	return (1);
}

int	build_game_map(t_game *game, char **map_lines, int map_count)
{
	game->map_height = map_count;
	compute_map_width(game, map_lines, map_count);
	if (!alloc_and_fill_map(game, map_lines, map_count))
		return (0);
	if (!find_and_set_spawn(game) || !validate_map_closed(game))
	{
		free_map_only(game->map, game->map_height);
		game->map = NULL;
		free_tex_paths(game);
		return (0);
	}
	return (1);
}
