# Neknaj Maze

# maze.js

## 迷路の自動生成  
### 実行する
https://neknaj.github.io/maze/generator

## 使用方法
classを初期化する  
```js
let maze = new Maze();
```
出力を取得する
```js
maze.maze // 迷路のデータ
maze.size // 迷路の大きさ
maze.start // スタートの場所
maze.goal // ゴールの場所
maze.sdir // スタートの向き
```

## 迷路を自動で解く
### 実行する
https://neknaj.github.io/maze/auto/1

## 使用方法
classを初期化する  
```js
let route = new MazeSolve1(maze)
```
出力を取得する
```js
route // 迷路の解
```

## 出力例(画像)
![image](https://user-images.githubusercontent.com/79097169/202877865-bc331b1e-753c-4dd8-b68b-32a7c239dc62.png)
![image](https://user-images.githubusercontent.com/79097169/202878001-9b143946-b285-4497-b9a8-840d74357425.png)
![image](https://user-images.githubusercontent.com/79097169/202878011-c798674f-2900-4c18-8a2a-8331f46a7a45.png)


# 3D Maze
自動生成された迷路で遊ぶ  
https://neknaj.github.io/maze/3d  
![image](https://user-images.githubusercontent.com/79097169/202878028-e6fc92b0-a5d9-4210-bc6f-4c2d9997b0eb.png)