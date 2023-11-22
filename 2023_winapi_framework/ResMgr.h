#pragma once
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc")
enum class SOUND_CHANNEL
{
	BGM, EFFECT, END
};
struct tSoundInfo
{
	FMOD::Sound* pSound; // 실제 사운드 메모리
	bool IsLoop;
};
class Texture;
class ResMgr
{
	SINGLE(ResMgr);
public:
	Texture* TexLoad(const wstring& _strKey,
		const wstring& _strRelativePath);
	Texture* TexFind(const wstring& _strKey);
	void Release();
private:
	map<wstring, Texture*> m_mapTex;
	FMOD::System* m_pSystem; // 사운드 시스템
	map<wstring, tSoundInfo*> m_mapSod;
	FMOD::Channel* m_pChannel[(UINT)SOUND_CHANNEL::END]; // 오디오 채널
public:
	void Init();
	void LoadSound(const wstring& _strKey, const wstring& _strReleativePath, bool _IsLoop);
	void Play(const wstring& _strKey);
	void Stop(SOUND_CHANNEL _eChannel);
	void Volume(SOUND_CHANNEL _eChannel, float _fVol);
	void Pause(SOUND_CHANNEL _eChannel, bool _Ispause);
private:
	tSoundInfo* FindSound(const wstring& _strKey);
};

