/**
 * File: bfs.c
 * Description: breath-frist-search算法实现
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.1
 * Date: 2017.5.25
 */
#include "map.h"

gboolean getBfsPath(MAP map) {
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
  // 创建三元组表并定义其插入操作
  int tripleIndex = 0;
  int mapSize = map.width * map.height;
  TRIPLE *triple = (TRIPLE*)malloc(sizeof(TRIPLE) * mapSize);
  void insert(int x,int y,int parent) {
    triple[tripleIndex].x = x;
    triple[tripleIndex].y = y;
    triple[tripleIndex].parent = parent;
    tripleIndex++;
  }
  // 该点是否可访问
  gboolean isAccess(int x,int y) {
    if(y < 0 || y >= map.height) return FALSE;
    else if(x < 0 || x >= map.width) return FALSE;
    else {
      GRID gridData = map.data[x][y];
      if(gridData == VISITED) return FALSE;
      else if(gridData == OBSTACLE) return FALSE;
      else if(gridData == START) return FALSE;
      else return TRUE;
    }
  }
  // 周围点相对当前点偏移值
  int offset[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};
  int currentX = startX,currentY = startY;
  insert(currentX,currentY,-1);
  
  // 开始遍历
  i = 0;
  while(currentX != targetX || currentY != targetY) {
    // 访问当前点的周围可访问点并加入三元组表
    for(j = 0;j < 4;j++) {
      int neighborX = currentX + offset[j][0],
      neighborY = currentY + offset[j][1];
      if(isAccess(neighborX,neighborY) == TRUE) {
        map.data[neighborX][neighborY] = VISITED;
        insert(neighborX,neighborY,i);
      }
    }
    i++;
    // 起点与目标被隔断
    if(i == tripleIndex) return FALSE;
    // 更新当前点
    currentX = triple[i].x;
    currentY = triple[i].y;
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