#include "PointNode.h"

PointNode::PointNode() : color(sf::Color::Green), next(nullptr), prev(nullptr) {};

PointNode::PointNode(string name, int x, int y, sf::Color color) {
	this->name = name;
	this->x = x;
	this->y = y;
	this->next = nullptr;
	this->prev = nullptr;
	this->color = color;
}

string PointNode::getName() { return this->name; }

int PointNode::getX() { return this->x; }

int PointNode::getY() { return this->y; }

sf::Color PointNode::getColor() { return this->color; }

PointNode* PointNode::getNext() { return  this->next; }

PointNode* PointNode::getPrev() { this->prev; }

void PointNode::setName(string name) { this->name = name; }

void PointNode::setX(int x) { this->x = x; }

void PointNode::setY(int y) { this->y = y; }

void PointNode::setColor(sf::Color color) { this->color = color; }

void PointNode::setNext(PointNode* next) { this->next = next; }

void PointNode::setPrev(PointNode* prev) { this->prev = prev; }