#include<iostream>
using namespace std;

void GameBoard(char **console, int width, int height)
{
    int i_count= 0, j_count= 0;
	for(i_count= 0; i_count<width; i_count++) //loop to print one wall of board using + sign

    {
		cout<<"+";
		for(j_count= 0; j_count<height; j_count++) 
      //loop to print underscore as spaces between two walls
        {
		    
        if(console[i_count][j_count] != 'A' &&console[i_count][j_count] != 'B')
			 console[i_count][j_count]= '_';
             cout<<console[i_count][j_count];
        }
		cout<<"x"<<endl; //print other wall of board using x sign
	}
}
int ThrowToken(char **console, char player_ID[])
{
    int tok_throw= 0;
    do
    {
        cout<<player_ID<<" turn."<<endl;
        cout<<"Drop your token.(1-7):  ";
        cin>>tok_throw;
        if((tok_throw >= 1) && (tok_throw <= 7) && (console[0][tok_throw-1]== '_'))
        {
            break;
        }
        cout<<"Error: Invalid input. Drop your token again."<<endl;
    }
    while(1);
    return tok_throw-1;
  //we are returning tok_throw-1 because the index of array starts from 0 and not 1.
}

void CheckBox(char **console, char player1_tag, int rows, int tok_throw)
{ 
    
    int span= rows-1, player_Turn= 0;
    do
    {
        if(console[span][tok_throw]== '_')
        {
            console[span][tok_throw]= player1_tag;
            player_Turn= 1;
        }
        else
        {
          if (span > 0)
            --span;
        }
    }
    while(player_Turn != 1); 
} 
int FourMatch(char **console, char player_tag, int rows, int columns)
{

  int victory= 0;
  //subtracting 1 from dimensions as array index begins from 0.
  rows= rows-1;
  columns =columns-1; 
  
  for(int i= rows ; i >= 0; --i)
  {
        for(int j = columns; j >= 0; --j)
		{
			// check main diagonal win
			if((console[i][j]== player_tag)&&(console[i-1][j-1] == player_tag)&&(console[i-2][j-2]== player_tag)&&(console[i-3][j-3]== player_tag))
			{
				 victory= 1;
			}

      		//check second diagonal win
			if((console[i][j]== player_tag)&&(console[i-1][j+1]== player_tag)&&(console[i-2][j+2]== player_tag)&&(console[i-3][j+3]== player_tag))
			{
				victory= 1;
			}
			
            //check right to left win
			if((console[i][j]== player_tag)&&(console[i][j-1]== player_tag)&&(console[i][j-2]== player_tag)&&(console[i][j-3]== player_tag ))
			{
				victory= 1;
			}
      
		//check left to right win
			if((console[i][j]== player_tag)&&(console[i][j+1]== player_tag)&&(console[i][j+2]== player_tag)&&(console[i][j+3]== player_tag))
			{
				victory= 1;
			}
      //check bottom to top win
			if((console[i][j]== player_tag)&&(console[i-1][j]== player_tag)&&(console[i-2][j] == player_tag)&&(console[i-3][j] == player_tag))
			{	
				victory= 1;
			}
		}
	}
    return victory;
}          

int StopInput(char **console)
{
    //restrictig user when slot filled
    int no_space= 0;
    for(int i= 0; i<7; i++)
    {
        if(console[0][i]!= '_')
        {
            no_space++;
        }
    }
    return no_space;
}

void Winner( char playerID[] )
{
    cout<<"Congratulations! "<<playerID<<" wins."<<endl;
}
int PlayAgain(char **console)
{
    //if user wants to play again, generate an empty board again
	int replay;
	cout<<"Would you like to restart? Enter 1 to replay or any other integer to exit.";
	cin>>replay;
	if(replay==1)
	{
		for(int i= 0; i<6; i++)
		{
			for(int j= 0; j<7; j++)
			{
				console[i][j] = '_';
			}
		}
	}
	else
    {
		cout<<"Game Over!"<<endl;
    }
    return replay;
}
int main()
{
    int tok_throw= 0, win= 0, replay= 1, full= 0;
    char player1_name[20], player2_name[20];
    char player1_tag= 'A', player2_tag= 'B';
    cout<<"Welcome to Connect 4. "<<"In Connect4, you have to join 4 of your tokens by dropping them into the container before your opponent does.";
    cout<<"\nPlayer One name: ";
    cin>>player1_name;
    cout<<"Player Two name: ";
    cin>>player2_name;
    int rows = 6, cols = 7;
    char** console= new char*[rows];
    for(int i= 0; i<rows; i++)
    {
        console[i]= new char[cols];
    }

  GameBoard(console,rows,cols);
    do
    {
     
      tok_throw=ThrowToken(console, player1_name);
      CheckBox(console, 'A', rows, tok_throw);
      GameBoard(console,rows,cols);
      if (FourMatch(console, player1_tag, rows, cols))
      {
         Winner(player1_name);
         replay= PlayAgain(console);
        
      if (replay !=1)
				
      break;
      }
    
		tok_throw= ThrowToken(console, player2_name);
		CheckBox(console, 'B', rows, tok_throw);
		GameBoard(console, rows, cols);

      //checking if player has won
	  if (FourMatch(console, player2_tag , rows, cols)) 
      {
        Winner( player2_name);
        replay= PlayAgain(console);
        if (replay !=1)
        {
            break;
        }
      }
		//full= StopInput(console);
		if(full==6)
		{
			cout<<"The board is full, it is a draw!"<<endl;
			replay= PlayAgain(console);
		}
	}
      while(replay);
      return 0;
}