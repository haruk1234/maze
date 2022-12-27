#include <iostream>
#include "../maze.h"


Maze maze(10,10);
void showmaze() {
    for (int y=0;y<maze.size[1];y++) {
        for (int x=0;x<maze.size[0];x++) {
            if (maze.maze[y][x]==0) {
                std::cout << "WW";
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
	std::cout << "Maze Test" << std::endl;
    showmaze();
    return 0;
}