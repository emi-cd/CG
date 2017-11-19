#include <GLUT/glut.h>
#include "display.hpp"

#include "scene_three.hpp"

namespace Three {
	//----------------------------------------------------
	// 直方体の定義
	//----------------------------------------------------
	GLdouble wall_one[][3] = {
		{ 0.0, 0.0, 0.0 },
		{ 30.0, 0.0, 0.0 },
		{ 30.0, 280.0, 0.0 },
		{ 0.0, 280.0, 0.0 },
		{ 0.0, 0.0, 70.0 },
		{ 30.0, 0.0, 70.0 },
		{ 30.0, 280.0, 70.0 },
		{ 0.0, 280.0, 70.0 }
	};
	GLdouble wall_two[][3] = {
		{ -90.0, 0.0, 0.0 },
		{ -60.0, 0.0, 0.0 },
		{ -60.0, 280.0, 0.0 },
		{ -90.0, 280.0, 0.0 },
		{ -90.0, 0.0, 70.0 },
		{ -60.0, 0.0, 70.0 },
		{ -60.0, 280.0, 70.0 },
		{ -90.0, 280.0, 70.0 }
	};
	GLdouble wall_three[][3] = {
		{ 0.0, 340.0, 0.0 },
		{ 30.0, 340.0, 0.0 },
		{ 30.0, 720.0, 0.0 },
		{ 0.0, 720.0, 0.0 },
		{ 0.0, 340.0, 70.0 },
		{ 30.0, 340.0, 70.0 },
		{ 30.0, 720.0, 70.0 },
		{ 0.0, 720.0, 70.0 }
	};
	GLdouble wall_four[][3] = {
		{ -90.0, 340.0, 0.0 },
		{ -60.0, 340.0, 0.0 },
		{ -60.0, 720.0, 0.0 },
		{ -90.0, 720.0, 0.0 },
		{ -90.0, 340.0, 70.0 },
		{ -60.0, 340.0, 70.0 },
		{ -60.0, 720.0, 70.0 },
		{ -90.0, 720.0, 70.0 }
	};
	GLdouble wall_five[][3] = {
		{ 30.0, 340.0, 0.0 },
		{ 330.0, 340.0, 0.0 },
		{ 330.0, 370.0, 0.0 },
		{ 30.0, 370.0, 0.0 },
		{ 30.0, 340.0, 70.0 },
		{ 330.0, 340.0, 70.0 },
		{ 330.0, 370.0, 70.0 },
		{ 30.0, 370.0, 70.0 }
	};
	GLdouble wall_six[][3] = {
		{ -440.0, 250.0, 0.0 },
		{ -90.0, 250.0, 0.0 },
		{ -90.0, 280.0, 0.0 },
		{ -440.0, 280.0, 0.0 },
		{ -440.0, 250.0, 70.0 },
		{ -90.0, 250.0, 70.0 },
		{ -90.0, 280.0, 70.0 },
		{ -440.0, 280.0, 70.0 }
	};
	GLdouble wall_seven[][3] = {
		{ 30.0, 250.0, 0.0 },
		{ 380.0, 250.0, 0.0 },
		{ 380.0, 280.0, 0.0 },
		{ 30.0, 280.0, 0.0 },
		{ 30.0, 250.0, 70.0 },
		{ 380.0, 250.0, 70.0 },
		{ 380.0, 280.0, 70.0 },
		{ 30.0, 280.0, 70.0 }
	};
	GLdouble wall_eight[][3] = {
		{ -440.0, 340.0, 0.0 },
		{ -90.0, 340.0, 0.0 },
		{ -90.0, 370.0, 0.0 },
		{ -440.0, 370.0, 0.0 },
		{ -440.0, 340.0, 70.0 },
		{ -90.0, 340.0, 70.0 },
		{ -90.0, 370.0, 70.0 },
		{ -440.0, 370.0, 70.0 }
	};
}

void Scene_three() {
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
			glVertex3dv(Three::wall_one[face[j][i]]);
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
			glVertex3dv(Three::wall_two[face[j][i]]);
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
			glVertex3dv(Three::wall_three[face[j][i]]);
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
			glVertex3dv(Three::wall_four[face[j][i]]);
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
			glVertex3dv(Three::wall_five[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();
	//直方体6
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
			glVertex3dv(Three::wall_six[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();
	//直方体7
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
			glVertex3dv(Three::wall_seven[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();
	//直方体8
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
			glVertex3dv(Three::wall_eight[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();

}
