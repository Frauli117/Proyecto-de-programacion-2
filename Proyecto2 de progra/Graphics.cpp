#include "Graphics.h"

Graphics::Graphics(RouteList& routeList) : routeList(routeList) {
    if (!font.loadFromFile("Fuente/ARIAL.ttf")) {
        // Manejar error
    }
    routeText.setFont(font);
    routeText.setCharacterSize(24);
    routeText.setFillColor(sf::Color::Black);

    // Configurar la "ventanita" para mostrar las rutas
    routeWindow.setSize(sf::Vector2f(200, 600));
    routeWindow.setFillColor(sf::Color(200, 200, 200, 255));
    routeWindow.setPosition(1000, 0);
    currentRouteName = ""; // Inicialmente no hay ruta seleccionada
}

void Graphics::display() {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Mapa de Rutas Turísticas");
    string currentPointName = "";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Detectar clic izquierdo para agregar puntos a la ruta seleccionada
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

        // Limpiar la ventana
        window.clear();

        // Cargar la textura de fondo
        sf::Texture fondoTexture;
        if (!fondoTexture.loadFromFile("Imagen/mapa de Costa Rica.jpg")) {
            return; // Manejo de error si no se puede cargar la imagen
        }
        sf::Sprite fondoSprite(fondoTexture);
        window.draw(fondoSprite);

        // Mostrar el nombre de la ruta en la esquina superior derecha
        routeText.setString("Ruta: " + currentRouteName);
        routeText.setPosition(1000, 20);
        window.draw(routeText);

        // Dibujar la ventanita con las rutas
        window.draw(routeWindow);
        drawRoutes(window);

        // Dibujar puntos turísticos
        drawPoints(window);

        // Mostrar todo en la ventana
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
            currentRouteName = routeNames[i].getString(); // Cambia la ruta actual
            cout << "Ruta seleccionada: " << currentRouteName << endl; // Confirmación en consola
            return;
        }
    }
    // Si no se hace clic en una ruta, solicita el nombre de una nueva ruta
    cout << "Nombre de la nueva ruta: ";
    cin >> currentRouteName;
    routeList.insertRoute(currentRouteName);
    updateRouteNames();
}

void Graphics::updateRouteNames() {
    routeNames.clear();
    RouteNode* current = routeList.getHead();
    int yOffset = 30; // Espacio entre nombres de rutas
    while (current != nullptr) {
        sf::Text routeName;
        routeName.setFont(font);
        routeName.setString(current->getName());
        routeName.setCharacterSize(24);
        routeName.setFillColor(sf::Color::Black);
        routeName.setPosition(1010, yOffset);
        routeNames.push_back(routeName);
        yOffset += 30; // Actualizar el offset para la siguiente ruta
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
            // Dibujar el círculo del punto
            sf::CircleShape circle(5); // Tamaño del punto
            circle.setFillColor(sf::Color::Red);
            circle.setPosition(point->getX(), point->getY());
            window.draw(circle);

            // Crear y dibujar el texto del nombre del punto
            sf::Text pointName;
            pointName.setFont(font);
            pointName.setString(point->getName());
            pointName.setCharacterSize(18); // Tamaño del texto
            pointName.setFillColor(sf::Color::Black);
            // Ajustar la posición del texto para que esté al lado del punto
            pointName.setPosition(point->getX() + 10, point->getY() - 10); // Desplazar a la derecha y hacia arriba

            window.draw(pointName); // Dibujar el texto

            point = point->getNext();
        }
        currentRoute = currentRoute->getNext();
    }
}
