#include "DxLib.h"
#include "Game.h"

// �Q�[�����[�v�𑱂��邩�H
bool ProgramLooping = true;

// �}�b�v�f�[�^
unsigned char map[][MAP_WIDTH] =
//    0  1  2  3  4  5  6  7  8  9 10 11 12 13
{ 
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // 0
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, }, // 1
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, }, // 2
	{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, }, // 3
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, }, // 4
	{ 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, }, // 5
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, }, // 6
	{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, }, // 7
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, }, // 8
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // 9
};

// �摜�n���h��
int imgMapChip[2];  // �w�i�}�b�v�`�b�v�摜
int imgPlayer;  // �v���[���[�摜

				  // �v���[���[�֘A�̃f�[�^
typedef struct Player
{
	float       x = 100.0f;           // �v���[���� x���W
	float       y = 140.0f;           // �v���[���� y���W
	float       vx = 0.0f;            // �v���[���� x�������x
	float       vy = 0.0f;            // �v���[���� y�������x         
	int         w = 40;               // �v���[���[�̓����蔻�蕝
	int         h = 56;               // �v���[���[�̓����蔻�荂��
	const float accel = 0.3f;         // �v���[���� �����������x
	const float brake_Ratio = 0.8f;   // �v���[���� �u���[�L�W��
}Player;

Player player;
const int MAX_OVERLAP_CAPACITY = 10;   // �Ǎő�߂荞�ݗ�

typedef struct tag_rect
{
	int x;
	int y;
	int w;
	int h;
}rect;

// ��`�q�b�g�`�F�b�N�֐�
bool checkHitRect(rect r1, rect r2)
{
	return ((r1.x < (r2.x + r2.w)) &&
		(r2.x < (r1.x + r1.w)) &&
		(r1.y < (r2.y + r2.h)) &&
		(r2.y < (r1.y + r1.h)));
}
///////////////
//�֐��錾
//////////////
//�}�b�v�`��p�֐�
void  DrawMap();
//�v���[���[�̈ړ�
void MovePlauer();
int		WINAPI		myWinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR     CmdLine, int CmdShow,
	int screen_x, int screen_y, bool FullScreen)
{
#ifdef WINDOW_MODE
	ChangeWindowMode(TRUE);
#endif 
	/////////////////////////////////////////////////////////
	// DXLIB�������֘A
	/////////////////////////////////////////////////////////
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, 60);
	DxLib_Init();   // DX���C�u��������������

	SetMouseDispFlag(true);
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�

	/////////////////////////////////////////////////////////
	// �Q�[�����̉摜�ǂݍ���
	/////////////////////////////////////////////////////////
	imgPlayer = LoadGraph("image/player.png");

	LoadDivGraph("image/mapchip.png", 2, 2, 1, MAP_CHIP_SIZE, MAP_CHIP_SIZE, imgMapChip);
	/////////////////////////////////////////////////////////
	// �Q�[�����[�v
	/////////////////////////////////////////////////////////
	while (ProgramLooping)
	{
		if (ProcessMessage() != 0) {
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}

		//�Q�[���֘A����
		INPUT_INSTANCE.update(); // ���̓L�[���ׂĒ��ׂ�
		//�v���[���[�̈ړ�
		MovePlauer();

		//�`��֘A
		ClearDrawScreen();

		//�}�b�v�`��
		DrawMap();

		//��ʃt���b�v
		ScreenFlip();
	}

	
	DxLib_End();
	return 0;
}






////////////////////////////////////////////////////////////////////////////////////////
// �R���\�[����ʂ���Windows�̂���@�ɔ�Ԃ��߂̃R�[�h
////////////////////////////////////////////////////////////////////////////////////////
void windowOpen(int screen_x, int screen_y, bool FullScreen)
{
	HINSTANCE	hInstance	= GetModuleHandle(0);
	int			iCmdShow	= SW_SHOWDEFAULT ;

	myWinMain( hInstance, NULL, NULL, iCmdShow, screen_x, screen_y, FullScreen);
}

// DOS�����̃G���g���[�|�C���g
int main(void)
{
	windowOpen( 1440, 900, false);

	return 0;
}

// �E�B���h�E�V�X�e���̎��̃G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	main();
	return 0;
}

