
#include "RouteList.h"
#include "Graphics.h"
#include "RouteFileManager.h"

int main() {
    RouteList routeList;
    Graphics graphics(routeList);
    RouteFileManager::loadRoutesFromFile("rutas.txt", routeList);
    graphics.updateRouteNames();
    graphics.display();
    RouteFileManager::saveRoutesToFile("rutas.txt", routeList);

    return 0;
}

