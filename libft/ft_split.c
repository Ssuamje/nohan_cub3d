/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 23:34:17 by hyungseok         #+#    #+#             */
/*   Updated: 2023/02/21 19:52:34 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t	is_c(char ch, char c)
{
	if (ch == c)
		return (1);
	return (0);
}

static size_t	count_s(const char *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] && is_c(s[i], c))
			i++;
		if (s[i] && !(is_c(s[i], c)))
		{
			while (s[i] && !(is_c(s[i], c)))
				i++;
			cnt++;
		}
	}
	if (cnt < 3)
		err_msg("error : improper elements");
	return (cnt);
}

static char	*ft_scpy(const char *s, char c, size_t i)
{
	size_t		cnt;
	char		*dest;

	cnt = 0;
	while (s[i] && !(is_c(s[i], c)))
	{
		i++;
		cnt++;
	}
	dest = (char *)malloc(sizeof(char) * (cnt + 1));
	if (!dest)
		return (0);
	i -= cnt;
	cnt = 0;
	while (s[i] && !(is_c(s[i], c)))
		dest[cnt++] = s[i++];
	dest[cnt] = 0;
	return (dest);
}

static char	**finalize_safe(char **result, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		free(result[i]);
	free(result);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**result;

	result = (char **)malloc(sizeof(char *) * (count_s(s, c) + 1));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_c(s[i], c))
			i++;
		if (s[i] && !(is_c(s[i], c)))
		{
			result[j] = ft_scpy(s, c, i);
			if (result[j] == 0)
				return (finalize_safe(result, j));
			j++;
			while (s[i] && !(is_c(s[i], c)))
				i++;
		}
	}
	result[j] = 0;
	return (result);
}
