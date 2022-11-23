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
        let bestscore = 0
        for (let i=0;i<1000;i++) {
            let tstart,tgoal;
            [tstart,tgoal] = this.rndstartgoal();
            let teval = new EvalMaze(new MazeSolve1({maze:this.#maze,start:tstart,goal:tgoal,sdir:null,size:this.#size})).get();
            if (teval>bestscore) {
                this.#start = tstart;this.#goal = tgoal;bestscore = teval;
            }
        }
        if (this.#maze[this.#start[0]-1][this.#start[1]]==0) {this.#sdir=0;}
        if (this.#maze[this.#start[0]][this.#start[1]-1]==0) {this.#sdir=1;}
        if (this.#maze[this.#start[0]+1][this.#start[1]]==0) {this.#sdir=2;}
        if (this.#maze[this.#start[0]][this.#start[1]+1]==0) {this.#sdir=3;}
    }
    rndstartgoal() {
        let start,goal;
        let s = Math.floor(Math.random()*this.#deadend.length);
        start = this.#deadend[s];
        while (true) {
            var e = Math.floor(Math.random()*this.#deadend.length);
            if (e!=s) {
                goal = this.#deadend[e];
                break;
            }
        }
        return [start,goal];
    }
}
class MazeSolve1 {
    #maze;
    constructor(maze) {
        this.#maze = maze;
        let x = maze.size[0];
        let y = maze.size[1];
        this.from = new Uint32Array(x*y).fill(0);
        this.from[maze.goal[1]*x+maze.goal[0]] = 1;
        while (this.searcharound()) {}
        return this.getResult();
    }
    getFrom() {
        return this.from;
    }
    getResult() {
        let p = this.#maze.start[1]*this.#maze.size[0]+this.#maze.start[0];
        let goalp = this.#maze.goal[1]*this.#maze.size[0]+this.#maze.goal[0];
        let res = [];
        while (p!=goalp) {res.push(p);p = this.from[p];}
        res.push(goalp);
        return res;
    }
    searcharound() {
        let flag = false;
        let x = this.#maze.size[0];
        let y = this.#maze.size[1];
        for (let cy=0;cy<y;cy++) {
            for (let cx=0;cx<x;cx++) {
                if (this.#maze.maze[cy][cx]==0) {continue;}
                if (this.from[(cy)*x+cx]!=0) {continue;}
                if (this.from[(cy-1)*x+cx]!=0) {flag = true;this.from[(cy)*x+cx] = (cy-1)*x+cx;}
                if (this.from[(cy)*x+cx-1]!=0) {flag = true;this.from[(cy)*x+cx] = (cy)*x+cx-1;}
                if (this.from[(cy+1)*x+cx]!=0) {flag = true;this.from[(cy)*x+cx] = (cy+1)*x+cx;}
                if (this.from[(cy)*x+cx+1]!=0) {flag = true;this.from[(cy)*x+cx] = (cy)*x+cx+1;}
            }
        }
        return flag;
    }
}
class EvalMaze {
    constructor(solvemaze) {this.solvemaze = solvemaze;}
    get() {return (this.solvemaze.length/10)**2}
}