#include "Graphics.h"

Graphics::Graphics(RouteList& routeList) : routeList(routeList), currentColor(sf::Color::Green) {
    if (!font.loadFromFile("Fuente/ARIAL.ttf")) {
        cerr << "Error al cargar la fuente" << endl;
        exit(1);
    }
    for (int i = 0; i < 4; ++i) {
        colorButtons[i].setSize(sf::Vector2f(40, 40));
        colorButtons[i].setFillColor(buttonColors[i]);
        colorButtons[i].setPosition(20, 700 + i * 50);
    }
    routeText.setFont(font);
    routeText.setCharacterSize(24);
    routeText.setFillColor(sf::Color::Black);

    routeWindow.setSize(sf::Vector2f(200, 600));
    routeWindow.setFillColor(sf::Color(200, 200, 200, 255));
    routeWindow.setPosition(1000, 0);
    currentRouteName = "";

    deleteButton.setSize(sf::Vector2f(180, 40));
    deleteButton.setFillColor(sf::Color(255, 0, 0));
    deleteButton.setPosition(1010, 500);

    deleteButtonText.setFont(font);
    deleteButtonText.setString("Eliminar Ruta");
    deleteButtonText.setCharacterSize(20);
    deleteButtonText.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = deleteButtonText.getLocalBounds();
    deleteButtonText.setPosition(1010 + (deleteButton.getSize().x - textBounds.width) / 2, 500 + (deleteButton.getSize().y - textBounds.height) / 2);

    deletePointButton.setSize(sf::Vector2f(180, 40));
    deletePointButton.setFillColor(sf::Color(255, 165, 0));
    deletePointButton.setPosition(1010, 550);

    deletePointButtonText.setFont(font);
    deletePointButtonText.setString("Eliminar Punto");
    deletePointButtonText.setCharacterSize(20);
    deletePointButtonText.setFillColor(sf::Color::Black);
    textBounds = deletePointButtonText.getLocalBounds();
    deletePointButtonText.setPosition(1010 + (deletePointButton.getSize().x - textBounds.width) / 2, 550 + (deletePointButton.getSize().y - textBounds.height) / 2);

    selectedPoint = nullptr;
    instructionsText.setFont(font);
    instructionsText.setString("Haz clic en la ventanita para agregar rutas.\nSelecciona el nombre de la ruta para manipularla.");
    instructionsText.setCharacterSize(18);
    instructionsText.setFillColor(sf::Color::Black);
    instructionsText.setPosition(600, 20);
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
                bool handled = false;

                for (int i = 0; i < 4; ++i) {
                    if (colorButtons[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        currentColor = buttonColors[i];
                        cout << "Color seleccionado: "
                            << (i == 0 ? "Azul" : i == 1 ? "Rojo" : i == 2 ? "Verde" : "Amarillo") << endl;
                        handled = true;
                        break;
                    }
                }
                if (handled) continue;

                if (deleteButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (!currentRouteName.empty()) {
                        deleteRoute();
                    }
                    continue;
                }

                if (deletePointButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (selectedPoint != nullptr) {
                        deleteSelectedPoint();
                    }
                    continue;
                }
                if (isMouseInRouteWindow(event)) {
                    selectRoute(event);
                    continue;
                }

                if (!currentRouteName.empty()) {
                    if (!selectPoint(event)) {
                        cout << "Nombre del punto: ";
                        cin >> currentPointName;
                        RouteNode* route = routeList.searchRoute(currentRouteName);
                        if (route && route->getPointList().isUniqueName(currentPointName)) {
                            route->getPointList().insertPoint(currentPointName, event.mouseButton.x, event.mouseButton.y, currentColor);
                        }
                        else {
                            cout << "El nombre del punto ya existe o la ruta no es válida." << endl;
                        }
                    }
                }
            }
        }

        window.clear();
        drawBackground(window);
        drawUI(window);
        window.display();
    }
}

