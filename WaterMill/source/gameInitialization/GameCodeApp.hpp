/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GameCodeApp.hpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 20:15
 */

#ifndef GAMECODEAPP_HPP
#define GAMECODEAPP_HPP

#include "DataFiles.hpp"
#include "AudioSystem.hpp"
#include "VideoSystem.hpp"

namespace watermill {

    class GameCodeApp {
    public:
        GameCodeApp();
        GameCodeApp(const GameCodeApp& orig);
        virtual ~GameCodeApp();
        bool initInstance();
    private:
        DataFiles *dataFiles;
        AudioSystem *audioSystem;
        VideoSystem *videoSystem;
        static const int MEGABYTE = 1024 * 1024;

    };
}
#endif /* GAMECODEAPP_HPP */

