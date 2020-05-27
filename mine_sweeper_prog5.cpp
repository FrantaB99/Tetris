#include <stdio.h>
#include <stdlib.h>

int mine_field_validity(char *mine_field_p, int size)
{

	int line_length;
	for(int i = 0; i < size; i++)
	{
		if(mine_field_p[i] == '\n')
		{
			line_length = i + 1;
			break;
		}
	}
	if(size % line_length)
	{
		return 1;
	}
	int new_line_quantity = size / line_length;
	for(int i = 1; i <= new_line_quantity; i++)
	{
		if(mine_field_p[(i * line_length) - 1] != '\n')
		{
			return 1;
		}
	}
	return 0;
}

int scanf_string(char **string_p, int *size)
{
	*string_p = (char *)malloc(sizeof(char));
	char tmp;
	while(scanf("%c", &tmp) != EOF)
	{
		if(tmp != '.' && tmp != '*' && tmp != '\n')
		{
			return 1;
		}
		(*size)++;
		*string_p = (char *)realloc(*string_p, (*size + 1) * sizeof(char));
		(*string_p)[*size - 1] = tmp;
	}
	return 0;
}

void printf_string(char *string_p, int size)
{
	for(int i = 0; i < size - 1; i++)
	{
		printf("%c", string_p[i]);
	}
	printf("\n");
}

void mine_checker(char *mine_field_p, int size)
{
	int line_length;
	for(int i = 0; i < size; i++)
	{
		if(mine_field_p[i] == '\n')
		{
			line_length = i + 1;
			break;
		}
	}
	char *counted_mines_p;
	counted_mines_p = (char *)malloc(size * sizeof(char));
	for(int i = 0; i < size; i++)
	{
		counted_mines_p[i] = '.';
		if(mine_field_p[i] == '\n')
		{
			counted_mines_p[i] = '\n';
			continue;
		}
		if(mine_field_p[i] == '*')
		{
			counted_mines_p[i] = '*';
			continue;
		}
		int mine_quantity = 0;
		for(int j = - 1; j < 2; j++)
		{
			int line = j * line_length;
			for(int k = - 1; k < 2; k++)
			{
				int index = i + line + k;
				if(index < 0 || index > size - 1)
				{
					continue;
				}
				char tmp_string_p[2];
				if(mine_field_p[index] == '*')
				{
					mine_quantity = mine_quantity + 1;
					sprintf(tmp_string_p, "%d", mine_quantity);
					counted_mines_p[i] = tmp_string_p[0];
				}
			}
		}
	}
	for(int i = 0; i < size; i++)
	{
		mine_field_p[i] = counted_mines_p[i];
	}
	free(counted_mines_p);
}

int main()
{
	char *mine_field_p;
	int size = 0;
	if(scanf_string(&mine_field_p, &size) ||
		mine_field_validity(mine_field_p, size))
	{
		printf("Invalid entry\n");
		return 1;
	}
	mine_checker(mine_field_p, size);
	printf_string(mine_field_p, size);
	free(mine_field_p);
	return 0;
}
