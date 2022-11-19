
    var maze = []
    function makemaze(x,y) { // size x,y
        maze = Array.from(Array(y*2+1),_=>Array(x*2+1).fill(0));
        maze[Math.floor(Math.random()*y)*2+1][Math.floor(Math.random()*x)*2+1] = 1
        while (searchwall(x,y)) {
            let lx = Math.floor(Math.random()*x)
            let ly = Math.floor(Math.random()*y)
            let ra = searcharound(lx,ly,x,y)
            makenewroad(lx,ly,ra)
        }
    }
    function searchwall(x,y) {
        for (let ly=0;ly<y;ly++) {
            for (let lx=0;lx<x;lx++) {
                if (maze[ly*2+1][lx*2+1]==0) {
                    return true;
                }
            }
        }
        return false;
    }
    function searcharound(cx,cy,x,y) {
        ax = cx*2+1;
        ay = cy*2+1;
        ra = [];
        if (maze[ay][ax]==0) {
            return ra;
        }
        if (cy>0&&maze[ay-2][ax]==0) {
            ra.push(1);
        }
        if (cx>0&&maze[ay][ax-2]==0) {
            ra.push(2);
        }
        if (cy<y-1&&maze[ay+2][ax]==0) {
            ra.push(3);
        }
        if (cx<x-1&&maze[ay][ax+2]==0) {
            ra.push(4);
        }
        return ra;
    }
    function makenewroad(cx,cy,ard) { // ard - around
        if (ard.length<1) {
            return false;
        }
        ax = cx*2+1;
        ay = cy*2+1;

        card = ard[Math.floor(Math.random()*ard.length)] // card - chose around
        if (card==1) {
            maze[ay-2][ax]=1;
            maze[ay-1][ax]=1;
        }
        if (card==2) {
            maze[ay][ax-2]=1;
            maze[ay][ax-1]=1;
        }
        if (card==3) {
            maze[ay+2][ax]=1;
            maze[ay+1][ax]=1;
        }
        if (card==4) {
            maze[ay][ax+2]=1;
            maze[ay][ax+1]=1;
        }
        return true;
    }
   
    function mazeto3d() {
        x = maze[0].length;
        y = maze.length;
        scene["maze"] = [];
        fmaze = scene["maze"];
        c = [212,210,254];
        fc = [242,240,254];
        sfc = [212,210,25];
        efc = [112,70,220];
        for (let ly=0;ly<y;ly++) {
            for (let lx=0;lx<x;lx++) {
                if (maze[ly][lx]==0) {
                    // // 上面
                    //fmaze.push([[lx,ly,1],[lx+1,ly,1],[lx+1,ly+1,1],[c[0],c[1],c[2]]])
                    //fmaze.push([[lx,ly+1,1],[lx,ly,1],[lx+1,ly+1,1],[c[0],c[1],c[2]]])
                    // 横面
                    if (!(lx>0&&maze[ly][lx-1]==0)) {
                        fmaze.push([[lx,ly,0],[lx,ly,1],[lx,ly+1,0],[c[0],c[1],c[2]]]);
                        fmaze.push([[lx,ly,1],[lx,ly+1,1],[lx,ly+1,0],[c[0],c[1],c[2]]]);
                    }                    
                    if (!(ly<y-1&&maze[ly+1][lx]==0)) {
                        fmaze.push([[lx,ly+1,0],[lx,ly+1,1],[lx+1,ly+1,1],[c[0],c[1],c[2]]]);
                        fmaze.push([[lx+1,ly+1,0],[lx,ly+1,0],[lx+1,ly+1,1],[c[0],c[1],c[2]]]);
                    }                    
                    if (!(lx<x-1&&maze[ly][lx+1]==0)) {
                        fmaze.push([[lx+1,ly+1,0],[lx+1,ly+1,1],[lx+1,ly,1],[c[0],c[1],c[2]]]);
                        fmaze.push([[lx+1,ly,0],[lx+1,ly+1,0],[lx+1,ly,1],[c[0],c[1],c[2]]]);
                    }                    
                    if (!(ly>0&&maze[ly-1][lx]==0)) {
                        fmaze.push([[lx+1,ly,0],[lx+1,ly,1],[lx,ly,1],[c[0],c[1],c[2]]]);
                        fmaze.push([[lx,ly,0],[lx+1,ly,0],[lx,ly,1],[c[0],c[1],c[2]]]);
                    }
                }
                else {
                    if (lx==1&&ly==1) {
                        fmaze.push([[lx,ly,0],[lx+1,ly,0],[lx+1,ly+1,0],[sfc[0],sfc[1],sfc[2]]])
                        fmaze.push([[lx,ly+1,0],[lx,ly,0],[lx+1,ly+1,0],[sfc[0],sfc[1],sfc[2]]])
                    }
                    else if (lx==x-2&&ly==y-2) {
                        fmaze.push([[lx,ly,0],[lx+1,ly,0],[lx+1,ly+1,0],[efc[0],efc[1],efc[2]]])
                        fmaze.push([[lx,ly+1,0],[lx,ly,0],[lx+1,ly+1,0],[efc[0],efc[1],efc[2]]])
                    }
                    else {
                        fmaze.push([[lx,ly,0],[lx+1,ly,0],[lx+1,ly+1,0],[fc[0],fc[1],fc[2]]])
                        fmaze.push([[lx,ly+1,0],[lx,ly,0],[lx+1,ly+1,0],[fc[0],fc[1],fc[2]]])
                    }
                }
            }
        }
    }
