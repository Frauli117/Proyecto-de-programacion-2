#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>

int main() {
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Ventana con Imagen de Fondo");

    // Cargar la textura de la imagen de fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("Imagen/mapa de Costa Rica.jpg")) {
        return -1; // Manejo de error si no se puede cargar la imagen
    }

    // Crear un sprite para la textura de fondo
    sf::Sprite fondoSprite;
    fondoSprite.setTexture(fondoTexture);

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar la imagen de fondo
        window.draw(fondoSprite);

        // Mostrar todo en la ventana
        window.display();
    }

    return 0;
}
