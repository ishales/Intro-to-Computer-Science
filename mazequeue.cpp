//
//  main.cpp
//  hw2 q3
//
//  Created by Isabelle Hales on 2/7/23.
//  Copyright © 2023 CS32. All rights reserved.
//

#include <iostream>
#include <string>
#include <queue>
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
    queue<Coord> coordQueue;      // declare a queue of Coords
    
    Coord start(sr, sc);
    coordQueue.push(start); // Push the starting coordinate (sr,sc) onto the enqueue item at back of queue
    maze[sr][sc] = '>'; // update maze[sr][sc] to indicate that the algorithm has encountered it
    
    while(!coordQueue.empty()){                     //While the queue is not empty,
        Coord current = coordQueue.front();         //gets top of queue for current coord
        coordQueue.pop();                           //Pop the front coordinate off the queue.
        
        //If the current is equal to the ending coordinate, then we've solved the maze!
        if(current.r() == er && current.c() == ec){
            return true;
        }
        
        //try to move EAST
        if(maze[current.r()][current.c()+1] == '.'){
            Coord newC(current.r(), current.c()+1);
            coordQueue.push(newC);
            maze[current.r()][current.c()+1] = '>';
        }
        
        //try to move NORTH
        if(maze[current.r()-1][current.c()] == '.'){
            Coord newC(current.r()-1, current.c());
            coordQueue.push(newC);
            maze[current.r()-1][current.c()] = '>';
        }

        //try to move WEST
        if(maze[current.r()][current.c()-1] == '.'){
            Coord newC(current.r(), current.c()-1);
            coordQueue.push(newC);
            maze[current.r()][current.c()-1] = '>';
        }

        //try to move SOUTH
        if(maze[current.r()+1][current.c()] == '.'){
            Coord newC(current.r()+1, current.c());
            coordQueue.push(newC);
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
