/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   VideoSystem.h
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 12:49
 */

#ifndef VIDEOSYSTEM_H
#define VIDEOSYSTEM_H

#include <string> // string

namespace base_game {

class VideoSystem {
public:
	VideoSystem();
	VideoSystem(const VideoSystem& orig);
	virtual ~VideoSystem();
	/* */
	//void startFreeGlut(std::string title);
	//void startFreeGlutMainLoop();
	/*	void display_xxx(); */
private:

};

namespace video_system {
//float angle; // = 0.0f;
// void renderScene();

/*
 void changeSize(int w, int h);

 void displayFreeGlut();
 void onChangeSize(int width, int height);
 void onClose();
 void onHideShow(int state);
 void onIdle();
 void onTimer(int value);

 */
}

}
#endif /* VIDEOSYSTEM_H */

