#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "ModuleController.h"
#include "PlayerMovementModule.h"

Player::Player()
	: m_pTex(nullptr)
	, m_pModuleController(nullptr)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\jiwoo.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));
	
	CreateAnimator();
	GetAnimator()->CreateAnim(L"Jiwoo_Front", m_pTex,Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Back", m_pTex, Vec2(0.f, 100.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Left", m_pTex, Vec2(0.f, 0.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Right", m_pTex, Vec2(0.f, 50.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Attack", m_pTex, Vec2(0.f, 200.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->PlayAnim(L"Jiwoo_Front",true);

	//// 오프셋 건드리기
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// 하나만
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// 프레임 다 
	//for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->SetFrameOffset(i, Vec2(0.f, 20.f));

	m_pModuleController = new ModuleController();
	m_pModuleController->SetOwner(this);
	m_pModuleController->AddModule(L"MOVEMENT_MODULE", new PlayerMovementModule(m_pModuleController));
}

Player::~Player()
{
	if (nullptr != m_pModuleController)
		delete m_pModuleController;
}

void Player::Update()
{
	m_pModuleController->Update();
	GetAnimator()->Update();
}

void Player::CreateBullet()
{
	Bullet* pBullet = new Bullet;
	Vec2 vBulletPos = GetPos();
	vBulletPos.y -= GetScale().y / 2.f;
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f,25.f));
//	pBullet->SetDir(M_PI / 4 * 7);
//	pBullet->SetDir(120* M_PI / 180);
	pBullet->SetDir(Vec2(-10.f,-15.f));
	pBullet->SetName(L"Player_Bullet");
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}

void Player::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Player::EnterCollision(Collider* _other)
{
	if (_other->GetObj()->GetName() == L"UNDER_GROUND") {
		((PlayerMovementModule*)m_pModuleController->GetModule(L"MOVEMENT_MODULE"))
			->SetGround(true);
	}
}

void Player::ExitCollision(Collider* _other)
{
	if (_other->GetObj()->GetName() == L"UNDER_GROUND") {
		((PlayerMovementModule*)m_pModuleController->GetModule(L"MOVEMENT_MODULE"))
			->SetGround(false);
	}
}
