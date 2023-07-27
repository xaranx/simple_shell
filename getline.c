#include "main.h"

/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
	size_t new_size;
	char *new_lineptr;

	if (*lineptr == NULL)
	{
		/* Set the initial size to BUFSIZE or j if j is larger */
		*n = (j > BUFSIZE) ? j : BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		/* Calculate the new size needed to store the buffer */
		new_size = (*n < j) ? j : *n;

		/* Allocate memory for the new lineptr buffer */
		new_lineptr = malloc(new_size);
		if (new_lineptr == NULL)
		{
			/* Memory allocation failed; handle the error as needed */
			/* For example, you can print an error message and exit the program. */
			/* For simplicity, we just return without changing anything. */
			return;
		}

		/* Copy the contents of the buffer to the new lineptr buffer */
		_strcpy(new_lineptr, buffer);

		/* Free the old buffer */
		free(*lineptr);

		/* Set the lineptr and size to the new values */
		*lineptr = new_lineptr;
		*n = new_size;
	}
}


/**
 * get_line - Read inpt from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t i;
	ssize_t retval;
	char *buffer = NULL;
	ssize_t bufsize = 0;
	int c;
	char *new_buffer;
	ssize_t new_size;

	/* Check if lineptr is NULL or *lineptr is NULL (i.e., no buffer is provided) */
	if (lineptr == NULL || *lineptr == NULL)
	{
		/* Use a default buffer size if n is NULL or *n is 0 */
		if (n == NULL || *n == 0)
		{
			bufsize = BUFSIZE;
		}
		else
		{
			bufsize = *n;
		}

		/* Allocate memory for the buffer */
		buffer = malloc(bufsize);
		if (buffer == NULL)
		{
			return (-1); /* Memory allocation failed */
		}
	}
	else
	{
		/* Reuse the existing buffer and size if provided */
		buffer = *lineptr;
		bufsize = *n;
	}

	/* Read characters from the stream until a newline is encountered */

	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		/* Resize the buffer if needed */
		if (i >= bufsize - 1)
		{
			new_size = bufsize + BUFSIZE;
			new_buffer = realloc(buffer, new_size);
			if (new_buffer == NULL)
			{
				free(buffer);
				return (-1); /* Memory allocation failed */
			}
			buffer = new_buffer;
			bufsize = new_size;
		}

		/* Store the character in the buffer */
		buffer[i++] = (char)c;
	}

	/* Null-terminate the buffer to form a valid C-string */
	buffer[i] = '\0';

	/* Update lineptr and n to reflect the new buffer and size */
	*lineptr = buffer;
	*n = bufsize;

	/* Return the number of characters read (excluding the newline) */
	retval = (i > 0 || c == '\n') ? i : -1;

	return (retval);
}


/**
 * read_line - reads the input string.
 *
 * @i_eof: return value of getline function
 * Return: input string
 */

char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
