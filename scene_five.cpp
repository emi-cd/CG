#include <GLUT/glut.h>
#include "display.hpp"

#include "scene_five.hpp"

//----------------------------------------------------
// 直方体の定義
//----------------------------------------------------
namespace Five {

	GLdouble wall_one[][3] = {
		{ 60.0,  0, -150.0},
		{ 30.0,  0, -150.0},
		{ 30.0,  0,  350.0},
		{ 60.0,  0,  350.0},
		{ 60.0, 70, -150.0},
		{ 30.0, 70, -150.0},
		{ 30.0, 70,  350.0},
		{ 60.0, 70,  350.0}
	};
	GLdouble wall_two[][3] = {
		{ -60.0,  0.0, -100.0},
		{ -30.0,  0.0, -100.0},
		{ -30.0,  0.0,  100.0},
		{ -60.0,  0.0,  100.0},
		{ -60.0, 70.0, -100.0},
		{ -30.0, 70.0, -100.0},
		{ -30.0, 70.0,  100.0},
		{ -60.0, 70.0,  100.0}
	};
	GLdouble wall_three[][3] = {
		{ -250.0,  0.0,  70.0},
		{  -60.0,  0.0,  70.0},
		{  -60.0,  0.0, 100.0},
		{ -250.0,  0.0, 100.0},
		{ -250.0, 70.0,  70.0},
		{  -60.0, 70.0,  70.0},
		{  -60.0, 70.0, 100.0},
		{ -250.0, 70.0, 100.0}
	};
	GLdouble wall_four[][3] = {
		{ -30.0,  0.0, 160.0},
		{ -60.0,  0.0, 160.0},
		{ -60.0,  0.0, 350.0},
		{ -30.0,  0.0, 350.0},
		{ -30.0, 70.0, 160.0},
		{ -60.0, 70.0, 160.0},
		{ -60.0, 70.0, 350.0},
		{ -30.0, 70.0, 350.0}
	};
	GLdouble wall_five[][3] = {
		{  -60.0,  0.0, 160.0},
		{ -250.0,  0.0, 160.0},
		{ -250.0,  0.0, 190.0},
		{  -60.0,  0.0, 190.0},
		{  -60.0, 70.0, 160.0},
		{ -250.0, 70.0, 160.0},
		{ -250.0, 70.0, 190.0},
		{  -60.0, 70.0, 190.0}
	};
}

void Scene_five() {

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	// 材質の設定
	// glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);
	// glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
	// glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
	// glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);

	// 直方体1
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]); //法線ベクトルの指定
		for (int i = 0; i < 4; ++i) {
			glTexCoord2dv(texcoord[i]);
			glVertex3dv(Five::wall_one[face[j][i]]);
		}
	}
	glEnd();

	// 直方体2
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]); //法線ベクトルの指定
		for (int i = 0; i < 4; ++i) {
			glTexCoord2dv(texcoord[i]);
			glVertex3dv(Five::wall_two[face[j][i]]);
		}
	}
	glEnd();

	// 直方体3
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]); //法線ベクトルの指定
		for (int i = 0; i < 4; ++i) {
			glTexCoord2dv(texcoord[i]);
			glVertex3dv(Five::wall_three[face[j][i]]);
		}
	}
	glEnd();

	// 直方体4
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]); //法線ベクトルの指定
		for (int i = 0; i < 4; ++i) {
			glTexCoord2dv(texcoord[i]);
			glVertex3dv(Five::wall_four[face[j][i]]);
		}
	}
	glEnd();

	// 直方体5
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]); //法線ベクトルの指定
		for (int i = 0; i < 4; ++i) {
			glTexCoord2dv(texcoord[i]);
			glVertex3dv(Five::wall_five[face[j][i]]);
		}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
