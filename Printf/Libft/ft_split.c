/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:59:06 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/20 15:34:14 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	count_words(char *s, char c)
{
	size_t	i;
	int		count;
	int		in_word;

	count = 0;
	i = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			in_word = 0;
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

char	**free_matrix(char **matrix, int index)
{
	while (index > 0)
		free(matrix[--index]);
	free(matrix);
	return (NULL);
}

char	**create_matrix(char **matrix, char const *s, char c, int index)
{
	int	i;
	int	start;
	int	length;

	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		length = 0;
		while (s[i] != c && s[i] != '\0')
		{
			length++;
			i++;
		}
		if (length > 0)
		{
			matrix[index] = ft_substr(s, start, length);
			if (matrix[index] == NULL)
				return (free_matrix(matrix, index), NULL);
			index++;
		}
	}
	return (matrix[index] = NULL, matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		words;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	words = count_words((char *)s, c);
	matrix = (char **)malloc(sizeof(char *) * (words + 1));
	if (matrix == NULL)
		return (NULL);
	matrix = create_matrix(matrix, s, c, index);
	if (matrix == NULL)
		return (NULL);
	return (matrix);
}

// {
// 	free(matrix[--words]);
// }
// free(matrix);

// int main(void)
// {
//     char    **result_my;
//     int     i;

//     i = 0;
//     result_my = ft_split("\t\t\t\thello!\t\t\t\tHELLO HELLO", '\t');
//     while (result_my[i] != NULL)
//     {
//         printf("Mein ergebniss : %s\n", result_my[i]);
//         i++;
//     }
//     return (0);

// }