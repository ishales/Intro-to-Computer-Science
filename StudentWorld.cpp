//
//  StudentWorld.cpp
//  p3
//
//  Created by Isabelle Hales on 2/23/23.
//  Copyright © 2023 CS32. All rights reserved.
//
#include "StudentWorld.h"
#include "GameConstants.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

//constructor for studentworld
StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), centralBankAcc(0)
{
}

//destructor for student world
StudentWorld::~StudentWorld() {
    cleanUp();
}

//get the board that we're using
Board StudentWorld::getBoard() const {
    return myBoard;
}

//get access to peach player
Player* StudentWorld::getPeach() const {
    return peachSW;
}

//get access to yoshi player
Player* StudentWorld::getYoshi() const {
    return yoshiSW;
}

//get access to central bank account
int StudentWorld::getBankBalance() const {
    return centralBankAcc;
}

//change central bank account
void StudentWorld::changeCentralBank(int amt) {
    centralBankAcc += amt;
}

//reset bank
void StudentWorld::reset_bank_coins() {
    centralBankAcc = 0;
}

//swaps player coins
void StudentWorld::swapCoins(){
    int temp = peachSW->checkCoins();
    peachSW->setCoins(yoshiSW->checkCoins());
    yoshiSW->setCoins(temp);
}

//swaps player stars
void StudentWorld::swapStars(){
    int temp = peachSW->checkStars();
    peachSW->setStars(yoshiSW->checkStars());
    yoshiSW->setStars(temp);
}


void swapStars(Player* play);      //swaps player stars


//get square at
Actor* StudentWorld::getSquare(int x, int y){
    //declare iterator
    vector<Actor*>::iterator check = m_items.begin();
    while(check != m_items.end()){
        Actor* curr = *check;
        if(curr->isSquare() == true){
            int cx = curr->getX();
            int cy = curr->getY();
            if(cx == x && cy == y){
                return curr;
            }
        }
        check++;
    }
    return nullptr;
}

//delete a square at
void StudentWorld::deleteSquare(int x, int y){
    Actor* square = getSquare(x,y); //grabs the square we want
    if(square != nullptr){
        vector<Actor*>::iterator match;
        match = find(m_items.begin(), m_items.end(), square);
        if(match != m_items.end()){
            m_items.erase(match);       //gets rid of square
        }
        delete square;                  //no memory leak
    }
}

//add a dropping square
void StudentWorld::addDropS(int x, int y){
    m_items.push_back(new DropS(this, x, y));
}

//determines winner of game
Player* StudentWorld::pickWinner() const{
    //check star value
    if(peachSW->checkStars() > yoshiSW->checkStars()){
        return peachSW;
    } else if(peachSW->checkStars() < yoshiSW->checkStars()){
        return yoshiSW;
    } else if(peachSW->checkStars() == yoshiSW->checkStars()){
        //even number of stars >>> use coins
        if(peachSW->checkCoins() > yoshiSW->checkCoins()){
            return peachSW;
        } else if(peachSW->checkCoins() < yoshiSW->checkCoins()){
            return yoshiSW;
        } else {
            //random choice
            int choice = randInt(1,2);
            if(choice == 1){
                return peachSW;
            } else {
                return yoshiSW;
            }
        }
    }
    return peachSW;
}

//add a vortex
void StudentWorld::addVortex(int x, int y, int dir) {
    m_items.push_back(new Vortex(this, x, y, dir));
    return;
}

//properly delete a vortex
void StudentWorld::destroyVortex(Actor* vx) {
    vector<Actor*>::iterator match = find(m_items.begin(), m_items.end(), vx);
    if(match != m_items.end()){
        m_items.erase(match);
    }
    delete vx;
    return;
}



