#pragma once

// ====== �C���N���[�h�� ======
#include <Windows.h>
#include <System/Macro.h>
#include <System/Singleton.h>

// ====== �N���X�錾 ======
class TimeManager : public Singleton<TimeManager>
{
public:	// �����o�֐�
	// �f�X�g���N�^
	~TimeManager() { Finalize(); }
	// ������
	void Init();
	// �X�V
	void Update();
	// �I������
	void Finalize();

public:	// �Q�b�^�[�E�Z�b�^�[
	// �o�ߎ��Ԏ擾
	float GetDeltaTime() const { return m_deltaTime; }
	// �o�ߎ��Ԏ擾(�b)
	float GetDeltaTimeSecond() const { return m_deltaTime * 0.001f; }
	// �t���[�����Ԏ擾
	float GetFrameTime() const { return m_frameTime; }
	// �t���[�����擾
	int GetFrameCount() const { return m_frameCount; }
	// FPS�擾
	float GetFPS() const { return m_fps; }

	void UpdateLastTime() { m_lastTime = m_currentTime; }

private:
	DWORD m_startTime;		// �J�n����
	DWORD m_currentTime;	// ���ݎ���
	DWORD m_lastTime;		// �O�񎞊�
	float m_deltaTime;		// �O��t���[������̌o�ߎ���
	float m_frameTime;		// �t���[������
	int m_frameCount;		// �t���[����
	float m_fps;			// FPS

private:	// �V���O���g���֘A
	// �R���X�g���N�^
	friend Singleton<TimeManager>;
	TimeManager() : m_startTime(0), m_currentTime(0), m_deltaTime(0), m_lastTime(0), m_frameTime(0), m_frameCount(0), m_fps(0) {}
};

// �V���O���g���C���X�^���X
#define TIME_MANAGER TimeManager::GetInstance()