#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <cstdlib>

using namespace sf;

int main()
{
    int width = 800;
    int height = 600;
    int rows = 40;
    int cols = 30;

    RenderWindow window(VideoMode(width, height), "Sand Simulation");

    Grid grid(rows, cols, width, height);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    grid.click(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        grid.update();

        window.clear();
        grid.drawTo(window);
        window.display();
    }

    return 0;
}
