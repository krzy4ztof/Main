/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GameCodeApp.cpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 20:15
 */

#include "GameCodeApp.hpp"
#include<iostream>
// cout

#include "Macros.hpp"
#include "DataFiles.hpp"
#include "AudioSystem.hpp"
#include "VideoSystem.hpp"
#include "ErrorCode.hpp"

GameCodeApp::GameCodeApp() {
    //    *dataFiles = NULL;
    //   *audioSystem = NULL;
    //  *videoSystem = NULL;
}

GameCodeApp::GameCodeApp(const GameCodeApp& orig) {
}

GameCodeApp::~GameCodeApp() {
}

bool GameCodeApp::InitInstance() {
    bool returnCode = true;

    try {
        dataFiles = new DataFiles;
        audioSystem = new AudioSystem;
        videoSystem = new VideoSystem;


        bool done = true;

        std::cout << "Main loop" << std::endl;
        while (!done) {
            // Main loop
        }

    } catch (ErrorCode& error) {
        error.informUser();

        returnCode = false;
    }
    SAFE_DELETE(videoSystem);
    SAFE_DELETE(audioSystem);
    SAFE_DELETE(dataFiles);

    return (returnCode);
}