#pragma once
#include "DxLib.h"
#include "input.h"

#ifndef __GAME_H__
#define __GAME_H__

//���R�����g�A�E�g�ɂ���ƃE�B���h�E�̂݃��[�h��
#define DEBUG_CONSOLE_MODE

#ifdef DEBUG_CONSOLE_MODE
#pragma comment(linker, "/SUBSYSTEM:CONSOLE" )
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS" )
#endif

// �E�B���h�E���E����
#define WINDOW_WIDTH   800
#define WINDOW_HEIGHT  450

// �}�b�v�̕��ƍ����E�`�b�v�T�C�Y
#define MAP_WIDTH       19
#define MAP_HEIGHT      100
#define MAP_CHIP_SIZE   32

//���R�����g�A�E�g����ƃt���X�N���[�����[�h��
//#define WINDOW_MODE

// �}�b�v
extern unsigned char map[][MAP_WIDTH];

void callQuit( char *nextappPath, char* nextexename );

#endif __GAME_H_