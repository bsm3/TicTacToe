#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void _clear(void)
{
	FILE * pf;

	pf = fopen("score.txt", "w+");
	fprintf(pf, "Player 1 | Player 2");
	fprintf(pf, "\n");
	fprintf(pf, "   %d     |    %d", 0, 0);
	fclose(pf);
}

void _score(int player, int end)
{
	int a;
	FILE * pf;
	pf = fopen("score.txt", "r+");
	char ch;

	while(ch != '\n')
		ch = fgetc(pf);
	
	ch = fgetc(pf);
	while(!isdigit(ch))
		ch = fgetc(pf);
	
	a = atoi(&ch);

	if(player == 1 && end != 0)
	{
		a += 1;
		fseek(pf, -1, SEEK_CUR);
		fprintf(pf, "%d", a);
		fclose(pf);
		return;
	}

	ch = fgetc(pf);
	while(!isdigit(ch))
		ch = fgetc(pf);
	a = atoi(&ch);

	if(player == 2 && end != 0)
	{
		a += 1;
		fseek(pf, -1, SEEK_CUR);
		fprintf(pf, "%d", a);
	}

	fclose(pf);
}

void _read()
{

    FILE * pf;
	pf = fopen("score.txt", "r");
	char ch;
		
		 while((ch = fgetc(pf)) != EOF)
		 {
		 	printf("%c", ch);
		 }

	fclose(pf);
}

int main(void)
{
	int row, col, player, go, end = 0;
	char count = '1', c;

	char arr[3][3] = {{'0'}};

	for(int i = 0; i < 3; i++)
	{
		int j = 0;
		while(3 > j)
		{
			arr[i][j] = count++;
			j++;
		}
	}

	for(int i = 0; i < 9 && end == 0; i++)
	{
		printf("-------------\n");
		printf("| %c | %c | %C | \n", arr[0][0], arr[0][1], arr[0][2]);
		printf("-------------\n");
		printf("| %c | %c | %C |\n", arr[1][0], arr[1][1], arr[1][2]);
		printf("-------------\n");
		printf("| %c | %c | %C | \n", arr[2][0], arr[2][1], arr[2][2]);
		printf("-------------\n");

		player = (i%2)+1;

		do
		{
			if(player == 1)
			{
				printf("Player %d, enter a number %c:\n", player, (player ==1)? 'X' : 'O');
				go = rand() % 9 + 1;
				sleep(1);
			}
			else
			{
				printf("Player %d, enter a number %c: ", player, (player ==1)? 'X' : 'O');
				scanf("%d", &go);
			}
			go--;
			row = go / 3;
			col = go % 3;

		} while(0 > go || go > 8 || arr[row][col] > '9');

		arr[row][col] = (player == 1)? 'X' : 'O';

		if(i > 3)
		{
			if((arr[0][0] == arr[1][1] && arr[0][0] == arr[2][2])||
				(arr[0][2] == arr[1][1] && arr[0][2] == arr[2][0]))
					end = 1;
			for(int j = 0; j < 3; j++)
			{
				if((arr[j][0] == arr[j][1] && arr[j][0] == arr[j][2]) ||
					(arr[0][j] == arr[1][j] && arr[0][j] == arr[2][j]))
						end = 1;
			}
		}
		system("clear");

	}

	for(int i = 0; i < 3; i++)
	{
		printf("-------------\n|");
		for(int j = 0; j < 3; j++)
		{
			printf(" %c |", arr[i][j]);
		}
		printf("\n");
	}
	printf("-------------\n");
	putchar('\n');
	if((player == 1 || player == 2) && (end != 0))
		printf("***Player %d wins***\n", player);
	else
		printf("Game Draws\n");
	
	printf("\nScore\n---------------------\n");
	_score(player, end);
	_read();
	printf("\n\n");
	printf("(s)Save\n(d)Delete\n\nEnter yuor choice: ");
	scanf(" %c", &c);

	switch(c)
	{
		case 'd':
			_clear();
			printf("Deleted\n");
			break;
		case 's':
			printf("Saved\n");
			break;
		default:
			printf("Exit\n");
	}


	return 0;
}
