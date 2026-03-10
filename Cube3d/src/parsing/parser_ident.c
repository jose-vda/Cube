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
