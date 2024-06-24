//
//  linear.cpp
//  hw 3 linear
//
//  Created by Isabelle Hales on 2/14/23.
//  Copyright © 2023 CS32. All rights reserved.
//

// Return true if the somePredicate function returns true for at
// least one of the array elements; return false otherwise.
bool anyTrue(const double a[], int n)
{
    //make sure one element is present
    if(n <= 0){
        return false;
    }
    
    //define base case (if not present, return false
    if(somePredicate(a[0])){
        return true;
    }
    
    //will check next element of array (until n-1 is 0 (end of array))
    return anyTrue(a+1, n-1);
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    //make sure one element of array is present
    if(n <= 0){
        return 0;
    }
    
    int count = 0;
    
    //define base case
    if(somePredicate(a[0])){
        count++;
    }
    
    //recursively check each next element of array
    return count + countTrue(a+1, n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    //make sure one element of array is present
    if(n <= 0){
        return -1;
    }
    
    //define base case
    if(somePredicate(a[0])){
        return 0;
    }
    
    //recursively check for -1, if not return index
    int check = firstTrue(a+1, n-1);
        if(check == -1){
            return -1;
        } else {
            return 1 + check;
        }
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told that no doubles are to
// be considered in the array, return -1.
int indexOfMinimum(const double a[], int n)
{
    //make sure one element of array is present
    if(n <= 0){
        return -1;
    }
    
    //base case
    if(n == 1){
        return n-1;
    }
    
    //recursively check with rest of array
    if(a[0] < a[1 +(indexOfMinimum(a+1, n-1))]){
        return 0;
    } else {
        return 1 + (indexOfMinimum(a+1, n-1));
    }
}

// If all n1 elements of a1 appear in the n2 element array a2, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 is not a
// not-necessarily-contiguous subsequence of a2), return false.
// (Of course, if a1 is empty (i.e., n1 is 0), return true.)

// For example, if a2 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a1 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a1 is
//    50 30 20
// or
//    10 20 20
bool isIn(const double a1[], int n1, const double a2[], int n2)
{
    //make sure one element of array a1 is present
    if(n1 <= 0){
        return true;
    }
    
    //no elements of a1 in a2 bc a2 is empty
    if(n2 <= 0){
        return false;
    }
    
    //recursively compare each element in array
    if(a1[0] == a2[0]){
        //if we find pair, move both arrays forward to keep checking
        return isIn(a1+1, n1-1, a2+1, n2-1);
    } else {
        //if we don't find a pair, keep checking same element of a1, move a2 along
        return isIn(a1, n1, a2+1, n2-1);
    }
}


