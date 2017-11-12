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

    // These indexes will be moved to narrow down the search.
    int leftindex = 0;
    int rightindex = n - 1;

    while (n > 0)
    {
        if (leftindex > rightindex)
        {
            return false;
        }

        // A match
        if (value == values[(leftindex + rightindex) / 2])
        {
            return true;
        }

        // A bigger number
        else if ( value > values[(leftindex + rightindex) / 2])
        {
            leftindex = (leftindex + rightindex) / 2 + 1;
        }

        // A smaller number
        else if ( value < values[(leftindex + rightindex) / 2])
        {
            rightindex = (leftindex + rightindex) / 2 - 1;
        }

    }
    return false;
}



// Selection sort is like organizing a hand of cards, plopping in the smallest of the rest of the cards
void sort(int values[], int n)
{
    // Starting from the leftmost number
    for (int i = 0; i < n - 1; i++)
    {

        // Find the smallest number
        int min_index = i;
        for (int j = (i + 1); j < n; j++)
        {
            if (values[j] < values[min_index])
            {
                min_index = j;
            }
        }

        // Swap the numbers
        int temp = values[i];
        values[i] = values[min_index];
        values[min_index] = temp;

        // Print for sanity check and to visualize errors
        printf("this is values i %i\n", values[i]);
        printf("this is values min %i\n", values[min_index]);
    }
}
