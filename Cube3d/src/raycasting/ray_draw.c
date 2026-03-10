/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	apply_door_tint(int color)
{
	int	r;
	int	gr;
	int	b;

	r = ((color >> 16) & 0xFF) * 6 / 10;
	gr = ((color >> 8) & 0xFF) * 4 / 10;
	b = (color & 0xFF) * 3 / 10;
	return ((r << 16) | (gr << 8) | b);
}

static void	get_fog_params(t_game *g, double *fog_dist, int *fr, int *fg, int *fb)
{
	if (g->theme_sunny)
	{
		*fog_dist = FOG_DIST_SUNNY;
		*fr = FOG_R_SUNNY;
		*fg = FOG_G_SUNNY;
		*fb = FOG_B_SUNNY;
	}
	else
	{
		*fog_dist = FOG_DIST;
		*fr = FOG_R;
		*fg = FOG_G;
		*fb = FOG_B;
	}
}

static void	compute_fog_components(int color, int fog_r, int fog_g, int fog_b,
		double fog, int *fr, int *fg, int *fb)
{
	int		r;
	int		b;

	r = (color >> 16) & 0xFF;
	*fg = (color >> 8) & 0xFF;
	b = color & 0xFF;
	*fr = (int)(r * (1.0 - fog) + fog_r * fog);
	*fg = (int)(*fg * (1.0 - fog) + fog_g * fog);
	*fb = (int)(b * (1.0 - fog) + fog_b * fog);
	if (*fr > 255)
		*fr = 255;
	if (*fg > 255)
		*fg = 255;
	if (*fb > 255)
		*fb = 255;
}

static int	apply_fog(t_game *g, int color, double perp_dist)
{
	double	fog;
	double	fog_dist;
	int		fog_r;
	int		fog_g;
	int		fog_b;
	int		fr;
	int		fg;
	int		fb;

	get_fog_params(g, &fog_dist, &fog_r, &fog_g, &fog_b);
	if (perp_dist >= fog_dist)
		return ((fog_r << 16) | (fog_g << 8) | fog_b);
	fog = perp_dist / fog_dist;
	if (fog > 1.0)
		fog = 1.0;
	compute_fog_components(color, fog_r, fog_g, fog_b, fog, &fr, &fg, &fb);
	return ((fr << 16) | (fg << 8) | fb);
}

static int	apply_sunny_brighten(int color)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * 13 / 10;
	g = ((color >> 8) & 0xFF) * 13 / 10;
	b = (color & 0xFF) * 12 / 10;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

void	draw_textured_wall(t_game *g, int x, int draw_start, int draw_end,
		int line_height, int tex_id, int tex_x, int is_door, double perp_dist)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0 * g->tex[tex_id].height / line_height;
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (g->tex[tex_id].height - 1);
		tex_pos += step;
		color = g->tex[tex_id].addr[tex_y * (g->tex[tex_id].line_len / 4)
			+ tex_x];
		if (is_door)
			color = apply_door_tint(color);
		color = apply_fog(g, color, perp_dist);
		if (g->theme_sunny)
			color = apply_sunny_brighten(color);
		put_pixel(&g->img, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_img *img, int x, int y_start, int y_end, int color)
{
	int	y;

	y = y_start;
	while (y < y_end)
	{
		put_pixel(img, x, y, color);
		y++;
	}
}

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
