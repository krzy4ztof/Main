/*
 * OpenGLRenderer.cpp
 *
 *  Created on: 17 sty 2020
 *      Author: Krzysztof
 */

#include "OpenGLRenderer.h"
#include "../debugging/Logger.h"

#include <sstream>      // std::stringstream

using std::stringstream;
using std::shared_ptr;

namespace base_game {

OpenGLRenderer::OpenGLRenderer(shared_ptr<VideoSystemGLFW> videoSystemGLFW) {
	logger::info("Create OpenGLRenderer");
	this->videoSystemGLFW = videoSystemGLFW;
}

OpenGLRenderer::~OpenGLRenderer() {
	logger::info("Destroy OpenGLRenderer");
}

bool OpenGLRenderer::vPreRender() {
	// Start scene
	return videoSystemGLFW->preRender();
}

bool OpenGLRenderer::vPostRender() {
	// End scene
	return videoSystemGLFW->postRender();
}


} /* namespace base_game */