//�}�b�v�`��p�֐�
void DrawMap()
{
	//�}�b�v�`��
	for (int iy = 0; iy < MAP_HEIGHT; iy++)
	{
		for (int ix = 0; ix < MAP_WIDTH; ix++)
		{
			/*int mapType = map[iy][ix];*/
			DrawGraph(ix *  MAP_CHIP_SIZE, iy *  MAP_CHIP_SIZE, imgMapChip[map[iy][ix]], FALSE);
		}
	}
	DrawGraph(player.x, player.y, imgPlayer, TRUE);
}
//�v���[���[�̈ړ�
void MovePlauer()
{
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT))
	{
		player.vx += player.accel;
		if (player.vx > MAX_OVERLAP_CAPACITY)
		{
			player.vx = MAX_OVERLAP_CAPACITY;
		}
	}

	if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT))
	{
		player.vx -= player.accel;
		if (player.vx < -MAX_OVERLAP_CAPACITY)
		{
			player.vx = -MAX_OVERLAP_CAPACITY;
		}
	}
	if (INPUT_INSTANCE.getInput(KEY_INPUT_DOWN))
	{
		player.vy += player.accel;
		if (player.vy > MAX_OVERLAP_CAPACITY)
		{
			player.vy = MAX_OVERLAP_CAPACITY;
		}
	}
	if (INPUT_INSTANCE.getInput(KEY_INPUT_UP))
	{
		player.vy -= player.accel;
		if (player.vy < -MAX_OVERLAP_CAPACITY)
		{
			player.vy = -MAX_OVERLAP_CAPACITY;
		}
	}

	if (!(INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT)) &&
		!(INPUT_INSTANCE.getInput(KEY_INPUT_LEFT)))
	{
		player.vx *= player.brake_Ratio;
	}
	if (!(INPUT_INSTANCE.getInput(KEY_INPUT_UP)) &&
		!(INPUT_INSTANCE.getInput(KEY_INPUT_DOWN)))
	{
		player.vy *= player.brake_Ratio;
	}

	player.x += player.vx;
	player.y += player.vy;

	//////////////////////////////
	//�v���C���[�ƕǂ̓����蔻��
	/////////////////////////////
	rect playerRect, blocrect;
	playerRect.x = (int)player.x;
	playerRect.y = (int)player.y;
	playerRect.w = player.w;
	playerRect.h = player.h;

	//�u���b�N��`
	blocrect.w = MAP_CHIP_SIZE;
	blocrect.h = MAP_CHIP_SIZE;

	//�v���C���[��������}�b�v�Y�����ԍ����Z�o
	//����
	int chkx = playerRect.x / MAP_CHIP_SIZE;
	int chky = playerRect.y / MAP_CHIP_SIZE;
	//�E��
	int maxchkx = (playerRect.x + playerRect.w) / MAP_CHIP_SIZE;
	int maxchky = (playerRect.y + playerRect.h) / MAP_CHIP_SIZE;
	//������\���̂��邷�ׂẴu���b�N�𒲂ׂ�
	for (int y = chky; y <= maxchky; y++)
	{
		for (int x = chkx; x <= maxchkx; x++)
		{
			//�����͒ʍs�s�\�ȃu���b�N��
			if (map[y][x] != 0)
			{
				//�Փ˃u���b�N�̍�����W���v�Z
				blocrect.x = x * MAP_CHIP_SIZE;
				blocrect.y = y * MAP_CHIP_SIZE;
				//�u���b�N�ƂԂ�������
				if (checkHitRect(playerRect, blocrect))
				{
					//���b�N�̉E�[�Ɠ������Ă�����
					if ((x + 1)*MAP_CHIP_SIZE - player.x < MAX_OVERLAP_CAPACITY&&
						player.vx < 0)
					{
						playerRect.x = (x + 1)*MAP_CHIP_SIZE;
						player.vx = 0;
					}
					if ((player.x + player.w) - x * MAP_CHIP_SIZE < MAX_OVERLAP_CAPACITY&&
						player.vx > 0)
					{
						playerRect.x = x * MAP_CHIP_SIZE - playerRect.w;
						player.vx = 0;
					}
					if ((y + 1)*MAP_CHIP_SIZE - player.y < MAX_OVERLAP_CAPACITY&&
						player.vy < 0)
					{
						playerRect.y = (y + 1)*MAP_CHIP_SIZE;
						player.vy = 0;
					}
					if ((player.y + player.h) - y * MAP_CHIP_SIZE < MAX_OVERLAP_CAPACITY&&
						player.vy > 0)
					{
						playerRect.y = y * MAP_CHIP_SIZE - playerRect.h;
						player.vy = 0;
					}
				}
			}

		}
	}
	player.x = playerRect.x;
	player.y = playerRect.y;
	printf("[ %4.3f,%4.3f ],\n", player.x, player.y);
}