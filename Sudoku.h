#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <set>
#include <iostream>
using namespace std;
#include <math.h>     

class Sudoku  : public Searchable{
	
	vector<vector<std::set<int>>> board;

public:
	int size;
	Sudoku(int sizeIn) : size(sizeIn) {
		
			set<int> s;
			for(int i=1; i<=size; i++){
				s.insert(i);
			}

			vector<set<int>> row;

			for (int j = 0; j < sizeIn; ++j)
			{
				row.push_back(s);  // putting set of (1-9) in a row
			}

			for (int i = 0; i < sizeIn; ++i)
			{

				board.push_back(row);  //putting each row in columns
			}

	}

	
	const int getSquare(int row, int col) const{

		if(board[row][col].size() != 1) {
			return -1;
		}

		return *board[row][col].begin();
	}
	
	vector<vector<std::set<int>>> getBoard(){
	return board;		
		}

	
	bool setSquare(int row, int col, int value)	{
		
		board[row][col].clear();
		board[row][col].insert(value);
		bool edited = true;
			while (edited)
				{
				edited = false;
				for (int r = 0; r < board.size(); ++r)
					for (int c = 0; c < board.size(); ++c)
						if (board[r][c].size() == 1)						//finding the first square with 1 element
							{
							int temp = *(board[r][c].begin());			//saving this element as temporary variable
							
							
							for (int k = 0; k < board.size(); k++)				//clearing rows so none of the squares in the same row have this element anymore
							if (r != k)
							{
								int tempSize = board[k][c].size();
								board[k][c].erase(temp);
									if (tempSize != board[k][c].size())
									edited = true;
									if (board[k][c].size() == 0)
									{
									return false;
									}
							}
							
							for (int k = 0; k < board.size(); k++)			//clearing cols so none of the squares in the same col have this element anymore
							if (c != k)
							{
								int tempSize = board[r][k].size();
								board[r][k].erase(temp);
								if (tempSize != board[r][k].size())
								edited = true;
								if (board[r][k].size() == 0)
								{
									return false;
								}
							}
							
		for (int k = (r/(int)sqrt(board.size()))*(int)sqrt(board.size()); k < (r/(int)sqrt(board.size()))*(int)sqrt(board.size())+(int)sqrt(board.size()); k++)				//clearing 3x3 box so none of the squares in the same box have this element anymore
			for (int m = (c/(int)sqrt(board.size()))*(int)sqrt(board.size()); m < (c/(int)sqrt(board.size()))*(int)sqrt(board.size())+(int)sqrt(board.size()); m++)
				if (r != k || c != m)
				{
					int tempSize = board[k][m].size();
					board[k][m].erase(temp); 
					if (tempSize != board[k][m].size())
						edited = true;
						if (board[k][m].size() == 0) {
						return false;
					}
				}
			}
		}
	
	return true;
	}
			

	bool isSolution() const {
			for (int j = 0; j < size; ++j)
			{
				for (int i = 0; i < size; ++i)
				{
					if(board[j][i].size() !=1){
						return false;
					}
				}
			}
	return true;
				
	}

	void write(ostream & os ) const{					//displays the sudoku board

		for (int i = 0; i < size; ++i)
				{
					for (int j = 0; j < size; ++j)
					{
						if(getSquare(i,j) == -1){
								os<<" ";
						}else {
								os<<getSquare(i,j);
						}
					}
					os<<endl;
		}
  			
	}

	int heuristicValue() const {				//displays heuristic value
		int value = 0;
		for(int r = 0; r < size; r++){
			for(int c = 0; c < size; c++){
				if(board[c][r].size() > 1){
					value++;
				}
			}
		}
		return value;
	}
    
	vector<unique_ptr<Searchable> > successors() const{
    	
		vector<unique_ptr<Searchable>> successors;
		set<int>::iterator iter;
		bool flag = false;
		for(int r = 0; r < size; r++){
			for(int c = 0; c < size; c++){
    			
				if(getSquare(r,c) == -1){
					for(iter = board[r][c].begin(); iter!=board[r][c].end(); iter++){
						Sudoku * copy = new Sudoku(*this);

						if(copy->setSquare(r,c,*iter)){
							successors.emplace_back(copy);
						} else {
							delete copy;
						}
					} 
					flag=true;
					break;
				}
				//if(flag) break;
			}
			if(flag) break;
    		
		}
	

	if(successors.size() == 1 && !successors[0].get()->isSolution()){
		return successors[0].get()->successors();
	}
	return successors;
}


};





#endif
