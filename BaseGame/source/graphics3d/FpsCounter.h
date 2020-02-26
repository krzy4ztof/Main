/*
 * FpsCounter.h
 *
 *  Created on: 6 sty 2020
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_FPSCOUNTER_H_
#define GRAPHICS3D_FPSCOUNTER_H_

namespace base_game {

class FpsCounter {
public:
	FpsCounter();
	virtual ~FpsCounter();

	bool renderNextFrame(double time);

	double getLastTime();

	void setLastTime(double lastTime);
	void setFirstTime(double firstTime);
	void debugReport(double time, double elapsedTime, double screenRefreshRate);

private:
	double screenRefershRate;
	double lastTime;
	double firstTime;
	int counter;
	int totalCounter;
	int fps;
};

} /* namespace base_game */

#endif /* GRAPHICS3D_FPSCOUNTER_H_ */
