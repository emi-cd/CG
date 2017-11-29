#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <math.h>
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
// Teapot の設定
//----------------------------------------------------
double timer = 0;
int size = std::rand() % 3 + 5;			// Teapot のサイズ
int tea_index = std::rand() % 20;		// Teapot の確率
int mp[5] = {0, 0, 0, 0, 0};
int x = 0;


//----------------------------------------------------
// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
//----------------------------------------------------
void Put_teapot(void);
void Ground(void);
void Goal(void);
void DrawString(std::string str, int x0, int y0, void *font = GLUT_BITMAP_TIMES_ROMAN_24);
void print_teapot_state(void);
void teapot(void);

//----------------------------------------------------
// 描画の関数
//----------------------------------------------------
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Zバッファの消去

	//透視変換行列の設定------------------------------
	glMatrixMode(GL_PROJECTION);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
	glLoadIdentity();//行列の初期化
	gluPerspective(80.0, (double)WindowWidth/(double)WindowHeight, 0.1, 160.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);

	//視点の設定------------------------------
	gluLookAt(		// http://atelier-yoka.com/dev_android/p_main.php?file=apigluglulookat
			 ViewPointX, ViewPointY, ViewPointZ, // 視点の位置x,y,z;
			 SideX, SideY, 30.0,   // カメラが見ている位置,y,z
			 0.0, 0.0, 1.0);  //カメラの上方向がどれくらいかx,y,z

	//陰影ON-----------------------------
	GLfloat light_position0[] = {ViewPointX, ViewPointY, 30.0, 1.0};	// 光源0の座標
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);		//光源0を利用

	//モデルビュー変換行列の設定--------------------------
	glMatrixMode(GL_MODELVIEW);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
	glLoadIdentity();//行列の初期化
	glViewport(0, 0, WindowWidth, WindowHeight);
	//----------------------------------------------

	switch(Scene) {
	case 0:
		print_teapot_state();
		teapot();
		Scene_one();
		Put_teapot();
		break;
	case 1:
		print_teapot_state();
		teapot();
		Scene_two();
		Put_teapot();
		break;
	case 2:
		print_teapot_state();
		teapot();
		Scene_three();
		Put_teapot();
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
	double ground_max_x = 500.0;
	double ground_max_y = 500.0;

	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();

	// 大地
	glColor3d(0.98039, 0.94118, 0.90196);  // 大地の色
	glBegin(GL_QUADS);
	glVertex3f(-500, -500.0, 0.0);
	glVertex3f(-500, 500.0, 0.0);
	glVertex3f( 500, -500.0, 0.0);
	glVertex3f( 500, 500.0, 0.0);
	glEnd();

	// 大地の線
	glColor3d(0.41176, 0.41176, 0.41176);  // 大地の線の色
	glBegin(GL_LINES);
	for(double ly = -ground_max_y ; ly <= ground_max_y; ly+=10.0){
		glVertex3d(-ground_max_x, ly, 0.2);
		glVertex3d(ground_max_x, ly, 0.2);
	}
	for(double lx = -ground_max_x ; lx <= ground_max_x; lx+=10.0){
		glVertex3d(lx, ground_max_y, 0.2);
		glVertex3d(lx, -ground_max_y, 0.2);
	}
	glEnd();

	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);

}

//----------------------------------------------------
// ゴールの描画
//----------------------------------------------------
void Goal(void) {
	char t_char[20];
	char t_char2[20];

	glDisable(GL_FOG);
	glClearColor(1.0, 0.98039, 0.94118, 1.0);

	// teapot1
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ms_gold.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_gold.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ms_gold.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &ms_gold.shininess);
	glTranslated(0, 60, 25);		// ティーポットの移動
	glRotatef(90.0, 1, 0, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);	// ティーポットの回転
	glutSolidTeapot(15);				// Teapotの大きさ
	glPopMatrix();

	// teapot2
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ms_pearl.ambient);    // http://www.field-and-network.jp/rihei/20091006170714.php
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_pearl.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ms_pearl.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &ms_pearl.shininess);
	glTranslated(-30, 70, 40);		// ティーポットの移動
	glRotatef(90.0, 1, 0, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);	// ティーポットの回転
	glutSolidTeapot(10);			// Teapotの大きさ
	glPopMatrix();

	// teapot3
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ms_jade.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_jade.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ms_jade.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &ms_jade.shininess);
	glTranslated(30, 70, 40);			// ティーポットの移動
	glRotatef(90.0, 1, 0, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);		// ティーポットの回転
	glutSolidTeapot(10);					// Teapotの大きさ
	glPopMatrix();

	// teapot4
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3d(0.29296,	0.0, 0.5078);	// indigo
	glTranslated(-60, 90, 50);			// ティーポットの移動
	glRotatef(90.0, 1, 0, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);		// ティーポットの回転
	glutSolidTeapot(10);					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();	

	// glPushMatrix();
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3d(0.9375,	0.5, 0.5);		// lightcoral
	glTranslated(60, 90, 50);			// ティーポットの移動
	glRotatef(90.0, 1, 0, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);		// ティーポットの回転
	glutSolidTeapot(10);					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	x = (x+1)%720000;
	timer = 3000 + sin(x*0.0005)*3000;

	DrawString("C O N G R A T U L A T I O N S ! !", 95, 95);
	DrawString("G O A L !", 210, 150);

}

