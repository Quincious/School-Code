/*
CS515 Assignment 11
File: HuffTree.cpp, PQueue.cpp, HuffTree.h, PQueue.h
Name: Jonathan Hart
Section: 2
Date: 11/19/2013
Collaboration Declaration: Red Bull
*/ 


#include "HuffTree.h"

void HuffTree::buildTree(char * chs, int * freqs, int size)
{
	PQueue<HuffNode, 100> q;
	
	for(size_t i = 0; i < 5; i++)
	{
		HuffNode *node = new HuffNode();
		node->data = chs[i];
		node->freq = freqs[i];
		
		q.insert(*node);
		
		cout << "Min - " << q.findMin().freq << endl;
	}
	
	//cout << "Size= " << q.size() << endl;	
	
	while(q.size() > 1)
	{
		HuffNode* leftNode = new HuffNode(q.findMin());
		q.deleteMin();
		HuffNode* rightNode = new HuffNode(q.findMin());
		q.deleteMin();
		
		HuffNode* newNode = new HuffNode();
		newNode->left = leftNode;
		newNode->right = rightNode;
		
		cout << leftNode->freq << " + " << rightNode->freq << " = ";
		
		newNode->freq = leftNode->freq + rightNode->freq;
		
		cout << newNode->freq << endl;
		
		q.insert(*newNode);		
	}
	
	_root = new HuffNode(q.findMin());
	
	string str = "";
	
	if(_root->left)
		setCode(_root->left, str + '0');
	if(_root->right)
		setCode(_root->right, str + '1');
}

string HuffTree::getCode(char c)
{
	string retVal = "";
	
	findCode(_root, retVal, c);
	
	return retVal;
}

void HuffTree::setCode(HuffNode * node, string code)
{
	if(!node->left && !node->right)//at leaf node
	{
		node->code = code;		
		cout << node->data << " - " << code << endl;
	}
	
	if(node->left)
		setCode(node->left, code + '0');
	if(node->right)
		setCode(node->right, code + '1');
}

void HuffTree::findCode(HuffNode * node, string &code, char c)
{
	if(code == "")
	{
		if(node->data == c)
		{
			code = node->code;
			return;
		}
		
		if(node->left)
			findCode(node->left, code, c);
		
		if(code == "" && node->right)
			findCode(node->right, code, c);
	}
}