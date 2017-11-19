#include <GLUT/glut.h>
#include "scene_one.hpp"
#include "scene_two.hpp"
#include "scene_three.hpp"

#include "display.hpp"


//----------------------------------------------------
// 物質質感の定義
//----------------------------------------------------
//jade(翡翠)
MaterialStruct ms_jade = {
  {0.135,     0.2225,   0.1575,   1.0},
  {0.54,      0.89,     0.63,     1.0},
  {0.316228,  0.316228, 0.316228, 1.0},
  12.8};
//ruby(ルビー)
MaterialStruct ms_ruby  = {
  {0.1745,   0.01175,  0.01175,   1.0},
  {0.61424,  0.04136,  0.04136,   1.0},
  {0.727811, 0.626959, 0.626959,  1.0},
  76.8};

//----------------------------------------------------
// 色の定義の定義
//----------------------------------------------------
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 }; //赤色
GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };//緑色
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };//青色
GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };//黄色
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };//白色
GLfloat shininess = 30.0;//光沢の強さ

//----------------------------------------------------
// 描画の関数
//----------------------------------------------------
void Display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //バッファの消去

  //透視変換行列の設定------------------------------
  glMatrixMode(GL_PROJECTION);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
  glLoadIdentity();//行列の初期化
  gluPerspective(80.0, (double)WindowWidth/(double)WindowHeight, 0.1, 500.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);

  //視点の設定------------------------------
  gluLookAt(		// http://atelier-yoka.com/dev_android/p_main.php?file=apigluglulookat
       ViewPointX, ViewPointY, ViewPointZ, // 視点の位置x,y,z;
       SideX, SideY, 30.0,   // カメラが見ている位置,y,z
       0.0, 0.0, 1.0);  //カメラの上方向がどれくらいかx,y,z

  //モデルビュー変換行列の設定--------------------------
  glMatrixMode(GL_MODELVIEW);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
  glLoadIdentity();//行列の初期化
  glViewport(0, 0, WindowWidth, WindowHeight);
  //----------------------------------------------

  //陰影ON-----------------------------
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);//光源0を利用
  //-----------------------------------

  switch(Scene) {
  case 0:
    Scene_one();
    break;
  case 1:
    Scene_two();
    break;
  case 2:
    Scene_three();
    break;
  }

  //陰影OFF-----------------------------
  glDisable(GL_LIGHTING);
  //-----------------------------------

  // 大地
  Ground();

  glutSwapBuffers(); //glutInitDisplayMode(GLUT_DOUBLE)でダブルバッファリングを利用可
}

//----------------------------------------------------
// 大地の描画
//----------------------------------------------------
void Ground(void) {
    double ground_max_x = 1000.0;
    double ground_max_y = 1000.0;
    glColor3d(0.8, 0.8, 0.8);  // 大地の色
    glBegin(GL_LINES);
    for(double ly = -ground_max_y ;ly <= ground_max_y; ly+=10.0){
      glVertex3d(-ground_max_x, ly,0);
      glVertex3d(ground_max_x, ly,0);
    }
    for(double lx = -ground_max_x ;lx <= ground_max_x; lx+=10.0){
      glVertex3d(lx, ground_max_y,0);
      glVertex3d(lx, -ground_max_y,0);
    }
    glEnd();
}