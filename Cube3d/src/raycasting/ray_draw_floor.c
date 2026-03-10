/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	get_floor_tex_dims(t_game *g, int *tw, int *th)
{
	if (g->theme_sunny)
	{
		*tw = g->floor_tex_sunny.width;
		*th = g->floor_tex_sunny.height;
	}
	else
	{
		*tw = g->floor_tex.width;
		*th = g->floor_tex.height;
	}
}

static int	get_floor_pixel_color(t_game *g, int tex_x, int tex_y,
	double row_dist, int use_sunny)
{
	int	color;

	if (use_sunny)
		color = g->floor_tex_sunny.addr[tex_y * (g->floor_tex_sunny.line_len / 4)
			+ tex_x];
	else
		color = g->floor_tex.addr[tex_y * (g->floor_tex.line_len / 4) + tex_x];
	color = apply_fog(g, color, row_dist);
	if (g->theme_sunny)
		color = apply_sunny_brighten(color);
	return (color);
}

static void	draw_floor_scanline(t_game *g, int x, int y, int tw, int th,
	double rdx, double rdy)
{
	double	row_dist;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;
	int		color;

	row_dist = (0.5 * HEIGHT) / (y - HEIGHT / 2);
	floor_x = g->player.x + row_dist * rdx;
	floor_y = g->player.y + row_dist * rdy;
	tex_x = (int)(floor_x * tw) % tw;
	tex_y = (int)(floor_y * th) % th;
	if (tex_x < 0)
		tex_x += tw;
	if (tex_y < 0)
		tex_y += th;
	color = get_floor_pixel_color(g, tex_x, tex_y, row_dist, g->theme_sunny);
	put_pixel(&g->img, x, y, color);
}

void	draw_textured_floor(t_game *g, int x, int draw_end,
	double ray_dir_x, double ray_dir_y)
{
	int	tw;
	int	th;
	int	y;

	get_floor_tex_dims(g, &tw, &th);
	y = draw_end;
	while (y < HEIGHT)
	{
		draw_floor_scanline(g, x, y, tw, th, ray_dir_x, ray_dir_y);
		y++;
	}
}
