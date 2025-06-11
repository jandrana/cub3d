/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:53:17 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/05 14:07:24 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(WHITESPACE, line[i]))
			return (0);
		i++;
	}
	return (1);
}

t_line_type	get_line_type(char *line)
{
	char	*trimmed;
	int		i;

	trimmed = ft_strtrim(line, WHITESPACE);
	if (!trimmed || is_empty_line(trimmed))
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
		if (!ft_strchr(VALID_MAP_CHARS, line[i]))
			return (free(trimmed), INVALID_LINE);
	}
	return (free(trimmed), MAP_LINE);
}

void	*free_array(char ***array)
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
	return (NULL);
}

int	array_len(char **array)
{
	int	len;

	len = -1;
	while (array[++len])
		;
	return (len);
}
