#include "main.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */

void rev_string(char *s)
{
	int count = 0, i;
	char *start = s, *end = s;
	char temp;

	while (*end != '\0')
	{
		count++;
		end++;
	}
	end--; /* Move 'end' to the last non-null character */

	for (i = 0; i < count / 2; i++)
	{
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}
