/********************************************************************
* Depth-first search
*
* Author: Paul Thompson
*
* Purpose: Creates a depth-first search method in the class DFS. The
* function open_door() starts the search and returns true if a
* solution to the maze was found.
*
********************************************************************/

#ifndef DFS_HPP
#define DFS_HPP

#include "search.hpp"
#include "visitor.hpp"


struct DFS {
    Maze maze;
    Location l;
    Color_table c;
    Visitor& v;
public:
    // Constructor sets the member variables with the
    // supplied maze and visitor objects
    DFS(Maze const&m, Visitor& v):
         maze(m),
         l(0,0),
         c(maze.dims()),
         v(v)
    { }

    // Begins the search
    bool open_door(){
        bool temp = dfs(l);
        v.draw(maze, c);
        return temp;
    }

    // dfs() takes a location object and searches its
    // neighboring tiles for the exit. Once all four
    // neighbor tiles have been searched as far as they
    // can be, the current location is colored black.
    bool dfs(Location l){
        if(maze(l).is_exit()) return true;

        bool found = check(l.north())
                ||   check(l.south())
                ||   check(l.east())
                ||   check(l.west());

        c(l) = Black;
        return found;
    }

    // Check() determines if a tile is in the maze
    // (is_valid), is a wall (is_wall) and if the tile
    // has been searched previously (color == White).
    // If all these conditions pass, push() recurses
    // back to dfs()
    bool check(Location l){
        if(maze.is_valid(l))
            if(!maze.is_wall(l))
                if(color(l) == White)
                    return push(l);
        return false;
    }

    // Get the current color of Location l
    Color color(Location l){ return c(l);}

    // push() simulates pushing onto a stack with recursion.
    // Before recursing, the location is colored gray to
    // indicate visited.
    bool push(Location l){
        c(l) = Gray;
        return dfs(l);
    }

};


#endif
