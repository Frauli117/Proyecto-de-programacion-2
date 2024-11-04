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

bool RouteList::isUniqueName(string name) { //Cambiar nombre
    RouteNode* current = head;
    while (current != nullptr) {
        if (!current->getPointList().isRepeatedname(name)) {
            return false;
        }
        current = current->getNext();
    }
    return true;
}

void RouteList::insertPointToRoute(const string& routeName, const string& pointName, int x, int y) {
    RouteNode* route = this->searchRoute(routeName);
    if (route != nullptr) {
        // Validar que el nombre del punto sea único
        if (route->getPointList().isRepeatedname(pointName)) {
            route->getPointList().insertPoint(pointName, x, y);
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

void RouteList::removeRoute(string name) {
    if (head == nullptr) return;

    if (head->getName() == name) {
        RouteNode* temp = head;
        head = head->getNext();
        delete temp;
        return;
    }

    RouteNode* current = head->getNext();

    while (current != nullptr) {
        if (current->getName() == name) {
            current->getPrev()->setNext(current->getNext());
            current->getNext()->setPrev(current->getPrev());
            delete current;
            return;
        }
        current = current->getNext();
    }
}

void RouteList::displayRoutes() {
    RouteNode* current = head;
    while (current != nullptr) {
        std::cout << current->getName() << ", ";
        current = current->getNext();
    }
}

RouteNode* RouteList::getHead() {
    return head;
}