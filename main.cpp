#include <GLUT/glut.h>
#include "display.hpp"
#include "keybord.hpp"

//----------------------------------------------------
// ウィンドウ構成条件
//----------------------------------------------------
// http://www.natural-science.or.jp/article/20091124233406.php
int WindowPositionX = 100;  //生成するウィンドウ位置のX座標
int WindowPositionY = 100;  //生成するウィンドウ位置のY座標
int WindowWidth = 512;    //生成するウィンドウの幅
int WindowHeight = 512;    //生成するウィンドウの高さ
char WindowTitle[] = "迷路";  //ウィンドウのタイトル

//----------------------------------------------------
// 視点の初期条件
//----------------------------------------------------
double ViewPointX = 0.0;	// 視点位置
double ViewPointY = 0.0; 
double ViewPointZ = 30.0;
double SideX = 0.0;		// 視界の方向
double SideY = 200.0;
Dir direction = FRONT;
int Scene = 0;

//----------------------------------------------------
// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
//----------------------------------------------------
void Initialize(void);
void Idle();

//----------------------------------------------------
// メイン関数
//----------------------------------------------------
int main(int argc, char *argv[]){
	glutInit(&argc, argv);//環境の初期化
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//ウィンドウの位置の指定
	glutInitWindowSize(WindowWidth, WindowHeight); //ウィンドウサイズの指定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定
	glutCreateWindow(WindowTitle);  //ウィンドウの作成
	glutDisplayFunc(Display); //描画時に呼び出される関数を指定する（関数名：Display）
	glutIdleFunc(Idle);       //プログラムアイドル状態時に呼び出される関数
	glutKeyboardFunc(Keyboard);//キーボード入力時に呼び出される関数を指定する（関数名：Keyboard）
	glutSpecialFunc(SpecialKeyBord); //特殊文字を受け取る
	Initialize(); //初期設定の関数を呼び出す

	glutMainLoop();
	return 0;
}

//----------------------------------------------------
// 初期設定の関数
//----------------------------------------------------
void Initialize(void){
	glClearColor(1.0, 1.0, 1.0, 1.0); //背景色
	glEnable(GL_DEPTH_TEST);//デプスバッファを使用：glutInitDisplayMode() で GLUT_DEPTH を指定する

	//光源の設定-------------------------------------- 
	// http://www.natural-science.or.jp/article/20101115171505.php
	GLfloat light_position0[] = { 0.0, 0.0, 50.0, 1.0 }; //光源0の座標
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0); //光源0を

	// 霧
	//フォグの設定
         glEnable(GL_FOG);
	 glFogi(GL_FOG_MODE, GL_EXP);
	 glFogf(GL_FOG_DENSITY, 0.02);
	 float fog_color[] = {0.8, 0.8, 0.8, 1.0};
	 glFogfv(GL_FOG_COLOR, fog_color);
	 glClearColor(0.8, 0.8, 0.8, 1.0);
 }

//----------------------------------------------------
// アイドル時に呼び出される関数
//----------------------------------------------------
void Idle(){
	glutPostRedisplay(); //glutDisplayFunc()を１回実行する
}
