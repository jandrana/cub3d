/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:12:17 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/25 17:10:30 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_char_in_set(char const *set, char const c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*strim;

	if (!str || !set)
		return (NULL);
	len = ft_strlen(str);
	start = 0;
	while (str[start] && ft_char_in_set(set, str[start]))
		start++;
	end = len - 1;
	while (end >= 0 && ft_char_in_set(set, str[end]))
		end--;
	if (start > end)
		return (ft_strdup(""));
	strim = ft_substr(str, start, end - start + 1);
	return (strim);
}
