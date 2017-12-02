#include <fstream>
#include <iostream>
#include <GLUT/glut.h>
#include "display.hpp"
#include "keybord.hpp"
#include "warp.hpp"

//----------------------------------------------------
// ウィンドウ構成条件
//----------------------------------------------------
int WindowPositionX = 100;					//生成するウィンドウ位置のX座標
int WindowPositionY = 100;					//生成するウィンドウ位置のY座標
int WindowWidth = 512;    					//生成するウィンドウの幅
int WindowHeight = 512;   					//生成するウィンドウの高さ
char WindowTitle[] = "Teapot's Labyrinth";  //ウィンドウのタイトル

//----------------------------------------------------
// 視点の初期条件
//----------------------------------------------------
double ViewPointX = 0.0;	// 視点位置
double ViewPointY = 30.0; 
double ViewPointZ = 0.0;
double SideX = 0.0;			// 視界の方向
double SideZ = 200.0;
Dir direction = FRONT;
int Scene = 0;
Node* node = NULL;

//----------------------------------------------------
// テクスチャ
//----------------------------------------------------
#define checkImageWidth 2048      // テクスチャの大きさを設定 2**m
#define checkImageHeight 1024     // テクスチャの大きさを設定 2**n
GLubyte checkImage[checkImageWidth][checkImageHeight][4];
GLdouble texcoord[4][2] = {
	{ 0.0, 0.0 },
	{ 1.0, 0.0 },
	{ 1.0, 1.0 },
	{ 0.0, 1.0 }
};
GLdouble texcoord_long[4][2] = {
	{ 0.0, 0.0 },
	{ 4.0, 0.0 },
	{ 4.0, 1.0 },
	{ 0.0, 1.0 }
};

//----------------------------------------------------
// 関数プロトタイプ
//----------------------------------------------------
void makeImage(void);
void Set_fog(void);
void Initialize(void);
void Idle();

//----------------------------------------------------
// メイン関数
//----------------------------------------------------
int main(int argc, char *argv[]){
	glutInit(&argc, argv);										// 環境の初期化
	glutInitWindowPosition(WindowPositionX, WindowPositionY);	// ウィンドウの位置の指定
	glutInitWindowSize(WindowWidth, WindowHeight); 				// ウィンドウサイズの指定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);	// ディスプレイモードの指定
	glutCreateWindow(WindowTitle);  							// ウィンドウの作成

	glutDisplayFunc(Display); 									// 描画時に呼び出される関数を指定する
	glutIdleFunc(Idle);       									// プログラムアイドル状態時に呼び出される関数
	glutKeyboardFunc(Keyboard);									// キーボード入力時に呼び出される関数を指定する
	glutSpecialFunc(SpecialKeyBord); 							// 特殊文字を受け取る
	Initialize(); 												// 初期設定の関数を呼び出す

	glutMainLoop();
	return 0;
}

//----------------------------------------------------
// テクスチャを読み込む
//----------------------------------------------------
void makeImage(void){
	std::ifstream ifs("renga2.txt");

	std::string str;

	for (int i = 0; i < checkImageWidth; i++) {
		for (int j = 0; j < checkImageHeight; j++) {
			std::getline(ifs,str, ' ');
			checkImage[i][j][0] = (GLubyte) std::atoi(str.c_str());
			std::getline(ifs,str, ' ');
			checkImage[i][j][1] = (GLubyte) std::atoi(str.c_str());
			std::getline(ifs,str, ' ');
			checkImage[i][j][2] = (GLubyte) std::atoi(str.c_str());
			checkImage[i][j][3] = (GLubyte) 255;
	}  
  }
}

//----------------------------------------------------
// 霧の設定
//----------------------------------------------------
void Set_fog(void) {
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_DENSITY, 0.5);
	float fog_color[] = {0.3627, 0.3627, 0.3627, 1.0};
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_START, ViewPointZ+10.0);  			// 霧の開始位置
	glFogf(GL_FOG_END, ViewPointZ+70.0); 				// 霧の終了位置
	glClearColor(0.3627, 0.3627, 0.3627, 1.0);
	glEnable(GL_FOG);
}

//----------------------------------------------------
// 初期設定の関数
//----------------------------------------------------
void Initialize(void){
	glEnable(GL_DEPTH_TEST);							//デプスバッファを使用：glutInitDisplayMode() で GLUT_DEPTH を指定する

	// 光源の設定-------------------------------------- 
	GLfloat light_position0[] = {0, 100.0, 0.0, 1.0};	// 光源0の座標
	GLfloat lightDiffuse[4]  = {0.3, 0.3, 0.3, 1.0};	// 拡散光
	GLfloat lightAmbient[4]  = {0.2, 0.2, 0.2, 1.0};	// 環境光
	GLfloat lightSpecular[4] = {0.1, 0.1, 0.1, 1.0};	// 鏡面光
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	// スポットライトの設定-------------------------------------- 
	GLfloat lightDiffuse1[4]  = {0.5, 0.5, 0.5, 1.0};		// 拡散光
	GLfloat lightAmbient1[4]  = {0.2, 0.2, 0.2, 1.0};		// 環境光
	GLfloat lightSpecular1[4] = {0.7, 0.7, 0.7, 1.0};		// 鏡面光
	GLfloat light_position1[] = { 0.0, 100.0, 80.0, 1.0 }; 	// スポットライト
	GLfloat spotDirrection[] = { 0.0, -1.0, 0.0 }; 			// スポットライトを向ける方向
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  lightDiffuse1);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  lightAmbient1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,  30.0 );			 // スポットライトの絞り（デフォルト 180.0）
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.1 );			 // スポットライトの中心からの減衰の度合い（デフォルト 0）
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1); 	 //座標をセット
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirrection );//スポットライトの向ける方向（デフォルト (0,0,-1.0)）

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);									// 光源0を利用

	// テクスチャの設定-------------------------------------- 
	makeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight,  
    	           0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

	// 霧 -------------------------------------- 
	Set_fog();

	// 迷宮の設定 -------------------------------------- 
	node = make_Labyrinth();
 }

//----------------------------------------------------
// アイドル時に呼び出される関数
//----------------------------------------------------
void Idle(){
	glutPostRedisplay(); //glutDisplayFunc()を１回実行する
}
