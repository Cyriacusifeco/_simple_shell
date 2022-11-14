#include "main.h"
#include <stdlib.h>
#include <stdio.h>
extern char **environ;

/**
 * main - check the code
 * 
 * Return: PATH.
 **/
int find_str(const char *str1, const char *str2);

void main(void)
{
	int i = 0;
	int p = 0;

	//Transversing through all environmental variables
	for (; *(environ[i]) != '\0'; i++)
	{


		p = find_str(environ[i], "PATH");

		if (p == 0) //i.e PATH is found
		{
			break;
		}

	}

	//result

	printf("%s\n", environ[i]);
}

int find_str(const char *str1, const char *str2)
{
	int i = 0, flag = 0;

	while (str2[i] != '\0')
	{

		if (str1[i] != str2[i])
		{
			flag = 1;
			break;
		}

		i++;
	}

return (flag);
}
