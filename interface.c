/**
 * File: interface.c
 * Description: 界面布局、事件绑定
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.1
 * Date: 2017.5.30
 */
#include "map.h"

// 回调函数
extern gboolean configure_cb(GtkWidget *widget,GdkEventConfigure *event,gpointer data);
extern gboolean draw_cb(GtkWidget *widget,cairo_t *cr,gpointer data);
extern gboolean generate_cb(GtkButton *button,gpointer data);
extern gboolean bfs_cb(GtkButton *button,gpointer data);
extern gboolean dijkstra_cb(GtkButton *button,gpointer data);

GtkWidget *window = NULL;
GtkWidget *drawing_area = NULL;
GtkWidget **entrys = NULL;
cairo_surface_t *surface = NULL;
static int drawing_area_width = 800;
static int drawing_area_height = 600;

// 创建画布
GtkWidget *create_drawing_area() {
  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area,drawing_area_width,drawing_area_height);
  // 绑定默认事件
  g_signal_connect(drawing_area,"configure-event",G_CALLBACK(configure_cb),NULL);
  g_signal_connect(drawing_area,"draw",G_CALLBACK(draw_cb),NULL);
  return drawing_area;
}
// 创建配置面板
GtkWidget *create_configure() {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
  gtk_container_set_border_width(GTK_CONTAINER(box),20);
  int i = 0;
  /* 输入框控件列表
   * 0-width 1-height
   * 2-start_x 3-start_y
   * 4-target_x 5-target_y
   * 6-obstacles
   */
  entrys = (GtkWidget**)malloc(sizeof(GtkWidget*)*7);
  for(i = 0;i < 7;i++) entrys[i] = gtk_entry_new();
  // 标签控件列表
  GtkWidget *labels[4] = {NULL};
  gchar *text[4] = {"SIZE(Width,Height)","START(X,Y)",
                    "TARGET(X,Y)","OBSTACLES"};
  for(i = 0;i < 4;i++) labels[i] = gtk_label_new(text[i]);
  // 按钮控件
  GtkWidget *button_generate = gtk_button_new_with_label("Generate"),
  *button_bfs = gtk_button_new_with_label("Bfs"),
  *button_dijkstra = gtk_button_new_with_label("Dijkstra");
  // 添加控件到盒子中
  gtk_box_pack_start(GTK_BOX(box),labels[0],TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),entrys[0],TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),entrys[1],TRUE,TRUE,0);
  
  gtk_box_pack_start(GTK_BOX(box),labels[1],TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),entrys[2],TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),entrys[3],TRUE,TRUE,0);
  
  gtk_box_pack_start(GTK_BOX(box),labels[2],TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),entrys[4],TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),entrys[5],TRUE,TRUE,0);
  
  gtk_box_pack_start(GTK_BOX(box),labels[3],TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),entrys[6],TRUE,TRUE,0);
  
  gtk_box_pack_start(GTK_BOX(box),button_generate,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),button_bfs,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),button_dijkstra,TRUE,TRUE,0);
  // 绑定按钮事件
  g_signal_connect(button_generate,"clicked",G_CALLBACK(generate_cb),NULL);
  g_signal_connect(button_bfs,"clicked",G_CALLBACK(bfs_cb),NULL);
  g_signal_connect(button_dijkstra,"clicked",G_CALLBACK(dijkstra_cb),NULL);
  // 设置输入框默认值
  gchar *values[7] = {"40","30",
  "0","0",
  "39","29",
  "100"};
  for(i = 0;i < 7;i++) gtk_entry_set_text(GTK_ENTRY(entrys[i]),values[i]);
  // 返回盒子
  return box;
}
// 销毁窗口
gboolean destroy_window() {
  // 退出前处理
  
  // 退出主循环
  gtk_main_quit();
}
// 创建窗口
gboolean *create_window() {
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  if(!window) return FALSE;
  // 设置窗口属性
  gtk_window_set_title(GTK_WINDOW(window),"Maze");
  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
  gtk_widget_set_size_request(window,1000,600);
  // 添加画布和配置面板
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
  gtk_container_add(GTK_CONTAINER(window),box);
  gtk_box_pack_start(GTK_BOX(box),create_drawing_area(),TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),create_configure(),TRUE,TRUE,0);
  // 绑定关闭事件
  g_signal_connect(window,"destroy",G_CALLBACK(destroy_window),NULL);
  // 显示窗口
  gtk_widget_show_all(window);
}
int main(int argc,char **argv) {
  // 初始化gtk程序
  gtk_init(&argc, &argv);
  // 创建窗口及其控件
  create_window();
  // 等待事件响应
  gtk_main();
  return 0;
}