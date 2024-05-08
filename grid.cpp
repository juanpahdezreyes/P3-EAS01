#include "grid.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;


Grid::Grid(int rows, int cols, int width, int height)
{
    this->rows = rows;
    this->cols = cols;
    this->sizeX = width / cols;
    this->sizeY = height / rows;
    for (int i = 0; i < rows; i++)
    {
        this->grid.push_back({});
        for (int j = 0; j < cols; j++)
        {
            this->grid[i].push_back(0);
        }
    }
    this->next = vector<vector<int>>(rows, vector<int>(cols, 0));
}

void Grid::drawTo(RenderWindow &window)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            RectangleShape rect(Vector2f(sizeX, sizeY));
            rect.setOutlineColor(Color::White);
            if (grid[j][i] == 0)
            {
                rect.setFillColor(Color::Black);
            }
            else
            {
                rect.setFillColor(Color::White);
            }
            rect.setOutlineThickness(1);
            rect.setPosition(Vector2f(j * rect.getSize().x, i * rect.getSize().y));
            window.draw(rect);
        }
    }
}

void Grid::click(int x, int y)
{
    int indexX = x / this->sizeX;
    int indexY = y / this->sizeY;
    grid[indexX][indexY] = 1;
}

void Grid::update()
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            if (grid[i][j] == 1) {
                int availableSpaces = contarEspaciosDisponibles(i, j);
                if (availableSpaces > 0) {
                    // Randomly choose one of the available spaces
                    int moveDirection = rand() % availableSpaces;

                    // Move the sand to the chosen direction
                    if (j < cols - 1 && grid[i + 1][j] == 0 && (moveDirection == 0 || (moveDirection == 1 && grid[i + 2][j - 1] == 1))) {
                        next[i + 1][j] = 1;
                    } else if (j > 0 && grid[i + 1][j - 1] == 0 && (moveDirection == 1 || (moveDirection == 0 && grid[i + 2][j + 1] == 1))) {
                        next[i + 1][j - 1] = 1;
                    } else if (j < cols - 1 && grid[i + 2][j] == 0) {
                        next[i + 2][j] = 1;
                    } else if (j > 0 && grid[i + 2][j - 1] == 0) {
                        next[i + 2][j - 1] = 1;
                    } else if (j < cols - 1 && grid[i + 1][j] == 0) {
                        next[i + 1][j] = 1;
                    } else if (j > 0 && grid[i + 1][j - 1] == 0) {
                        next[i + 1][j - 1] = 1;
                    }
                }
            }
        }
    }
    this->grid = this->next;
}

int Grid::contarEspaciosDisponibles(int i, int j)
{
    int availableSpaces = 0;
    if (i < rows - 2 && (grid[i + 1][j] == 0 || (j > 0 && grid[i + 1][j - 1] == 0))) {
        availableSpaces++;
    }
    if (j < cols - 1 && i < rows - 2 && (grid[i + 1][j] == 0 || (j > 0 && grid[i + 1][j - 1] == 0))) {
        availableSpaces++;
    }
    return availableSpaces;
}

