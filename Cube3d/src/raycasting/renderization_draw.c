/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderization_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:41:24 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_img *img, int x0, int y0, int w, int h, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			put_pixel(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

void	clear_image(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	int		start_row;
	int		start_col;
	double	px;
	double	py;

	if (!game->show_minimap || !game->map)
		return ;
	start_row = (int)(game->player.y - 0.5) - MINIMAP_MAX_H / 2;
	start_col = (int)(game->player.x - 0.5) - MINIMAP_MAX_W / 2;
	if (start_row < 0)
		start_row = 0;
	if (start_col < 0)
		start_col = 0;
	draw_minimap_grid(game, start_row, start_col);
	px = MINIMAP_OFFSET_X + (game->player.x - 0.5 - start_col) * MINIMAP_TILE;
	py = MINIMAP_OFFSET_Y + (game->player.y - 0.5 - start_row) * MINIMAP_TILE;
	draw_rect(&game->img, (int)(px - 1), (int)(py - 1), 3, 3, MINIMAP_PLAYER);
}

void	draw_crosshair(t_game *game)
{
	int	cx;
	int	cy;
	int	i;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	i = -2;
	while (i <= 2)
	{
		put_pixel(&game->img, cx + i, cy, 0x00FF00);
		put_pixel(&game->img, cx, cy + i, 0x00FF00);
		i++;
	}
}
