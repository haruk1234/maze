// bem130 2022 maze.js //

class Maze {
    #maze;#deadend;#start;#goal;#sdir;#size;#osize;
    constructor (x,y) {
        this.#osize = [x,y];
        this.makemaze();
        this.searchdeadend();
        this.choosestartgoal();
        return {maze:this.#maze,start:this.#start,goal:this.#goal,sdir:this.#sdir,size:this.#size};
    }
    makemaze() {
        let x = this.#osize[0];
        let y = this.#osize[1];
        this.#size = [x*2+1,y*2+1];
        this.#maze = Array.from(Array(y*2+1),_=>Array(x*2+1).fill(0));
        this.#maze[Math.floor(Math.random()*y)*2+1][Math.floor(Math.random()*x)*2+1] = 1;
        while (this.searchwall(x,y)) {
            let lx = Math.floor(Math.random()*x);
            let ly = Math.floor(Math.random()*y);
            let ra = this.searcharound(lx,ly,x,y);
            this.makenewroad(lx,ly,ra);
        }
    }
    searchwall(x,y) {
        for (let ly=0;ly<y;ly++) {
            for (let lx=0;lx<x;lx++) {
                if (this.#maze[ly*2+1][lx*2+1]==0) {return true;}
            }
        }
        return false;
    }
    searcharound(cx,cy,x,y) {
        let ax = cx*2+1;
        let ay = cy*2+1;
        let ra = [];
        if (this.#maze[ay][ax]==0) {return ra;}
        if (cy>0&&this.#maze[ay-2][ax]==0) {ra.push(1);}
        if (cx>0&&this.#maze[ay][ax-2]==0) {ra.push(2);}
        if (cy<y-1&&this.#maze[ay+2][ax]==0) {ra.push(3);}
        if (cx<x-1&&this.#maze[ay][ax+2]==0) {ra.push(4);}
        return ra;
    }
    makenewroad(cx,cy,ard) { // ard - around
        if (ard.length<1) {return false;}
        let ax = cx*2+1;
        let ay = cy*2+1;
        let car = ard[Math.floor(Math.random()*ard.length)] // card - chose around
        if (car==1) {this.#maze[ay-2][ax]=1;this.#maze[ay-1][ax]=1;}
        if (car==2) {this.#maze[ay][ax-2]=1;this.#maze[ay][ax-1]=1;}
        if (car==3) {this.#maze[ay+2][ax]=1;this.#maze[ay+1][ax]=1;}
        if (car==4) {this.#maze[ay][ax+2]=1;this.#maze[ay][ax+1]=1;}
        return true;
    }
    searchdeadend() {
        let x = this.#maze[0].length/2-1;
        let y = this.#maze.length/2-1;
        this.#deadend = [];
        for (let ly=0;ly<y;ly++) {
            for (let lx=0;lx<x;lx++) {
                if (this.#maze[ly*2+1][lx*2+1]==1) {
                    let awcnt = 0;
                    if (this.#maze[ly*2+1-1][lx*2+1]==0) {awcnt++;}
                    if (this.#maze[ly*2+1][lx*2+1-1]==0) {awcnt++;}
                    if (this.#maze[ly*2+1+1][lx*2+1]==0) {awcnt++;}
                    if (this.#maze[ly*2+1][lx*2+1+1]==0) {awcnt++;}
                    if (awcnt==3) {
                        this.#deadend.push([lx*2+1,ly*2+1]);
                    }
                }
            }
        }
    }
    choosestartgoal() {
    }
    rndstartgoal() {   
        let s = Math.floor(Math.random()*this.#deadend.length);
        this.#start = this.#deadend[s];
        while (true) {
            var e = Math.floor(Math.random()*this.#deadend.length);
            if (e!=s) {
                this.#goal = this.#deadend[e];
                break;
            }
        }
        if (this.#maze[this.#start[0]-1][this.#start[1]]==0) {this.#sdir=0;}
        if (this.#maze[this.#start[0]][this.#start[1]-1]==0) {this.#sdir=1;}
        if (this.#maze[this.#start[0]+1][this.#start[1]]==0) {this.#sdir=2;}
        if (this.#maze[this.#start[0]][this.#start[1]+1]==0) {this.#sdir=3;}
    }
}