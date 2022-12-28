#ifndef NeknajMaze
#define NeknajMaze

#include <array>
#include <vector>
#include <cmath>
#include <random>

// https://ja.wikipedia.org/wiki/Xorshift
struct xorshift64_state {
  uint64_t a;
};
uint64_t xorshift64(struct xorshift64_state *state)
{
	uint64_t x = state->a;
	x ^= x << 7;
	x ^= x >> 9;
	return state->a = x;
}
//


typedef std::vector<std::vector<unsigned char>> MazeObj;
class Maze {
    private:
        typedef std::array<int,2> location;
    public:
        location start;
        location goal;
        std::array<int,2> size;
        MazeObj maze;
        Maze(unsigned int x,unsigned int y) {
            osize[0] = (int)x;
            osize[1] = (int)y;
            makemaze();
            return;
        }
    private:
        std::array<int,2> osize;
        std::vector<location> deadend;
        std::random_device rnd;
        xorshift64_state rndm;
        void makemaze() {
            rndm.a = rnd();
            int x = osize[0];int y = osize[1];
            size[0] = x*2+1;size[1] = y*2+1;
            maze.clear();
            maze.assign(y*2+1,std::vector<unsigned char>(x*2+1,0));
            maze[std::floor(xorshift64(&rndm)%y)*2+1][std::floor(xorshift64(&rndm)%x)*2+1] = 1;
            while (searchwall(x,y)) {
                int lx = std::floor(xorshift64(&rndm)%x);
                int ly = std::floor(xorshift64(&rndm)%y);
                std::vector<char> ra = searcharound(lx,ly,x,y);
                makenewroad(lx,ly,ra);
            }
        }
        bool searchwall(int x,int y) {
            for (int ly=0;ly<y;ly++) {
                for (int lx=0;lx<x;lx++) {
                    if (maze[ly*2+1][lx*2+1]==0) {return true;}
                }
            }
            return false;
        }
        std::vector<char> searcharound(int cx,int cy,int x,int y) {
            int ax = cx*2+1;int ay = cy*2+1;
            std::vector<char> ra = {};
            if (maze[ay][ax]==0) {return ra;}
            if (cy>0&&maze[ay-2][ax]==0) {ra.insert(ra.end(),(char)1);}
            if (cx>0&&maze[ay][ax-2]==0) {ra.insert(ra.end(),(char)2);}
            if (cy<y-1&&maze[ay+2][ax]==0) {ra.insert(ra.end(),(char)3);}
            if (cx<x-1&&maze[ay][ax+2]==0) {ra.insert(ra.end(),(char)4);}
            return ra;
        }
        bool makenewroad(int cx,int cy,std::vector<char> ard) {
            if (ard.size()<1) {return false;}
            int ax = cx*2+1;int ay = cy*2+1;
            int car = ard[std::floor(xorshift64(&rndm)%ard.size())];
            switch (car)
            {
                case 1:
                    maze[ay-2][ax] = 1;maze[ay-1][ax]=1;break;
                case 2:
                    maze[ay][ax-2] = 1;maze[ay][ax-1]=1;break;
                case 3:
                    maze[ay+2][ax] = 1;maze[ay+1][ax]=1;break;
                case 4:
                    maze[ay][ax+2] = 1;maze[ay][ax+1]=1;break;
            }
            return true;
        }
};

#endif