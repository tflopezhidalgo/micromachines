cmake_minimum_required(VERSION 3.9)
project(Plugins)

add_library(DecreaseSpeedIfDamaged SHARED DecreaseSpeedIfDamaged.cpp ../Plugin.cpp)