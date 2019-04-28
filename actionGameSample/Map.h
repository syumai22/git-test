#pragma once
class Player;
class Rule;
class Map
{
public:

	int		X = 0;
	int		Y = 0;
	int		score;
	int		imgMapChip[75];		// �w�i�}�b�v�`�b�v�摜
	int CheckEliminatBlock()
	{
		int k;
		int ClsFlag; // ��ł��������u���b�N�����������A�̃t���O

		do {
			// �ꎞ�g�p�p�u���b�N�f�[�^��������
			InitBufferBlock();

			// �������u���b�N�����邩�A�t���O��|��
			ClsFlag = FALSE;

			// �e�u���b�N�������邩���ׂ�
			for (int i = 0; i < MAP_HEIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					// �����u���b�N���Ȃ��ꍇ�͎��Ɉڂ�
					if (map[j][i] == 0) continue;

					// �u���b�N�������邩�ǂ������ׂĒ������ʂ��o�b�t�@�ɕۑ�����
					BufferBlock[j][i] = CheckEliminatBlockToOne(j, i);
				}
			}

			// ������Ɣ��f���ꂽ�u���b�N������
			for (int i = 0; i < MAP_HEIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (BufferBlock[j][i] == 1)
					{
						ClsFlag = TRUE;
						map[j][i] = 0;
					}
				}
			}

