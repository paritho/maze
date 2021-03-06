
#include "maze.hpp"
#include "generate.hpp"
#include "search.hpp"
#include "bfs.hpp"
#include "dfs.hpp"
#include "iostream.hpp"
#include "visitor.hpp"
#include "curses.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>


constexpr auto E = Tile::Empty;
constexpr auto W = Tile::Wall;
constexpr auto X = Tile::Exit;


// Control flags.
enum Flags
{
    Exec_bfs = 0x01,
    Exec_dfs = 0x02,
    Exec_both = Exec_bfs | Exec_dfs
};


int 
main(int argc, char** argv)
{
    std::srand(std::time(0));

    Flags exec = Exec_both;
    if (argc == 2) {
        std::string a = argv[1];
    if (a == "bfs")
        exec = Exec_bfs;
    if (a == "dfs")
        exec = Exec_dfs;
    }

    // Visitor config.
    Headless_visitor hvis;
    Ostream_visitor iovis;
    Visitor& vis = iovis;


    // Maze m(10, 10);
    Maze m(40, 80);
    generate(m, vis);
    //vis.draw(m);

    // Create the objects that will perform the searches
    // BFS will use breadth-first searching, while DFS will use
    // depth-first searching
    BFS bf(m, vis);
    DFS df(m, vis);

    std::cout << "\npress any key to start";
    std::cin.get();

    if (exec & Exec_bfs) {
        if (bf.open_door())
            std::cout << "\nsolved!\n";
        else
            std::cout << "\nno solution!\n";
    std::cin.get();
    }

    if (exec & Exec_dfs) {
        if (df.open_door())
            std::cout << "\nsolved!\n";
        else
            std::cout << "\nno solution!\n";
    std::cin.get();
  }
}
