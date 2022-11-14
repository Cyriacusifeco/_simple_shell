#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
#define BUFFSIZE 1024
#define STR_DELIM " \t\r\n\a"
extern char **environ;

/**
 * print_prompt - promts the user for command line argument.
 * Return: decimal value
 */

char *read_line(void);
char **split_str(char *buffer);
int execute_cmd(char **str_token);


void print_prompt(void)
{
	char *buffer;
	char **str_token;
	int status;

	while(status)
	{
		printf("#cisfun$: ");
		buffer = read_line();
		str_token = split_str(buffer);
		status = execute_cmd(str_token);
	}

	free(buffer);
	free(str_token);

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

char **split_str(char *buffer)
{
	int mem_position = 0;
	int buff_size = BUFFSIZE;
	char *token;

	char **str_token = malloc(buff_size * sizeof(char *));

	if (!str_token)
	{
		printf("allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(buffer, STR_DELIM);

	while (token != NULL)
	{
		str_token[mem_position] = token;
		mem_position++;

		if (mem_position >= buff_size)
		{
			buff_size += BUFFSIZE;

			str_token = realloc(str_token, (sizeof(char *) * buff_size));

			if (str_token == NULL)
			{
				printf("failed to allocate memory\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, STR_DELIM);
	}

	str_token[mem_position] = '\0';

return (str_token);
}

int execute_cmd(char **str_token)
{
	int pid, status = 1;

	char *enVar[] = { "HOME=/root", "PATH=/bin:/sbin", NULL};

	pid = fork();

	if (pid == 0)
	{
		if (execve(str_token[0], str_token, enVar) == -1)
		{
			perror("execution failure");
			return (1);

		}

	}

	else if (pid < 0)
	{
		perror("error forking");
	}

	else
	{
		wait(NULL);
	}

return (status);
}
