#include <stdio.h>
#include <cs50.h>
#include "helpers.h"

// BINARY SEARCH // Divide and Conquer, The array must be sorted first.
// Worst - O(log n)
// Best - Omega(1)

// Repeat until the (sub)array is size 0:
//     Calculate the middle point of the (sub)array.
//     If the target is at the middle, stop.
//     Otherwise, if the target is less than what's at the middle, repeat, changing endpoint to be left of middle.
//     Otherwise, if the target is greater than what's at the middle, repeat, changing endpoint to be right of middle.

// Returns true if value is in array of n values, else false.
bool search(int value, int values[], int n)
{

    int leftindex = 0;
    int rightindex = n - 1;
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    while ()
    {

    }
    return;
}
