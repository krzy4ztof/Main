/*
 * FpsCounter.cpp
 *
 *  Created on: 6 sty 2020
 *      Author: Krzysztof
 */

#include "FpsCounter.h"
#include "../debugging/Logger.h"

#include <sstream>      // std::stringstream

using std::stringstream;

namespace base_game {

FpsCounter::FpsCounter() {
	logger::info("Create FpsCounter");

	//fps = -1;
	fps = 30; //fps = 1; //fps = 30; //fps = 60; // fps = -1;

	// fps = -1 -> 90%GPU
	// fps = 15, 30, 60 -> 60%GPU

	// fps = 1 -> 1% GPU
	screenRefershRate = 1 / fps; // 1sec / 1frame / 1 sec

	lastTime = 0;
	firstTime = 0;
	counter = 0;
	totalCounter = 0;
}

FpsCounter::~FpsCounter() {
	logger::info("Destroy FpsCounter");
}

double FpsCounter::getLastTime() {
	return lastTime;
}

void FpsCounter::setLastTime(double lastTime) {
	this->lastTime = lastTime;
}

void FpsCounter::setFirstTime(double firstTime) {
	this->firstTime = lastTime;
	this->lastTime = lastTime;
}


void FpsCounter::debugReport(double time, double elapsedTime,
		double screenRefreshRate) {
	stringstream ss;
	double totalTime = time - firstTime;

	ss << "GLUT RENDER SCENE: time:" << time << "; elapsedTime " << elapsedTime
			<< "; counter: " << counter << "; totalTime: " << totalTime
			<< "; totalCounter: " << totalCounter;

	logger::info (ss);
	// [   info] : GLUT RENDER SCENE: time:11.1505; elapsedTime 10.0065; counter: 1120
//
//			[   info] : GLUT RENDER SCENE: time:10.0008; elapsedTime 10.0008; counter: 5278; totalTime: 10.0008; totalCounter: 5278
//			[   info] : Current FPS: 527.8; totalFps: 527.757
//			[   info] : ----------------
//			[   info] : GLUT RENDER SCENE: time:20.0012; elapsedTime 10.0004; counter: 6852; totalTime: 20.0012; totalCounter: 12130
//			[   info] : Current FPS: 685.2; totalFps: 606.463
//			[   info] : ----------------
//			[   info] : GLUT RENDER SCENE: time:30.0013; elapsedTime 10.0001; counter: 6924; totalTime: 30.0013; totalCounter: 19054
//			[   info] : Current FPS: 692.4; totalFps: 635.105

	double currentFps = counter / screenRefreshRate;
	double totalFps = totalCounter / totalTime;

	ss << "Current FPS: " << currentFps << "; totalFps: " << totalFps;
	logger::info(ss);

	logger::info("----------------");
}

bool FpsCounter::renderNextFrame(double time) {
	stringstream ss;
	counter++;
	totalCounter++;

	double elapsedTime = time - lastTime;

	if (fps <= 0) {
		if (elapsedTime >= 10.0) { // screenRefershRate) {
			this->debugReport(time, elapsedTime, 10.0);

			counter = 0;
			lastTime = time;
		}
	}

	if (fps > 0) {
		if (elapsedTime >= screenRefershRate) {
			this->debugReport(time, elapsedTime, screenRefershRate);
			counter = 0;
			lastTime = time;
			return true;
		} else {
			return false;
		}
	}

	return true;

}


} /* namespace base_game */
