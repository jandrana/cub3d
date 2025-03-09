/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:09:18 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/09 20:22:07 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*double_to_str(double num, char *buffer, size_t size)
{
	int		integer_part;
	int		decimal_part;
	char	*int_str;
	char	temp[32];

	integer_part = (int)num;
	decimal_part = (int)((num - integer_part) * 10 + 0.5);
	int_str = ft_itoa(integer_part);
	if (!int_str)
		return (NULL);
	ft_strlcpy(temp, int_str, sizeof(temp));
	ft_strlcat(temp, ".", sizeof(temp));
	free(int_str);
	int_str = ft_itoa(decimal_part);
	if (!int_str)
		return (NULL);
	ft_strlcat(temp, int_str, sizeof(temp));
	free(int_str);
	ft_strlcpy(buffer, temp, size);
	return (buffer);
}

void	format_fps(char *dest, size_t size, double fps)
{
	char	num_str[16];

	if (size < 1)
		return ;
	dest[0] = '\0';
	ft_strlcpy(dest, "FPS: ", size);
	if (double_to_str(fps, num_str, sizeof(num_str)))
		ft_strlcat(dest, num_str, size);
}