			// �󂫂�ς߂�
			for (int i = MAP_HEIGHT - 2; i > -1; i--)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (map[j][i] != 0)
					{
						for ( k = i + 1; k < MAP_HEIGHT && map[j][k] == 0; k++) {}
						k--;

						if (k != i)
						{
							map[j][k] = map[j][i];
							map[j][i] = 0;
						}
					}
				}
			}

		} while (ClsFlag);	// �������u���b�N���������ꍇ�ēx�`�F�b�N

							// �I��
		return 0;
	}
	// �A�N�e�B�u�u���b�N����ʏ�̃u���b�N�ɓ������Ă��Ȃ������ׂ�
	int CheckHitActiveBlock(int x, int y)
	{

		// �R����u���b�N�����ꂼ���ʏ�̃u���b�N�ɓ������Ă��Ȃ������ׂ�
		for (int i = 0; y - i >= 0 && i < 3; i++)
		{
			// �������Ă����炱���ŏI��
			if (map[x][y - i] != 0)
			{
				return -1;
			}
		}

		// �������Ă��Ȃ��ꍇ�����O��Ԃ�
		return 0;
	}
	// �A�N�e�B�u�u���b�N���Œ肷��
	// �y�ю��̃u���b�N���o��
	// �������̃u���b�N���o���X�y�[�X���Ȃ�������Q�[���I�[�o�[
	int LockActiveBlock(int x, int y)
	{

		for (int i = 0; i < 3; i++)
		{
			// ��ʏォ��O��Ă���ꍇ�̓Z�b�g���Ȃ�
			if (y - i < 0) continue;

			// �u���b�N�̌Œ�
			map[x][y - i] = ActiveBlock[i];
		}

		// ������u���b�N������ꍇ�͏���
		CheckEliminatBlock();

		// �V�����u���b�N���Z�b�g
		{
			// �A�N�e�B�u�u���b�N�̈ʒu���Z�b�g
			ActiveX = MAP_WIDTH / 2;
			ActiveY = 2;

			// �V�����A�N�e�B�u�u���b�N�𐶐�
			CreateNewActiveBlock();

		}
	}
	int		MoveActiveBlock(int MoveX, int MoveY)	// �A�N�e�B�u�u���b�N�̈ړ�
	{
		int NewX, NewY;

		// �ړ���̍��W���Z�b�g����
		NewX = MoveX + ActiveX;
		NewY = MoveY + ActiveY;

		// ���E�ړ��̏���
		if (MoveX != 0 && NewX >= 0 && NewX <  MAP_WIDTH)
		{
			// �e�R�̃u���b�N����ʏ�̃u���b�N�ɓ������Ă��Ȃ������ׂ�
			if (CheckHitActiveBlock(NewX, NewY) == -1)
			{
				// �������Ă����獶�E�ړ��𖳌��ɂ���
				MoveX = 0;
			}
		}

	
		// �㉺�ړ��̏���
		if (MoveY != 0)
		{
			// ��ʂ̈�ԉ��̃u���b�N�ʒu�܂ŗ��Ă�����u���b�N���Œ肳����
			if (NewY >= MAP_HEIGHT)
			{
				LockActiveBlock(ActiveX, ActiveY);

				// �ړ��𖳌��ɂ���
				MoveY = 0;
			}
			else
				// �e�R�̃u���b�N����ʏ�̃u���b�N�ɓ������Ă��Ȃ������ׂ�
				if (CheckHitActiveBlock(NewX, NewY) == -1)
				{
					// �������Ă�����u���b�N���Œ肷��
					LockActiveBlock(ActiveX, ActiveY);

					// �ړ��𖳌��ɂ���
					MoveY = 0;
				}
		}

		// ���W���ړ�����
		ActiveX += MoveX;
		ActiveY += MoveY;

	}
	int CheckEliminatBlockToOne(int x, int y)
	{
		int CheckBlock;
		int i;
		int BlockNum;

		// �`�F�b�N����u���b�N�̎�ނ�ۑ�
		CheckBlock = map[x][y];


		// ���E�ɂǂꂾ���Ȃ����Ă��邩���ׂ�
		for (i = 0; x + i >= 0 && map[x + i][y] == CheckBlock; i--) {}
		i++;
		for (BlockNum = 0; x + i < MAP_WIDTH && map[x + i][y] == CheckBlock; BlockNum++, i++) {}

		// �R�ȏ�Ȃ����Ă����炱���ŏI��
		if (BlockNum >= 3) return 1;


		// �㉺�ɂǂꂾ���Ȃ����Ă��邩���ׂ�
		for (i = 0; y + i >= 0 && map[x][y + i] == CheckBlock; i--) {}
		i++;
		for (BlockNum = 0; y + i < MAP_HEIGHT && map[x][y + i] == CheckBlock; BlockNum++, i++) {}

		// �R�ȏ�Ȃ����Ă����炱���ŏI��
		if (BlockNum >= 3) return 1;


		// ���ォ��E���ɂ����Čq�����Ă��鐔�𒲂ׂ�
		for (i = 0; y + i >= 0 && x + i >= 0 && map[x + i][y + i] == CheckBlock; i--) {}
		i++;
		for (BlockNum = 0; x + i < MAP_WIDTH && y + i < MAP_HEIGHT && map[x + i][y + i] == CheckBlock; BlockNum++, i++) {}

		// �R�ȏ�Ȃ����Ă����炱���ŏI��
		if (BlockNum >= 3) return 1;


		// �E�ォ�獶���ɂ����Čq�����Ă��鐔�𒲂ׂ�
		for (i = 0; y + i >= 0 && x - i < MAP_WIDTH && map[x - i][y + i] == CheckBlock; i--) {}
		i++;
		for (BlockNum = 0; x - i >= 0 && y + i < MAP_HEIGHT && map[x - i][y + i] == CheckBlock; BlockNum++, i++) {}

		// �R�ȏ�Ȃ����Ă����炱���ŏI��
		if (BlockNum >= 3) return 1;


		// �����܂ŗ��Ă���������Ȃ�
		return 0;
	}
	int		WaitCounter;	// ���ɏ���ɗ��Ƃ��܂ł̎��Ԍv���p
	int		NowTime;	// ���݂̃t���[���Ōo�߂�������
	int		OldTime;	// �O�̃t���[���̂Ƃ���GetNowCount�֐��œ����^�C��

	int		ActiveX, ActiveY;	// �A�N�e�B�u�u���b�N�̈�ԉ��̃u���b�N�̈ʒu
	int		ActiveVY = MAP_CHIP_SIZE + 1000;
	char	BufferBlock[MAP_WIDTH][MAP_HEIGHT];
	char	ActiveBlock[3];
	void	scroll(Player *player);
	void	InitMap();
	void	DrawMap(Rule *rule);
	void	CreateNewActiveBlock();		// �V�����u���b�N�̐���
	void	InitBufferBlock();
	bool	rightMove;
};

typedef struct tag_rect
{
	int x;
	int y;
	int w;
	int h;
}rect;