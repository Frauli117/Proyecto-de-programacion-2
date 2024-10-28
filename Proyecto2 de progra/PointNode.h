#pragma once

#include <iostream>
#include <string>

using namespace std;

class PointNode
{
private:
	string name;
	int x;
	int y;
	PointNode* next;
	PointNode* prev;
public:
	PointNode();
	PointNode(string name, int x, int y);
	string getName();
	int getX();
	int getY();
	PointNode* getNext();
	PointNode* getPrev();
	void setName(string name);
	void setX(int x);
	void setY(int y);
	void setNext(PointNode* next);
	void setPrev(PointNode* prev);
};

