#include "main.h"

/**
 * get_len - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */

int get_len(int n)
{
	int length;
	unsigned int n1;

	if (n == 0)
		return (1);

	length = (n < 0) ? 1 : 0; /* Initialize length to 1 if n is negative */

	/* Convert negative number to positive for calculations */
	n1 = (n < 0) ? -n : n;

	/* Calculate the length using a loop */
	while (n1 > 0)
	{
		length++;
		n1 /= 10;
	}

	return (length);
}


/**
 * aux_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */

char *aux_itoa(int n)
{
	int n1 = n;
	int i;
	int length = get_len(n);
	int isNegative = 0;
	char *buffer;

	if (n < 0)
	{
		isNegative = 1;
		n1 = -n;
		length++;
	}

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == NULL)
		return (NULL);

	buffer[length] = '\0';

	for (i = length - 1; i >= isNegative; i--)
	{
		buffer[i] = (n1 % 10) + '0';
		n1 /= 10;
	}

	if (isNegative)
		buffer[0] = '-';

	return (buffer);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */

int _atoi(char *s)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	/* Check for a negative sign */
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}

	/* Convert the string to an integer */
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}

	return (result * sign);
}
