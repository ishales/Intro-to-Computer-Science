//
//  StudentWorld.h
//  p3
//
//  Created by Isabelle Hales on 2/23/23.
//  Copyright © 2023 CS32. All rights reserved.
//

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include <string>
#include <vector>
#include "GameWorld.h"
#include "Board.h"

class GameObject;
class Player;
class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
  ~StudentWorld();                      //destructor for class
  virtual int init();
  virtual int move();
  virtual void cleanUp();

  Board getBoard() const;             //keeps track of the board that we were using
  Player* getPeach() const;            //allows us to access peach player
  Player* getYoshi() const;            //allows us to access yoshi player
  int getBankBalance() const; // get # of coins in the bank
  void changeCentralBank(int coins); // add coins to the bank
  void reset_bank_coins();   // reset # of coins in the bank to zero
  Actor* getSquare(int x, int y);     //find square from actors
  void deleteSquare(int x, int y);  //remove a square
  void addDropS(int x, int y);      //adds a dropping square (bowser)
  void swapCoins();      //swaps player coins
  void swapStars();      //swaps player stars
  Player*  pickWinner() const;          //determines winner of game
  void addVortex(int x, int y, int dir);        //add a vortex to board
  void destroyVortex(Actor* vx);               //properly get rid of vortex

    
    
private:
    //vector of pointers to each actors
    std::vector<Actor*> m_items;
    Player* peachSW;
    Player* yoshiSW;
    Board myBoard;
    int centralBankAcc;                //central bank account
};

#endif // STUDENTWORLD_H_
