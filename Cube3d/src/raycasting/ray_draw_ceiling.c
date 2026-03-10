/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw_ceiling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	draw_ceiling_scanline(t_game *g, int x, int y, int tw, int th,
	double rdx, double rdy)
{
	double	row_dist;
	double	ceil_x;
	double	ceil_y;
	int		tex_x;
	int		tex_y;
	int		color;

	row_dist = (0.5 * HEIGHT) / (HEIGHT / 2 - y);
	ceil_x = g->player.x + row_dist * rdx;
	ceil_y = g->player.y + row_dist * rdy;
	tex_x = (int)(ceil_x * tw) % tw;
	tex_y = (int)(ceil_y * th) % th;
	if (tex_x < 0)
		tex_x += tw;
	if (tex_y < 0)
		tex_y += th;
	color = g->ceiling_tex.addr[tex_y * (g->ceiling_tex.line_len / 4) + tex_x];
	color = apply_fog(g, color, row_dist);
	if (g->theme_sunny)
		color = apply_sunny_brighten(color);
	put_pixel(&g->img, x, y, color);
}

void	draw_textured_ceiling(t_game *g, int x, int draw_start,
	double ray_dir_x, double ray_dir_y)
{
	int	tw;
	int	th;
	int	y;

	if (!g->has_ceiling_tex)
		return ;
	tw = g->ceiling_tex.width;
	th = g->ceiling_tex.height;
	y = 0;
	while (y < draw_start)
	{
		draw_ceiling_scanline(g, x, y, tw, th, ray_dir_x, ray_dir_y);
		y++;
	}
}
