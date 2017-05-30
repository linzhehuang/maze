/**
 * File: dijkstra.c
 * Description: 迪杰斯特拉算法实现
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.1
 * Date: 2017.5.25
 */
#include "map.h"

gboolean getDijkstraPath(MAP map) {
  if(!map.data) return FALSE;
  // 寻找起点和目标
  int startX = 0,startY = 0,
  targetX = 0,targetY = 0;
  int i = 0,j = 0,count = 0;
  for(i = 0;i < map.width;i++) {
    for(j = 0;j < map.height;j++) {
      if(map.data[i][j] == START) {
        startX = i;
        startY = j;
        count++;
      }
      else if(map.data[i][j] == TARGET) {
        targetX = i;
        targetY = j;
        count++;
      }
      else continue;
    }
  }
  // 未找到起点或目标
  if(count != 2) return FALSE;
  
  typedef struct triple {
    int x,y;  // 位置
    int parent;  // 父节点
  } TRIPLE;  // 三元组
  // 创建三元组表并定义其插入、更新父节点操作
  int tripleIndex = 0;
  int mapSize = map.width * map.height;
  TRIPLE *triple = (TRIPLE*)malloc(sizeof(TRIPLE) * mapSize);
  void insert(int x,int y,int parent) {
    triple[tripleIndex].x = x;
    triple[tripleIndex].y = y;
    triple[tripleIndex].parent = parent;
    tripleIndex++;
  }
  void updateParent(int x,int y,int parent) {
    int k = 0;
    while(triple[k].x != x || triple[k].y != y) k++;
    triple[k].parent = parent;
  }
  // 斜着是否可通过
  gboolean isDiagonalAccess(int srcX,int srcY,int dstX,int dstY) {
    int distX = dstX - srcX,
    distY = dstY - srcY;
    // 不为斜着走
    if(!distX || !distY) return TRUE;
    int count = 0;
    if(map.data[srcX+distX][srcY] == OBSTACLE) count++;
    if(map.data[srcX][srcY+distY] == OBSTACLE) count++;
    // 若计数为2则不能通过
    if(count == 2) return FALSE;
    else return TRUE;
  }
  // 该点是否可访问
  gboolean isAccess(int srcX,int srcY,int dstX,int dstY) {
    if(dstY < 0 || dstY >= map.height) return FALSE;
    else if(dstX < 0 || dstX >= map.width) return FALSE;
    // 不越界
    else {
      GRID gridData = map.data[dstX][dstY];
      if(gridData == VISITED) return FALSE;
      else if(gridData == OBSTACLE) return FALSE;
      else if(gridData == START) return FALSE;
      // 不为已访问、障碍、起点
      else {
        return isDiagonalAccess(srcX,srcY,dstX,dstY);
      }
    }
  }
  
  // 周围点相对当前点偏移值
  int offset[8][2] = {{0,-1},{1,0},{0,1},{-1,0},
  {1,-1},{1,1},{-1,1},{-1,-1}};
  // 周围点相对当前点路径值，斜走为14
  int offsetWeight[8] = {10,10,10,10,
  14,14,14,14};
  int currentX = startX,currentY = startY;
  insert(currentX,currentY,-1);
  
  // 开始遍历
  i = 0;
  while(currentX != targetX || currentY != targetY) {
    // 访问当前点的周围点
    for(j = 0;j < 8;j++) {
      int neighborX = currentX + offset[j][0],
      neighborY = currentY + offset[j][1];
      if(isAccess(currentX,currentY,neighborX,neighborY) == TRUE) {
        // 判断是否为新点
        if(map.weight[neighborX][neighborY] == 0) {
          insert(neighborX,neighborY,i);
          map.weight[neighborX][neighborY] = map.weight[currentX][currentY] +
          offsetWeight[j];
        }
        else {
          // 比较旧新路径
          if(map.weight[neighborX][neighborY] > (map.weight[currentX][currentY] +
          offsetWeight[j]) ) {
			  
            // 新路径小，更新路径长度和父节点
            map.weight[neighborX][neighborY] = map.weight[currentX][currentY] +
          offsetWeight[j];
		    updateParent(neighborX,neighborY,i);
          }
		  
        }
      }  // isAccess end
    }
    i++;
    // 起点与目标被隔断
    if(i == tripleIndex) return FALSE;
    // 更新当前点
    currentX = triple[i].x;
    currentY = triple[i].y;
    map.data[currentX][currentY] = VISITED;
  }
  // 回溯标记路径
  while(i != -1) {
    map.data[currentX][currentY] = PATH;
    currentX = triple[i].x;
    currentY = triple[i].y;
    i = triple[i].parent;
  } 
  // 还原起点和目标位置数据
  map.data[startX][startY] = START;
  map.data[targetX][targetY] = TARGET;
  return TRUE;
}