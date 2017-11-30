#ifndef _DISPLAY_HPP_
#define _DISPLAY_HPP_

// 描画する関数
void Display(void);

// 視点の設定
extern double ViewPointX;
extern double ViewPointY; 
extern double ViewPointZ;
extern double SideX;
extern double SideZ;

extern int WindowWidth;		// 生成するウィンドウの幅
extern int WindowHeight;	// 生成するウィンドウの高さ


extern int face[][4];			// 面の定義
extern GLdouble normal[][3];	 // 面の法線ベクトル

extern int Scene; 					// 描画するシーン

extern GLdouble texcoord[4][2];
extern GLdouble texcoord_long[4][2];

extern float rot_y;

//----------------------------------------------------
// 物質質感の定義
//----------------------------------------------------
struct MaterialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
};
extern struct MaterialStruct ms_jade;
extern struct MaterialStruct ms_ruby;
extern struct MaterialStruct ms_gold;
extern struct MaterialStruct ms_pearl;

#endif // _DISPLAY_HPP_