#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
#include "RouteList.h"

class Graphics{
private:
    RouteList& routeList;
    sf::Font font;
    sf::Text routeText;
    sf::RectangleShape routeWindow;
    vector<sf::Text> routeNames;
    string currentRouteName;
    sf::RectangleShape deleteButton;
    sf::Text deleteButtonText;
    sf::RectangleShape deletePointButton;
    sf::Text deletePointButtonText;
    sf::Text instructionsText;
    PointNode* selectedPoint;
    sf::RectangleShape colorButtons[4];
    sf::Color buttonColors[4] = { sf::Color::Blue, sf::Color::Red, sf::Color::Green, sf::Color::Yellow };
    sf::Color currentColor;
public:
    Graphics(RouteList& routeList);
    void display();
    bool selectPoint(sf::Event& event);
    void deleteSelectedPoint();
    bool isMouseInRouteWindow(sf::Event& event);
    void selectRoute(sf::Event& event);
    void updateRouteNames();
    void deleteRoute();
    void drawBackground(sf::RenderWindow& window);
    void drawUI(sf::RenderWindow& window);
    void drawRoutes(sf::RenderWindow& window);
    void drawPoints(sf::RenderWindow& window);

};

