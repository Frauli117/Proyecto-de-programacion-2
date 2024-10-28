#pragma once
#include "RouteNode.h"

class RouteList
{
private:
	RouteNode* head;
public:
	RouteList();
	void insertRout(string name);
	RouteNode* searchRoute(string name);
	bool isUniqueName(string name);
	void insertPointToRoute(string name);
	void removeRoute(string name);
	void displayRoutes();
};

