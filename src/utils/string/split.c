#include <minishell.h>

static char	*copy_words(char *s, int *i, char delim)
{
	char	*words;
	int		fin;

	while (s[*i] == delim)
		(*i)++;
	fin = *i;
	while (s[fin] != '\0' && s[fin] != delim)
		fin++;
	words = ft_substr(s, *i, (fin - *i));
	*i = fin;
	return (words);
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
//delimiter or end of the string, it means that we have found the end of a word
// We count a word
// We advance to the next character
// We return the total number of words found

static void	ft_free(char **ret, int j)
{
	while (j >= 0)
	{
		free(ret[j]);
		j--;
	}
	free(ret);
}
//It releases one by one the strings stored in ret from the last used position (j) to the first (0).
//It is done backwards because if something fails in ret[j], the previous ones were already reserved correctly.

char	**ft_split(char *s, char c)
{
	char	**ret;   // Array that will store the pointers to the words
	int		count;   // Total number of words we will find
	int		j;       // Index to traverse the array 'ret'
	int		str_index;       // Index to traverse the original string 's'

	j = 0;			// Initialize the array index
	i = 0;          // Initialize the index to traverse the original string

	count = count_words(s, c);
	ret = ft_calloc(count + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (j < count)
	{
		ret[j] = copy_words(s, &i, c);
		if (ret[j] == NULL)
		{
			ft_free(ret, j);
			return (NULL);
		}
		j++; 
	}
	return (ret);
}
// We count how many words there are separated by the delimiter 'c'.
// We reserve memory for 'count' pointers to words, plus 1 for the final NULL
// If the reservation fails, we return NULL
// Iterate as long as we have not copied all detected words
// Copy the next word from 's' using the current index 'i'.
// If there was an error while copying the word, we free all the memory already reserved
// Move to the next slot in the array
// Return the NULL-terminated array of words

int	main (void)
{
	char pepe[] = "hola que tal"; 
	char c = ' ';
	char **temp = ft_split(pepe,c);
	int i = 0;
	while (temp[i] != NULL)
	{
		printf("%s\n",temp[i]);
		i++;
	}
	return (0);
}
