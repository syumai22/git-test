#include"Header.h"

const float Player::Accel				= 0.3f;					// プレーヤの 横方向加速度 
const float Player::Brake_Ratio			= 0.2f;
const float Player::JumpPower			= 8.0f;
const float Player::Jumpbrake_Ratio		= 0.3f;
const float Player::Gravity				= 0.3f;
const float	Player::epsiron				= 0.4f;

bool p_checkHitRect(rect r1, rect r2)
{
		return ((r1.x < (r2.x + r2.w)) &&
				(r2.x < (r1.x + r1.w)) &&
				(r1.y < (r2.y + r2.h)) &&
				(r2.y < (r1.y + r1.h)));
}

void Player::InitPlayer()
{
	LoadDivGraph("image/player.png", 16, 16, 1, 32, 32, imgPlayer);
	LoadDivGraph("image/player2.png", 5, 5, 1, 32, 32, imgp_Atk);
	LoadDivGraph("image/kiru.png", 3, 3, 1, 32, 32,	imgp_zan);
	LoadDivGraph("image/efe_fire.png", 8, 8, 1, 32, 32, img_efe_fire);
	LoadDivGraph("image/recovery2.png", 6, 6, 1, 128, 126,img_recovery);
	LoadDivGraph("image/uke.png", 5, 5, 1, 120, 120, img_damege);

	capsule = LoadGraph("image/capser.bmp");
	x= 80.0f;
	y = 3110.0f;
	vx = 0.0f;
	vy = 0.0f;
	hp = PLAYER_LIFE;
	atk=1;
	hpba=0;
	hp_max=50;
	p_xOffset = 13.0f;
	damagecont = 1.5f;
	animNum = anim_Walk_Start;
	atkAnimNum = 0;
	atkEfekt = 0;
	EfektAnimNum = 0;
	fireEfektAnimNum=0;
	damageEfektAnimNum=0;
	ani =false;
	atkFlag = false;
	atkDamage=false;
    rightbrokflag=false;
    leftbrokflag=false;
	for (int i = 0; i < 9; i++)
	{
		iltemsGetto[i] = true;
	}
	damageFlag= false;
	damageEfctFlag = false;
	fireEfektFlag = false;
	efektFlag = false;
	damageFlag = false;
	ef = false;
	dir = FALSE;
}

