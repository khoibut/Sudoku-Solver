#include<iostream>
#include<vector>
using namespace std;
int Problems[82][82]={0};
const int BoardSize=10;
void PrintBoard(int Board[BoardSize][BoardSize])
{
  cout<<"╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗"<<endl; //The top of the board
  for(int k=1;k<BoardSize;k++) //Print the board out
  {
    for(int h=1;h<BoardSize;h++)
    {
      if(h==1)
      {
        cout<<"║"; //Print the thicker outer border
      }
      cout<<" "<<Board[k][h]<<" ";
      if(h%3==0) //Print thick border every 3 columns
      {
        cout<<"║";
      }else //Print think border every columns
      {
        cout<<"│";
      }
    }
    if(k==9)
    {
      cout<<endl<<"╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝"<<endl; //Print the bottom border
    }
    else if(k%3==0)
    {
      cout<<endl<<"╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣"<<endl; //Print the thick border every 3 rows
    }
    else
    {
      cout<<endl<<"╟───┼───┼───╫───┼───┼───╫───┼───┼───╢"<<endl; //Print the think border every rows
    }
  }
}


void clrscr() //Clear screen
{
	system("cls");
}
bool CheckSolved(int Board[BoardSize][BoardSize]) //Check if the board is solved
{
  for(int i=1;i<BoardSize;i++)
  {
    for(int j=1;j<BoardSize;j++)
    {
      if(Board[i][j]==0) //If there are 0 then the board is not solved
      {
        return false;
      }
    }
  }
  return true;
}


bool CheckComp(int Boardtemp[BoardSize][BoardSize],int x,int row, int col) //Check if the number is compatible in the spot
{
  if (Boardtemp[row][col]!=0)
  {
    return false;
  }
  int startrow,starcol,endrow,endcol,count=0; //Used to mark the 3x3 area the X is beloned to
  int BoardMap[BoardSize][BoardSize]={{0,1,2,3,4,5,6,7,8,9},
                                      {1,1,1,1,2,2,2,3,3,3},
                                      {2,1,1,1,2,2,2,3,3,3},
                                      {3,1,1,1,2,2,2,3,3,3},
                                      {4,4,4,4,5,5,5,6,6,6},
                                      {5,4,4,4,5,5,5,6,6,6},
                                      {6,4,4,4,5,5,5,6,6,6},
                                      {7,7,7,7,8,8,8,9,9,9},
                                      {8,7,7,7,8,8,8,9,9,9},
                                      {9,7,7,7,8,8,8,9,9,9}}; //A general map of all the areas of the board
  switch(BoardMap[row][col]) //Get where the start and the end of the area that X belonged to
  {
    case 1:
      startrow=1;
      starcol=1;
      endrow=3;
      endcol=3;
      break;
    case 2:
      startrow=1;
      starcol=4;
      endrow=3;
      endcol=6;
      break;
    case 3:
      startrow=1;
      starcol=7;
      endrow=3;
      endcol=9;
      break;
    case 4:
      startrow=4;
      starcol=1;
      endrow=6;
      endcol=3;
      break;
    case 5:
      startrow=4;
      starcol=4;
      endrow=6;
      endcol=6;
      break;
    case 6:
      startrow=4;
      starcol=7;
      endrow=6;
      endcol=9;
      break;
    case 7:
      startrow=7;
      starcol=1;
      endrow=9;
      endcol=3;
      break;
    case 8:
      startrow=7;
      starcol=4;
      endrow=9;
      endcol=6;
      break;
    case 9:
      startrow=7;
      starcol=7;
      endrow=9;
      endcol=9;
      break;
  }
  Boardtemp[row][col]=x; //Enter the x into temporary board
  for(int i=1;i<BoardSize;i++)
  {
    if(Boardtemp[row][i]==x) //Check if any number in the same row or column same with the X
    {
      count++;
    }
    if(Boardtemp[i][col]==x)
    {
      count++;
    }
  }
  if(count>2)
  {
    Boardtemp[row][col]=0;
    return false;
  }
  count=0;
  for(int i=startrow;i<=endrow;i++) //Check the 3x3 area than x belonged to for any repeatance
  {
    for(int j=starcol;j<=endcol;j++)
    {
      if(Boardtemp[i][j]==x)
      {
        count++;
      }
    }
  }
  if(count>1)
  {
    Boardtemp[row][col]=0;
    return false;
  }
  return true;
}
void Solve(int Board[BoardSize][BoardSize],int x)
{
  if(CheckSolved(Board)==true) //Print the solved board out if found
  {
    PrintBoard(Board);
  }else
  {
    for(int i=1;i<BoardSize;i++) //Backtracking checking every number that fit in the position without breaking sudoku law
    {
      Board[Problems[x][x]][Problems[x+1][x]]=0;
      if(CheckComp(Board,i,Problems[x][x],Problems[x+1][x])==true)
      {
        Board[Problems[x][x]][Problems[x+1][x]]=i;
        Solve(Board,x-1);
        Board[Problems[x][x]][Problems[x+1][x]]=0;
      }
    }
  }
}
int main()
{
  clrscr();
  int goal=0;
  int Board[BoardSize][BoardSize]={0};
  for(int i=1;i<BoardSize;i++) //Get datas for the board
  {
    for(int j=1;j<BoardSize;j++)
    {
      PrintBoard(Board);
      cout<<i<<","<<j<<":";
      cin>>Board[i][j];
      if(Board[i][j]==0)
      {
        goal++;
        Problems[goal][goal]=i;
        Problems[goal+1][goal]=j;
      }
      clrscr(); //Reset the screen
    }
  }
  Solve(Board,goal);
  return 0;
}
