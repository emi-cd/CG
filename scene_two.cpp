#include <GLUT/glut.h>
#include "display.hpp"

#include "scene_two.hpp"

namespace Two {
	//----------------------------------------------------
	// 直方体の定義
	//----------------------------------------------------
	GLdouble wall_one[][3] = {
		{ -90.0, -300.0, 0.0 },
		{ -60.0, -300.0, 0.0 },
		{ -60.0, 720.0, 0.0 },
		{ -90.0, 720.0, 0.0 },
		{ -90.0, -300.0, 70.0 },
		{ -60.0, -300.0, 70.0 },
		{ -60.0, 720.0, 70.0 },
		{ -90.0, 720.0, 70.0 }
	};
	GLdouble wall_two[][3] = {
		{ 0.0, -300.0, 0.0 },
		{ 30.0, -300.0, 0.0 },
		{ 30.0, 130.0, 0.0 },
		{ 0.0, 130.0, 0.0 },
		{ 0.0, -300.0, 70.0 },
		{ 30.0, -300.0, 70.0 },
		{ 30.0, 130.0, 70.0 },
		{ 0.0, 130.0, 70.0 }
	};
	GLdouble wall_three[][3] = {
		{ 0.0, 190.0, 0.0 },
		{ 30.0, 190.0, 0.0 },
		{ 30.0, 720.0, 0.0 },
		{ 0.0, 720.0, 0.0 },
		{ 0.0, 190.0, 70.0 },
		{ 30.0, 190.0, 70.0 },
		{ 30.0, 720.0, 70.0 },
		{ 0.0, 720.0, 70.0 }
	};
	GLdouble wall_four[][3] = {
		{ 30.0, 100.0, 0.0 },
		{ 330.0, 100.0, 0.0 },
		{ 330.0, 130.0, 0.0 },
		{ 30.0, 130.0, 0.0 },
		{ 30.0, 100.0, 70.0 },
		{ 330.0, 100.0, 70.0 },
		{ 330.0, 130.0, 70.0 },
		{ 30.0, 130.0, 70.0 }
	};
	GLdouble wall_five[][3] = {
		{ 30.0, 190.0, 0.0 },
		{ 330.0, 190.0, 0.0 },
		{ 330.0, 210.0, 0.0 },
		{ 30.0, 210.0, 0.0 },
		{ 30.0, 190.0, 70.0 },
		{ 330.0, 190.0, 70.0 },
		{ 330.0, 210.0, 70.0 },
		{ 30.0, 210.0, 70.0 }
	};
}

void Scene_two() {
	//直方体1
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);    // http://www.field-and-network.jp/rihei/20091006170714.php
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);
	glTranslated(30.0, 50.0, 0.0);//平行移動値の設定
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]); //法線ベクトルの指定
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(Two::wall_one[face[j][i]]);
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
			glVertex3dv(Two::wall_two[face[j][i]]);
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
			glVertex3dv(Two::wall_three[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();
	//直方体4
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
			glVertex3dv(Two::wall_four[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();
	//直方体5
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
			glVertex3dv(Two::wall_five[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();

}
