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

#include "SystemCalls.hpp"

using namespace std;

namespace watermill {

    GameCodeApp::GameCodeApp() {
        //    *dataFiles = NULL;
        //   *audioSystem = NULL;
        //  *videoSystem = NULL;
    }

    GameCodeApp::GameCodeApp(const GameCodeApp& orig) {
    }

    GameCodeApp::~GameCodeApp() {
    }

    bool GameCodeApp::initInstance() {
        bool returnCode = true;
        SystemCalls systemCalls;

#ifndef _DEBUG
        if (!systemCalls.isOnlyInstance(GAME_PROCESS_NAME)) {

            //if (!systemCalls.IsOnlyInstance(GAME_TITLE)) {
            cout << "There is another process running" << endl;
            return false;
        }
#endif

        // Check for adequate machine resources.
        bool resourceCheck = false;
        while (!resourceCheck) {
            const DWORDLONG physicalRAM = 512 * MEGABYTE;
            const DWORDLONG virtualRAM = 1024 * MEGABYTE;
            const DWORDLONG diskSpace = 10 * MEGABYTE;
            if (!systemCalls.checkHardDisk(diskSpace))
                return false;

            /*
            const DWORD minCpuSpeed = 1300; // 1.3Ghz
            DWORD thisCPU = systemCalls.readCPUSpeed();
            if (thisCPU < minCpuSpeed) {
                cout << "GetCPUSpeed reports CPU is too slow for this game." << endl;
                return false;
            }
             */

            resourceCheck = true;
        }



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


}

