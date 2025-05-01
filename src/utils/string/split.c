#include <minishell.h>

static char	*copy_word(char *str, int *position, char delimiter)
{
	char	*word;
	int		end;

	while (str[*position] == delimiter)
		(*position)++;
	end = *position;
	while (str[end] != '\0' && str[end] != delimiter)
		end++;
	word = ft_substr(str, *position, (end - *position));
	*position = end;
	return (word);
}
// Skip the initial delimiters (spaces)
// Save the beginning of the word
// Advance until we find the next delimiter or the end of the string
// Extract the word using ft_substr from *i to end - *i
// Update *i to continue after this word

static int	count_words(const char *str, char delim)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != delim) && (str[i + 1] == delim || str[i + 1] == '\0'))
		{
			count++;
		}
		i++;
	}
	return (count);
}
// Initialize word counter
// Start from the first character of the string
// We go through the whole string
// If the current character is not the delimiter and the next character is the
// delimiter or end of the string, it means that we have found the
// end of a word
// We count a word
// We advance to the next character
// We return the total number of words found

static void	ft_free(char **ret, int array_index)
{
	while (array_index >= 0)
	{
		free(ret[array_index]);
		array_index--;
	}
	free(ret);
}
// It releases one by one the strings stored in ret from the
// last used position (array_index) to the first (0).
// It is done backwards because if something fails in ret[array_index],
// the previous ones were already reserved correctly.

char	**ft_split(char *s, char c)
{
	char	**ret;
	int		word_count;
	int		array_index;
	int		str_index;

	array_index = 0;
	str_index = 0;
	word_count = count_words(s, c);
	ret = ft_calloc(word_count + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (array_index < word_count)
	{
		ret[array_index] = copy_word(s, &str_index, c);
		if (ret[array_index] == NULL)
		{
			ft_free(ret, array_index);
			return (NULL);
		}
		array_index++;
	}
	return (ret);
}
// We count how many words there are separated by the delimiter 'c'.
// We reserve memory for 'count' pointers to words, plus 1 for the final NULL
// If the reservation fails, we return NULL
// Iterate as long as we have not copied all detected words
// Copy the next word from 's' using the current index 'i'.
// If there was an error while copying the word,
// we free all the memory already reserved
// Move to the next slot in the array
// Return the NULL-terminated array of words
/*
int	main(void)
{
	char	pepe[] = " a    a ";
	char	c;
	char	**temp;
	int		i;

	c = ' ';
	temp = ft_split(pepe, c);
	i = 0;
	while (temp[i] != NULL)
	{
		printf("%s\n", temp[i]);
		free(temp[i]);
		i++;
	}
	free(temp);
	return (0);
}*/
