#include <SFML/Graphics.hpp>
#include <iostream>

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

    // mouse tracker
    sf::CircleShape cursor(5.f);
    cursor.setFillColor(sf::Color(255, 100, 100));
    cursor.setOrigin(5.f, 5.f); // mouse pos

    // Drag state
    bool isDragging = false;
    sf::Vector2f dragStart;

    // mvt speed
    const float baseSpeed = 4.f;
    const float fastSpeed = 10.f;

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

            // Keyboard events
            if (event.type == sf::Event::KeyPressed){
                // ESC closes
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                // reset
                if (event.key.code == sf::Keyboard::R){
                    box.setPosition(400.f, 300.f);
                    std::cout << "Reset\n";
                }
            }

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
            

            // ===== dragging =========
            // start dragging
            if (event.type == sf::Event::MouseButtonPressed && 
                    event.mouseButton.button == sf::Mouse::Left){
                isDragging = true;
                dragStart = sf::Vector2f(
                        static_cast<float>(event.mouseButton.x),
                        static_cast<float>(event.mouseButton.y)
                        );
                std::cout << "Drag started: "
                    << dragStart.x << ", "
                    << dragStart.y << "\n";
            }
            // dgar end
            if (event.type == sf::Event::MouseButtonReleased &&
                    event.mouseButton.button == sf::Mouse::Left){
                if (isDragging) {
                    sf::Vector2f dragEnd = sf::Vector2f(
                            static_cast<float>(event.mouseButton.x),
                            static_cast<float>(event.mouseButton.y)
                            );
                }
                isDragging = false;
            }

            // check if shift is held for speed mvt
            bool shiftHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

            float speed = shiftHeld ? fastSpeed : baseSpeed;

            //current box pos
            sf::Vector2f pos = box.getPosition();

            // keys
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) pos.y -= speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) pos.y += speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) pos.x -= speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) pos.x += speed;

            // box stays within the window
            pos.x = std::max(20.f, std::min(pos.x, 980.f));
            pos.y = std::max(20.f, std::min(pos.y, 780.f));

            box.setPosition(pos);


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

        // change tracker color when draggind
        if (isDragging)
            cursor.setFillColor(sf::Color(100, 255, 100)); //Green
        else
            cursor.setFillColor(sf::Color(255, 100, 100)); //Red

        window.draw(cursor); // show mouse tracker
        window.draw(box);

        // shapes

        // display
        window.display();
    }

    return 0;
}
