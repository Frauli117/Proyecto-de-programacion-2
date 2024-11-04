#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
#include "RouteList.h"

class Graphics
{
private:
    RouteList& routeList;
    sf::Font font;
    sf::Text routeText;
    sf::RectangleShape routeWindow;
    vector<sf::Text> routeNames;
    string currentRouteName; // Almacena la ruta actualmente seleccionada
public:
    Graphics(RouteList& routeList);
    void display();
    bool isMouseInRouteWindow(sf::Event& event, sf::RenderWindow& window);
    void selectRoute(sf::Event& event, sf::RenderWindow& window);
    void updateRouteNames();
    void drawRoutes(sf::RenderWindow& window);
    void drawPoints(sf::RenderWindow& window);

};


