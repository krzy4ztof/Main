#include "HumanView.h"
#include "../debugging/Logger.h"

#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h

namespace base_game {
	HumanView::HumanView() {
		logger::info("Create HumanView");
		tempAngle = 0.0f;
	}

	HumanView::~HumanView() {
		logger::info("Destroy HumanView");
	}

	void HumanView::vOnAttach(unsigned int vid, unsigned int aid) {
		m_ViewId = vid;
		m_ActorId = aid;
	}

	void HumanView::vOnRestore() {
		logger::info("vOnRestore HumanView");
	}

	void HumanView::vOnRender(double fTime, float fElapsedTime) {
		//logger::info("vOnRender HumanView");
		tempOnRender(fTime, fElapsedTime);

	}


	void HumanView::tempOnRender(double fTime, float fElapsedTime) {

		//	stringstream ss;
		//float angle = 0.0f;

		// Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f); // Red

		// Reset transformations
		glLoadIdentity();
		// Set the camera
		gluLookAt(	0.0f, 0.0f, 10.0f,
					0.0f, 0.0f,  0.0f,
					0.0f, 1.0f,  0.0f);

		glRotatef(tempAngle, 0.0f, 1.0f, 0.0f);

		glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f,-2.0f, 0.0f);
		glVertex3f( 2.0f, 0.0f, 0.0);
		glVertex3f( 0.0f, 2.0f, 0.0);
		glEnd();

		//if (angle < 3.0f){
		tempAngle+=0.1f;
		//}
		glutSwapBuffers();

	}
}
