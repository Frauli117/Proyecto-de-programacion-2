#include "PointList.h"

PointList::PointList() {
	this->head = nullptr;
}

void PointList::insertPoint(string name, int x, int y, sf::Color color) {
    PointNode* newNode = new PointNode(name, x, y, color);
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

bool PointList::isUniqueName(string name) {
    PointNode* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            return false;
        }
        current = current->getNext();
    }
    return true;
}

void  PointList::removePoint(const string& pointName) {
    PointNode* current = head;
    PointNode* previous = nullptr;

    while (current != nullptr) {
        if (current->getName() == pointName) {
            // Si es el primer nodo
            if (previous == nullptr) {
                head = current->getNext();
            }
            else {
                previous->setNext(current->getNext());
            }

            delete current;
            cout << "Punto eliminado: " << pointName << endl;
            return;
        }
        previous = current;
        current = current->getNext();
    }
    cout << "No se encontró el punto: " << pointName << endl;
}

PointNode* PointList::getHead() {
    return head;
}