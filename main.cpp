#include <iostream>
#include <sstream>
#include <vector>

#include <Graphics.hpp>
#include <System.hpp>
#include <Window.hpp>
#include <Audio.hpp>
#include <Network.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Works!", sf::Style::Default);
    window.setFramerateLimit(120);

    // Init game
    float gridSizeF = 100.f;
    unsigned gridSize = static_cast<unsigned>(gridSizeF);
    float deltaTime;
    sf::Clock dtClock;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2i mousePosView;
    sf::Vector2i mousePosGrid;

    sf::Font font;
    font.loadFromFile("Fonts/nulshock.otf");

    sf::Text text;
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, 20.f);
    text.setString("TEST");

    // init window
    sf::View view;
    view.setSize(1920.f, 1080.f);
    view.setCenter(window.getSize().x/2.f, window.getSize().y/2.f);
    float viewSpeed = 200.f;

    // init game elements
    sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));

    int mapSize = 1000;
    std::vector<std::vector<sf::RectangleShape>> tileMap;
    tileMap.resize(mapSize, std::vector<sf::RectangleShape>());

    for(size_t x = 0; x < mapSize; x++)
    {
        tileMap[x].resize(mapSize, sf::RectangleShape());
        for(size_t y = 0; y < mapSize; y++)
        {
            tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tileMap[x][y].setFillColor(sf::Color(123, 123, 123, 255));
            tileMap[x][y].setOutlineThickness(1.f);
            tileMap[x][y].setOutlineColor(sf::Color::Black);
            tileMap[x][y].setPosition(x * gridSizeF,y * gridSizeF);
        }
    }

    int fromX = 0;
    int toX = 0;
    int fromY = 0;
    int toY = 0;

    sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(3.f);
    tileSelector.setOutlineColor(sf::Color::Red);

    while(window.isOpen())
    {
        // Update DT
        deltaTime = dtClock.restart().asSeconds();

        // Update mouse pos
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = static_cast<sf::Vector2i>(window.mapPixelToCoords(mousePosWindow));
        mousePosGrid.x = static_cast<int>(mousePosView.x) / gridSizeF;
        mousePosGrid.y = static_cast<int>(mousePosView.y) / gridSizeF;
        window.setView(window.getDefaultView());

        // Update game elements
        tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);

        // Update Ui
        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

        text.setString(ss.str());

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

        }

        // Update

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Left
        {
            view.move(-viewSpeed * deltaTime, 0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Right
        {
            view.move(viewSpeed * deltaTime, 0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Up
        {
            view.move(0.f, -viewSpeed * deltaTime);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Down
        {
            view.move(0.f, viewSpeed * deltaTime);
        }

        // render
        window.clear();

        // Render
        window.setView(view);
        // window.draw(shape);

        fromX = view.getCenter().x / gridSizeF - 4;
        toX = view.getCenter().x / gridSizeF + 5;

        fromY = view.getCenter().y / gridSizeF - 4;
        toY = view.getCenter().y / gridSizeF + 5;

        if(fromX < 0)
            fromX = 0;
        else if (fromX >= mapSize)
            fromX = mapSize - 1;
        if(toX < 0)
            toX = 0;
        else if (toX >= mapSize)
            toX = mapSize - 1;

        if(fromY < 0)
            fromY = 0;
        else if (fromY >= mapSize)
            fromY = mapSize - 1;
        if(fromX < 0)
            fromX = 0;
        else if (fromX >= mapSize)
            fromX = mapSize - 1;

        for(size_t x = fromX; x < toX; x++)
        {
            for(size_t y = fromY; y < toY; y++)
            {
                window.draw(tileMap[x][y]);
            }
        }

        window.draw(tileSelector);


        // Ui
        window.setView(window.getDefaultView());

        window.draw(text);

        window.display();
    }

    return 0;
}

