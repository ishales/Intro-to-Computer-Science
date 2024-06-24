//
//  vehicle.cpp
//  hw3
//
//  Created by Isabelle Hales on 2/14/23.
//  Copyright © 2023 CS32. All rights reserved.
//

//Your declarations and implementations would go here
class Vehicle {
public:
    Vehicle(string id) : idV(id){};                  //constructor (not virtual)
    string id() const {return idV;};        //function to get vehicle id
    virtual string description() const = 0;          //base gets vehicle description
    virtual bool canHover() const {return true; };        //base if vehicle can hover
    virtual ~Vehicle() {} ;             //base destructor
private:
    string idV;
};

class Drone: public Vehicle {
public:
    Drone(string id) : Vehicle(id) {};                    //drone constructing
    virtual string description() const {return "a drone";};     //gets vehicle description
    virtual bool canHover() const {return 1; };        //drones can hover
    virtual ~Drone() {cout << "Destroying " << id() << ", a drone" << endl;};                //destructor
};

class Balloon: public Vehicle {
public:
    Balloon(string id, double diameter) : Vehicle(id), diameterB(diameter) {};                    //balloon constructing
    virtual string description() const {if(diameterB < 8) {return "a small balloon";} else {return "a large balloon";}};     //gets vehicle description
                //special code to detect the size of the balloon (if/else statement)
    virtual bool canHover() const {return true; };        //balloons can hover
    virtual ~Balloon() {cout << "Destroying the balloon " << id() << endl;};              //destructor
private:
    //balloons have an extra member variable (will be private)
    double diameterB;
};

class Satellite: public Vehicle {
public:
    Satellite(string id) : Vehicle(id) {};                    //satellite constructing
    virtual string description() const {return "a satellite";};     //gets vehicle description
    virtual bool canHover() const {return false; };        //satellites can't hover
    virtual ~Satellite() {cout << "Destroying the satellite " << id() << endl;};            //destructor
};

