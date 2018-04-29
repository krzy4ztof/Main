/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   AudioSystem.cpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 12:48
 */

#include "AudioSystem.h"
#include "ErrorCode.h"
#include "../debugging/Logger.h"

namespace base_game {

	AudioSystem::AudioSystem() {
		logger::trace("Create AudioSystem");

		// Initialization
		bool somethingWentWrong = false;

		if (somethingWentWrong) {
			throw ErrorCode("EC_AUDIOSYSTEM_PROBLEM", 789);
		}
	}

	AudioSystem::AudioSystem(const AudioSystem& orig) {
		logger::trace("Create AudioSystem");
	}

	AudioSystem::~AudioSystem() {
		logger::trace("Destroy AudioSystem");
	}
}
