/*
 * T004figuresView.h
 *
 *  Created on: 7 lut 2019
 *      Author: Krzysztof
 */

#ifndef BASIC_TEMPT004FIGURESVIEW_H_
#define BASIC_TEMPT004FIGURESVIEW_H_

//#include "../main/IOpenGLView.h"
#include "HumanView.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

namespace base_game {
// see: Temp06View.h

//class TempT004figuresView: public IOpenGLView {
class TempT004figuresView: public HumanView {
public:
	TempT004figuresView();
	virtual ~TempT004figuresView();

	virtual void vInit();
	//virtual void vRender(double fTime, float fElapsedTime);
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vTerminate();
	virtual void vActivate();
	virtual void vDeactivate();

protected:
	// GLuint vertex_array_object;
	GLuint programID;

	GLuint positionBuffer;
	GLuint colorBuffer;
};

namespace temp_t004_figures_view {
TempT004figuresView* getView(bool reset);
}

} /* namespace base_game */

#endif /* BASIC_TEMPT004FIGURESVIEW_H_ */
