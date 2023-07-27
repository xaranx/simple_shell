#include "main.h"

/**
 * _memcpy - copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */

void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	const unsigned char *char_ptr = (const unsigned char *)ptr;
	unsigned char *char_newptr = (unsigned char *)newptr;
	unsigned int i;

	/* Perform memory copying using pointer arithmetic */
	for (i = 0; i < size; i++)
	{
		char_newptr[i] = char_ptr[i];
	}
}


/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	unsigned int min_size;
	unsigned char *char_newptr;
	unsigned char *char_ptr;
	void *newptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
	{
		newptr = malloc(new_size);
		if (newptr == NULL)
			return (NULL);
	}
	else
	{
		newptr = malloc(new_size);
		if (newptr == NULL)
			return (NULL);

		char_ptr = (unsigned char *)ptr;
		char_newptr = (unsigned char *)newptr;

		/* Perform memory copying using pointer arithmetic */
		min_size = (old_size < new_size) ? old_size : new_size;
		for (i = 0; i < min_size; i++)
		{
			char_newptr[i] = char_ptr[i];
		}

		free(ptr);
	}

	return (newptr);
}



/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */

char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (new_size == 0)
	{
		if (ptr != NULL)
			free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
	{
		newptr = malloc(sizeof(char *) * new_size);
		if (newptr == NULL)
			return (NULL);
	}
	else
	{
		newptr = malloc(sizeof(char *) * new_size);
		if (newptr == NULL)
			return (NULL);

		for (i = 0; i < old_size && i < new_size; i++)
		{
			newptr[i] = ptr[i];
		}

		free(ptr);
	}

	return (newptr);
}
