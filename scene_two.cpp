#include <GLUT/glut.h>
#include "display.hpp"

#include "scene_two.hpp"

//----------------------------------------------------
// 直方体の定義
//----------------------------------------------------
namespace Two {
	GLdouble wall_one[][3] = {
		{ -60.0, -100.0, 0.0 },
		{ -30.0, -100.0, 0.0 },
		{ -30.0, 350.0, 0.0 },
		{ -60.0, 350.0, 0.0 },
		{ -60.0, -100.0, 70.0 },
		{ -30.0, -100.0, 70.0 },
		{ -30.0, 350.0, 70.0 },
		{ -60.0, 350.0, 70.0 }
	};
	GLdouble wall_two[][3] = {
		{ 30.0, -100.0, 0.0 },
		{ 60.0, -100.0, 0.0 },
		{ 60.0, 100.0, 0.0 },
		{ 30.0, 100.0, 0.0 },
		{ 30.0, -100.0, 70.0 },
		{ 60.0, -100.0, 70.0 },
		{ 60.0, 100.0, 70.0 },
		{ 30.0, 100.0, 70.0 }
	};
	GLdouble wall_three[][3] = {
		{ 30.0, 160.0, 0.0 },
		{ 60.0, 160.0, 0.0 },
		{ 60.0, 350.0, 0.0 },
		{ 30.0, 350.0, 0.0 },
		{ 30.0, 160.0, 70.0 },
		{ 60.0, 160.0, 70.0 },
		{ 60.0, 350.0, 70.0 },
		{ 30.0, 350.0, 70.0 }
	};
	GLdouble wall_four[][3] = {
		{ 60.0, 70.0, 0.0 },
		{ 250.0, 70.0, 0.0 },
		{ 250.0, 100.0, 0.0 },
		{ 60.0, 100.0, 0.0 },
		{ 60.0, 70.0, 70.0 },
		{ 250.0, 70.0, 70.0 },
		{ 250.0, 100.0, 70.0 },
		{ 60.0, 100.0, 70.0 }
	};
	GLdouble wall_five[][3] = {
		{ 60.0, 160.0, 0.0 },
		{ 250.0, 160.0, 0.0 },
		{ 250.0, 190.0, 0.0 },
		{ 60.0, 190.0, 0.0 },
		{ 60.0, 160.0, 70.0 },
		{ 250.0, 160.0, 70.0 },
		{ 250.0, 190.0, 70.0 },
		{ 60.0, 190.0, 70.0 }
	};
}

void Scene_two() {
	glPushMatrix();

	// 材質の設定
	glMaterialfv(GL_FRONT, GL_AMBIENT, ms_ruby.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ms_ruby.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ms_ruby.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &ms_ruby.shininess);

	// 直方体1
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]);
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(Two::wall_one[face[j][i]]);
		}
	}
	glEnd();

	// 直方体2
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]);
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(Two::wall_two[face[j][i]]);
		}
	}
	glEnd();

	// 直方体3
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]);
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(Two::wall_three[face[j][i]]);
		}
	}
	glEnd();

	// 直方体4
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]);
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(Two::wall_four[face[j][i]]);
		}
	}
	glEnd();

	// 直方体5
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(normal[j]);
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(Two::wall_five[face[j][i]]);
		}
	}
	glEnd();

	glPopMatrix();

}
