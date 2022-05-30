#include<stdio.h>
#include <stdbool.h>

#define COMPUTER 1 
#define HUMAN 2 

#define side 3 

#define COMPUTERMOVE 'O' 
#define HUMANMOVE 'X' 


void showBoard(char board[][side])
{ 
	printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]); 
	printf("-----------\n"); 
	printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]); 
	printf("-----------\n"); 
	printf(" %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);  
} 
void showInstructions() 
{ 
	printf("\nChoose a numbere from 1 to 9 \n\n"); 
	
	printf("1 | 2 | 3 \n"); 
	printf("----------\n"); 
	printf("4 | 5 | 6 \n"); 
	printf("-----------\n"); 
	printf(" 7 | 8 | 9 \n\n"); 
} 

// A function to initialise the game 
void initialise(char board[][side]) 
{	

	for (int i=0; i<side; i++) 
	{ 
		for (int j=0; j<side; j++) 
			board[i][j] = ' '; 
	} 
} 

bool gameOver(char board[][side]) 
{ 
    for (int i=0; i<side; i++) 
	{ 
		if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') || 
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') ||
            (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
            (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
			return (true); 
	} 
	return(false); 
}

// Function to calculate best score
int minimax(char board[][side], bool isAI)
{
    int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	 if(isAI == true)
			{
				bestScore = -999;
				for(int i=0; i<side; i++)
				{
					for(int j=0; j<side; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, false);
							board[i][j] = ' ';
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
            {
				bestScore = 999;
				for (int i = 0; i < side ;i++)
				{
					for (int j = 0; j < side; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = HUMANMOVE;
							score = minimax(board, true);
							board[i][j] = ' ';
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
        
}

// Function to calculate best move
int bestMove(char board[][side])
{
    int x = -1, y = -1;
	int score = 0, bestScore = -999;

    for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				score = minimax(board, false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

void play(int turn)
{
    char board[side][side];
    int x=0, y=0;

    initialise(board);
    showInstructions();
    
    while (gameOver(board) == false)
    
    {

    int n;

    if(turn == COMPUTER)
    {
        n = bestMove(board);
		x = n / side;
		y = n % side;
		board[x][y] = COMPUTERMOVE;
        showBoard(board);
        turn = HUMAN;

    }

    else if (turn == HUMAN)
    {
          printf("\n\nEnter the position 1 to 9 = ");
          scanf("%d",&n);
          x = n / side;
		  y = n % side; 
          if(board[x][y] == ' ' )
          {
              board[x][y] = HUMANMOVE; 
              showBoard(board);
              turn = COMPUTER;

          }

     } 
    }
}

int main() 
{ 
	    printf("Tic-Tac-Toe\n"); 
       
            char choice;
            printf("Do you want to start first?(y/n) : ");
            scanf(" %c", &choice);

            if(choice=='n')
                play(COMPUTER);
            else if(choice=='y')
                play(HUMAN);
            else
                printf("Invalid choice\n"); 

         
        
	    return (0); 
} 
