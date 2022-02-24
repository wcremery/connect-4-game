#include <iostream>
#include <array>
using namespace std;

enum class Color
{
    none = 0,
    red = 1,
    yellow = 2
};

typedef array<array<Color, 7>, 6> Grid;

void initialize(Grid& grid);
void display(const Grid& grid);
void game(Grid& grid, Color const& player_color);
bool isWin(const Grid& grid, Color const& player_color);
bool full(const Grid& grid);

int main()
{
    Grid grid;

    initialize(grid);
    display(grid);

    Color player_color(Color::yellow);
    bool bWin;

    do {
        cout << "Player ";
        if (player_color == Color::yellow) { cout << 'X'; }
        else { cout << 'O'; }
        cout << ", Your choice: " << endl;

        game(grid, player_color);
        display(grid);
        bWin = isWin(grid, player_color);

        if (player_color == Color::yellow) { player_color = Color::red; }
        else { player_color = Color::yellow; }

    } while (!bWin && ! full(grid));

    if (bWin) 
    {
        cout << "The player ";
        if (player_color == Color::yellow) { cout << 'O'; }
        else { cout << 'X'; }
        cout << " wins' !" << endl;
    }
    else { cout << "Draw !" << endl; }

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
    cout << endl;

    for (auto line : grid) {
        cout << " |";
        for (auto kase : line) 
        {
            if (kase == Color::none) { cout << ' '; }
            else if (kase == Color::red) { cout << 'O'; }
            else { cout << 'X'; }
            cout << '|';
        }
        cout << endl;
    }

    cout << '=';
    for (size_t i(1); i <= grid[0].size(); ++i) 
    {
        cout << '=' << i;
    }
    cout << "==";

    cout << endl << endl;
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
        cin >> column;
        --column;

        bLegit = play(grid, column, player_color);
        if (!bLegit) { cout << " > You can not play here" << endl; }
    } while (!bLegit);
}

bool full(Grid const& grid)
{
    for (auto kase : grid[0]) 
    {
        if (kase == Color::none) { return false; }
    }

    return true;
}