//アニメーション
void Player::PlayerAnime(Map *scr,Rule *rule,BitmapText text,Sound *sound)
{
	
	if (ani == true)
	{
	
		//移動アニメ―ション
		if (rule->frameCount % walkingMotionCount == 0)
		{
			animNum++;
		}
	
		if (animNum >=anim_Walk_End)
		{
			animNum = anim_Walk_Start;
		}
		else if (!(INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT)) &&
			!(INPUT_INSTANCE.getInput(KEY_INPUT_LEFT)))
		{
			animNum = anim_Wait_Start;
		}
		//ジャンプアニメーション
		if (!p_onGround)
		{
			animNum = jnpAni;
		}
	}
	else
	{
		ani = false;
	}
	//プレーヤの攻撃アニメーション
	if (atkFlag == true)
	{
		vx = 0;

		if (rule->frameCount % atkMotionCount == 0)
		{
			atkAnimNum++;
		}
		if (rule->frameCount % atkEfektMotionCount == 0)
		{
			atkEfekt++;
		}
		if (atkEfekt == atkEfekt_End)
		{
			atkEfekt = atkEfekt_Start;
		}
		if (atkAnimNum == atkAnimNum_End)
		{
			atkAnimNum = atkAnimNum_Start;
			atkFlag = false;
		}
		if (dir == TRUE)
		{
			DrawRotaGraph(x + rightAtkModification - scr->X, y - scr->Y + Modification, 1.0f, 0, imgp_zan[atkEfekt], TRUE, dir);
		}
		else
		{
			DrawRotaGraph(x - leftArkModification - scr->X, y - scr->Y + Modification, 1.0f, 0, imgp_zan[atkEfekt], TRUE, dir);
		}
	}
	else
	{
		atkFlag = false;
	}
	
	//プレイヤー攻撃画像への画像切り替え
	if (atkFlag == true)
	{
		DrawRotaGraph(x + p_xOffset - scr->X, y - scr->Y + Modification, 1.0f, 0, imgp_Atk[atkAnimNum], TRUE, dir);
	}
	if(!atkFlag )
	{
		if(!damageEfctFlag )
		{
			DrawRotaGraph(x + p_xOffset - scr->X, y - scr->Y + Modification, 1.0f, 0, imgPlayer[animNum], TRUE, dir);
		}
		if (damageEfctFlag== true|| fireEfektFlag == true)
		{
			
			if (rule->frameCount % 10 == 0)
			{
				text.setFontColor(255, 0, 0);
				DrawRotaGraph(x + p_xOffset - scr->X, y - scr->Y + Modification, 1.0f, 0, imgPlayer[animNum], TRUE, dir);
				text.setFontColor(255, 255, 255);
			}
		}
        else if (efektFlag == true)
        {
            if (rule->frameCount % 10 == 0)
            {
                text.setFontColor(255, 255, 0);
                DrawRotaGraph(x + p_xOffset - scr->X, y - scr->Y + Modification, 1.0f, 0, imgPlayer[animNum], TRUE, dir);
                text.setFontColor(255, 255, 255);
            }
        }
	}
	//ダメージエフェクト
	if (rule->frameCount % 5 == 0)
	{
		damageEfektAnimNum++;
	}
	
	if (damageEfctFlag == true)
	{
		DrawGraph(x - scr->X - efektModification_x, y - scr->Y - efektModification_y, img_damege[damageEfektAnimNum], TRUE);
	}
	if (damageEfektAnimNum == damageEfektAnim_End)
	{
		damageEfektAnimNum = damageEfektAnim_Start;
	}
	//回復エフェクト
	if (rule->frameCount % 8 == 0)
	{
		EfektAnimNum++;
		
	}
	if (EfektAnimNum == recoveryEfektAnim_End)
	{
		EfektAnimNum = recoveryEfektAnim_Start;
	}
	if (efektFlag == true)
	{
		
		DrawGraph(x - scr->X - efektModification_x, y - scr->Y - efektModification_x, img_recovery[EfektAnimNum], TRUE);
	}
	//ファイアエフェクト
	if (rule->frameCount % 8 == 0)
	{
		fireEfektAnimNum++;
	}
	if (fireEfektAnimNum == fireEfektAnim_End)
	{
		fireEfektAnimNum = fireEfektAnim_start;
	}
	if (fireEfektFlag == true)
	{	
		DrawGraph(x - scr->X, y - scr->Y + 5, img_efe_fire[fireEfektAnimNum], TRUE);
	}
	
	if(iltemsGetto[0])
	{
		DrawGraph(150 - scr->X, 2010 - scr->Y, capsule,TRUE);
	}
	if (iltemsGetto[1])
	{
		DrawGraph(100 - scr->X, 1600 - scr->Y, capsule, TRUE);
	}
	if (iltemsGetto[2])
	{
		DrawGraph(200 - scr->X, 1200 - scr->Y, capsule, TRUE);
	}
	if (iltemsGetto[3])
	{
		DrawGraph(50 - scr->X, 800 - scr->Y, capsule, TRUE);
	}
	if (iltemsGetto[4])
	{
		DrawGraph(50 - scr->X, 500 - scr->Y, capsule, TRUE);
	}
	if (iltemsGetto[5])
	{
		DrawGraph(400 - scr->X, 1000 - scr->Y, capsule, TRUE);
	}
	if (iltemsGetto[6])
	{
		DrawGraph(450 - scr->X, 3000 - scr->Y, capsule, TRUE);
	}
	if (iltemsGetto[7])
	{
		DrawGraph(450 - scr->X, 1900 - scr->Y, capsule, TRUE);
	}
    if (iltemsGetto[8])
    {
        DrawGraph(450 - scr->X, 1500 - scr->Y, capsule, TRUE);
    }
}


