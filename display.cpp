#include <vector>
#include <GLUT/glut.h>

#include "display.hpp"


//----------------------------------------------------
// 直方体の定義
//----------------------------------------------------
GLdouble wall_one[][3] = {
  { 0.0, -20.0, 0.0 },
  { 30.0, -20.0, 0.0 },
  { 30.0, 100.0, 0.0 },
  { 0.0, 100.0, 0.0 },
  { 0.0, -20.0, 70.0 },
  { 30.0, -20.0, 70.0 },
  { 30.0, 100.0, 70.0 },
  { 0.0, 100.0, 70.0 }
};
GLdouble wall_two[][3] = {
  { -90.0, -20.0, 0.0 },
  { -60.0, -20.0, 0.0 },
  { -60.0, 100.0, 0.0 },
  { -90.0, 100.0, 0.0 },
  { -90.0, -20.0, 70.0 },
  { -60.0, -20.0, 70.0 },
  { -60.0, 100.0, 70.0 },
  { -90.0, 100.0, 70.0 }
};
GLdouble wall_three[][3] = {
  { -90.0, 160.0, 0.0 },
  { 30.0, 160.0, 0.0 },
  { 30.0, 190.0, 0.0 },
  { -90.0, 190.0, 0.0 },
  { -90.0, 160.0, 70.0 },
  { 30.0, 160.0, 70.0 },
  { 30.0, 190.0, 70.0 },
  { -90.0, 190.0, 70.0 }
};
int face[][4] = {//面の定義
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 }
};
GLdouble normal[][3] = {//面の法線ベクトル
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};


//----------------------------------------------------
// 物質質感の定義
//----------------------------------------------------
struct MaterialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
};
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
  gluPerspective(30.0, (double)WindowWidth/(double)WindowHeight, 0.1, 1000.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);

  //視点の設定------------------------------
  gluLookAt(		// http://atelier-yoka.com/dev_android/p_main.php?file=apigluglulookat
       ViewPointX, ViewPointY, ViewPointZ, // 視点の位置x,y,z;
       Side, ViewPointY + 200, 30.0,   // カメラが見ている位置,y,z
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

  Scene_one();

  //陰影OFF-----------------------------
  glDisable(GL_LIGHTING);
  //-----------------------------------

  // 大地
  Ground();

  glutSwapBuffers(); //glutInitDisplayMode(GLUT_DOUBLE)でダブルバッファリングを利用可
}

void Scene_one() {
  //直方体1
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);		// http://www.field-and-network.jp/rihei/20091006170714.php
  glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);
  glTranslated(30.0, 50.0, 0.0);//平行移動値の設定
  glBegin(GL_QUADS);
  for (int j = 0; j < 6; ++j) {
  	glNormal3dv(normal[j]); //法線ベクトルの指定
    for (int i = 0; i < 4; ++i) {
      glVertex3dv(wall_one[face[j][i]]);
    }
  }
  glEnd();
  glPopMatrix();
  //直方体2
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);
  glTranslated(30.0, 50.0, 0.0);//平行移動値の設定
  glBegin(GL_QUADS);
  for (int j = 0; j < 6; ++j) {
  	glNormal3dv(normal[j]); //法線ベクトルの指定
    for (int i = 0; i < 4; ++i) {
      glVertex3dv(wall_two[face[j][i]]);
    }
  }
  glEnd();
  glPopMatrix();
  //直方体3
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);
  glTranslated(30.0, 50.0, 0.0);//平行移動値の設定
  glBegin(GL_QUADS);
  for (int j = 0; j < 6; ++j) {
  	glNormal3dv(normal[j]); //法線ベクトルの指定
    for (int i = 0; i < 4; ++i) {
      glVertex3dv(wall_three[face[j][i]]);
    }
  }
  glEnd();
  glPopMatrix();

}

//----------------------------------------------------
// 大地の描画
//----------------------------------------------------
void Ground(void) {
    double ground_max_x = 300.0;
    double ground_max_y = 300.0;
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