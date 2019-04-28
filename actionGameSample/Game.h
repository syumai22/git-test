#pragma once
#include "DxLib.h"
#include "input.h"

#ifndef __GAME_H__
#define __GAME_H__

//↓コメントアウトにするとウィンドウのみモードに
#define DEBUG_CONSOLE_MODE

#ifdef DEBUG_CONSOLE_MODE
#pragma comment(linker, "/SUBSYSTEM:CONSOLE" )
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS" )
#endif

// ウィンドウ幅・高さ
#define WINDOW_WIDTH   800
#define WINDOW_HEIGHT  450

// マップの幅と高さ・チップサイズ
#define MAP_WIDTH       19
#define MAP_HEIGHT      100
#define MAP_CHIP_SIZE   32

//↓コメントアウトするとフルスクリーンモードに
//#define WINDOW_MODE

// マップ
extern unsigned char map[][MAP_WIDTH];

void callQuit( char *nextappPath, char* nextexename );

#endif __GAME_H_