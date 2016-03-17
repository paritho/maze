/********************************************************************
* Breadth-first search
*
* Author: Paul Thompson
*
* Purpose: Creates a breadth-first search method in the BFS class.
* The open_door() function begins the search. BFS uses a queue to
* search sequentially through the maze. It searches the first item
* in the queue, then removes it, adding additional items to the back
* when encountered.
*
********************************************************************/

#ifndef BFS_HPP
#define BFS_HPP

#include "search.hpp"
#include "visitor.hpp"
#include "maze.hpp"
#include "queue.hpp"
#include "iostream.hpp"

struct BFS {
    Maze maze;
    Location l;
    Color_table c;
    Queue<Location> q;
    Visitor& v;
public:
    // Constructor sets the member variables with the
    // supplied maze and visitor objects.
    BFS(Maze const& m, Visitor& v):
            maze(m),
            l(0,0),
            c(m.dims()),
            q(),
            v(v)
    { }

    // Open_door() begins the search. On first run it
    // pushes the start location (0,0) to the queue.
    // Then, it searches each location in the queue,
    // front to back.
    bool open_door(){
        q.push(l);
        while(!q.is_empty()){
            // Get the location at the front of the q
            Location loc = q.front();
            q.pop();

            // If the current location is the exit,
            // stop searching
            if(maze(loc).is_exit()) {
                v.draw(maze, c);
                return true;
            }
            search(loc);

            // Done searching this location, color it black
            c(loc) = Black;
        }
        v.draw(maze, c);
        return false;
    }

    // Search makes four calls to check(), one each for the
    // tiles surrounding the given location
    void search(Location l){
        check(l.north());
        check(l.south());
        check(l.east());
        check(l.west());
    }

    // Check() determines if a tile is in the maze
    // (is_valid), is a wall (is_wall) and if the tile
    // has been searched previously (color == White).
    // If all these conditions pass, the location is
    // sent to the end of the queue with enq().
    void check(Location l){
        if(maze.is_valid(l))
            if(!maze.is_wall(l))
                if(color(l) == White)
                    enq(l);
    }

    // Get the color of the given location
    Color color(Location l){ return c(l);}

    // Marks the location as visited (gray) and pushes
    // it onto the queue
    void enq(Location l) {
        c(l) = Gray;
        q.push(l);
    }

};

#endif
