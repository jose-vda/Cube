/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != '3'
			&& line[i] != 'D' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != 'K' && line[i] != 'X' && line[i] != 'P'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static void	set_dir_plane(t_player *p, double dx, double dy,
		double px, double py)
{
	p->dir_x = dx;
	p->dir_y = dy;
	p->plane_x = px;
	p->plane_y = py;
}

static void	set_dir_from_spawn(char c, t_player *p)
{
	if (c == 'N')
		set_dir_plane(p, 0, -1, 0.66, 0);
	else if (c == 'S')
		set_dir_plane(p, 0, 1, -0.66, 0);
	else if (c == 'E')
		set_dir_plane(p, 1, 0, 0, 0.66);
	else if (c == 'W')
		set_dir_plane(p, -1, 0, 0, -0.66);
}

static void	set_player_spawn(t_game *game, int i, int j, char c)
{
	game->player.x = j + 0.5;
	game->player.y = i + 0.5;
	set_dir_from_spawn(c, &game->player);
	game->map[i][j] = '0';
}

static int	scan_row_for_spawn(t_game *game, int i, int *count)
{
	int	j;

	j = 0;
	while (j < game->map_width && game->map[i][j])
	{
		if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
			|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
		{
			if (*count)
			{
				printf("Error\nDuplicate player spawn\n");
				return (0);
			}
			(*count)++;
			set_player_spawn(game, i, j, game->map[i][j]);
		}
		j++;
	}
	return (1);
}

int	find_and_set_spawn(t_game *game)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < game->map_height)
	{
		if (!scan_row_for_spawn(game, i, &count))
			return (0);
		i++;
	}
	if (count == 0)
	{
		printf("Error\nNo player spawn (N/S/E/W) in map\n");
		return (0);
	}
	return (1);
}

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
