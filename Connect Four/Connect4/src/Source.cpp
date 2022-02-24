#include <iostream>
#include <array>

enum class Color
{
    none = 0,
    red = 1,
    yellow = 2
};

typedef std::array<std::array<Color, 7>, 6> Grid;

void initialize(Grid& grid);
void display(const Grid& grid);
void game(Grid& grid, Color const& player_color);
bool isWin(const Grid& grid, Color const& player_color);
bool isFull(const Grid& grid);

int main()
{
    Grid grid;

    initialize(grid);
    display(grid);

    Color player_color(Color::yellow);
    bool bWin;

    do {
        std::cout << "Player ";
        if (player_color == Color::yellow) { std::cout << 'X'; }
        else { std::cout << 'O'; }
        std::cout << ", Your choice: " << std::endl;

        game(grid, player_color);
        display(grid);
        bWin = isWin(grid, player_color);

        if (player_color == Color::yellow) { player_color = Color::red; }
        else { player_color = Color::yellow; }

    } while (!bWin && ! isFull(grid));

    if (bWin) 
    {
        std::cout << "The player ";
        if (player_color == Color::yellow) { std::cout << 'O'; }
        else { std::cout << 'X'; }
        std::cout << " wins' !" << std::endl;
    }
    else { std::cout << "Draw !" << std::endl; }

    return 0;
}

void initialize(Grid& grid)
{
    for (auto& line : grid) 
    {
        for (auto& kase : line) 
        {
            kase = Color::none;
        }
    }
}

void display(const Grid& grid)
{
    std::cout << std::endl;

    for (auto line : grid) {
        std::cout << " |";
        for (auto kase : line) 
        {
            if (kase == Color::none) { std::cout << ' '; }
            else if (kase == Color::red) { std::cout << 'O'; }
            else { std::cout << 'X'; }
            std::cout << '|';
        }
        std::cout << std::endl;
    }

    std::cout << '=';
    for (size_t i(1); i <= grid[0].size(); ++i) 
    {
        std::cout << '=' << i;
    }
    std::cout << "==";

    std::cout << std::endl << std::endl;
}

bool play(Grid& grid, size_t column, Color color)
{
    // if column is invalid
    if (column >= grid[0].size()) { return false; }

    size_t line(grid.size() - 1);
    while ((line < grid.size()) && (grid[line][column] != Color::none)) 
    {
        --line;
    }

    if (line < grid.size()) 
    {
        grid[line][column] = color;
        return true;
    }
    else { return false; }
}

unsigned int count(const Grid& grid, size_t const& start_line, size_t const& start_column, int const& direction_line, int const& direction_column)
{
    unsigned int counter(0);

    size_t line(start_line);
    size_t column(start_column);

    while (grid[line][column] == grid[start_line][start_column])
    {
        ++counter;
        line = line + direction_line;
        column = column + direction_column;
    }

    return counter;
}

bool isWin(const Grid& grid, Color const& player_color)
{
    for (size_t line(0); line < grid.size(); ++line) 
    {
        for (size_t column(0); column < grid[line].size(); ++column) 
        {
            Color couleur_case(grid[line][column]);

            if (couleur_case == player_color) 
            {
                const size_t ligne_max(grid.size() - 4);
                const size_t colonne_max(grid[line].size() - 4);
                if (
                    // diagonally, up and to the right
                    (line >= 3 && column <= colonne_max &&
                        count(grid, line, column, -1, +1) >= 4) ||

                    // horizontally, to the right
                    (column <= colonne_max &&
                        count(grid, line, column, 0, +1) >= 4) ||

                    // diagonally, down and to the right
                    (line <= ligne_max && column <= colonne_max &&
                        count(grid, line, column, +1, +1) >= 4) ||

                    // vertically, downwards
                    (line <= ligne_max &&
                        count(grid, line, column, +1, 0) >= 4)) {

                    return true;
                }
            }
        }
    }

    return false;
}

// ======================================================================
void game(Grid& grid, Color const& player_color)
{
    size_t column;
    bool bLegit;

    do {
        std::cin >> column;
        --column;

        bLegit = play(grid, column, player_color);
        if (!bLegit) { std::cout << " > You can not play here" << std::endl; }
    } while (!bLegit);
}

bool isFull(Grid const& grid)
{
    for (auto kase : grid[0]) 
    {
        if (kase == Color::none) { return false; }
    }

    return true;
}