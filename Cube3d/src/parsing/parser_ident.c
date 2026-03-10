/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ident.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	set_tex_path(t_game *game, int idx, char *path, int *got, int gi)
{
	game->tex_path[idx] = ft_strdup(skip_spaces(path));
	got[gi] = 1;
}

static int	parse_tex_no_so_ea_we(t_game *game, char *line, int *got)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !game->tex_path[TEX_NORTH])
		set_tex_path(game, TEX_NORTH, line + 3, got, 0);
	else if (ft_strncmp(line, "SO ", 3) == 0 && !game->tex_path[TEX_SOUTH])
		set_tex_path(game, TEX_SOUTH, line + 3, got, 1);
	else if (ft_strncmp(line, "EA ", 3) == 0 && !game->tex_path[TEX_EAST])
		set_tex_path(game, TEX_EAST, line + 3, got, 2);
	else if (ft_strncmp(line, "WE ", 3) == 0 && !game->tex_path[TEX_WEST])
		set_tex_path(game, TEX_WEST, line + 3, got, 3);
	else
		return (0);
	return (1);
}

static int	parse_tex_w2_w3_ct(t_game *game, char *line)
{
	if (ft_strncmp(line, "W2 ", 3) == 0 && !game->tex_path[TEX_WALL2])
	{
		game->tex_path[TEX_WALL2] = ft_strdup(skip_spaces(line + 3));
		return (1);
	}
	else if (ft_strncmp(line, "W3 ", 3) == 0 && !game->tex_path[TEX_WALL3])
	{
		game->tex_path[TEX_WALL3] = ft_strdup(skip_spaces(line + 3));
		return (1);
	}
	else if (ft_strncmp(line, "CT ", 3) == 0 && !game->ceiling_tex_path)
	{
		game->ceiling_tex_path = ft_strdup(skip_spaces(line + 3));
		return (1);
	}
	return (0);
}

static int	parse_tex_identifier(t_game *game, char *line, int *got)
{
	if (parse_tex_no_so_ea_we(game, line, got))
		return (1);
	if (parse_tex_w2_w3_ct(game, line))
		return (1);
	return (0);
}

static int	parse_color_identifier(t_game *game, char *line, int *got)
{
	if ((ft_strncmp(line, "F ", 2) == 0) && game->floor_color == -1)
	{
		if (!parse_rgb(line + 2, &game->floor_color))
			return (0);
		got[4] = 1;
		return (1);
	}
	if ((ft_strncmp(line, "C ", 2) == 0) && game->ceiling_color == -1)
	{
		if (!parse_rgb(line + 2, &game->ceiling_color))
			return (0);
		got[5] = 1;
		return (1);
	}
	return (0);
}

int	parse_identifier(t_game *game, char *line, int *got)
{
	line = trim_newline(line);
	if (!line || !line[0])
		return (1);
	if (parse_tex_identifier(game, line, got))
		return (1);
	if (parse_color_identifier(game, line, got))
		return (1);
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W'
		|| line[0] == '0' || line[0] == '1' || line[0] == '2' || line[0] == '3'
		|| line[0] == 'D' || line[0] == 'K' || line[0] == 'X' || line[0] == 'P'
		|| line[0] == ' ')
		return (2);
	return (0);
}
