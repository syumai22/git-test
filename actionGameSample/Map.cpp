#include"Header.h"

void Map::InitMap()
{
	LoadDivGraph("image/Block1.png", 75, 5, 15, MAP_CHIP_SIZE, MAP_CHIP_SIZE, imgMapChip);
	// �A�N�e�B�u�u���b�N�𐶐�
	CreateNewActiveBlock();
	ActiveX = MAP_WIDTH / 2;
	ActiveY = 2000;
	rightMove=false;
	
}
//�}�b�v�`��p�֐�
void Map::DrawMap(Rule *rule)
{
	//�}�b�v�`��
	for (int iy = 0; iy < MAP_HEIGHT; iy++)
	{
		for (int ix = 0; ix < MAP_WIDTH; ix++)
		{
			DrawGraph(ix *  MAP_CHIP_SIZE - X, iy *  MAP_CHIP_SIZE - Y, imgMapChip[map[iy][ix]], FALSE);
		}
	}
	//if (ActiveVY > 950 )
	//{
	//	//ActiveVY =1000;
	//	rightMove = false;
	//}
	//else if (ActiveVY < 700)
	//{
	///*	ActiveVY = 500;*/
	//	rightMove = true;
	//}
	//if(rightMove==true)
	//{
	//	if (rule->frameCount % 2 == 0)
	//	{
	//		ActiveVY+=2;
	//	}
	//}
	//else
	//{ 
	//	if (rule->frameCount % 2 == 0)
	//	{
	//		ActiveVY-=2;
	//	}
	//}
	//for (int ix = 0; ix < 3; ix++)
	//{
	//	DrawGraph(ix *  MAP_CHIP_SIZE - X + 32, ActiveVY - Y, imgMapChip[ActiveBlock[ix]], FALSE);
	//	
	//}
	

	
}
//��ʃX�N���[��
void Map::scroll(Player *player)
{
	/*if (player->x >= X + 740)
	{*/
		X += (player->x - (X + WINDOW_WIDTH/2));

		if (X < MAP_CHIP_SIZE * MAP_WIDTH - WINDOW_WIDTH+200)
		{
			X = MAP_CHIP_SIZE * MAP_WIDTH - WINDOW_WIDTH+200;
		}
		if (X > MAP_CHIP_SIZE * MAP_WIDTH - WINDOW_HEIGHT-260)
		{
			X = MAP_CHIP_SIZE * MAP_WIDTH - WINDOW_HEIGHT-260;
		}
	/*}*/
	/*if (player->x <= X + 740)
	{
		X += (player->x - (X + 740));
	}*/
	/*if (player->y >= Y + 450)*/
	/*{*/
		Y += (player->y - (Y + WINDOW_HEIGHT/2));


		if (Y > MAP_CHIP_SIZE * MAP_HEIGHT - WINDOW_HEIGHT)
		{
			Y = MAP_CHIP_SIZE * MAP_HEIGHT - WINDOW_HEIGHT;

		}
	/*}*/

	/*if (player->y <= Y + 450)
	{*/	
	/*Y += (player->y - (Y + 450));*/
	
}
void Map::CreateNewActiveBlock()
{
	// �����_���ɂR�u���b�N���Z�b�g
	for (int i = 0; i < 3; i++)
	{
		ActiveBlock[i] = 7;
	}
}
void Map::InitBufferBlock()
{

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			BufferBlock[j][i] = 0;
		}
	}
}
