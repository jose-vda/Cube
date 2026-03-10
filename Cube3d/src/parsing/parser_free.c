/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	free_tex_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->tex_path[i])
		{
			free(game->tex_path[i]);
			game->tex_path[i] = NULL;
		}
		i++;
	}
	if (game->ceiling_tex_path)
	{
		free(game->ceiling_tex_path);
		game->ceiling_tex_path = NULL;
	}
}

void	free_map_only(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map_lines_arr(char **map_lines, int map_count)
{
	while (map_count--)
		free(map_lines[map_count]);
	free(map_lines);
}
