#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(
            sf::VideoMode(800, 600),
            "ShapeBuilder"
            );

    // mouse tracker
    sf::CircleShape cursor(5.f);
    cursor.setFillColor(sf::Color(255, 100, 100));
    cursor.setOrigin(5.f, 5.f); // mouse pos

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

            // Mouse events       
            if (event.type == sf::Event::MouseButtonPressed){
                // Left click
                if (event.mouseButton.button == sf::Mouse::Left){
                    std::cout << "Left click: "
                        << event.mouseButton.x << ", "
                        << event.mouseButton.y << "\n";
                }
                // right click
                if (event.mouseButton.button == sf::Mouse::Right){
                    std::cout << "Right Click: "
                        << event.mouseButton.x << ", "
                        << event.mouseButton.y << "\n";
                }
            }
            // release mouseButton
            if (event.type == sf::Event::MouseButtonReleased){
                std::cout << "Mouse button releaseds";
            }
            // scroll wheel
            if (event.type == sf::Event::MouseWheelScrolled){
                if (event.mouseWheelScroll.delta > 0)
                    std::cout << "Scrolled up";
                else 
                    std::cout << "Scrolled down";
            }
            //RT mouse pos
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // track
            cursor.setPosition(
                    static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y)
            );
        }

        // Clear screen with a dark background each frame
        window.clear(sf::Color(30, 30, 30));
        window.draw(cursor); // show mouse tracker

        // shapes

        // display
        window.display();
    }

    return 0;
}
