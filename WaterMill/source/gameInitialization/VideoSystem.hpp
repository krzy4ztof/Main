/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   VideoSystem.hpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 12:49
 */

#ifndef VIDEOSYSTEM_HPP
#define VIDEOSYSTEM_HPP

#include <string> // string

namespace watermill {

	class VideoSystem {
		public:
			VideoSystem();
			VideoSystem(const VideoSystem& orig);
			virtual ~VideoSystem();
/* */
			void startFreeGlut(std::string title);
			void startFreeGlutMainLoop();
		/*	void display_xxx(); */
		private:


	};


	namespace video_system {
		void safe_delete(VideoSystem* p);
		void displayFreeGlut();
	}
}
#endif /* VIDEOSYSTEM_HPP */

