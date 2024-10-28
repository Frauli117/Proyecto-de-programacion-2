#pragma once
#include "PointNode.h"

class PointList
{
private:
	PointNode* head;

public:

	PointList();
	void insertPoint(string name, int x, int y);
	bool isRepeatedname(string name);
	void displayPoints();
};