////////////////////////////////////////////////////////
// プレーヤー移動処理
////////////////////////////////////////////////////////
//プレーヤーの移動
void Player::MovePlayer(Sound *sound)
{
  
    //右移動処理
    if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT))
    {
        //向き
        dir = TRUE;
        if (!ef)
        {
            ani = true;
        }
      
        if (vx <= 2.0f)
        {
            vx += Accel;
        }
        
        if (vx > MAX_OVERLAP_CAPACITY)
        {
            vx = MAX_OVERLAP_CAPACITY;
        }
    }
   
  
        //左移動処理
        if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT))
        {
            dir = FALSE;
            if (!ef)
            {
                ani = true;
            }
          
                if (vx >= -2.0f)
                {
                    vx -= Accel;
                }
            
            if (vx < -MAX_OVERLAP_CAPACITY)
            {
                vx = -MAX_OVERLAP_CAPACITY;
            }
        }
    
	//攻撃
	//if (INPUT_INSTANCE.getInput(KEY_INPUT_Z) == 1)
	//{
	//	PlaySoundMem(sound->p_atk, DX_PLAYTYPE_BACK); // 攻撃効果音を再生する
	//	zan = true;
	//	atkFlag = true;
	//	atkDamage = true;
	//	damageFlag =true;
	//	if (vx < 0.0f && vx > -epsiron)
	//	{
	//		vx = 0.0f;
	//	}
	//	
	//}
	//else
	//{
	//	fraicount = 100;
	//}
	
	//ブレーキ
	if (!(INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT)) &&
		!(INPUT_INSTANCE.getInput(KEY_INPUT_LEFT)))
	{
		vx *= Brake_Ratio;
	}

	//ずれ防止
	/*if (vx < 0.0f && vx > -epsiron)
	{
		vx = 0.0f;
	}*/
	/*if (vy< 0.0f && vy > -epsiron)
	{
		vy = 0.0f;
	}*/

	// ジャンプボタン押した
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN
		&& p_onGround)
	{
		ani = true;
		vy = -JumpPower;
		p_onGround = false;
		PlaySoundMem(sound->jump, DX_PLAYTYPE_BACK); // ジャンプ効果音を再生する
	}
	
	//空中にいるとき
	if (!p_onGround)
	{
		ani = true;
		// y方向に重力加速度分加速させる
		vy += Gravity;
		// 落下最高速度以上いかないようにする
		if (vy >=10.0f)
		{
			vy =10.0f;
		}
	}
	if (!p_onGround)
	{
		if (INPUT_INSTANCE.getInput(KEY_INPUT_C))
		{
			vy += 1.0f;
		}
	}
	
	//暫定プレーヤー位置算出
	next_x = x + vx;
	next_y = y + vy;
}

