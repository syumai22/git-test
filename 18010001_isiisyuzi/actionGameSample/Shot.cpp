#include"Header.h"

void Shot::InitShot()
{
	
	int shotGraph = graph;
	if (shotGraph < 0)
	{
		LoadDivGraph("image/shotani.png", 8, 8, 1, 32, 32, img_Shot);
	}
	graph = shotGraph;
	shotFlag = false;
	x = 0;
	y = 0;
	int shotW, shotH;
	GetGraphSize(shotGraph, &shotW, &shotH);
	w = shotW;
	h = shotH;
	shotAnimNum=0;
	
}
void Shot::DrawShot(Rule *rule,Map *scr)
{
	if (INPUT_INSTANCE.getInput(KEY_INPUT_S) == 1)
	{
		shotFlag = true;
	}
	if (shotFlag)
	{
		if (rule->frameCount % 8 == 0)
		{
			shotAnimNum++;
		}
		if (shotAnimNum == shotAnimNum_End)
		{
			 shotAnimNum=shotAnimNum_Start;
		}
	/*	DrawRotaGraph(x +  - scr->X, y - scr->Y + 15, 1.0f, 0, img_Shot[shotAnimNum], TRUE,dir);*/
	}
}