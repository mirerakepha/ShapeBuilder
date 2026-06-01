#include <SFML/Graphics.hpp>
#include <iostream>
#include "input/Mouse.hpp"
#include "input/Keyboard.hpp"
#include "shapes/ShapeManager.hpp"
#include "ui/Dialog.hpp"
#include "Camera.hpp"

int main()
{
    sf::RenderWindow window(
            sf::VideoMode(1000, 800),
            "ShapeBuilder"
            );
    window.setFramerateLimit(60);

    /*
    // move square (WASD)
    sf::RectangleShape box(sf::Vector2f(40.f, 40.f));
    box.setFillColor(sf::Color(100, 100, 255));
    box.setOrigin(20.f, 20.f);
    box.setPosition(400.f, 300.f); //center
    */
    
    Mouse mouse;
    Keyboard keyboard;
    ShapeManager shapes;
    Dialog dialog(window.getSize());
    Camera camera(window.getSize());

    /*
    // blocks spawn point
    sf::Vector2f windowCenter(
            window.getSize().x / 2.f,
            window.getSize().y / 2.f
            );
    */

    sf::Vector2f worldMouse;
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

            // camera handles scroll
            camera.handleEvent(event);

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
                worldMouse = camera.screenToWorld(
                        window,
                        mouse.getScreenPosition()
                        );
               shapes.handleEvent(event, worldMouse);

                // ctrl + Z
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z && event.key.control)
                {
                    shapes.undo();
                }

                /*
                // reset
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
                {
                    box.setPosition(400.f, 300.f);
                }
                */

            }

            // dialog events independdently
            dialog.handleEvent(event);

        }
        if (dialog.wasConfirmed())
        {
            sf::Vector2f worldCenter = camera.screenToWorld(
                    window,
                    sf::Vector2i(
                        window.getSize().x / 2,
                        window.getSize().y / 2
                        )
                    );
            if (dialog.getConfirmedTab() == 0)
            {
                shapes.spawnBlock(dialog.getSelectedCells(), worldCenter);
            }
            else 
            {
                // offset each materiala so they dont stack on each other
                float offsetX = 0.f;
                for (const auto& mat : dialog.getMaterials())
                {
                    for (int i = 0; i < mat.count; i++)
                    {
                        sf::Vector2f pos(worldCenter.x + offsetX, worldCenter.y);
                        shapes.spawnMaterialBlock(mat.color, pos);
                        offsetX += 50.f;
                    }
                }
                dialog.resetMaterialsCount();
            }
        } 

        worldMouse = camera.screenToWorld(
                window,
                mouse.getScreenPosition()
                );

        mouse.update(window);
        camera.update();
        // keyboard.update(box);
        shapes.update(worldMouse);
        // Clear screen with a dark background each frame
        window.clear(sf::Color(30, 30, 30));
        // window.draw(box);
        camera.applyWorldView(window);
        shapes.draw(window);

        camera.applyUIView(window);

        mouse.draw(window);
        dialog.draw(window);
        // display
        window.display();
    }

    return 0;
}
