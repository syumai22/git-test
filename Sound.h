#pragma once

class Player;
class Rule;
class Sound
{
public:
	int		win;
	int		title;
	int		p_atk;
	int		e_atk;
	int		jump;
	int		battle;
	int		title_s;
	int		loos;
	int		decide;
	int		idou;
	int		soundCount;
	int		powerJump;
	int		flame;
	int		cure;
	int		Decision;
	
	void InitSound();
	void ringSound(Rule *rule,int sou);
	void TitleSound(Rule *rule);
	void GameSound(Rule *rule);
	void GameoverSound(Rule *rule);
};