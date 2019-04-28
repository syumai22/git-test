#include"Header.h"
Input::Input()
{
	nowKey  = 0;
	prevKey = 1;

	for( int i = 0; i < 256; i++ )
	{
		key[i] = 0;
		keyState[nowKey][i]  = KEY_STATE_OFF;
		keyState[prevKey][i] = KEY_STATE_OFF;
	}
}

void Input::update()
{
	// ���݂̃L�[�ƈ�O�̃t���[���̃L�[��Ԃ����ւ���
	nowKey  ^= 1;
	prevKey  = nowKey ^ 1;

	// �L�[��Ԏ擾
	GetHitKeyStateAll( keyState[nowKey] );

	//
	for( int i = 0; i < 256; i++ )
	{
		char nowInput  = keyState[nowKey][i];
		char prevInput = keyState[prevKey][i];

		if( nowInput )
		{
			//���݉�����Ă���

			//�O�̃t���[����������Ă����H
			if( prevInput )
			{
				key[i] = KEY_STATE_PRESSED; // ��������ςȂ�
			} else {
				key[i] = KEY_STATE_PUSHDOWN;// �������ꂽ
			}

		}
		else
		{
			// ���݃L�[�͉�����Ă��Ȃ�
			
			// �O�̃t���[���ŉ�����Ă����H
			if( prevInput )
			{
				key[i] = KEY_STATE_PULLUP;
			} else {
				key[i] = KEY_STATE_OFF;
			}
		}
	}

#ifdef DEBUG_CONSOLE
	//printf("[%d]\n",key[KEY_INPUT_Z] );
#endif

}