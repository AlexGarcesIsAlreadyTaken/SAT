#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h> 
#include "SAT.hh"

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "Window");
    sf::CircleShape square(100, 4);
    sf::CircleShape triangle(100, 3);
    
    sf::Vector2f sq_position = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f tr_position = sf::Vector2f(25.0f + 300.f, 25.f + 30.f);

    float sq_rotation = 0.0f;

    square.setFillColor(sf::Color::Black);
    square.setOutlineThickness(3.0f);
    square.setOutlineColor(sf::Color::Blue);
    square.setOrigin(square.getRadius(), square.getRadius());
    square.setPosition(sq_position);

    triangle.setFillColor(sf::Color::Black);
    triangle.setOutlineThickness(3.0f);
    triangle.setOutlineColor(sf::Color::Green);
    triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
    triangle.setPosition(tr_position);
    
    window.setFramerateLimit(144);

    SAT sat;
    sf::Clock clock;
    
    window.clear();
    window.draw(triangle);
    window.draw(square);
    window.display();

    
    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2f sq_velocity = sf::Vector2f(0.0, 0.0);
        sf::Vector2f tr_velocity = sf::Vector2f(0.0, 0.0);
        float delta_rotation = 0.0f;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                        delta_rotation += 80.0f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                        delta_rotation -= 80.0f;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        sq_velocity.x -= 250.0f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        sq_velocity.x += 250.0f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                        sq_velocity.y -= 250.0f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        sq_velocity.y += 250.0f;
                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        tr_velocity.x -= 250.0f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        tr_velocity.x += 250.0f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        tr_velocity.y -= 250.0f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        tr_velocity.y += 250.0f;
        }

        float delta_time = clock.restart().asSeconds();
        
        sq_position += sq_velocity * delta_time;
        sq_rotation += delta_rotation * delta_time;
        tr_position += tr_velocity * delta_time;

        if (sq_velocity != sf::Vector2f(0.0, 0.0) or delta_rotation != 0.0f or tr_velocity != sq_velocity) {
            sf::Vector2f auxPos = square.getPosition();
            sf::Vector2f aux2Pos = triangle.getPosition();
            float auxRot = square.getRotation();
            square.setPosition(sq_position);
            square.setRotation(sq_rotation);
            triangle.setPosition(tr_position);
           if (sat.collides(square, triangle, window)) {
               square.setPosition(auxPos);
               square.setRotation(auxRot);
               triangle.setPosition(aux2Pos);
               square.setFillColor(sf::Color::Red);
           }
           else square.setFillColor(sf::Color::Black);
        }
        window.draw(triangle);
        window.draw(square);
        window.display();
        window.clear();
    }
}
