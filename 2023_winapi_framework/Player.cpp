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
#include "PlayerAttackModule.h"
#include "PlayerDashModule.h"
#include "PlayerIdleModule.h"
#include "PlayerJumpModule.h"
#include "PlayerFallModule.h"
#include "Boss.h"

Player::Player()
	: m_pTex(nullptr)
	, m_pModuleController(nullptr)
	, m_gravityDir(1)
	, m_target(nullptr)
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

	CreateRigidbody();

	m_pModuleController = new ModuleController();
	m_pModuleController->SetOwner(this);
	
	m_pModuleController->AddModule(L"IdleModule", new PlayerIdleModule(m_pModuleController));
	m_pModuleController->AddModule(L"MovementModule", new PlayerMovementModule(m_pModuleController));
	m_pModuleController->AddModule(L"JumpModule", new PlayerJumpModule(m_pModuleController));
	m_pModuleController->AddModule(L"FallModule", new PlayerFallModule(m_pModuleController));
	m_pModuleController->AddModule(L"AttackModule", new PlayerAttackModule(m_pModuleController));
	m_pModuleController->AddModule(L"DashModule", new PlayerDashModule(m_pModuleController));
	
	m_pModuleController->ChangeModule(L"IdleModule");
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

void Player::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Player::EnterCollision(Collider* _other)
{
	if (_other->GetObj()->GetName() == (m_gravityDir == 1 ? L"UnderGround" : L"UpperGround")) {
		m_isGround = true;
	}
}

void Player::ExitCollision(Collider* _other)
{
	if (_other->GetObj()->GetName() == (m_gravityDir == 1 ? L"UnderGround" : L"UpperGround")) {
		m_isGround = false;
	}
}

void Player::ChangeGravity()
{
	m_gravityDir *= -1;
}
