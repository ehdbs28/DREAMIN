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
#include "Rigidbody.h"
#include "DamageCaster.h"
#include "Game_Scene.h"
#include "Particle.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "InGameScreen.h"
#include "UIManager.h"

Player::Player()
	: m_pTex(nullptr)
	, m_pModuleController(nullptr)
	, m_target(nullptr)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\PlayerMinsung.bmp");

	CreateCollider();
	GetCollider()->SetOffSetPos(Vec2(0.f, 15.f));
	GetCollider()->SetScale(Vec2(30.f,50.f));
	
	CreateAnimator();

#pragma region Add Animation Clip

	GetAnimator()->CreateAnim(L"Minsung_Idle_Right_Top", m_pTex,Vec2(0.f, 0.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Idle_Left_Top", m_pTex, Vec2(0.f, 16.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Walk_Right_Top", m_pTex, Vec2(0.f, 32.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 4, 0.1f);
	GetAnimator()->CreateAnim(L"Minsung_Walk_Left_Top", m_pTex, Vec2(0.f, 48.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 4, 0.1f);
	GetAnimator()->CreateAnim(L"Minsung_Dash_Right_Top", m_pTex, Vec2(0.f, 64.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Dash_Left_Top", m_pTex, Vec2(0.f, 80.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Jump_Right_Top", m_pTex, Vec2(0.f, 96.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 2, 0.1f);
	GetAnimator()->CreateAnim(L"Minsung_Jump_Left_Top", m_pTex, Vec2(0.f, 112.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 2, 0.1f);
	GetAnimator()->CreateAnim(L"Minsung_Shoot_Right_Top", m_pTex, Vec2(0.f, 128.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 2, 0.05f);
	GetAnimator()->CreateAnim(L"Minsung_Shoot_Left_Top", m_pTex, Vec2(0.f, 144.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 2, 0.05f);
	GetAnimator()->CreateAnim(L"Minsung_Idle_Right_Bottom", m_pTex, Vec2(0.f, 160.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Idle_Left_Bottom", m_pTex, Vec2(0.f, 176.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Walk_Right_Bottom", m_pTex, Vec2(0.f, 192.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 4, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Walk_Left_Bottom", m_pTex, Vec2(0.f, 208.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 4, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Dash_Right_Bottom", m_pTex, Vec2(0.f, 224.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Dash_Left_Bottom", m_pTex, Vec2(0.f, 240.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Minsung_Jump_Right_Bottom", m_pTex, Vec2(0.f, 256.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 2, 0.1f);
	GetAnimator()->CreateAnim(L"Minsung_Jump_Left_Bottom", m_pTex, Vec2(0.f, 272.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 2, 0.1f);
	GetAnimator()->CreateAnim(L"Minsung_Shoot_Right_Bottom", m_pTex, Vec2(0.f, 288.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 2, 0.05f);
	GetAnimator()->CreateAnim(L"Minsung_Shoot_Left_Bottom", m_pTex, Vec2(0.f, 304.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 2, 0.05f);

#pragma endregion

	//// 오프셋 건드리기
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// 하나만
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// 프레임 다 
	//for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->SetFrameOffset(i, Vec2(0.f, 20.f));

	CreateRigidbody();

	CreateDamageCaster();
	GetDamageCaster()->SetMaxHealth(1);

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
	if (KEY_PRESS(KEY_TYPE::D)) {
		GetDamageCaster()->OnDamage(10);
	}

	m_pModuleController->Update();
	GetAnimator()->Update();
}

void Player::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Player::EnterCollision(Collider* _other)
{
	if (_other->GetObj()->GetName() == (GetRigidbody()->GetGravityScale() == 1 ? L"UnderGround" : L"UpperGround")) {
		m_isGround = true;
	}
}

void Player::StayCollision(Collider* _other)
{
	if (_other->GetObj()->GetName() == L"Portal") {
		if (KEY_PRESS(KEY_TYPE::UP)) {
			std::dynamic_pointer_cast<Game_Scene>(SceneMgr::GetInst()->GetCurScene())->NextStage();
		}
	}
}

void Player::ExitCollision(Collider* _other)
{
	if (_other->GetObj()->GetName() == (GetRigidbody()->GetGravityScale() == 1 ? L"UnderGround" : L"UpperGround")) {
		m_isGround = false;
	}
}

void Player::SetAnimation(wstring _key, bool _repeat, bool _isRight, bool _gravityUnder)
{
	_key += (_isRight ? L"_Right" : L"_Left");
	_key += (_gravityUnder ? L"_Top" : L"_Bottom");
	GetAnimator()->PlayAnim(_key, _repeat);
}

void Player::OnDamage(float _damage)
{
	if (m_isInvincibility) {
		return;
	}
	GetDamageCaster()->OnDamage(_damage);
}

void Player::DeadHandle()
{
	Particle* particle = new Particle(PARTICLE_TYPE::PLAYER_DEAD, 0.06f, false);
	particle->SetPos(GetPos());
	particle->SetScale(Vec2(125, 125));
	SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);
	std::dynamic_pointer_cast<InGameScreen>(UIManager::GetInst()->GetTopPanel())->SetStatus(true);
	std::dynamic_pointer_cast<Game_Scene>(SceneMgr::GetInst()->GetCurScene())->SetFail();
}
