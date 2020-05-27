#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char *sentence;
}line;

int init_string(char **string, int *length, int increment)
{
	int scanf_value;
	int size = 0;
	int index = 0;
	int delimiter_found = 0;
	*string = (char *)malloc(1);
	while(!delimiter_found)
	{
		*string = (char *)realloc(*string, size = size + increment);
		for(int i = 0; i < increment; i++)
		{
			char tmp;
			scanf_value = scanf("%c", &tmp);
			if(tmp == '\n' || scanf_value == EOF)
			{
				(*string)[index] = '\0';
				delimiter_found = 1;
				index++;
				break;
			}
			(*string)[index] = tmp;
			index++;
		}
	}
	*length = index;
	return scanf_value;
}

void init_lines(line **lines, int *length)
{
	int size = 0;
	int index = 0;
	*lines = (line *)malloc(1);
	while(index < 5)
	{
		char *tmp;
		int tmp_length;
		if(init_string(&tmp, &tmp_length, 10) == EOF)
		{
			break;
		}
		*lines = (line *)realloc(*lines, size = size + sizeof(line));
		(*lines)[index].sentence = (char *)malloc(tmp_length);
		strcpy((*lines)[index++].sentence, tmp);
	}
	*length = index;
}

void search_fraze(line *frazes, int frazes_length)
{
	char *searched_fraze;
	int searched_fraze_length;
	int found_frazes_quantity = 0;
	int *found_frazes;
	found_frazes = (int *)malloc(sizeof(int));
	init_string(&searched_fraze, &searched_fraze_length, 10);
	for(int i = 0; i < frazes_length; ++i)
	{

		size_t sentence_length = strlen(frazes[i].sentence) + 1;
		int delimiter_found = 0;
		int sentence_index = 0;
		int searched_fraze_index = 0;
		int matches = 0;
		while(sentence_index < sentence_length - 1 && searched_fraze_index < searched_fraze_length - 1)
		{
			if(frazes[i].sentence[sentence_index] == ':')
			{
				delimiter_found = 1;
				++sentence_index;
			}
			if(delimiter_found == 1)
			{
				matches = frazes[i].sentence[sentence_index++] == searched_fraze[searched_fraze_index++] ? matches + 1 : matches;
				if(matches == searched_fraze_length - 1)
				{
					found_frazes = (int *)realloc(found_frazes, ++found_frazes_quantity * sizeof(int));
					found_frazes[found_frazes_quantity - 1] = i;
				}
			}
		}
	}
	printf("Nalezeno: %d\n", found_frazes_quantity);
	for(int i = 0; i < found_frazes_quantity; ++i)
	{
		int found_frazes_index = found_frazes[i];
		printf("> %s\n", frazes[found_frazes_index].sentence + 1);
	}
}

int main()
{
	line *frazes;
	int frazes_length;
	printf("Casto hledane fraze:\n");
	init_lines(&frazes, &frazes_length);
	printf("Hledani:\n");
	search_fraze(frazes, frazes_length);
	return 0;
}
