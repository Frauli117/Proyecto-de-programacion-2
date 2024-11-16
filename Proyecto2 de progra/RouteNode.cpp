#include "RouteNode.h"

RouteNode::RouteNode() {}

RouteNode::RouteNode(string name) { this->name = name; }

string RouteNode::getName() { return this->name; }

PointList& RouteNode::getPointList() { return this->pointList; }

RouteNode* RouteNode::getNext() { return this->next; }

RouteNode* RouteNode::getPrev() { return this->prev; }

void RouteNode::setName(string name) { this->name = name; }

void RouteNode::setPointList(PointList pointList) { this->pointList = pointList; }

void RouteNode::setNext(RouteNode* next) { this->next = next; }

void RouteNode::setPrev(RouteNode* prev) { this->prev = prev; }