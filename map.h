/**
 * File: map.h
 * Description: map.c头文件
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.2
 * Date: 2017.5.26
 */
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef enum grid {
  ROAD = 0,  // 路
  OBSTACLE = 1,  // 障碍
  START = 2,  // 起点
  TARGET = 3,  // 目标
  VISITED = 4,  // 被访问
  PATH = 5  // 路径
} GRID;  // 地图格
typedef struct map {
  GRID **data;  // 地图数据
  int **weight;  // 权值
  int width,height;  // 地图尺寸
} MAP;  // 地图

// 创建地图
gboolean createMap(MAP *map);
// 销毁地图
gboolean destroyMap(MAP *map);
// 置地图格数据
gboolean setGridData(MAP map,int x,int y,GRID type);
// 置地图格权值
gboolean setGridWeight(MAP map,int x,int y,int weight);
// 障碍生成器
gboolean obstacleGenerator(MAP map,int amount);
// 复位地图
gboolean resetMap(MAP map);