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
#include "scene_four.hpp"
#include "scene_five.hpp"

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
int flag = 0;
int last_teapot = -1;
int old_scene = -1;

// 空間の回転
float rot_y = 0.0;


//----------------------------------------------------
// 関数プロトタイプ
//----------------------------------------------------
void Put_teapot(void);
void Ground(void);
void Goal(void);
void DrawString(std::string str, int x0, int y0, int flag, void *font = GLUT_BITMAP_TIMES_ROMAN_24);
void print_teapot_state(void);
void teapot(void);
void Celling(void);

//----------------------------------------------------
// 描画の関数
//----------------------------------------------------
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Zバッファの消去

	//透視変換行列の設定------------------------------
	glMatrixMode(GL_PROJECTION);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
	glLoadIdentity();//行列の初期化
	gluPerspective(100.0, (double)WindowWidth/(double)WindowHeight, 0.1, 160.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);

	// 視点の設定------------------------------
	gluLookAt(		// http://atelier-yoka.com/dev_android/p_main.php?file=apigluglulookat
			 ViewPointX, ViewPointY, ViewPointZ, // 視点の位置x,y,z;
			 SideX, 30.0, SideZ,   // カメラが見ている位置,y,z
			 0.0, 1.0, 0.0);  //カメラの上方向がどれくらいかx,y,z

	// 光源の設定-----------------------------
	GLfloat light_position0[] = {ViewPointX, 30.0, ViewPointZ, 1.0};	// 光源0の座標
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	// fog-----------------------------
	glFogf(GL_FOG_START, ViewPointZ+20.0);  //開始位置
	glFogf(GL_FOG_END, ViewPointZ+70.0); //終了位置

	// モデルビュー変換行列の設定--------------------------
	glMatrixMode(GL_MODELVIEW);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
	glLoadIdentity();//行列の初期化
	glViewport(0, 0, WindowWidth, WindowHeight);


	glTranslated(ViewPointX, ViewPointY, ViewPointZ);
	glRotatef(rot_y, 0.0f, 1.0f, 0.0f);
	glTranslated(-ViewPointX, -ViewPointY, -ViewPointZ);

	if(mp[0] + mp[1] + mp[2] + mp[3] + mp[4] != 5) {
		switch(Scene) {
		case 0:
			print_teapot_state();
			Celling();
			teapot();
			Scene_one();
			flag = 1;
			break;
		case 1:
			print_teapot_state();
			Celling();
			teapot();
			Scene_two();
			flag = 1;
			break;
		case 2:
			print_teapot_state();
			Celling();
			teapot();
			Scene_three();
			flag = 1;
			break;
		case 3:
			print_teapot_state();
			Celling();
			teapot();
			Scene_five();
			flag = 1;
			break;
		case 4:
			print_teapot_state();
			Celling();
			teapot();
			Scene_four();
			Put_teapot();
			flag = 0;
			break;
		}
	}else {
		glEnable(GL_LIGHT2);
		Goal();
	}

	// 大地
	Ground();

	if(flag && last_teapot!=-1) {
		mp[last_teapot] = 1;	
		last_teapot = -1;
	}

	x = (x+1)%720000;
	timer = 3000 + sin(x*0.0005)*3000;

	glutSwapBuffers(); //glutInitDisplayMode(GLUT_DOUBLE)でダブルバッファリングを利用可
}

