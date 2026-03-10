/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	has_cub_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len <= 4)
		return (0);
	return (ft_strcmp(filename + len - 4, ".cub") == 0);
}

char	*trim_newline(char *line)
{
	int	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

char	*skip_spaces(char *s)
{
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	return (s);
}

int	parse_rgb(char *s, int *out)
{
	int	r;
	int	g;
	int	b;

	s = skip_spaces(s);
	r = ft_atoi(s);
	while (*s && *s != ',' && *s != ' ')
		s++;
	if (*s == ',')
		s++;
	else
		s = skip_spaces(s);
	g = ft_atoi(s);
	while (*s && *s != ',' && *s != ' ')
		s++;
	if (*s == ',')
		s++;
	else
		s = skip_spaces(s);
	b = ft_atoi(s);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	*out = (r << 16) | (g << 8) | b;
	return (1);
}
