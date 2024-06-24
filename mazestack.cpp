//
//  main.cpp
//  hw 2
//
//  Created by Isabelle Hales on 2/1/23.
//  Copyright © 2023 CS32. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Coord
      {
        public:
          Coord(int r, int c) : m_row(r), m_col(c) {}
          int r() const { return m_row; }
          int c() const { return m_col; }
        private:
          int m_row;
          int m_col;
      };

// is there a path from (sr,sc) to (er,ec) through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;        //declare a stack of coords
    
    Coord start(sr, sc);
    coordStack.push(start); // Push the starting coordinate (sr,sc) onto the coordinate stack
    maze[sr][sc] = '>'; // update maze[sr][sc] to indicate that the algorithm has encountered it
    
    while(!coordStack.empty()){         //While the stack is not empty,
        Coord current = coordStack.top();      //sets top of stack to current coord
        coordStack.pop();                      //Pop the top coordinate off the stack.
        
        //If the current is equal to the ending coordinate, then we've solved the maze!
        if(current.r() == er && current.c() == ec){
            return true;
        }
        
        //try to move EAST
        if(maze[current.r()][current.c()+1] == '.' && maze[current.r()][current.c()+1] != '>'){
            Coord newC(current.r(), current.c()+1);
            coordStack.push(newC);
            maze[current.r()][current.c()+1] = '>';
        }
        
        //try to move NORTH
        if(maze[current.r()-1][current.c()] == '.' && maze[current.r()-1][current.c()] != '>'){
            Coord newC(current.r()-1, current.c());
            coordStack.push(newC);
            maze[current.r()-1][current.c()] = '>';
        }

        //try to move WEST
        if(maze[current.r()][current.c()-1] == '.' && maze[current.r()][current.c()-1] != '>'){
            Coord newC(current.r(), current.c()-1);
            coordStack.push(newC);
            maze[current.r()][current.c()-1] = '>';
        }

        //try to move SOUTH
        if(maze[current.r()+1][current.c()] == '.' && maze[current.r()+1][current.c()] != '>'){
            Coord newC(current.r()+1, current.c());
            coordStack.push(newC);
            maze[current.r()+1][current.c()] = '>';
        }
    }
    
    //There was no solution, so return false
    return false;
}

int main() {
    string maze[10] = {
        "XXXXXXXXXX",
        "X..X...X.X",
        "X.XXXX.X.X",
        "X.X.X..X.X",
        "X...X.XX.X",
        "XXX......X",
        "X.X.XXXX.X",
        "X.XXX....X",
        "X...X..X.X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 5,3, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
