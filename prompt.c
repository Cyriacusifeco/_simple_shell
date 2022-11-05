#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#define BUFFSIZE 1024

/**
 * read_textfile - read a txt file.
 * @filename: File to be read.
 * @letters: number of characters to be read.
 * Return: decimal value
 */

char *read_line(void);


void print_prompt(void)
{
	char *buffer;

	while(1)
	{
		printf("#cisfun$: ");
		buffer = read_line();
		printf("%s\n", buffer);
	}

	free(buffer);

}

char *read_line(void)
{
	int buff_size = BUFFSIZE, mem_position = 0, c;
	char *buffer;

	buffer = malloc(sizeof(char) * buff_size);
	if (buffer == NULL)
	{
		printf("allocation error");
		exit (EXIT_FAILURE);
	}

	while (buffer)
	{
		c = getchar();

		if (c == EOF || c == '\n')
		{
			buffer[mem_position] = '\0';
			return (buffer);
		}
		else
			buffer[mem_position] = c;
		mem_position++;

		if (mem_position >= buff_size)
		{
			buff_size += BUFFSIZE;

			buffer = realloc(buffer, buff_size);
				if (buffer == NULL)
				{
					printf("allocation error");
					exit (EXIT_FAILURE);
				}
		}
	}
return (buffer);
}
