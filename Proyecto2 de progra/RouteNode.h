#pragma once
#include <string>
#include "PointList.h"

using namespace std;

class RouteNode
{
private:
    string name;
    PointList pointList;
    RouteNode* next;
    RouteNode* prev;
public:
    RouteNode();
    RouteNode(string name);
    string getName();
    PointList& getPointList();
    RouteNode* getNext();
    RouteNode* getPrev();
    void setName(string name);
    void setPointList(PointList pointList);
    void setNext(RouteNode* next);
    void setPrev(RouteNode* prev);
};

