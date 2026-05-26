#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
            sf::VideoMode(800, 600),
            "ShapeBuilder"
            );
     // Main loop — keeps the window open
    while (window.isOpen())
    {
        // Event loop — checks for stuff like close window
        sf::Event event;
        while (window.pollEvent(event))
        {
            // close the window
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape, also close
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        // Clear screen with a dark background each frame
        window.clear(sf::Color(30, 30, 30));

        // shapes

        // display
        window.display();
    }

    return 0;
}
