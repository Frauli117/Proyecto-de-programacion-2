#include "RouteFileManager.h"

void RouteFileManager::saveRoutesToFile(const string& filename, RouteList& routeList) {
    ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar las rutas." << std::endl;
        return;
    }

    RouteNode* current = routeList.getHead();
    while (current) {
        file << current->getName() << "\n";
        PointNode* point = current->getPointList().getHead();
        while (point) {
            file << point->getName() << " "
                << point->getX() << " "
                << point->getY() << " "
                << point->getColor().toInteger() << "\n";
            point = point->getNext();
        }
        file << "\n";
        current = current->getNext();
    }

    file.close();
    std::cout << "Rutas guardadas correctamente en " << filename << std::endl;
}

void RouteFileManager::loadRoutesFromFile(const string& filename, RouteList& routeList) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar las rutas." << std::endl;
        return;
    }

    string line;
    RouteNode* currentRoute = nullptr;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream ss(line);
        string word1;
        int x, y;
        sf::Uint32 colorInt;

        ss >> word1;

        if (!(ss >> x >> y >> colorInt)) {
            routeList.insertRoute(word1);
            currentRoute = routeList.searchRoute(word1);
        }
        else {
            if (currentRoute != nullptr) {
                sf::Color color(colorInt);
                currentRoute->getPointList().insertPoint(word1, x, y, color);
            }
            else {
                std::cerr << "Error: Punto sin una ruta asociada: " << word1 << std::endl;
            }
        }
    }

    file.close();
    std::cout << "Rutas cargadas correctamente desde " << filename << std::endl;
}