/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   VideoSystem.cpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 12:49
 */

#include "VideoSystem.hpp"
#include "ErrorCode.hpp"

namespace watermill {

    VideoSystem::VideoSystem() {
        // Initialization
        bool somethingWentWrong = false;

        if (somethingWentWrong) {
            throw ErrorCode("EC_VIDEOSYSTEM_PROBLEM", 789);
        }
    }

    VideoSystem::VideoSystem(const VideoSystem& orig) {
    }

    VideoSystem::~VideoSystem() {
    }
}
