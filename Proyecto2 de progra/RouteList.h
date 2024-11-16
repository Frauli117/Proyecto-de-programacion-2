#pragma once
#include "RouteNode.h"

class RouteList
{
private:
	RouteNode* head;
public:
	RouteList();
	void insertRoute(string name);
	RouteNode* searchRoute(string name);
	bool isUniquePointName(string name);
	void insertPointToRoute(const string& routeName, const string& pointName, int x, int y, sf::Color color);
	void removeRoute(string& name);
	RouteNode* getHead();
};

