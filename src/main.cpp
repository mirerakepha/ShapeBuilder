#include <SFML/Graphics.hpp>
#include <iostream>
#include "input/Mouse.hpp"
#include "input/Keyboard.hpp"
#include "shapes/ShapeManager.hpp"
#include "ui/Dialog.hpp"


int main()
{
    sf::RenderWindow window(
            sf::VideoMode(1000, 800),
            "ShapeBuilder"
            );

    // move square (WASD)
    sf::RectangleShape box(sf::Vector2f(40.f, 40.f));
    box.setFillColor(sf::Color(100, 100, 255));
    box.setOrigin(20.f, 20.f);
    box.setPosition(400.f, 300.f); //center

    Mouse mouse;
    Keyboard keyboard;
    ShapeManager shapes;
    Dialog dialog(window.getSize());

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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
            {
                dialog.toggle();
            }

            // pass events to the game when dialo isn't open
            if (!dialog.isOpen())
            {

                // mouse events
                mouse.handleEvent(event);
                // Keyboard events
                keyboard.handleEvent(event, window);

               // hitTest
               shapes.handleEvent(event, mouse.getPosition());

                // ctrl + Z
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z && event.key.control)
                {
                    shapes.undo();
                }

                // reset
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
                {
                    box.setPosition(400.f, 300.f);
                }

            }

            // dialog events independdently
            dialog.handleEvent(event);
        }
        if (dialog.wasConfirmed())
        {
            const auto& cells = dialog.getSelectedCells();

            //print the no of cells selected
            std::cout << "Spawn pattern: \n";
            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 3; col++)
                {
                    std::cout << (cells[row * 3 + col] ? "X" : ".");
                }
                std::cout << "\n";
            }
        }

        mouse.update(window);
        keyboard.update(box);
        shapes.update(mouse.getPosition());
        // Clear screen with a dark background each frame
        window.clear(sf::Color(30, 30, 30));
        shapes.draw(window);
        window.draw(box);

        mouse.draw(window);
        dialog.draw(window);
        // display
        window.display();
    }

    return 0;
}
