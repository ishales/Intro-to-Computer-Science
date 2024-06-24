//
//  oddlist.cpp
//  hw 4 A
//
//  Created by Isabelle Hales on 3/6/23.
//  Copyright © 2023 CS32. All rights reserved.

void removeOdd(list<int>& li)
{
    //int s = li.size();      //get size of list
    list<int>::iterator el = li.begin();
    while(el != li.end()){
        int temp = *el;
        if((temp % 2) == 1){
            el = li.erase(el);
        } else {
            el++;
        }
    }
}

