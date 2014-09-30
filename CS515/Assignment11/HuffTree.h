/*
CS515 Assignment 11
File: HuffTree.cpp, PQueue.cpp, HuffTree.h, PQueue.h
Name: Jonathan Hart
Section: 2
Date: 11/19/2013
Collaboration Declaration: Red Bull
*/ 

#ifndef HUFFTREE_H
#define HUFFTREE_H

#include <iostream>
#include <string>
#include "PQueue.h"
using namespace std;

struct HuffNode{
    // default constructor
    HuffNode(HuffNode* l = 0, HuffNode* r = 0, int f = 0, char d = '\0')
        : left(l), right(r), freq(f), data(d){}
    HuffNode * left, * right;  // two child node
    unsigned int freq; // freqency of the node
    char data;  // char value for leaf nodes; '\0' for internal nodes
    string code;  // Huffman code for leaf nodes; not assigned for internal nodes
    
    // do not change above code
    // you may add below here
	friend bool operator <(const HuffNode& n1, const HuffNode& n2){
		return n1.freq < n2.freq;
		}
	friend bool operator <=(const HuffNode& n1, const HuffNode& n2){
		return n1.freq <= n2.freq;
		}
};

class HuffTree{
public:
    // get Huffman code and return it as a string
    string getCode(char);
    
    // build Huffman tree from an array of characters
    // and and an array of their corresponding freqencys;
    // the size of both arrays is given
    void buildTree(char * chs, int * freqs, int size);
    
private:
    HuffNode * _root; // root of the Huffman tree
   
    // do not change above code
    // you may add below here
	void setCode(HuffNode * node, string code);
	void findCode(HuffNode * node, string &code, char c);
};

#endif