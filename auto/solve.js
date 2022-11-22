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
    main() {
    }
    getResult() {
        let p = maze.start[1]*maze.size[0]+maze.start[0];
        let goalp = maze.goal[1]*maze.size[1]+maze.goal[0];
        let res = [];
        while (p!=goalp) {res.push(p);p = this.from[p];}
        res.push(goalp);
        return res;
    }
    searcharound() {
        let flag = false;
        let x = maze.size[0];
        let y = maze.size[1];
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