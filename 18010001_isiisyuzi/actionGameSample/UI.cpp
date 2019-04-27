#include"Header.h"
#pragma warning (disable:4996)

#define WD 400
// UI������.
void UI::InitUI()
{
	titleBak = LoadGraph("image/start.png");
	hpber = LoadGraph("image/hpber.png");
	gameOverBak= LoadGraph("image/loose.png");
	title = LoadGraph("image/title.png");
	sky= LoadGraph("image/sky.bmp");
	hp_x=50;
	hp_y=10;
	R = 0 ;
	G = 0;
	B=0;
	colorCount=0;;
}

void UI::DrawUI(Rule *rule, Player *player,Map *scr,BitmapText text)
{
	// �c�胉�C�t�����镶����.
	char buf[128];
	char sco[128];
	// HP�\�����n�߂�X���W.
	int sc = LIMIT_TIME_COUNT + ((rule->gameStartTime - GetNowCount()) / 1000);
	
	sprintf(buf, "TIME:%d", LIMIT_TIME_COUNT + ((rule->gameStartTime - GetNowCount()) / 1000));
	sprintf(sco, "SCORE:%d", player->hp *100);
	
	//Please press the space key
	text.setFontImage(16, 6, "font.bmp");
	text.reMapText(" !\"#$%&`[]*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\tabcdefghijklmnopqrstuvwxyz{|}~\\");
	// ���[�����Ƃɕ\������ς���.
	switch (rule->state)
	{
		// �^�C�g��.
	case STATE_TITLE:
		
		SetFontSize(TITLE_FONT_SIZE);
		DrawExtendGraph(0-1, 0, WINDOW_WIDTH-1, WINDOW_HEIGHT, titleBak, TRUE);
		// ��ʃT�C�Y/2 ����@�`�悷�镶����̕�2/�A�܂��ʂ̒����ɕ�����\�����Ă���.
		/*DrawString(WINDOW_WIDTH / 2 - GetDrawStringWidthFull(TITLE_STR) / 2, WINDOW_HEIGHT / 2 + TITLE_STR_OFFSET_Y, TITLE_STR, GetColor(255, 255, 255));*/
		/*text.textDraw(WINDOW_WIDTH / 3+30, WINDOW_HEIGHT / 2 + TITLE_STR_OFFSET_Y, "Ninja Tower");*/
		DrawGraph(WINDOW_WIDTH/6  ,WINDOW_HEIGHT / 2 + TITLE_STR_OFFSET_Y+1, title,TRUE);
		text.setFontColor(R, G, B);
		
		R+=2;
		
		text.textDraw(WINDOW_WIDTH / 4, WINDOW_HEIGHT - 100, "Please press space key");
		
		break;
		// �Q�[����.
	case STATE_GAME:

		
		// ��������.
		if(GetNowCount() - rule->gameStartTime>=45*1000)
		{	text.setFontColor(255, 0, 0);
			text.textDraw(WINDOW_WIDTH / 2 + TIME_STR_OFFSET_X, TIME_STR_POS_Y, buf);
		}
		else
		{ 
			text.setFontColor(0,255,0);
			text.textDraw(WINDOW_WIDTH / 2 + TIME_STR_OFFSET_X, TIME_STR_POS_Y, buf);
		}
		// GetNowCount��1000���̂P�b�Ȃ̂ł�������v�Z����.

		// �v���C���[�̗�.
		if(player->hp>=20)
		{
			DrawBox(10, 0, 0 + WD, 20, GetColor(0, 255, 255), FALSE);//���[�^�[�̘g��`��
			DrawBox(10, 0, 0 + WD * player->hp / player->hp_max, 20, GetColor(0, 255, 255), TRUE);//���[�^�[�̒��g��`��
		}
		else
		{
			DrawBox(10, 0, 0 + WD, 20, GetColor(255, 0, 0), FALSE);//���[�^�[�̘g��`��
			DrawBox(10, 0, 0 + WD * player->hp / player->hp_max, 20, GetColor(255, 0, 0), TRUE);//���[�^�[�̒��g��`��
		}
		break;

		// �N���A���.
	case STATE_CLEAR:
	
		text.setFontColor(0, 255, 255);
		text.textDraw(WINDOW_WIDTH / 2-100, WINDOW_HEIGHT / 2 + TITLE_STR_OFFSET_Y, "GAMECLEAR");
	
		text.setFontColor(R, 100, B);
		text.textDraw(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT  + TITLE_STR_OFFSET_Y-100, sco);
		text.setFontColor(0, G, 50);
		G++;
		text.textDraw(WINDOW_WIDTH / 4, WINDOW_HEIGHT + TITLE_STR_OFFSET_Y, "Space key to title");
		R++;
		
		break;
		// �Q�[���I�[�o�[.
	case STATE_GAMEOVER:

		text.setFontColorShadow(128, 0, 255);
		text.setFontShadowOffset(3, 3);
		text.textDrawWithShadow(WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2 + TITLE_STR_OFFSET_Y, "GAMEOVER");
		text.textDraw(WINDOW_WIDTH / 4+10, WINDOW_HEIGHT - 100, "Space key to title");
		break;
	default:
		break;
	}
}