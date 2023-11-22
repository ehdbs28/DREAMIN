#include "pch.h"
#include "ResMgr.h"
#include "PathMgr.h"
#include "Texture.h"
Texture* ResMgr::TexLoad(const wstring& _strKey, const wstring& _strRelativePath)
{
    // 잘 찾았으면 그거 던져주기
    Texture* pTex = TexFind(_strKey);
    if (nullptr != pTex)
        return pTex;

    // 처음에는 없을거니까.. 경로 찾아서
    wstring strFilepath = PathMgr::GetInst()->GetResPath();
    strFilepath += _strRelativePath;
    // 만들어줘가지고..
    pTex = new Texture;
    pTex->Load(strFilepath); // 텍스처 자체를 로드..
    pTex->SetKey(_strKey); // 키 경로 세팅해두고..
    pTex->SetRelativePath(_strRelativePath);
    m_mapTex.insert({ _strKey,pTex }); // 그거를 맵에다가 저장.
    return pTex;
}

Texture* ResMgr::TexFind(const wstring& _strKey)
{
    // 찾아서 return
    auto iter = m_mapTex.find(_strKey);
    if (iter != m_mapTex.end())
    {
        return iter->second;
    }
    return nullptr;
}

void ResMgr::Release()
{
    // Texture
    map<wstring, Texture*>::iterator iter;
    for (iter = m_mapTex.begin(); iter != m_mapTex.end(); ++iter)
    {
        if (nullptr != iter->second)
            delete iter->second;
    }
    m_mapTex.clear();

    // SOUND
    map<wstring, tSoundInfo*>::iterator itersod;
    for (itersod = m_mapSod.begin(); itersod != m_mapSod.end(); ++itersod)
    {
        if (nullptr != itersod->second)
            delete itersod->second;
    }
    m_mapSod.clear();

    // 다 쓰고 난 후 시스템 닫고 반환
    m_pSystem->close();
    m_pSystem->release();
}

void ResMgr::Init()
{
    FMOD::System_Create(&m_pSystem); // 시스템 생성 함수
    // 채널수, 사운드 모드
    if (m_pSystem != nullptr)
        m_pSystem->init((int)SOUND_CHANNEL::END, FMOD_INIT_NORMAL, nullptr);
}

void ResMgr::LoadSound(const wstring& _strKey, const wstring& _strReleativePath, bool _IsLoop)
{
    if (FindSound(_strKey))
        return;
    wstring strFilePath = PathMgr::GetInst()->GetResPath();
    strFilePath += _strReleativePath;

    // wstring to string
    std::string str;
    str.assign(strFilePath.begin(), strFilePath.end());

    // 루프할지 말지 결정
    FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
    if (!_IsLoop)
        eMode = FMOD_DEFAULT; // 사운드 1번만 출력

    tSoundInfo* ptSound = new tSoundInfo;
    ptSound->IsLoop = _IsLoop;
    // 사운드 객체를 만드는 것은 system임.
                            //파일경로,  FMOD_MODE, NULL, &sound
    m_pSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
    m_mapSod.insert({ _strKey, ptSound });
}

void ResMgr::Play(const wstring& _strKey)
{
    tSoundInfo* ptSound = FindSound(_strKey);
    if (!ptSound)
        return;
    m_pSystem->update(); // play할때 update를 주기적으로 호출해야 사운드가 정지되지 않음.
    SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
    if (!ptSound->IsLoop)
        eChannel = SOUND_CHANNEL::EFFECT;
    // 사운드 재생 함수. &channel로 어떤 채널을 통해 재생되는지 포인터 넘김
    m_pSystem->playSound(ptSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);

}

void ResMgr::Stop(SOUND_CHANNEL _eChannel)
{
    m_pChannel[(UINT)_eChannel]->stop();
}

void ResMgr::Volume(SOUND_CHANNEL _eChannel, float _fVol)
{
    // 0.0 ~ 1.0 볼륨 조절
    m_pChannel[(UINT)_eChannel]->setVolume(_fVol);
}

void ResMgr::Pause(SOUND_CHANNEL _eChannel, bool _Ispause)
{
    // bool값이 true면 일시정지. 단, 이 함수를 쓰려면 Createsound할때 
    // FMOD_MODE가 FMOD_LOOP_NORMAL 이어야 함.
    m_pChannel[(UINT)_eChannel]->setPaused(_Ispause);
}

tSoundInfo* ResMgr::FindSound(const wstring& _strKey)
{
    map<wstring, tSoundInfo*>::iterator iter = m_mapSod.find(_strKey);

    if (iter == m_mapSod.end())
        return nullptr;
    return iter->second;
}
