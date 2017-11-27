#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <GLUT/glut.h>
#include "scene_one.hpp"
#include "scene_two.hpp"
#include "scene_three.hpp"

#include "display.hpp"


//----------------------------------------------------
// 物質質感の定義
//----------------------------------------------------
// jade(翡翠)
MaterialStruct ms_jade = {
	{0.135,     0.2225,   0.1575,   1.0},
	{0.54,      0.89,     0.63,     1.0},
	{0.316228,  0.316228, 0.316228, 1.0},
	12.8};
// ruby(ルビー)
MaterialStruct ms_ruby  = {
	{0.1745,   0.01175,  0.01175,   1.0},
	{0.61424,  0.04136,  0.04136,   1.0},
	{0.727811, 0.626959, 0.626959,  1.0},
	76.8};
// gold(金)
MaterialStruct ms_gold  = {
	{0.24725,	0.1995, 	0.0745,	1.0},
	{0.75164,	0.60648,	0.22648,1.0},
	{0.628281,	0.555802,	0.366065,1.0},
	48.0};
// pearl(真珠)
MaterialStruct ms_pearl  = {
	{0.25,		0.20725,	0.20725,1.0},
	{0.9,		0.729,		0.729,	1.0},
	{0.296648,	0.296648,	0.296648,1.0},
	5.0};


//----------------------------------------------------
// 色の定義の定義
//----------------------------------------------------
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };		//赤色
GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };	//緑色
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };	//青色
GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };	//黄色
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };	//白色
GLfloat shininess = 30.0;					//光沢の強さ

//----------------------------------------------------
// Teapot のために
//----------------------------------------------------
int timer = 0;
int size = std::rand() % 3 + 5;		// Teapot のサイズ
int tea_index = std::rand() % 20;		// Teapot の確率
int mp[5] = {0, 0, 0, 0, 0};


//----------------------------------------------------
// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
//----------------------------------------------------
void Put_teapot(void);
void Draw_String(int x, int y, char *string, void *font = GLUT_BITMAP_TIMES_ROMAN_24);
void Display_Text(int x, int y, char *string);


//----------------------------------------------------
// 描画の関数
//----------------------------------------------------
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Zバッファの消去

	//透視変換行列の設定------------------------------
	glMatrixMode(GL_PROJECTION);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
	glLoadIdentity();//行列の初期化
	gluPerspective(80.0, (double)WindowWidth/(double)WindowHeight, 0.1, 190.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);

	//視点の設定------------------------------
	gluLookAt(		// http://atelier-yoka.com/dev_android/p_main.php?file=apigluglulookat
			 ViewPointX, ViewPointY, ViewPointZ, // 視点の位置x,y,z;
			 SideX, SideY, 30.0,   // カメラが見ている位置,y,z
			 0.0, 0.0, 1.0);  //カメラの上方向がどれくらいかx,y,z

	//陰影ON-----------------------------
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);		//光源0を利用
	//光源の設定------------------------------
	GLfloat light_position0[] = {ViewPointX, ViewPointY, 30.0, 1.0};	// 光源0の座標
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	//GLfloat spotDirrection[] = {SideX, SideY, 20.0};		//スポットライトを向ける方向
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirrection);
	//-----------------------------------

	//モデルビュー変換行列の設定--------------------------
	glMatrixMode(GL_MODELVIEW);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
	glLoadIdentity();//行列の初期化
	glViewport(0, 0, WindowWidth, WindowHeight);
	//----------------------------------------------

	// Teapot
	Put_teapot();

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
	case 3:
		Goal();
		break;
	}

	// 大地
	Ground();

	//陰影OFF-----------------------------
	glDisable(GL_LIGHTING);
	//-----------------------------------

	glutSwapBuffers(); //glutInitDisplayMode(GLUT_DOUBLE)でダブルバッファリングを利用可
}

//----------------------------------------------------
// 大地の描画
//----------------------------------------------------
void Ground(void) {
		double ground_max_x = 1000.0;
		double ground_max_y = 1000.0;

		glPushMatrix();
		glColor3d(0.65, 0.65, 0.65);  // 大地の色
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
		glPopMatrix();
}

void Goal(void) {
	char t_char[20];
	char t_char2[20];

	strcpy(t_char2, "Goal!!");
	sprintf(t_char, "%d", 2);
	strcat(t_char2, t_char);
	Display_Text(5, 95, t_char2  );
}

//----------------------------------------------------
// 文字描画
//----------------------------------------------------
void Display_Text(int x, int y, char *string){
	int list;
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glPushAttrib(GL_ENABLE_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0, 0.0, 0.0);
	glCallList(list);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glMatrixMode(GL_MODELVIEW);
	list=glGenLists(1);
	glNewList(list,GL_COMPILE);

	Draw_String(x, y, string , GLUT_BITMAP_TIMES_ROMAN_24);
	glEndList();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void Draw_String(int x, int y, char *string, void *font){
	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++){
		glutBitmapCharacter(font, string[i]);
	}
}

//----------------------------------------------------
// やかんを生み出す
//----------------------------------------------------
void Put_teapot(void) {
	mp[tea_index] = 1;
	if(tea_index == 0) {
		// Teapot1 GOLD!! (1/20)
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_gold.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_gold.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_gold.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_gold.shininess);
		glTranslated(0,210,50);		// ティーポットの移動
		glRotatef(90.0, 1, 0, 1);		// ティーポットの回転
		glRotatef(timer*0.2, 0, 0, 1);	// ティーポットの回転
		glutSolidTeapot(10);				// Teapotの大きさ
		glPopMatrix();
	}else if(tea_index < 4) {
	// Teapot2	(3/20)
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_pearl.ambient);    // http://www.field-and-network.jp/rihei/20091006170714.php
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_pearl.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_pearl.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_pearl.shininess);
		glTranslated(0,210,50);		// ティーポットの移動
		glRotatef(timer*0.3, 0, 1, 1);	// ティーポットの回転
		glutSolidTeapot(7);				// Teapotの大きさ
		glPopMatrix();
	}else if(tea_index < 7) {
		// Teapot3	(3/20)
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_jade.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_jade.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_jade.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_jade.shininess);
		glTranslated(0,210,50);			// ティーポットの移動
		glRotatef(timer*0.1, 1, 1, 1);		// ティーポットの回転
		glutSolidTeapot(7);					// Teapotの大きさ
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
	}else if(tea_index < 13) {
		// Teapot4	(6/20)
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(0.29296,	0.0, 0.5078);	// indigo
		glTranslated(0,210,50);			// ティーポットの移動
		glRotatef(timer*0.2, 1, 0, 1);		// ティーポットの回転
		glutSolidTeapot(5);					// Teapotの大きさ
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
	}else {
		// Teapot5   (7/20)
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(0.9375,	0.5, 0.5);		// lightcoral
		glTranslated(0,210,50);			// ティーポットの移動
		glRotatef(timer*0.4, 1, 1, 0);		// ティーポットの回転
		glutSolidTeapot(5);					// Teapotの大きさ
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
	}

	timer = (timer + 1) % 4320;

}

