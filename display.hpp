#ifndef   _DISPLAY_HPP_
#define   _DISPLAY_HPP_

void Display(void);
void Scene_one();
void Ground(void);  //大地の描画

extern double ViewPointX;
extern double ViewPointY; 
extern double ViewPointZ;
extern double Side;

extern int WindowWidth;    //生成するウィンドウの幅
extern int WindowHeight;    //生成するウィンドウの高さ

#endif // _DISPLAY_HPP_