#include "RouteList.h"

RouteList::RouteList() {
    this->head = nullptr;
}

void RouteList::insertRoute(string name) {
    RouteNode* newNode = new RouteNode(name);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        RouteNode* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newNode);
        newNode->setPrev(current);
    }
}

RouteNode* RouteList::searchRoute(string name) {
    RouteNode* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

bool RouteList::isUniquePointName(string name){
    RouteNode* current = head;
    while (current != nullptr) {
        if (!current->getPointList().isUniqueName(name)) {
            return false;
        }
        current = current->getNext();
    }
    return true;
}

void RouteList::insertPointToRoute(const string& routeName, const string& pointName, int x, int y, sf::Color color) {
    RouteNode* route = searchRoute(routeName);
    if (route != nullptr) {
        if (route->getPointList().isUniqueName(pointName)) {
            route->getPointList().insertPoint(pointName, x, y, color);
            cout << "Punto agregado: " << pointName << " en (" << x << ", " << y << ")" << endl;
        }
        else {
            cout << "No se pudo agregar el punto. El nombre ya existe en la ruta." << endl;
        }
    }
    else {
        cout << "No se pudo agregar el punto. La ruta no existe." << endl;
    }
}

void RouteList::removeRoute(string& name) {
    if (head == nullptr) return;

    if (head->getName() == name) {
        RouteNode* temp = head;
        head = head->getNext();
        if (head != nullptr) { 
            head->setPrev(nullptr);
        }
        delete temp;
        return;
    }

    RouteNode* current = head->getNext();
    while (current != nullptr) {
        if (current->getName() == name) {
            if (current->getNext() != nullptr) {
                current->getNext()->setPrev(current->getPrev());
            }
            current->getPrev()->setNext(current->getNext());
            delete current;
            return;
        }
        current = current->getNext();
    }
}

RouteNode* RouteList::getHead() {
    return head;
}