//----------------------------------------------------
// 大地の描画
//----------------------------------------------------
void Ground(void) {
	double ground_max_x = 500.0;
	double ground_max_z = 500.0;

	glEnable(GL_COLOR_MATERIAL);

	// 大地
	glColor3d(0.50196, 0.50196, 0.50196);  // 大地の色;
	glBegin(GL_QUADS);
	glVertex3f(-1000.0, 0.0, -1000.0);
	glVertex3f( 1000.0, 0.0, -1000.0);
	glVertex3f( 1000.0, 0.0,  1000.0);
	glVertex3f(-1000.0, 0.0,  1000.0);
	glEnd();

	// 大地の線
	glColor3d(0.8529, 0.8529, 0.8529);  // 大地の線の色
	glBegin(GL_LINES);
	for(double lz = -ground_max_z ; lz <= ground_max_z; lz+=10.0){
		glVertex3d(-ground_max_x, 0.2, lz);
		glVertex3d(ground_max_x, 0.2, lz);
	}
	for(double lx = -ground_max_x ; lx <= ground_max_x; lx+=10.0){
		glVertex3d(lx, 0.2, ground_max_z);
		glVertex3d(lx, 0.2, -ground_max_z);
	}
	glEnd();

	glDisable(GL_COLOR_MATERIAL);

}

void Celling(void) {
	glColor3d(0.50196, 0.50196, 0.50196);  // 大地の色;
	glBegin(GL_QUADS);
	glVertex3f(-1000.0, 70.0, -1000.0);
	glVertex3f( 1000.0, 70.0, -1000.0);
	glVertex3f( 1000.0, 70.0,  1000.0);
	glVertex3f(-1000.0, 70.0,  1000.0);
	glEnd();
}

//----------------------------------------------------
// ゴールの描画
//----------------------------------------------------
void Goal(void) {
	char t_char[20];
	char t_char2[20];

	glDisable(GL_FOG);
	glClearColor(1.0, 0.98039, 0.94118, 1.0);
	rot_y = 0.0;
	ViewPointX = 0.0;
	ViewPointZ = 0.0;
	SideX = 0.0;
	SideZ = 200.0;

	// teapot1
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ms_gold.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_gold.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ms_gold.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &ms_gold.shininess);
	glTranslated(0, 25, 40);		// ティーポットの移動
	glRotatef(90.0, 0, 1, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);	// ティーポットの回転
	glutSolidTeapot(15);			// Teapotの大きさ
	glPopMatrix();

	// teapot2
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ms_pearl.ambient);    // http://www.field-and-network.jp/rihei/20091006170714.php
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_pearl.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ms_pearl.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &ms_pearl.shininess);
	glTranslated(-30, 40, 50);		// ティーポットの移動
	glRotatef(90.0, 0, 1, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);	// ティーポットの回転
	glutSolidTeapot(10);			// Teapotの大きさ
	glPopMatrix();

	// teapot3
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ms_jade.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_jade.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ms_jade.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &ms_jade.shininess);
	glTranslated(30, 40, 50);			// ティーポットの移動
	glRotatef(90.0, 0, 1, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);		// ティーポットの回転
	glutSolidTeapot(10);					// Teapotの大きさ
	glPopMatrix();

	// teapot4
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3d(0.29296,	0.0, 0.5078);	// indigo
	glTranslated(-60, 50, 70);			// ティーポットの移動
	glRotatef(90.0, 0, 1, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);		// ティーポットの回転
	glutSolidTeapot(10);					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();	

	// glPushMatrix();
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3d(0.9375,	0.5, 0.5);		// lightcoral
	glTranslated(60, 50, 70);			// ティーポットの移動
	glRotatef(90.0, 0, 1, 0);		// ティーポットの回転
	glRotatef(timer*0.3, 0, 1, 0);		// ティーポットの回転
	glutSolidTeapot(10);					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	DrawString("C O N G R A T U L A T I O N S ! !", 95, 95, 0);
	DrawString("G O A L !", 210, 150, 0);

}

