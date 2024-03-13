/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jade-haa <jade-haa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:41:23 by jade-haa          #+#    #+#             */
/*   Updated: 2024/01/09 15:28:42 by jade-haa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	*free_result(char **result, int elements)
// {
// 	int	i;

// 	i = 0;
// 	while (i < elements)
// 	{
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// 	return (NULL);
// }

// static int	subcounter(char const *s, char c)
// {
// 	int	count;
// 	int	inside_word;

// 	count = 0;
// 	inside_word = 0;
// 	while (*s)
// 	{
// 		if (*s == c)
// 		{
// 			if (inside_word)
// 			{
// 				count++;
// 				inside_word = 0;
// 			}
// 		}
// 		else
// 		{
// 			if (!inside_word)
// 				inside_word = 1;
// 		}
// 		s++;
// 	}
// 	if (inside_word)
// 		count++;
// 	return (count);
// }

// char	**do_split(char **new_array, char const *s, char c)
// {
// 	int	wordlen;
// 	int	j;
// 	int	i;
// 	int	max;

// 	max = subcounter(s, c);
// 	j = 0;
// 	i = 0;
// 	while (j < max)
// 	{
// 		while (s[i] == c && s[i] != '\0')
// 			i++;
// 		wordlen = 0;
// 		while (s[i + wordlen] != c && s[i + wordlen] != '\0')
// 			wordlen++;
// 		new_array[j] = malloc(wordlen + 1 * sizeof(char));
// 		if (!new_array[j])
// 			return (free_result(new_array, j));
// 		ft_strlcpy(new_array[j], &s[i], wordlen + 1);
// 		i += wordlen;
// 		j++;
// 	}
// 	new_array[j] = NULL;
// 	return (new_array);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**new_array;

// 	new_array = (char **)malloc((subcounter(s, c) + 1) * sizeof(char *));
// 	if (!new_array)
// 		return (NULL);
// 	return (do_split(new_array, s, c));
// }
static void	free_array(char **split_array, int i)
{
	int	x;

	x = 0;
	while (x < i)
	{
		free(split_array[x]);
		x++;
	}
	free(split_array);
}

int	count_delimiter(char const *s, char c)
{
	int	count;
	int	inside_word;

	count = 0;
	inside_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (inside_word)
			{
				count++;
				inside_word = 0;
			}
		}
		else
		{
			if (!inside_word)
				inside_word = 1;
		}
		s++;
	}
	if (inside_word)
		count++;
	return (count);
}

static int	copy_word(char **split_arr, const char *start, int len, int i)
{
	int	j;

	j = 0;
	split_arr[i] = (char *)malloc(len + 1);
	if (!split_arr[i])
	{
		free_array(split_arr, i);
		return (0);
	}
	while (j < len)
	{
		split_arr[i][j] = start[j];
		j++;
	}
	split_arr[i][j] = '\0';
	return (1);
}

static int	put_words(char **split_arr, const char *s, char c)
{
	int			len;
	const char	*start;
	int			i;
	int			check;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			start = s;
			while (*s && *s != c)
				s++;
			len = s - start;
			check = copy_word(split_arr, start, len, i);
			if (!check)
				return (0);
			i++;
		}
	}
	return (1);
}

char	**ft_split(char *s, char c)
{
	int		del_count;
	int		check;
	char	**split_arr;

	del_count = count_delimiter(s, c);
	split_arr = (char **)malloc((del_count + 1) * sizeof(char *));
	if (!split_arr)
		return (0);
	check = put_words(split_arr, s, c);
	if (!check)
		return (0);
	split_arr[del_count] = 0;
	return (split_arr);
}
// int	main(void)
// {
// 	const char *input = "asd-f-saf";
// 	// const char test[] = "tripouille";
// 	char delimiter = '-';
// 	char **substrings = ft_split(input, delimiter);
// 	int count = 0;
// 	// while (substrings[count])
// 	// {
// 	// 	printf("%s$\n", substrings[count]);
// 	// 	free(substrings[count++]);
// 	// }

// 	while (substrings[count] != NULL)
// 	{
// 		count++;
// 	}

// 	for (int i = 0; i <= count; i++)
// 	{
// 		printf("Substring %d: %s\n", i, substrings[i]);
// 		free(substrings[i]);
// 	}
// 	// printf("%s\n", substrings[count]);
// 	// printf("%zu\n", ft_strlen(substrings[0]));
// 	free(substrings);

// 	return (0);
// }