#include"Header.h"
#pragma warning (disable:4996)

#define WD 400
// UI初期化.
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
	// 残りライフを入れる文字列.
	char buf[128];
	char sco[128];
	// HP表示を始めるX座標.
	int sc = LIMIT_TIME_COUNT + ((rule->gameStartTime - GetNowCount()) / 1000);
	
	sprintf(buf, "TIME:%d", LIMIT_TIME_COUNT + ((rule->gameStartTime - GetNowCount()) / 1000));
	sprintf(sco, "SCORE:%d", player->hp *100);
	
	//Please press the space key
	text.setFontImage(16, 6, "font.bmp");
	text.reMapText(" !\"#$%&`[]*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\tabcdefghijklmnopqrstuvwxyz{|}~\\");
	// ルールごとに表示物を変える.
	switch (rule->state)
	{
		// タイトル.
	case STATE_TITLE:
		
		SetFontSize(TITLE_FONT_SIZE);
		DrawExtendGraph(0-1, 0, WINDOW_WIDTH-1, WINDOW_HEIGHT, titleBak, TRUE);
		// 画面サイズ/2 から　描画する文字列の幅2/、つまり画面の中央に文字を表示している.
		/*DrawString(WINDOW_WIDTH / 2 - GetDrawStringWidthFull(TITLE_STR) / 2, WINDOW_HEIGHT / 2 + TITLE_STR_OFFSET_Y, TITLE_STR, GetColor(255, 255, 255));*/
		/*text.textDraw(WINDOW_WIDTH / 3+30, WINDOW_HEIGHT / 2 + TITLE_STR_OFFSET_Y, "Ninja Tower");*/
		DrawGraph(WINDOW_WIDTH/6  ,WINDOW_HEIGHT / 2 + TITLE_STR_OFFSET_Y+1, title,TRUE);
		text.setFontColor(R, G, B);
		
		R+=2;
		
		text.textDraw(WINDOW_WIDTH / 4, WINDOW_HEIGHT - 100, "Please press space key");
		
		break;
		// ゲーム中.
	case STATE_GAME:

		
		// 制限時間.
		if(GetNowCount() - rule->gameStartTime>=45*1000)
		{	text.setFontColor(255, 0, 0);
			text.textDraw(WINDOW_WIDTH / 2 + TIME_STR_OFFSET_X, TIME_STR_POS_Y, buf);
		}
		else
		{ 
			text.setFontColor(0,255,0);
			text.textDraw(WINDOW_WIDTH / 2 + TIME_STR_OFFSET_X, TIME_STR_POS_Y, buf);
		}
		// GetNowCountは1000分の１秒なのでそこから計算する.

		// プレイヤー体力.
		if(player->hp>=20)
		{
			DrawBox(10, 0, 0 + WD, 20, GetColor(0, 255, 255), FALSE);//メーターの枠を描画
			DrawBox(10, 0, 0 + WD * player->hp / player->hp_max, 20, GetColor(0, 255, 255), TRUE);//メーターの中身を描画
		}
		else
		{
			DrawBox(10, 0, 0 + WD, 20, GetColor(255, 0, 0), FALSE);//メーターの枠を描画
			DrawBox(10, 0, 0 + WD * player->hp / player->hp_max, 20, GetColor(255, 0, 0), TRUE);//メーターの中身を描画
		}
		break;

		// クリア画面.
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
		// ゲームオーバー.
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