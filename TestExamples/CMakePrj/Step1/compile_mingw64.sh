#!/bin/bash

cmake -G "MSYS Makefiles" -S . -B ./build_mingw64
cmake -G "MSYS Makefiles" --build ./build_mingw64


