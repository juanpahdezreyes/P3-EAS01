#ifndef Grid_hpp
#define Grid_hpp

#include <SFML/Graphics.hpp>
#include <vector>

class Grid {
private:
    int rows;
    int cols;
    int sizeX;
    int sizeY;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> next;

public:
    Grid(int rows, int cols, int width, int height);

    void drawTo(sf::RenderWindow &window);

    void click(int x, int y);

    void update();

private:
    int contarEspaciosDisponibles(int i, int j);
};

#endif /* Grid_hpp */