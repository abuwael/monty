#include "monty.h"

/**
 * getline2 - read a line of input from a file stream
 * and store it in a dynamically allocated buffer.
 * @lineptr: pointer to buffer in which to store input
 * @n: pointer to size of buffer
 * @stream: file stream from which to read input
 *
 * Return: number of characters read, or -1 on error
 */
ssize_t getline2(char **lineptr, size_t *n, FILE *stream)
{
	int c;
	size_t pos = 0;
	char *new_ptr;

	if (!lineptr || !n || !stream)
	{
		errno = EINVAL;
		return (-1);
	}

	if (*lineptr == NULL)
	{
		*lineptr = malloc(128);
		if (*lineptr == NULL)
			return (-1);
		*n = 128;
	}

	while ((c = getc(stream)) != EOF)
	{
		if (pos + 1 >= *n)
		{
			size_t new_size = *n + (*n >> 2);

			if (new_size < 128)
				new_size = 128;
			new_ptr = realloc(*lineptr, new_size);
			if (new_ptr == NULL)
				return (-1);
			*n = new_size;
			*lineptr = new_ptr;
		}
		((unsigned char *)(*lineptr))[pos++] = c;

		if (c == '\n')
			break;
	}
	(*lineptr)[pos] = '\0';
	return (pos == 0 ? (-1) : (ssize_t)pos);
}
