#include "pch.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Scene.h"
#include "Collider.h"
void CollisionMgr::Update()
{
	for (UINT Row = 0; Row < (UINT)OBJECT_GROUP::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)OBJECT_GROUP::END; ++Col)
		{
			if (m_arrCheck[Row] & (1 << Col))
			{
				CollisionGroupUpdate((OBJECT_GROUP)Row, (OBJECT_GROUP)Col);
			}
		}
	}
}
void CollisionMgr::CollisionGroupUpdate(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	std::shared_ptr<Scene> pCurScene = SceneMgr::GetInst()->GetCurScene();
	const vector<Object*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<Object*>& vecRight = pCurScene->GetGroupObject(_eRight);
	
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->GetCollider() == nullptr ||
				vecLeft[i] == vecRight[j])
				continue;
			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();
			COLLIDER_ID colID;
			colID.left_ID = pLeftCol->GetID();
			colID.right_ID = pRightCol->GetID();

			auto iter = m_mapColInfo.find(colID.ID);
			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert({ colID.ID, false });
				iter = m_mapColInfo.find(colID.ID);
			}
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 이전에도 충돌 중
				if (iter->second)
				{
					// 둘중 하나 삭제 예정이라면
					if(vecLeft[i]->GetIsDead() || vecRight[j]->GetIsDead())
					{
						pLeftCol->ExitCollision(pRightCol);
						pRightCol->ExitCollision(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->StayCollision(pRightCol);
						pRightCol->StayCollision(pLeftCol);
					}
				}
				// 이전에 충돌x
				else
				{
					//if()
					pLeftCol->EnterCollision(pRightCol);
					pRightCol->EnterCollision(pLeftCol);
					iter->second = true;
				}
			}
			// 안하네?
			else
			{
				if (iter->second)
				{
					pLeftCol->ExitCollision(pRightCol);
					pRightCol->ExitCollision(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionMgr::IsCollision(Collider* _pLeft, Collider* _pRight)
{
	Vec2 vLeftPos = _pLeft->GetFinalPos();
	if (_pLeft->GetObj()->GetName() == L"Laser") {
		vLeftPos = Vec2(_pLeft->GetObj()->GetPos().x - _pLeft->GetObj()->GetScale().x / 2 + 15,
			_pLeft->GetObj()->GetPos().y);
	}
	Vec2 vRightPos = _pRight->GetFinalPos();
	if (_pRight->GetObj()->GetName() == L"Laser") {
		vRightPos = Vec2(_pRight->GetObj()->GetPos().x - _pRight->GetObj()->GetScale().x / 2 + 15,
			_pRight->GetObj()->GetPos().y);
	}

	Vec2 vDist = vRightPos - vLeftPos;

	Vec2 vLeftHeight = _pLeft->GetHeightVector();
	Vec2 vLeftWidth = _pLeft->GetWidthVector();
	Vec2 vRightHeight = _pRight->GetHeightVector();
	Vec2 vRightWidth = _pRight->GetWidthVector();

	Vec2 vectors[4] = {
		vLeftHeight,
		vLeftWidth,
		vRightHeight,
		vRightWidth
	};

	for (int i = 0; i < 4; i++) {
		double sum = 0.;
		Vec2 normalVector = vectors[i].Normalized();

		for (int j = 0; j < 4; j++) {
			sum += abs(Vec2::Dot(vectors[j], normalVector));
		}

		float distanceVecltor = abs(Vec2::Dot(vDist, normalVector));
		if (distanceVecltor > sum) {
			return false;
		}
	}

	return true;
}

void CollisionMgr::CheckGroup(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	// 작은쪽을 행으로 씁시다.
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	Row = min(Row, Col);

	//// 비트 연산
	// 체크가 되어있다면
	if (m_arrCheck[Row] & (1 << Col))
	{
		m_arrCheck[Row] &= ~(1 << Col);
	}
	// 체크가 안되어있다면r
	else
	{
		m_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionMgr::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)(OBJECT_GROUP::END));
}

