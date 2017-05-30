/**
 * File: callback.c
 * Description: 事件的回调函数
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.1
 * Date: 2017.5.29
 */
#include "map.h"

extern cairo_surface_t *surface;
extern GtkWidget *drawing_area;
extern GtkWidget **entrys;
extern gboolean getBfsPath(MAP map);
extern gboolean getDijkstraPath(MAP map);

MAP g_map = {NULL,NULL,0,0};
// 格子尺寸
int grid_size = 20;

// 画网格背景
static void draw_bg(int x,int y) {
  cairo_t *cr = cairo_create (surface);
  int i = 0;
  void draw_line(int s_x,int s_y,int e_x,int e_y) {
	cairo_set_source_rgb (cr,0.5,0.5,0.5);
	cairo_move_to(cr,s_x,s_y);
	cairo_line_to(cr,e_x,e_y);
	cairo_stroke(cr);
  }
  // 清空画布
  cairo_set_source_rgb(cr,0,0,0);
  cairo_paint(cr);
  // 画网格
  for(i = 0;i < x+1;i++) draw_line(i*grid_size,0,i*grid_size,y*grid_size);
  for(i = 0;i < y+1;i++) draw_line(0,i*grid_size,x*grid_size,i*grid_size);
  cairo_destroy(cr);
  gtk_widget_queue_draw_area(drawing_area,0,0,
                             gtk_widget_get_allocated_width(drawing_area),
                             gtk_widget_get_allocated_height(drawing_area));
}
// 画格子
static void draw_grid(int x,int y,int type) {
  cairo_t *cr = cairo_create (surface);
  /* 格子颜色列表
   * 0-路     1-障碍
   * 2-起点   3-目标
   * 4-被访问 5-路径
   */
  int colors[6][3] = {
  {0,0,0},  {1,1,1}   ,
  {0,1,0},  {1,0,0}   ,
  {0,1,1},{1,1,0.5}   };
  //
  cairo_set_source_rgb(cr,colors[type][0],colors[type][1],colors[type][2]);
  cairo_rectangle(cr,x*grid_size+1,y*grid_size+1,grid_size-2,grid_size-2);
  cairo_fill(cr);
  cairo_destroy(cr);
  gtk_widget_queue_draw_area(drawing_area,x*grid_size+1,y*grid_size+1,grid_size-2,grid_size-2);
}
// 画地图
static void draw_map() {
  draw_bg(g_map.width,g_map.height);
  int i = 0,j = 0;
  for(i = 0;i < g_map.width;i++) {
	for(j = 0;j < g_map.height;j++) {
	  if(g_map.data[i][j] == ROAD) continue;
	  else draw_grid(i,j,g_map.data[i][j]);
	}
  }
}

// 检查数值是否正确
static gboolean check_values(int values[7],gchar *err_msg) {
  
}

// 画布配置事件
gboolean configure_cb(GtkWidget *widget,GdkEventConfigure *event,gpointer data) {
  surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
                                              CAIRO_CONTENT_COLOR,
                                              gtk_widget_get_allocated_width(widget),
                                              gtk_widget_get_allocated_height(widget));
  return TRUE;
}
// 画布绘制事件
gboolean draw_cb(GtkWidget *widget,cairo_t *cr,gpointer data) {
  cairo_set_source_surface(cr,(cairo_surface_t*)surface,0,0);
  cairo_paint(cr);
  return TRUE;
}
// 生成地图按钮点击事件
gboolean generate_cb(GtkButton *button,gpointer data) {
  // 取出输入框的值
  int i = 0,values[7] = {0};
  for(i = 0;i < 7;i++) values[i] = atoi(gtk_entry_get_text(GTK_ENTRY(entrys[i])));
  // 检查数值是否正确
  
  // 设置地图
  g_map.width = values[0];
  g_map.height = values[1];
  createMap(&g_map);
  setGridData(g_map,values[2],values[3],START);
  setGridData(g_map,values[4],values[5],TARGET);
  obstacleGenerator(g_map,values[6]);
  // 绘制地图
  draw_map();
}
// bfs按钮点击事件
gboolean bfs_cb(GtkButton *button,gpointer data) {
  if(!g_map.data) return FALSE;
  resetMap(g_map);
  getBfsPath(g_map);
  draw_map();
  return TRUE;
}
// dijkstra按钮点击事件
gboolean dijkstra_cb(GtkButton *button,gpointer data) {
  if(!g_map.data) return FALSE;
  resetMap(g_map);
  getDijkstraPath(g_map);
  draw_map();
  return TRUE;
}