//----------------------------------------------------
// 文字描画
//----------------------------------------------------
void DrawString(std::string str, int x, int y, int flag, void *font) {
    glDisable(GL_LIGHTING);
    // 平行投影にする
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    if(flag)
    	glColor3d(1.0, 1.0, 1.0);
    else 
    	glColor3d(0.0, 0.0, 0.0);
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
	glEnable(GL_LIGHT1);		// スポットライト
	// Teapot1 GOLD!! (1/10)
	if(tea_index < 1 && !mp[0]) {
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_gold.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_gold.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_gold.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_gold.shininess);
		glTranslated(0, 40, 80);		// ティーポットの移動
		glRotatef(90.0, 1, 0, 1);		// ティーポットの回転
		glRotatef(timer*0.2, 0, 0, 1);	// ティーポットの回転
		glutSolidTeapot(17);			// Teapotの大きさ
		glPopMatrix();
		last_teapot = 0;
	}else if(tea_index < 3 && !mp[1]) {			// Teapot2	(2/10)
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_pearl.ambient);    // http://www.field-and-network.jp/rihei/20091006170714.php
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_pearl.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_pearl.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_pearl.shininess);
		glTranslated(0, 40, 80);		// ティーポットの移動
		glRotatef(timer*0.3, 0, 1, 1);	// ティーポットの回転
		glutSolidTeapot(13);				// Teapotの大きさ
		glPopMatrix();
		last_teapot = 1;
	}else if(tea_index < 5 && !mp[2]) {			// Teapot3	(2/10)
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, ms_jade.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_jade.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, ms_jade.specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, &ms_jade.shininess);
		glTranslated(0, 40, 80);			// ティーポットの移動
		glRotatef(timer*0.1, 1, 1, 1);		// ティーポットの回転
		glutSolidTeapot(13);					// Teapotの大きさ
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
		last_teapot = 2;
	}else if(tea_index && !mp[3]) {				// Teapot4	(2/10)
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(0.29296,	0.0, 0.5078);	// indigo
		glTranslated(0, 40, 80);			// ティーポットの移動
		glRotatef(timer*0.2, 1, 0, 1);		// ティーポットの回転
		glutSolidTeapot(10);					// Teapotの大きさ
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
		last_teapot = 3;
	}else if(!mp[4]){								// Teapot4	(2/10)
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glColor3d(0.9375,	0.5, 0.5);		// lightcoral
		glTranslated(0, 40, 80);			// ティーポットの移動
		glRotatef(timer*0.4, 1, 1, 0);		// ティーポットの回転
		glutSolidTeapot(10);					// Teapotの大きさ
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
		last_teapot = 4;
	}
	glDisable(GL_LIGHT1);

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

	DrawString(str, 5, 20, 1, GLUT_BITMAP_HELVETICA_10);
}

//----------------------------------------------------
// もぶTeapotを生み出す
//----------------------------------------------------
void teapot(void){
	glEnable(GL_COLOR_MATERIAL);
	glColor3d(0.90196,	0.90196, 1.0);

	glPushMatrix();
	glTranslated(130+timer*0.01, 60+timer*0.005, 130-timer*0.01);			// ティーポットの移動
	glRotatef(timer*0.1, 1, 1, 0);		// ティーポットの回転
	glutWireTeapot(15+5*cos(timer*0.005));					// Teapotの大きさ
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glTranslated(-40-timer*0.05, 40+cos(timer*0.005)*10, 130+sin(timer*0.005)*20);			// ティーポットの移動
	glRotatef(timer*0.2, 1, 0, 0);		// ティーポットの回転
	glutWireTeapot(15+5*cos(timer*0.01));					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glTranslated(20, 60, 60);			// ティーポットの移動
	glRotatef(30.0, 0, 1, 1);		// ティーポットの回転
	glutWireTeapot(15+5*sin(timer*0.01));					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glTranslated(-100, 60, 100);			// ティーポットの移動
	glRotatef(70.0, 1, 1, 1);		// ティーポットの回転
	glutWireTeapot(20+5*cos(timer*0.01));					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glTranslated(10+sin(timer*0.005)*30,  60+sin(timer*0.005)*10, 140+cos(timer*0.005)*10);			// ティーポットの移動
	glRotatef(70.0, 1, 1, 0);		// ティーポットの回転
	glutWireTeapot(20+5*cos(timer*0.01));					// Teapotの大きさ
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

