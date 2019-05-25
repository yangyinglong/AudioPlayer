#include <stdio.h>


// maximum length of list
#define MAX_LENGTH 40
// maximum length of filename
#define MAX_FILE_LENGTH 255
// for scanf() input filename
#define GET_NAME "%255s"


int main(int argc, char const *argv[])
{
	// i is index of array, l is length of list
	unsigned int i, l; 
	// pointer of list
	char * p_list[MAX_LENGTH];
	// list of filename, +1 is store string's terminator
	char f_list[MAX_LENGTH][MAX_FILE_LENGTH+1];
	// to accept meun selection
	int select_value;
	// to exit main program
	char exit_switch = 1;
	char * p_temp;

	l = 0;
	for (int i = 0; i < MAX_LENGTH; ++i)
	{
		p_list[i] = NULL;
		f_list[i][0] = 0;
	}

	do 
	{
		puts("Please select the operation command: ");
		puts("(1) Add new file");
		puts("(2) Delete files from the list");
		puts("(3) Print playlist");
		puts("(4) Sort by filename");
		puts("(9) eixt");
		
		scanf("%1d", &select_value);
		getchar();
		switch (select_value) {
			case 1: 
			{
				if (l < MAX_LENGTH)
				{
					puts("Please input filename: ");
					for (int i = 0; i < MAX_LENGTH; ++i)
					{
						if (!f_list[i][0])
						{
							while (!scanf(GET_NAME, f_list[i]))
							{
								puts("Please enter the correct file name!");
							}
							p_list[l++] = f_list[i];
							break;
						}
					}
				}
				else
				{
					puts("File list is full!");
				}
				break;
			}
			case 2: 
			{
				puts("Please input the file number: ");
				scanf("%u", &i);
				if (i > 0 && i < l)
				{
					*p_list[--i] = NULL;
					while (i < l - 1)
					{
						p_list[i] = p_list[++i];

					}
					l--;
				}
				else
				{
					puts("The file number does not exist!");
				}
				break;
			}
			case 3: 
			{
				for (int i = 0; i < l; ++i)
				{
					printf("%d : %s\n", i + 1, p_list[i]);
				}
				break;
			}
			case 4:
			{
				if (l > 1)
				{
					for (int i = 0; i < l - 1; ++i)
					{
						for (int j = i + 1; j < l; ++j)
						{
							if (*p_list[i] > *p_list[j])
							{
								p_temp = p_list[i];
								p_list[i] = p_list[j];
								p_list[j] = p_temp;
							}
						}
					}
				}
				break;
			}
			case 9: 
			{
				exit_switch = 0;
				break;
			}
			default:
			{
				puts("Please input 1-9!");
				break;
			}
		}
	} while (exit_switch);




	return 0;
}