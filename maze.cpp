//
//  maze.cpp
//  maze hw3
//
//  Created by Isabelle Hales on 2/15/23.
//  Copyright © 2023 CS32. All rights reserved.
//

#include <iostream>
#include <string>

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

bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
//If the start location is equal to the ending location, then we've solved the maze, so return true.
if(sr == er && sc == ec){
    return true;
}

//Mark the start location as visted.
maze[sr][sc] = '>';

//check each location
//check east
//If the location one step in that direction (from the start location) is unvisited,
if(maze[sr+1][sc] != '>'){
    //then call pathExists starting from that location
    // If that returned true, then return true.
    if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec)){
        return true;
    }
}

//check north
//If the location one step in that direction (from the start location) is unvisited,
if(maze[sr][sc-1] != '>'){
    //then call pathExists starting from that location
    // If that returned true, then return true.
    if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec)){
        return true;
    }
}

//check west
//If the location one step in that direction (from the start location) is unvisited,
if(maze[sr-1][sc] != '>'){
    //then call pathExists starting from that location
    // If that returned true, then return true.
    if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec)){
        return true;
    }
}

//check south
//If the location one step in that direction (from the start location) is unvisited,
if(maze[sr][sc+1] != '>'){
    //then call pathExists starting from that location
    // If that returned true, then return true.
    if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec)){
        return true;
    }
}

    return false;
}


