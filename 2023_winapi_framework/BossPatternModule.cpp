#include "pch.h"
#include "pch.h"
#include "BossPatternModule.h"
#include "BossPattern.h"
#include "ModuleController.h"

BossPatternModule::BossPatternModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_currentPattern(nullptr)
	, m_patternIndex(0)
{
}

BossPatternModule::~BossPatternModule()
{
	for (int i = 0; i < m_vecPattern.size(); i++) {
		delete m_vecPattern[i];
	}
	m_vecPattern.clear();
}

void BossPatternModule::EnterModule()
{
	BaseModule::EnterModule();
}

void BossPatternModule::UpdateModule()
{
	if (m_currentPattern == nullptr) {
		SelectPattern();
	}
	else {
		m_currentPattern->ExcutePattern();
		if (!m_currentPattern->IsExcute()) {
			SelectPattern();
		}
	}
}

void BossPatternModule::ExitModule()
{
	BaseModule::ExitModule();
}

void BossPatternModule::AddPattern(BossPattern* _newPattern)
{
	m_vecPattern.push_back(_newPattern);
}

void BossPatternModule::SelectPattern()
{
	if (m_patternIndex >= m_vecPattern.size()) {
		ShufflePatternOrder();
	}
	m_currentPattern = m_vecPattern[m_vecOrder[m_patternIndex++]];
}

void BossPatternModule::ShufflePatternOrder()
{
	m_vecOrder.resize(m_vecPattern.size(), 0);
	for (int i = 0; i < m_vecOrder.size(); i++) {
		m_vecOrder[i] = i;
	}

	int sour, dest, temp;
	for (int i = 0; i < 100; i++) {
		sour = rand() % m_vecPattern.size();
		dest = rand() % m_vecPattern.size();

		temp = m_vecOrder[sour];
		m_vecOrder[sour] = m_vecOrder[dest];
		m_vecOrder[dest] = temp;
	}

	m_patternIndex = 0;
}
