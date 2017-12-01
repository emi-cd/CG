#include <GLUT/glut.h>
#include "display.hpp"

#include "scene_four.hpp"

//----------------------------------------------------
// 直方体の定義
//----------------------------------------------------
namespace Four {
	GLdouble wall_one[][3] = {
		{ 30.0,  0.0, -100.0},
		{ 60.0,  0.0, -100.0},
		{ 60.0,  0.0,  100.0},
		{ 30.0,  0.0,  100.0},
		{ 30.0, 70.0, -100.0},
		{ 60.0, 70.0, -100.0},
		{ 60.0, 70.0,  100.0},
		{ 30.0, 70.0,  100.0}
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
		{ -60.0,  0.0, 100.0},
		{  60.0,  0.0, 100.0},
		{  60.0,  0.0, 130.0},
		{ -60.0,  0.0, 130.0},
		{ -60.0, 70.0, 100.0},
		{  60.0, 70.0, 100.0},
		{  60.0, 70.0, 130.0},
		{ -60.0, 70.0, 130.0}
	};
}

void Scene_four() {

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	// 材質の設定  http://www.field-and-network.jp/rihei/20091006170714.php
	// glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);
	// glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
	// glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
	// glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);

	// 直方体1
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]);
		for (int i = 0; i < 4; ++i) {
			glTexCoord2dv(texcoord[i]);
			glVertex3dv(Four::wall_one[face[j][i]]);
		}
	}
	glEnd();

	// 直方体2
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]);
		for (int i = 0; i < 4; ++i) {
			glTexCoord2dv(texcoord[i]);
			glVertex3dv(Four::wall_two[face[j][i]]);
		}
	}
	glEnd();

	// 直方体3
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]);
		for (int i = 0; i < 4; ++i) {
			glTexCoord2dv(texcoord_long[i]);
			glVertex3dv(Four::wall_three[face[j][i]]);
		}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
