//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        data[size] = idx;                               //put new value at end of heap
        upheap(size, weightArr);                        //move element up until its in correct spot
        size++;                                         //increment heap size
    }

    int pop(int weightArr[]) {
        if (size == 0) return -1;                       //checks if empty
        int ret = data[0];                              //saves smallest root value
        size--;                                         //decrement heap size
        data[0] = data[size];                           //moves last element from heap to root
        if (size > 0) downheap(0, weightArr);       //Fixes if there are elements left
        return ret;                                     //return smallest imdex
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif