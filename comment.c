#include "main.h"

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */


char *without_comment(char *in)
{
	int i, j;
	char *new_str;

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
			{
				/* Allocate memory for the new string without the comment */
				new_str = (char *)malloc((i + 1) * sizeof(char));
				if (new_str == NULL)
				{
					perror("Memory allocation error");
					exit(1);
				}

				/* Copy characters before the comment into the new string */
				for (j = 0; j < i; j++)
				{
					new_str[j] = in[j];
				}

				new_str[j] = '\0';
				free(in);
				return (new_str);
			}
		}
	}

	return (in);
}
