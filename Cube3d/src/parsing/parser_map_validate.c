/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_validate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	cell_is_outside(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map_height)
		return (1);
	if (x < 0 || x >= game->map_width)
		return (1);
	if (x >= ft_strlen(game->map[y]))
		return (1);
	return (game->map[y][x] == ' ');
}

static int	check_cell_neighbors(t_game *game, int i, int j)
{
	if (cell_is_outside(game, i - 1, j))
	{
		printf("Error\nMap not closed (hole near %d,%d)\n", j, i);
		return (0);
	}
	if (cell_is_outside(game, i + 1, j))
	{
		printf("Error\nMap not closed (hole near %d,%d)\n", j, i);
		return (0);
	}
	if (cell_is_outside(game, i, j - 1))
	{
		printf("Error\nMap not closed (hole near %d,%d)\n", j, i);
		return (0);
	}
	if (cell_is_outside(game, i, j + 1))
	{
		printf("Error\nMap not closed (hole near %d,%d)\n", j, i);
		return (0);
	}
	return (1);
}

static int	is_walkable_cell(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'K' || c == 'X' || c == 'P');
}

int	validate_map_closed(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width && game->map[i][j])
		{
			if (is_walkable_cell(game->map[i][j]))
			{
				if (!check_cell_neighbors(game, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
