//
//  oddvector.cpp
//  h4 2
//
//  Created by Isabelle Hales on 3/6/23.
//  Copyright © 2023 CS32. All rights reserved.
//

void removeOdd(vector<int>& v)
{
    vector<int>::iterator want = v.begin();
    while(want != v.end()){
        int temp = *want;
        if(temp % 2 == 1){
            want = v.erase(want);
        } else {
            want++;
        }
        
    }
}
