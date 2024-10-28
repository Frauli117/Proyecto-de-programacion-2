#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>

int main() {
    //Crear una ventana de 800x600 píxeles
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dibujar con el mouse");

    //Vector para almacenar las líneas dibujadas
    std::vector<sf::Vertex> lines;

    bool isDrawing = false;

    //Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Cerrar la ventana
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Iniciar el dibujo cuando se mantiene el clic izquierdo
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                isDrawing = true;
            }

            // Detener el dibujo cuando se suelta el clic izquierdo
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isDrawing = false;
            }

            // Limpiar la pantalla si se presiona clic derecho
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                lines.clear();
            }
        }

        // Dibujar solo si se mantiene el clic izquierdo
        // Verificamos si la variable isDrawing es verdadera, lo que significa que el usuario está manteniendo presionado el botón izquierdo del mouse.
        if (isDrawing) {
            // Obtener la posición actual del mouse dentro de la ventana
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // Añadir la posición actual del mouse como un nuevo vértice (punto) en el vector lines.
            // Este vértice es representado con coordenadas en el espacio 2D de la ventana y se dibuja de color blanco.
            lines.push_back(sf::Vertex(sf::Vector2f(mousePos.x, mousePos.y), sf::Color::White));
        }

        // Limpiar la ventana
        // Antes de dibujar cualquier cosa, se limpia el contenido actual de la ventana para que no quede información residual de fotogramas anteriores.
        window.clear();

        // Dibujar las líneas almacenadas
        // Verificamos si el vector lines no está vacío (es decir, si hay puntos que dibujar).
        if (!lines.empty()) {
            // Si hay puntos en lines, se dibujan como una línea continua conectada entre ellos usando sf::LinesStrip.
            // sf::LinesStrip dibuja una serie de vértices conectados, formando una línea desde el primer punto hasta el último.
            window.draw(&lines[0], lines.size(), sf::LinesStrip);
        }

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
