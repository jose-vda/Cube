/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	get_minimap_cell_color(t_game *game, int row, int col, char c)
{
	if (c == '1' || c == '2' || c == '3' || c == ' ')
		return (MINIMAP_WALL);
	if (c == 'D')
		return (door_is_open(game, row, col) ? MINIMAP_FLOOR : MINIMAP_DOOR);
	if (c == 'K')
		return (MINIMAP_KEY);
	if (c == 'X')
		return (MINIMAP_EXIT);
	if (c == 'P')
		return (cell_is_pushed(game, row, col) ? MINIMAP_FLOOR : MINIMAP_PUSH);
	return (MINIMAP_FLOOR);
}

static void	draw_minimap_cell(t_game *game, int start_row, int start_col,
		int i, int j)
{
	int		sx;
	int		sy;
	char	c;
	int		row;
	int		col;

	sx = MINIMAP_OFFSET_X + j * MINIMAP_TILE;
	sy = MINIMAP_OFFSET_Y + i * MINIMAP_TILE;
	row = start_row + i;
	col = start_col + j;
	if (col >= ft_strlen(game->map[row]))
		return ;
	c = game->map[row][col];
	draw_rect(&game->img, sx, sy, MINIMAP_TILE, MINIMAP_TILE,
		get_minimap_cell_color(game, row, col, c));
}

void	draw_minimap_grid(t_game *game, int start_row, int start_col)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_MAX_H && start_row + i < game->map_height)
	{
		j = 0;
		while (j < MINIMAP_MAX_W && start_col + j < game->map_width)
		{
			draw_minimap_cell(game, start_row, start_col, i, j);
			j++;
		}
		i++;
	}
}
