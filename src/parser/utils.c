/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:17 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/18 19:45:24 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_line_type	get_line_type(char *line)
{
	char	*trimmed;
	int		i;

	trimmed = ft_strtrim(line, " \t\r\v\f\n");
	if (!trimmed)
		return (free(trimmed), EMPTY_LINE);
	if (!ft_strncmp(trimmed, "NO", 2) || !ft_strncmp(trimmed, "SO", 2)
		|| !ft_strncmp(trimmed, "WE", 2) || !ft_strncmp(trimmed, "EA", 2))
		return (free(trimmed), TEXTURE_LINE);
	if (!ft_strncmp(trimmed, "F", 1))
		return (free(trimmed), COLOR_LINE);
	if (!ft_strncmp(trimmed, "C", 1))
		return (free(trimmed), COLOR_LINE);
	i = -1;
	while (line[++i])
	{
		if (!ft_strchr("NSEW10 ", line[i]))
			return (free(trimmed), INVALID_LINE);
	}
	return (MAP_LINE);
}

void	free_array(char ***array)
{
	int	i;

	i = -1;
	if (*array)
	{
		while ((*array)[++i])
			free((*array)[i]);
		free(*array);
		*array = NULL;
	}
}

int	array_len(char **array)
{
	int	len;

	len = -1;
	while (array[++len])
		;
	return (len);
}

bool	check_color_value(t_color color)
{
	if (color.r < 0 || color.g < 0 || color.b < 0)
		return (1);
	if (color.r > 255 || color.g > 255 || color.b > 255)
		return (1);
	return (0);
}
