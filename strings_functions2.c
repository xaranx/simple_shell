#include "main.h"

/**
 * _strdup - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */

char *_strdup(const char *s)
{
	char *new;
	size_t len, i;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));

	if (new == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
	{
		new[i] = s[i];
	}

	return (new);
}


/**
 * _strlen - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */

int _strlen(const char *s)
{
	const char *ptr = s;

	while (*ptr)
	{
		ptr++;
	}

	return (ptr - s);
}



/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */

int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j;

	for (i = 0; str[i]; i++)
	{
		int found = 0;

		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				found = 1;
				break;
			}
		}

		if (!found)
			return (0);
	}

	return (1);
}


/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */

char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		/* Check if any characters in the string match the delimiter */
		if (cmp_chars(str, delim))
			return (NULL);

		splitted = str; /* Store the first address of the string */
		i = _strlen(str);
		str_end = &str[i]; /* Store the last address of the string */
	}

	str_start = splitted;
	if (str_start == str_end) /* Check if we have reached the end of the string */
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/* Breaking loop to find the next token */
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;

		/* Replacing delimiter with a null character */
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}

		/* Check if the string is not empty and not equal to the delimiter */
		if (bool == 0 && *splitted)
			bool = 1;
	}

	/* Check if the string is equal to the delimiter */
	if (bool == 0)
		return (NULL);

	return (str_start);
}




/**
 * _isdigit - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */

int _isdigit(const char *s)
{
	unsigned int i = 0;

	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
