/****************************************
GameEngine.h
Author: Root
Date: 2019/12/09
Description:
定义了程序游戏模块的头文件，用GameEngine命名空间防止同名污染
各函数说明：
void InitGame()	   初始化游戏
void Play()		   开始游戏
void DestroyGame() 结束游戏
void RenderIntro() 绘制游戏说明
*****************************************/
#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Graphic.h"
#include "Controller.h"
#include <time.h>
#include <conio.h>
namespace GameEngine {
	void InitGame();
	void Play();
	void DestroyGame();
	void RenderIntro();
}
#endif // GAMEENGINE_H