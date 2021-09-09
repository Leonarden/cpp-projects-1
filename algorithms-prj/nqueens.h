#ifndef NQUEENS_H_INCLUDED
#define NQUEENS_H_INCLUDED
#include <iostream>

//Abstract class
using namespace std;


class NBacktracking {
public:

    NBacktracking( int n, int defValue){
      N = n;
      defVal = defValue;
//board = this->generateBoard();
      ld = new int[n*n];
      rd = new int[n*n];
      cl = new int[n*n];
    }
virtual ~NBacktracking(){}
virtual bool solve(){}
virtual bool solveUtil(int **board,int level){}
int** generateBoard(){
int **b = new int*[N];

for(int i = 0; i < N; ++i) {
    b[i] = new int[N];

}
for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            b[i][j] = defVal;

return b;
}
virtual void printSolution() {}
virtual void deleteBoard();
//protected:
int N;
int defVal = 0;
int **board;
int *ld;
int *rd;
int *cl;


};


void NBacktracking::deleteBoard(){
for(int i = 0; i < N; ++i) {
    delete [] board[i];
}
delete [] board;

}

//NQueens problem
class NQueens : public NBacktracking {
public:
    NQueens(int n,int defValue):NBacktracking(n,defValue){}
    virtual ~NQueens() {}
    virtual bool solve();
    virtual bool solveUtil(int **board, int col);
    virtual void printSolution();



};

bool NQueens::solveUtil(int **board, int col){


	/* base case: If all queens are placed
	then return true */
	if (col >= N)
		return true;

	/* Consider this column and try placing
	this queen in all rows one by one */
	for (int i = 0; i < N; i++) {
		/* Check if the queen can be placed on
		board[i][col] */
		/* A check if a queen can be placed on
		board[row][col].We just need to check
		ld[row-col+n-1] and rd[row+coln] where
		ld and rd are for left and right
		diagonal respectively*/
		if ((ld[i - col + N - 1] != 1 &&
				rd[i + col] != 1) && cl[i] != 1) {
			/* Place this queen in board[i][col] */
			board[i][col] = 1;
			ld[i - col + N - 1] =
						rd[i + col] = cl[i] = 1;

			/* recur to place rest of the queens */
			if (solveUtil(board, col + 1))
				return true;

			/* If placing queen in board[i][col]
			doesn't lead to a solution, then
			remove queen from board[i][col] */
			board[i][col] = 0; // BACKTRACK
			ld[i - col + N - 1] =
						rd[i + col] = cl[i] = 0;
		}
	}

	/* If the queen cannot be placed in any row in
		this colum col then return false */
	return false;


}

bool NQueens::solve(){

    board = this->generateBoard();
	if (solveUtil(board, 0) == false) {
		cout << "No solution to the problem" << endl;
		return false;
	}

	printSolution();
	this->deleteBoard();
	return true;

}

void NQueens::printSolution(){
int nsol = 0;
cout << " Backtracking solution for NQueens problem: " << N << endl;
for(int i=0;i<N;i++){
  for(int j=0;j<N;j++)
    if(board[i][j]!=1)
        cout << "-X-";
    else {
        nsol++;
        cout << "-Q-";
    }
 cout << endl;
}

cout << " End print solution, found " << nsol << " Queens";

}






#endif // NQUEENS_H_INCLUDED
