#include "PointList.h"

PointList::PointList() {
	this->head = nullptr;
}

void PointList::insertPoint(string name, int x, int y) {
    PointNode* newNode = new PointNode(name, x, y);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        PointNode* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newNode);
        newNode->setPrev(current);
    }
}

bool PointList::isRepeatedname(string name) {
    PointNode* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            return false;
        }
        current = current->getNext();
    }
    return true;
}

void PointList::displayPoints() {
    PointNode* current = head;
    while (current != nullptr) {
        std::cout << current->getName() << ", ";
        current = current->getNext();
    }
}

PointNode* PointList::getHead() {
    return head;
}