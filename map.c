/**
 * File: map.c
 * Description: 实现地图的各种操作
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.2
 * Date: 2017.5.26
 */
#include "map.h"
// 创建地图
gboolean createMap(MAP *map) {
  if(map->width <= 0 || map->height <= 0) return FALSE;
  // 每个地图格默认赋值为ROAD，权值默认为0
  GRID **col = (GRID**)malloc(sizeof(GRID*) * map->width);
  int **weightCol = (int**)malloc(sizeof(int*) * map->width);
  
  int i = 0,j = 0;
  for(i = 0;i < map->width;i++) {
    GRID *row = (GRID*)malloc(sizeof(GRID) * map->height);
    int *weightRow = (int*)malloc(sizeof(int) * map->height);
    for(j = 0;j < map->height;j++) {
      row[j] = ROAD;
      weightRow[j] = 0;
    }
    col[i] = row;
    weightCol[i] = weightRow;
  }
  // 传出地图
  map->data = col;
  map->weight = weightCol;
  return TRUE;
}
// 销毁地图
gboolean destroyMap(MAP *map) {
  if(!map->data) return FALSE;
  int i = 0;
  for(i = 0;i < map->width;i++) {
    free(map->data[i]);
    free(map->weight[i]);
  }
  free(map->data);
  free(map->weight);
  map->data = NULL;
  map->weight = NULL;
  return TRUE;
}
// 置地图格数据
gboolean setGridData(MAP map,int x,int y,GRID type) {
  if(!map.data) return FALSE;
  else if(x < 0 || x >= map.width ||
  y < 0 || y >= map.height) return FALSE;
  else {
    map.data[x][y] = type;
    return TRUE;
  }
}
// 置地图格权值
gboolean setGridWeight(MAP map,int x,int y,int weight) {
  if(!map.weight) return FALSE;
  else if(x < 0 || x >= map.width ||
  y < 0 || y >= map.height) return FALSE;
  else {
    map.weight[x][y] = weight;
    return TRUE;
  }
}
// 障碍生成器
gboolean obstacleGenerator(MAP map,int amount) {
  if(!map.data) return FALSE;
  if(amount > (map.width*map.height-2)) return FALSE;
  // 取随机数
  srand(time(NULL));
  int getRandomNum(int min,int max) {
    return floor(rand() % (max-min+1)) + min;
  }
  // 放置障碍
  while(amount) {
    int x = getRandomNum(0,map.width-1),
    y = getRandomNum(0,map.height-1);
    GRID gridData = map.data[x][y];
    if(gridData != OBSTACLE && gridData != START &&
    gridData != TARGET) {
      map.data[x][y] = OBSTACLE;
      amount--;
    }
  }
  return TRUE;
}
// 复位地图，清除路径和被访问节点
gboolean resetMap(MAP map) {
  int i = 0,j = 0;
  for(;i < map.width;i++) {
	for(j = 0;j < map.height;j++) {
	  if(map.data[i][j] == VISITED || 
	  map.data[i][j] == PATH) map.data[i][j] = ROAD;
	  map.weight[i][j] = 0;
	}
  }
  return TRUE;
}