bool Graphics::selectPoint(sf::Event& event) {
    RouteNode* currentRoute = routeList.searchRoute(currentRouteName);
    if (currentRoute) {
        PointNode* point = currentRoute->getPointList().getHead();
        while (point) {
            if (abs(event.mouseButton.x - point->getX()) <= 5 && abs(event.mouseButton.y - point->getY()) <= 5) {
                selectedPoint = point;
                cout << "Punto seleccionado: " << point->getName() << endl;
                return true;
            }
            point = point->getNext();
        }
    }
    selectedPoint = nullptr;
    return false;
}

void Graphics::deleteSelectedPoint() {
    if (selectedPoint != nullptr && !currentRouteName.empty()) {
        RouteNode* route = routeList.searchRoute(currentRouteName);
        if (route) {
            route->getPointList().removePoint(selectedPoint->getName());
            cout << "Punto eliminado: " << selectedPoint->getName() << endl;
            selectedPoint = nullptr;
        }
    }
}

bool Graphics::isMouseInRouteWindow(sf::Event& event) {
    return (event.mouseButton.x >= 1000 && event.mouseButton.x <= 1200 &&
        event.mouseButton.y >= 0 && event.mouseButton.y <= 600);
}

void Graphics::selectRoute(sf::Event& event) {
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
    while (current) {
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

void Graphics::deleteRoute() {
    if (!currentRouteName.empty()) {
        RouteNode* routeToDelete = routeList.searchRoute(currentRouteName);
        if (routeToDelete) {
            routeList.removeRoute(currentRouteName);
            cout << "Ruta eliminada: " << currentRouteName << endl;
            currentRouteName = "";
            updateRouteNames();
        }
        else {
            cout << "No se encontró la ruta para eliminar." << endl;
        }
    }
}

void Graphics::drawBackground(sf::RenderWindow& window) {
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("Imagen/Mapa.png")) {
        cerr << "Error al cargar la imagen" << endl;
        return;
    }
    sf::Sprite fondoSprite(fondoTexture);
    window.draw(fondoSprite);
}

void Graphics::drawUI(sf::RenderWindow& window) {
    routeText.setString("Ruta: " + currentRouteName);
    routeText.setPosition(1000, 20);
    window.draw(routeText);
    window.draw(routeWindow);
    drawRoutes(window);

    for (int i = 0; i < 4; ++i) {
        window.draw(colorButtons[i]);
    }

    if (!currentRouteName.empty()) {
        window.draw(deleteButton);
        window.draw(deletePointButton);
        window.draw(deleteButtonText);
        window.draw(deletePointButtonText);
        drawPoints(window);
    }

    window.draw(instructionsText);
}

void Graphics::drawRoutes(sf::RenderWindow& window) {
    for (const auto& routeName : routeNames) {
        window.draw(routeName);
    }
}

void Graphics::drawPoints(sf::RenderWindow& window) {
    RouteNode* currentRoute = routeList.searchRoute(currentRouteName);
    if (currentRoute) {
        PointNode* point = currentRoute->getPointList().getHead();
        vector<sf::Vertex> vertices;

        while (point) {
            sf::CircleShape circle(6);
            if (point == selectedPoint) {
                circle.setFillColor(sf::Color::Red);
            }
            else {
                circle.setFillColor(point->getColor());
            }
            circle.setPosition(point->getX() - 6, point->getY() - 6);
            window.draw(circle);

            sf::Text pointName;
            pointName.setFont(font);
            pointName.setString(point->getName());
            pointName.setCharacterSize(18);
            pointName.setFillColor(sf::Color::Black);
            pointName.setPosition(point->getX() + 10, point->getY() - 10);
            window.draw(pointName);

            vertices.push_back(sf::Vertex(sf::Vector2f(point->getX(), point->getY()), sf::Color::Black));
            point = point->getNext();
        }

        if (vertices.size() > 1) {
            window.draw(&vertices[0], vertices.size(), sf::LinesStrip);
        }
    }
}
