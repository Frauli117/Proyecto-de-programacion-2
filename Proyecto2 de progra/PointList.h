#pragma once
#include "PointNode.h"

class PointList
{
private:
	PointNode* head;

public:

	PointList();
	void insertPoint(string name, int x, int y, sf::Color color);
	bool isUniqueName(string name);
	void removePoint(const string& pointName);
	PointNode* getHead();
};

