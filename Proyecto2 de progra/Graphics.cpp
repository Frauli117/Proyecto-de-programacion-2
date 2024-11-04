#include "Graphics.h"

Graphics::Graphics(RouteList& routeList) : routeList(routeList) {
    if (!font.loadFromFile("Fuente/ARIAL.ttf")) {
       
    }
    routeText.setFont(font);
    routeText.setCharacterSize(24);
    routeText.setFillColor(sf::Color::Black);

    routeWindow.setSize(sf::Vector2f(200, 600));
    routeWindow.setFillColor(sf::Color(200, 200, 200, 255));
    routeWindow.setPosition(1000, 0);
    currentRouteName = ""; 
}

void Graphics::display() {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Mapa de Rutas Turísticas");
    string currentPointName = "";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (isMouseInRouteWindow(event, window)) {
                    selectRoute(event, window);
                }
                else {
                    if (!currentRouteName.empty()) {
                        cout << "Nombre del punto: ";
                        cin >> currentPointName;
                        RouteNode* route = routeList.searchRoute(currentRouteName);
                        if (route && route->getPointList().isRepeatedname(currentPointName)) {
                            route->getPointList().insertPoint(currentPointName, event.mouseButton.x, event.mouseButton.y);
                        }
                        else {
                            cout << "El nombre del punto ya existe o la ruta no es válida." << endl;
                        }
                    }
                }
            }
        }

        window.clear();

        sf::Texture fondoTexture;
        if (!fondoTexture.loadFromFile("Imagen/mapa de Costa Rica.jpg")) {
            return;
        }
        sf::Sprite fondoSprite(fondoTexture);
        window.draw(fondoSprite);

        routeText.setString("Ruta: " + currentRouteName);
        routeText.setPosition(1000, 20);
        window.draw(routeText);

        window.draw(routeWindow);
        drawRoutes(window);

        drawPoints(window);

        window.display();
    }
}

bool Graphics::isMouseInRouteWindow(sf::Event& event, sf::RenderWindow& window) {
    return (event.mouseButton.x >= 1000 && event.mouseButton.x <= 1200 &&
        event.mouseButton.y >= 0 && event.mouseButton.y <= 600);
}

void Graphics::selectRoute(sf::Event& event, sf::RenderWindow& window) {
    for (size_t i = 0; i < routeNames.size(); ++i) {
        if (routeNames[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            currentRouteName = routeNames[i].getString();
            cout << "Ruta seleccionada: " << currentRouteName << endl;
            return;
        }
    }
    cout << "Nombre de la nueva ruta: ";
    cin >> currentRouteName;
    routeList.insertRoute(currentRouteName);
    updateRouteNames();
}

void Graphics::updateRouteNames() {
    routeNames.clear();
    RouteNode* current = routeList.getHead();
    int yOffset = 30;
    while (current != nullptr) {
        sf::Text routeName;
        routeName.setFont(font);
        routeName.setString(current->getName());
        routeName.setCharacterSize(24);
        routeName.setFillColor(sf::Color::Black);
        routeName.setPosition(1010, yOffset);
        routeNames.push_back(routeName);
        yOffset += 30;
        current = current->getNext();
    }
}

void Graphics::drawRoutes(sf::RenderWindow& window) {
    for (const auto& routeName : routeNames) {
        window.draw(routeName);
    }
}

void Graphics::drawPoints(sf::RenderWindow& window) {
    RouteNode* currentRoute = routeList.getHead();
    while (currentRoute != nullptr) {
        PointNode* point = currentRoute->getPointList().getHead();
        while (point != nullptr) {
            sf::CircleShape circle(5);
            circle.setFillColor(sf::Color::Red);
            circle.setPosition(point->getX(), point->getY());
            window.draw(circle);

            sf::Text pointName;
            pointName.setFont(font);
            pointName.setString(point->getName());
            pointName.setCharacterSize(18);
            pointName.setFillColor(sf::Color::Black);
            pointName.setPosition(point->getX() + 10, point->getY() - 10);

            window.draw(pointName);

            point = point->getNext();
        }
        currentRoute = currentRoute->getNext();
    }
}