void Player::PlayerBlocrect(Sound *sound,Rule *rule,Map *scr)
{
	rect playerRect, blocrect;
	//////////////////////////////
	//プレイヤーと壁の当たり判定
	/////////////////////////////

	//プレーヤーの暫定一の短形
	playerRect.x = next_x;
	playerRect.y = next_y;
	playerRect.w = w;
	playerRect.h = h;

	//ブロック矩形
	blocrect.w = MAP_CHIP_SIZE;
	blocrect.h = MAP_CHIP_SIZE;
	
	
	//プレイヤーが属するマップ添え字番号を算出
	//左下
	int chkx = playerRect.x / MAP_CHIP_SIZE;
	int chky = playerRect.y / MAP_CHIP_SIZE;
	//右下
	int maxchkx = (playerRect.x + playerRect.w) / MAP_CHIP_SIZE;
	int maxchky = (playerRect.y + playerRect.h) / MAP_CHIP_SIZE;
	
   
	if ((chkx >= 0 && chky > 0) || (chkx <= MAP_WIDTH && chky <= MAP_HEIGHT))
	{
		//当たる可能性のあるすべてのブロックを調べる
		for (int x = chkx; x <= maxchkx; x++)
		{
			for (int y = chky; y <= maxchky; y++)
			{
				//そこは通行不可能なブロックか
				if (map[y][x] != 3&&map[y][x] != 73)
				{
					//衝突ブロックの左上座標を計算
					blocrect.x = x * MAP_CHIP_SIZE;
					blocrect.y = y * MAP_CHIP_SIZE;
					//ブロックとぶつかったか
					if (p_checkHitRect(playerRect, blocrect))
					{
						if ((playerRect.y + playerRect.h) - blocrect.y<=  MAX_OVERLAP_CAPACITY
							&& vy > 0.0f)
						{
							
							playerRect.y = blocrect.y - playerRect.h;
							vy = 0;
							
							if (map[y][x] == 68)
							{

								vy -= 10.0f;
								if (vy <= -10.0f)
								{
									vy = -10.0f;
								}
								PlaySoundMem(sound->powerJump, DX_PLAYTYPE_BACK);
							}
						}
					
						// ブロックの下端とぶつかった
						if ((blocrect.y + blocrect.h) - playerRect.y <= MAX_OVERLAP_CAPACITY
							&& vy < 0.0f)
						{
							playerRect.y = blocrect.y + blocrect.h ;
							vy = 0.0f;
						}

						// ブロックの左端とぶつかった
						if ((playerRect.x + playerRect.w) - blocrect.x< MAX_OVERLAP_CAPACITY &&
							vx > 0.0f)
						{
                          
							playerRect.x = blocrect.x - playerRect.w;
							vx = 0.0f;
						}
                       
						// ブロックの右端とぶつかった
						if ((blocrect.x + blocrect.w) - playerRect.x< MAX_OVERLAP_CAPACITY &&
							vx < 0.0f)
						{
                            
							playerRect.x = blocrect.x + blocrect.w;
							vx = 0.0f;
						}
                     
		
					
					}
					
				}
			
				
				if (map[y][x] == 10)
				{
					fireEfektFlag = true;
					
					if(rule->frameCount%10==0)
					{ 
						
						hp -= 1;
					}
					if (rule->frameCount % 60 == 0)
					{
						PlaySoundMem(sound->flame, DX_PLAYTYPE_BACK);
					}
				}
				else
				{
					fireEfektFlag = false;
				}
				if (map[y][x] == 9)
				{
					vx+=0.6f;
					if (vx <= 4.0f)
					{
						vx = 4.0f;
					}
				}
				if (map[y][x] == 19)
				{
					vx-=0.6f;
					if (vx <= -4.0f)
					{
						vx = -4.0f;
					}
				}

				if (map[y][x] == 24)
				{
					
					if (hp < hp_max)
					{
						efektFlag = true;
						if (rule->frameCount % 10 == 0)
						{	
							
							hp+=1;
						}
						if (rule->frameCount % 60 == 0)
						{
							PlaySoundMem(sound->cure, DX_PLAYTYPE_BACK);
						}
					}
				}
				else
				{
					efektFlag = false;
				}
			}
		}
		
		
	}
	

	// プレーヤーの1dot下に地面ブロックがあるかの確認
	// プレーヤー左下点のマップ番号算出
	chky = (playerRect.y + playerRect.h) / MAP_CHIP_SIZE;
	chkx = (playerRect.x + 1 ) / MAP_CHIP_SIZE;

	p_onGround = true;
	// 左下点は空中か？
	if (map[chky][chkx] == 3)
	{
		//右下点も空中か？
		chkx = (playerRect.x + playerRect.w - 1) / MAP_CHIP_SIZE;
		if (map[chky][chkx] == 3)
		{
			//両足とも空中にいる
			p_onGround = false;
		}
	}
	// プレーヤ位置確定
	x = (float)playerRect.x;
	y = (float)playerRect.y;

	
}
void Player::IitemHit(Map *scr,Enemy *enemy,Sound *sound)
{
	rect PlayerHitChecRect, Iitemhitchecrect[9];
	PlayerHitChecRect.x = x - scr->X;
	PlayerHitChecRect.y = y - scr->Y;
	PlayerHitChecRect.w = w;
	PlayerHitChecRect.h = h;

	Iitemhitchecrect[0].x = 150-scr->X;
	Iitemhitchecrect[0].y = 2010-scr->Y;
	Iitemhitchecrect[0].w = 32;
	Iitemhitchecrect[0].h = 32;

	Iitemhitchecrect[1].x = 100 - scr->X;
	Iitemhitchecrect[1].y = 1600 - scr->Y;
	Iitemhitchecrect[1].w = 32;
	Iitemhitchecrect[1].h = 32;

	Iitemhitchecrect[2].x = 200 - scr->X;
	Iitemhitchecrect[2].y = 1200 - scr->Y;
	Iitemhitchecrect[2].w = 32;
	Iitemhitchecrect[2].h = 32;

	Iitemhitchecrect[3].x = 50 - scr->X;
	Iitemhitchecrect[3].y = 800 - scr->Y;
	Iitemhitchecrect[3].w = 32;
	Iitemhitchecrect[3].h = 32;

	Iitemhitchecrect[4].x = 50 - scr->X;
	Iitemhitchecrect[4].y = 500 - scr->Y;
	Iitemhitchecrect[4].w = 32;
	Iitemhitchecrect[4].h = 32;

	Iitemhitchecrect[5].x = 400 - scr->X;
	Iitemhitchecrect[5].y = 1000 - scr->Y;
	Iitemhitchecrect[5].w = 32;
	Iitemhitchecrect[5].h = 32;

	Iitemhitchecrect[6].x = 450 - scr->X;
	Iitemhitchecrect[6].y = 3000 - scr->Y;
	Iitemhitchecrect[6].w = 32;
	Iitemhitchecrect[6].h = 32;

	Iitemhitchecrect[7].x = 450 - scr->X;
	Iitemhitchecrect[7].y = 1900 - scr->Y;
	Iitemhitchecrect[7].w = 32;
	Iitemhitchecrect[7].h = 32;

    Iitemhitchecrect[8].x = 450 - scr->X;
    Iitemhitchecrect[8].y = 1500 - scr->Y;
    Iitemhitchecrect[8].w = 32;
    Iitemhitchecrect[8].h = 32;

	for(int i=0;i<9;i++)
	{ 
		if (iltemsGetto[i] == true)
		{
			if (p_checkHitRect(PlayerHitChecRect, Iitemhitchecrect[i]))
			{
				hpba+=5;
				hp_max += 5;
				PlaySoundMem(sound->IltemuGet, DX_PLAYTYPE_BACK);
				iltemsGetto[i] = false;
			}
		}
	
	}
}