int StudentWorld::init()
{
    Board bd;
    //load in the board
    string boardNum = to_string(getBoardNumber());
    string board_file = assetPath() + "board0" + boardNum + ".txt";
    Board::LoadResult result = bd.loadBoard(board_file);
    
    if (result == Board::load_success) {
        cerr << "Successfully loaded board\n";
     
    //Initialize the data structures used to keep track of your game’s world
        
    //keep track of each item that you are loading in
    //go through the contents of the grid
    for (int gy = 0; gy < BOARD_HEIGHT; gy++) {
        for (int gx = 0; gx < BOARD_WIDTH; gx++){
            Board::GridEntry ge = bd.getContentsOf(gx, gy);
            int actor_x = gx * SPRITE_WIDTH;
            int actor_y = gy * SPRITE_WIDTH;
            switch (ge) {
                case Board::empty:
                    break;
                //players start at same place (and start on a coin square)
                //Allocate Peach and Yoshi objects into the game world
                case Board::player:
                    peachSW = new Peach(this, actor_x, actor_y);
                    yoshiSW = new Yoshi(this, actor_x, actor_y);
                    m_items.push_back(new COINSquare(this, IID_BLUE_COIN_SQUARE, actor_x, actor_y, 1));
                    break;
                //Allocate and insert all of the other objects (e.g., squares, baddies, etc.) into the game world as described below.
                case Board::red_coin_square:
                    m_items.push_back(new COINSquare(this, IID_RED_COIN_SQUARE, actor_x, actor_y, 2));
                    break;
                case Board::blue_coin_square:
                    m_items.push_back(new COINSquare(this, IID_BLUE_COIN_SQUARE, actor_x, actor_y, 1));
                    break;
                case Board::up_dir_square:
                    m_items.push_back(new DIRSquare(this, actor_x, actor_y, 90));
                    break;
                case Board::down_dir_square:
                    m_items.push_back(new DIRSquare(this, actor_x, actor_y, 270));
                    break;
                case Board::right_dir_square:
                    m_items.push_back(new DIRSquare(this, actor_x, actor_y, 0));
                    break;
                case Board::left_dir_square:
                    m_items.push_back(new DIRSquare(this, actor_x, actor_y, 180));
                    break;
                case Board::event_square:
                    m_items.push_back(new EventS(this, actor_x, actor_y));
                    break;
                case Board::bank_square:
                    m_items.push_back(new BankS(this, actor_x, actor_y));
                    break;
                case Board::star_square:
                    m_items.push_back(new StarS(this, actor_x, actor_y));
                    break;
                case Board::boo:
                    m_items.push_back(new Boo(this, actor_x, actor_y));
                    m_items.push_back(new COINSquare(this, IID_BLUE_COIN_SQUARE, actor_x, actor_y, 1));
                    break;
                case Board::bowser:
                    m_items.push_back(new Bowser(this, actor_x, actor_y));
                    m_items.push_back(new COINSquare(this, IID_BLUE_COIN_SQUARE, actor_x, actor_y, 1));
                    break;
                }
            }
        }
    
    
    myBoard = bd;
    startCountdownTimer(99);  
    return GWSTATUS_CONTINUE_GAME;
        
    } else {
        return GWSTATUS_BOARD_ERROR; 
    }
}

int StudentWorld::move()
{
    //set vortex strings
    ostringstream oss1;
    oss1 << "";
    string pV = "";
    if(peachSW->hasVortex()){
        pV = " VOR ";
        oss1 << setw(5) << pV;
    }
    
    ostringstream oss2;
    oss2 << "";
    string yV = "";
    if(yoshiSW->hasVortex()){
        yV = " VOR ";
        oss2 << setw(5) << yV;
    }
    
    //define strings
    string s1 = oss1.str();
    string s2 = oss2.str();
    
    setGameStatText("P1 Roll: " + to_string((peachSW->Ticks2Move())/8) + " Stars: " + to_string(peachSW->checkStars()) + " $$: " + to_string(peachSW->checkCoins()) + s1 + " | Time: " + to_string(timeRemaining()) + " | Bank: " + to_string(centralBankAcc) + " | P2 Roll: " + to_string((yoshiSW->Ticks2Move())/8) + " Stars: " + to_string(yoshiSW->checkStars()) + " $$: " + to_string(yoshiSW->checkCoins()) + s2);
    
    if (timeRemaining() <= 0){
        Player* winner = pickWinner();
        setFinalScore(winner->checkStars(), winner->checkCoins());
        playSound(SOUND_GAME_FINISHED);
        if(winner == peachSW){
            return GWSTATUS_PEACH_WON;
        } else if(winner == yoshiSW){
            return GWSTATUS_YOSHI_WON;
        }
    }
    
    
    //access vector of objects to do something
       unsigned long Vsize = m_items.size();
       for(int i = 0; i < Vsize; i++){
           Actor* temp = m_items[i];
           temp->doSomething();
       }

        
    
    //do something for players
    peachSW->doSomething();
    yoshiSW->doSomething();
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    //delete vector of objects
    //vector<Actor*>::iterator it;
    unsigned long Vsize = m_items.size();
    
    for(int i = 0; i < Vsize; i++){
        Actor* curr = m_items[i];
        delete curr;
    }
    
    m_items.clear();

    
    //delete peach and yoshi objects
    delete peachSW;
    delete yoshiSW;
}

