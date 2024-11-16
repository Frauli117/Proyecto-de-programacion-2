#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class PointNode
{
private:
	string name;
	int x;
	int y;
	sf::Color color;
	PointNode* next;
	PointNode* prev;
public:
	PointNode();
	PointNode(string name, int x, int y, sf::Color color);
	string getName();
	int getX();
	int getY();
	sf::Color getColor();
	PointNode* getNext();
	PointNode* getPrev();
	void setName(string name);
	void setX(int x);
	void setY(int y);
	void setColor(sf::Color color);
	void setNext(PointNode* next);
	void setPrev(PointNode* prev);
};