void Player::PlayerHitChec(Enemy *enemy,Map scr,Sound *sound)
{
	
	rect PlayerHitChecRect, EnemyHitChecRect;
	PlayerHitChecRect.x = x-scr.X;
	PlayerHitChecRect.y = y-scr.Y;
	PlayerHitChecRect.w = w;
	PlayerHitChecRect.h = h; 

	EnemyHitChecRect.x = enemy->x - scr.X;
	EnemyHitChecRect.y = enemy->y - scr.Y;
	EnemyHitChecRect.w = enemy->w;
	EnemyHitChecRect.h = enemy->h;

	if (ef)
	{
		if (p_checkHitRect(PlayerHitChecRect, EnemyHitChecRect))
		{
			//敵の上端
			if ((PlayerHitChecRect.y + PlayerHitChecRect.h) - EnemyHitChecRect.y + 2 <= MAX_OVERLAP_CAPACITY
				&& vy > 0.0f)
			{
				PlayerHitChecRect.y = EnemyHitChecRect.y - PlayerHitChecRect.h;
				vy -= 4.0f;
				if (dir = true)
				{
					enemy->vx+=4.0f;
				}
				else
				{
					enemy->vx -= 4.0f;
				}
			}
			// 敵の下端
			if ((EnemyHitChecRect.y + EnemyHitChecRect.h) - PlayerHitChecRect.y <= MAX_OVERLAP_CAPACITY
			&& vy < 0.0f)
			{
				PlayerHitChecRect.y = EnemyHitChecRect.y + EnemyHitChecRect.h + 5;
				vy = 0.0f;
			}

			//敵の左端 
			if ((PlayerHitChecRect.x + PlayerHitChecRect.w) - EnemyHitChecRect.x < 15 &&
				vx > 0.0f)
			{
				PlayerHitChecRect.x = EnemyHitChecRect.x - PlayerHitChecRect.w;
				vx = 0.0f;
				damagecont = 0;
				ani = false;
				if (enemy->dir)
				{
					vx+=4.0f;
				}
				else
				{
					vx -= 4.0f;
				}
				PlaySoundMem(sound->e_atk, DX_PLAYTYPE_BACK);
				hp -= enemy->Atke;//ヒットポイント減算				
				ef = false;//当たり無効
				damageEfctFlag=true;
			}
			
			//敵の右端 
			if ((EnemyHitChecRect.x + EnemyHitChecRect.w) - PlayerHitChecRect.x < 24 &&
			vx < 0)
			{
				PlayerHitChecRect.x = EnemyHitChecRect.x + EnemyHitChecRect.w;
				vx = 0.0f;
				damagecont = 0;
				ani = false;
				if (enemy->dir)
				{
					vx += 4.0f;
				}
				else
				{
					vx -= 4.0f;
				}
				PlaySoundMem(sound->e_atk, DX_PLAYTYPE_BACK);
				hp -= enemy->Atke;//ヒットポイント減算
				ef = false;//当たり無効
				damageEfctFlag = true;
			}
		}
	}
	if (!ef)
	{
		if (damagecont == 150)
		{
			ef = true;//当たり有効
		;
		}
		if (damagecont == 10)
		{
			damageEfctFlag = false;
		}
		
	}
	
	/*printfDx("leftPos:%  leftHbaPos:%d\n", leftPos, leftHbaPos);*/
}