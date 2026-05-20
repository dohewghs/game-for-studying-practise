#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// g - grass
// d - dirt

struct Block
{
    const int w = 35;
    const int h = 35;

    long x;
    long y;
    char type;

    Block(int col, int row, char type)
    {
        x = w * col;
        y = h * row;
        this->type = type;
    }
    
    std::string toString()
    {
        std::stringstream ss;

        // Пишемо туди все, що завгодно, чергуючи текст, змінні та числа
        ss << this->x
            << ' ' << this->y
            << ' ' << this->w
            << ' '<< this->h
            << ' '<< this->type;

        return ss.str(); // Повертаємо зібраний рядок
    }
};


int main()
{
    std::vector<Block> blocks;

    std::ifstream inFile("Source.txt");

    if (!inFile.is_open())
    {
        std::cerr << "Не вдалося відкрити файл для читання!" << std::endl;
        return 1;
    }

    long column = 0;
    long j = 0;

    std::string line;

    while (std::getline(inFile, line))
    {
        for (char symbol : line)
        {
            switch (symbol)
            {
            case '.':
                column++;
                break;
            case 'g':
                column++;
                blocks.push_back(Block(column, j, 'g'));
                break;
            case 'd':
                column++;
                blocks.push_back(Block(column, j, 'd'));
                break;
            default:
                break;
            }
        }
        ++j;
        column = 0;
    }

    inFile.close();

    std::ofstream outFile("..//..//assets//Maps//map1.txt");

    for (Block bl : blocks)
    {
        outFile << bl.toString() << std::endl;
    }
    outFile.close();
	return 0;
}