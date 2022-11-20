class MazeSolve1 {
    #maze;
    constructor(maze) {
        this.#maze = maze;
        this.#main();
    }
    #main() {
        let maze = this.#maze;
        console.log(maze);
        let y = maze.size[0];
        let x = maze.size[1];
        let from = new Uint32Array(x*y).fill(0);
        let head = [];
    }
}