// //----------------------------------------------------
// // 文字描画
// //----------------------------------------------------
void DrawString(std::string str, int x, int y, void *font) {
    glDisable(GL_LIGHTING);
    // 平行投影にする
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glColor3d(0.1, 0.1, 0.1);
    glLoadIdentity();
    gluOrtho2D(0, WindowWidth, WindowHeight, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 画面上にテキスト描画
    glRasterPos2f(x, y);
    int size = (int)str.size();
    for(int i = 0; i < size; ++i){
        char c = str[i];
        glutBitmapCharacter(font, c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
}

//----------------------------------------------------
// Teapotを生み出す
//----------------------------------------------------
void Put_teapot(void) {
	if(tea_index == 0) {
		// Teapot1 GOLD!! (1/20)
		mp[0] = 1;
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_gold.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_gold.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_gold.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_gold.shininess);
		glTranslated(0,130,55);		// ティーポットの移動
		glRotatef(90.0, 1, 0, 1);		// ティーポットの回転
		glRotatef(timer*0.2, 0, 0, 1);	// ティーポットの回転
		glutSolidTeapot(17);				// Teapotの大きさ
		glPopMatrix();
	}else if(tea_index < 4) {
		// Teapot2	(3/20)
		mp[1] = 1;
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_pearl.ambient);    // http://www.field-and-network.jp/rihei/20091006170714.php
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_pearl.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_pearl.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_pearl.shininess);
		glTranslated(0,130,55);		// ティーポットの移動
		glRotatef(timer*0.3, 0, 1, 1);	// ティーポットの回転
		glutSolidTeapot(13);				// Teapotの大きさ
		glPopMatrix();
	}else if(tea_index < 7) {
		// Teapot3	(3/20)
		mp[2] = 1;
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_jade.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_jade.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_jade.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_jade.shininess);
		glTranslated(0,130,55);			// ティーポットの移動
		glRotatef(timer*0.1, 1, 1, 1);		// ティーポットの回転
		glutSolidTeapot(13);					// Teapotの大きさ
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
	}else if(tea_index < 13) {
		// Teapot4	(6/20)
		mp[3] = 1;
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(0.29296,	0.0, 0.5078);	// indigo
		glTranslated(0,130,55);			// ティーポットの移動
		glRotatef(timer*0.2, 1, 0, 1);		// ティーポットの回転
		glutSolidTeapot(10);					// Teapotの大きさ
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
	}else {
		// Teapot5   (7/20)
		mp[4] = 1;
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(0.9375,	0.5, 0.5);		// lightcoral
		glTranslated(0,130,55);			// ティーポットの移動
		glRotatef(timer*0.4, 1, 1, 0);		// ティーポットの回転
		glutSolidTeapot(10);					// Teapotの大きさ
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
	}

	x = (x+1)%720000;
	timer = 3000 + sin(x*0.0005)*3000;

}

//----------------------------------------------------
// 出会ったTeapotの数を表示
//----------------------------------------------------
void print_teapot_state(void){
	char t_char[20];
	char t_char2[20];
	int sum = 0;

	for(int i = 0; i<5; i++)
		sum += mp[i];

	strcpy(t_char2, "Your teapot:  ");
	sprintf(t_char, "%d", sum);
	strcat(t_char2, t_char);
	strcat(t_char2, "/ 5");

	std::string str(t_char2);

	DrawString(str, 5, 20, GLUT_BITMAP_HELVETICA_10);
}

//----------------------------------------------------
// もぶTeapotを生み出す
//----------------------------------------------------
void teapot(void){
	glEnable(GL_COLOR_MATERIAL);
	glColor3d(0.90196,	0.90196, 1.0);

	glPushMatrix();
	glTranslated(130+timer*0.01, 180-timer*0.01, 60+timer*0.005);			// ティーポットの移動
	glRotatef(timer*0.1, 1, 1, 0);		// ティーポットの回転
	glutWireTeapot(15+5*cos(timer*0.005));					// Teapotの大きさ
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glTranslated(40-timer*0.05, 180+sin(timer*0.005)*20, 40+cos(timer*0.005)*10);			// ティーポットの移動
	glRotatef(timer*0.2, 1, 0, 0);		// ティーポットの回転
	glutWireTeapot(15+5*cos(timer*0.01));					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glTranslated(-20, 100, 60);			// ティーポットの移動
	glRotatef(30.0, 0, 1, 1);		// ティーポットの回転
	glutWireTeapot(15+5*sin(timer*0.01));					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glTranslated(-100, 200, 60);			// ティーポットの移動
	glRotatef(70.0, 1, 1, 1);		// ティーポットの回転
	glutWireTeapot(20+5*cos(timer*0.01));					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glTranslated(10+sin(timer*0.005)*30, 250+cos(timer*0.005)*10, 60+sin(timer*0.005)*10);			// ティーポットの移動
	glRotatef(70.0, 1, 1, 0);		// ティーポットの回転
	glutWireTeapot(20);					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

