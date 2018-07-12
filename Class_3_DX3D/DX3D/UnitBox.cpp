#include "stdafx.h"
#include "UnitBox.h"
#include "Mob.h"
#include "Ray.h"
#include "TeamAI.h"

HANDLE hUnitLoadingThread = NULL;
UINT iUnitLoadingPercentage = 0;
int mobCreateBuffer = 0;

DWORD __stdcall UnitLoadingThread(LPVOID classPointer) {
	UnitBox* uBox = (UnitBox*)classPointer;
	while (true) {
		/*if (mobCreateBuffer > 0) {
		Mob* tempMob = new Mob;
		tempMob->Init();
		tempMob->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + (rand() % 40), 2.67f, GSM().mobPos.z + (rand() % 350)));
		//m_pMob2.push_back(tempMob);
		//uBox->m_pMob.push_back(tempMob);
		if (tempMob->m_Act._moving == ��_�����̵� || tempMob->m_Act._reload == ��_������ || tempMob->m_Act._engage == ��_���󹰿�����)
		{
		uBox->FindHidingInTheWallLocation(tempMob);
		}
		uBox->m_pMob.push_back(tempMob);
		mobCreateBuffer--;
		}*/
		if (mobCreateBuffer > 0) {
			vector<Mob*> pMob;
			for (int i = 0; i < mobCreateBuffer; i++) {
				Mob* tempMob = new Mob;
				tempMob->Init();
				tempMob->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + (rand() % 40), 2.67f, GSM().mobPos.z + (rand() % 350)));
				//m_pMob2.push_back(tempMob);
				//uBox->m_pMob.push_back(tempMob);
				if (tempMob->m_Act._moving == ��_�����̵� || tempMob->m_Act._reload == ��_������ || tempMob->m_Act._engage == ��_���󹰿�����)
				{
					uBox->FindHidingInTheWallLocation(tempMob);
				}
				pMob.push_back(tempMob);
			}
			uBox->m_pMob.insert(uBox->m_pMob.end(), pMob.begin(), pMob.end());
			mobCreateBuffer = 0;
		}
		Sleep(10);
	}
	return 0;
}

UnitBox::UnitBox()
{
	m_SameChk = false;
	MobNum = 0;
	MobStart = false;
	mobCreateBuffer = 0;
	NOL_Team = 0;
}

UnitBox::~UnitBox()
{
	TerminateThread(UnitLoadingThread, 0);
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		SAFE_RELEASE(m_pMob[i]);
	}
	for (size_t i = 0; i < m_pTeam.size(); i++)
	{
		SAFE_RELEASE(m_pTeam[i]);
	}
}



void UnitBox::Init()
{
	m_game.MaxAmount = 0;
	MobStart = false;
	TeamPosition();
	RandomSelectPosition();
	m_CanSave.resize(m_SaveLocation.size(), true);
	FindEmptyWallDirection();
	//�Ʊ�AI����
	m_pTeam.resize(TeamSize);
	for (int i = 0; i < TeamSize; i++)
	{
		m_pTeam[i] = new TeamAI;
		m_pTeam[i]->Init();
		m_pTeam[i]->SetPosition(&m_TeamPosition[posit[i]]);
	}
	posit.clear();
	hUnitLoadingThread = CreateThread(NULL, 0, UnitLoadingThread, this, NULL, NULL);
	LocationSharing();
	//CreateMob(50);
}

void UnitBox::Update()
{
	//Debug->EndLine();
		
	/*if (mobCreateBuffer <= 0) {
	mobCreateBuffer += 20;
	}*/
	/*if (GetAsyncKeyState(VK_F2) & 0x0001)
	{
		GameWaveSetting(10);
	}*/
	/*if (GetAsyncKeyState(VK_F3) & 0x0001)
	{
		MobStart = true;
	}*/
		
	//if (GetAsyncKeyState(VK_F4) & 0x0001)
	//�Ʊ� ���� ����
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		RandomSelectPosition();
		RegenTeam();
		posit.clear();
	}

	if (GetAsyncKeyState(VK_F6) & 0x0001)
	{
		for (auto p : m_pTeam)
		{
			p->setHealth(0);
		}
	}
	Debug->AddText("����ִ¸��� : ");
	Debug->AddText(CheckNumberOfLivingAI(m_game.MaxAmount));
	Debug->EndLine();
	FindCanMoveroad();
	////���� ���������� ��ֹ� ��������ġ ����
	//for (auto p : m_pMob)
	//{
	//	if(p->m_Act._moving==��_�����̵�)
	//		p->EraseLocationSoldier();
	//}
	//�Ʊ�Ai�� ��Ai�ν��ϴ� ����
	if (m_pTeam.size() > 0)
	{
		for (size_t i = 0; i < m_pTeam.size(); i++)
		{
			SAFE_UPDATE(m_pTeam[i]);
		}
	}
	//Ÿ�������� �����̴� ����
	if (MobStart)
	{
		if (m_pMob.size() > 0)
		{
			for (size_t i = 0; i < m_game.MaxAmount; i++)
			{
				SAFE_UPDATE(m_pMob[i]);
				//��ֹ��ڿ� ����
				if (m_pMob[i]->GetPosition().x > NODE_POSITSIZEX + 150.0f)
				{
					MobMoveInTheWall(i);
				}
				m_pMob[i]->UpdatePositionToDestination();
			}
		}
	}
}

void UnitBox::Render()
{
	if (MobStart)
	{
		if (m_pMob.size() > 0)
		{
			for (size_t i = 0; i < m_game.MaxAmount; i++)
			{
				SAFE_RENDER(m_pMob[i]);
			}
		}
	}
	
	for (size_t i = 0; i < m_pTeam.size(); i++)
	{
		SAFE_RENDER(m_pTeam[i]);
	}
}

void UnitBox::FindEmptyWallDirection()
{
	for (int i = 0; i < m_SaveLocation.size(); i++)
	{
		int sum = 0;
		for (int j = 0; j < m_SaveLocation.size(); j++)
		{
			if (i != j && m_SaveLocation[i].x == m_SaveLocation[j].x)
			{
				float leng = m_SaveLocation[i].z - m_SaveLocation[j].z;
				if (abs(leng) < 7.5f)
				{
					leng > 0 ? sum += (int)����ֹ����� : sum += (int)����ֹ�����;
				}
			}
		}
		switch (sum)
		{
		case 0:
			m_CanSeeDirection.push_back(��������);
		case 1:
			m_CanSeeDirection.push_back(����ֹ�����);
			break;
		case 2:
			m_CanSeeDirection.push_back(����ֹ�����);
			break;
		case 3:
			m_CanSeeDirection.push_back(��������);
			break;
		}
	}
}

void UnitBox::FindHidingInTheWallLocation(Mob* _mob)
{
	D3DXVECTOR3 Save;
	for (size_t i = 0; i < m_SaveLocation.size(); i++)
	{
		Save = D3DXVECTOR3(m_SaveLocation[i].x + 1.0f, m_SaveLocation[i].y, m_SaveLocation[i].z);
		//����ġ�κ��� Z����10�ΰ��� �˻�
		if (abs(m_SaveLocation[i].z - _mob->GetPosition().z) < 10)
		{
			if (i == 0)
			{
				_mob->SetMoveTheWall(Save, i, m_CanSeeDirection[i]);
				continue;
			}

			for (int j = 0; j < _mob->GetMoveTheWall().size(); j++)
			{
				//���� ��������ġ�� ������ ��ֹ���ġ�� x���� ���������� ���� 
				if (_mob->GetMoveTheWall()[j].x != Save.x)
				{
					m_SameChk = false;
				}
				else //���� ��������ġ�� ������ ��ֹ���ġ�� x���� ������ �ӽ�����
				{
					m_SameChk = true;
					_mob->SetTemporary(Save, i, m_CanSeeDirection[i]);
					j = _mob->GetMoveTheWall().size();
				}
			}
			if (m_SameChk == false)
			{
				_mob->SetMoveTheWall(Save, i, m_CanSeeDirection[i]);
			}
			m_SameChk = false;
		}
	}
	//��������ġ���� ����(�ڷΰ����� ����ġ�� �����)
	_mob->LocationSwap();
	//�ӽ���������ġ���� ����(�ڷΰ����� ���������� �����)
	_mob->TemporarySwap();
}

void UnitBox::MobMoveInTheWall(int _Mobnum)
{
	//����������ġ�� ������ ��ȣ�� ����
	if (m_pMob[_Mobnum]->GetMoveTheWall().empty() == true)
	{
		if (m_pMob[_Mobnum]->m_move == false)
		{
			//m_pMob[_Mobnum]->SetDestination(D3DXVECTOR3(5.0f + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((_Mobnum + 1) * 20 + NODE_POSITSIZE)));
			m_pMob[_Mobnum]->SetDestination(D3DXVECTOR3(NODE_POSITSIZEX + 100.0f, 2.67f, m_pMob[_Mobnum]->GetPosition().z));
			m_pMob[_Mobnum]->m_move = true;
		}
	}
	else
	{
		//�����̵��ϴ³� && �����̵��̾ �����ÿ� ���买������ && ���ڸ���� �ϴٰ� ���� ������
		if (m_pMob[_Mobnum]->m_Act._moving == ��_�����̵� || (m_pMob[_Mobnum]->m_Act._engage == ��_���󹰿����� && m_pMob[_Mobnum]->PlayerSearch() == true)
			|| ((m_pMob[_Mobnum]->HaveBullet() == false && m_pMob[_Mobnum]->MaxBullet() == true) && m_pMob[_Mobnum]->m_Act._engage == ��_���ڸ�����))
		{
			if (m_pMob[_Mobnum]->m_move == false)
			{
				m_pMob[_Mobnum]->SetDestination(m_pMob[_Mobnum]->GetMoveTheWall().back());
				m_pMob[_Mobnum]->UpdatePositionToDestination();
				m_pMob[_Mobnum]->m_move = true;
			}

			if (m_pMob[_Mobnum]->m_move == true)
			{
				float Dist = D3DXVec3Length(&(m_pMob[_Mobnum]->GetMoveTheWall().back() - m_pMob[_Mobnum]->GetPosition()));
				if (Dist < 20 && m_pMob[_Mobnum]->GetDetermined() == false)
				{
					//������ΰ��°�
					if (m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] == true)
					{
						m_pMob[_Mobnum]->SetDetermined(true);
						m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] = false;
					}
					else     //�������� ���°�
					{
						int j = m_pMob[_Mobnum]->GetTemporary().size() - 1;
						while (j > -1)
						{
							//����ġ���� �ӽ�������ġ�� �ڿ������� ����
							if (m_pMob[_Mobnum]->GetMoveTheWall().back().x < m_pMob[_Mobnum]->GetTemporary()[j].x)
							{
								m_pMob[_Mobnum]->EraseTemporary();
								j = m_pMob[_Mobnum]->GetTemporary().size() - 1;
								continue;
							}
							//���� ����ġ�� X���̶� �ӽ�������ġ�� X���� ������(�����濡�ִ°�)
							if (m_pMob[_Mobnum]->GetMoveTheWall().back().x == m_pMob[_Mobnum]->GetTemporary()[j].x)
							{
								//�ӽ�������ġ�� �����ִ°��϶� �������ִ���ġ ����� �ӽ�������ġ�� �������
								if (m_CanSave[m_pMob[_Mobnum]->GetTemporaryNum().back()] == true)
								{
									m_pMob[_Mobnum]->EraseWallLocation();
									m_pMob[_Mobnum]->SetMoveTheWall(m_pMob[_Mobnum]->GetTemporary().back(), m_pMob[_Mobnum]->GetTemporaryNum().back()
										, m_pMob[_Mobnum]->GetTemporaryDirection().back());
									m_pMob[_Mobnum]->EraseTemporary();
									break;
								}
								else //�����°��϶� �ű����
								{
									m_pMob[_Mobnum]->EraseTemporary();
									j = m_pMob[_Mobnum]->GetTemporary().size() - 1;
								}

							}
							else //�����濡 �ӽ�������ġ�� ������ ������ �׶��� ����
							{
								m_pMob[_Mobnum]->EraseWallLocation();
								break;
							}
						}

						//�����̵��϶� ��ܿ� ���뿡�� ������������ϰ� �ϴܳ��뿡�� �̵��� ����ġ �����Ը���
						if (m_pMob[_Mobnum]->GetLocationNum().empty() == false)
						{
							m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] = false;
							m_pMob[_Mobnum]->SetDestination(m_pMob[_Mobnum]->GetMoveTheWall().back());
							m_pMob[_Mobnum]->UpdatePositionToDestination();
							Dist = D3DXVec3Length(&(m_pMob[_Mobnum]->GetMoveTheWall().back() - m_pMob[_Mobnum]->GetPosition()));
						}
						//��ֹ� ������
						m_pMob[_Mobnum]->SetDetermined(true);
					}
				}
				//���� ��ֹ��� ���� ���� ���ǹ�
				if (Dist < 1.0f)
				{
					m_pMob[_Mobnum]->hidingChk = true;
					if (m_pMob[_Mobnum]->PlayerSearch() == �ֺ�������)
					{
						m_pMob[_Mobnum]->SetMoveSpeed(0);
						m_pMob[_Mobnum]->num++;
						if (m_pMob[_Mobnum]->num > 100)
						{
							m_pMob[_Mobnum]->SetMoveSpeed(1.0f);
							m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] = true;
							m_pMob[_Mobnum]->SetDetermined(false);
							if (!m_pMob[_Mobnum]->GetMoveTheWall().empty())
								m_pMob[_Mobnum]->EraseWallLocation();
							m_pMob[_Mobnum]->m_move = false;
							m_pMob[_Mobnum]->num = 0;
							m_pMob[_Mobnum]->hidingChk = false;
						}
					}
				}
			}
		}
	}
}

void UnitBox::TeamPosition()
{
	//��������
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 114.0f), 2.67f, 221.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 114.0f), 2.67f, 230.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 114.0f), 2.67f, 239.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 115.0f), 2.67f, 271.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 115.0f), 2.67f, 277.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 105.0f), 2.67f, 316.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 105.0f), 2.67f, 323.0f));
	//m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 94.0f), 2.67f, 337.0f));
	//m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 83.0f), 2.67f, 347.0f));
	//m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 81.5f), 2.67f, 355.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 112.0f), 2.67f, 378.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 112.0f), 2.67f, 386.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 112.0f), 2.67f, 395.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 98.0f), 2.67f, 422.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 98.0f), 2.67f, 433.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 100.0f), 2.67f, 490.0f));
	m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 100.0f), 2.67f, 503.0f));
	//�޽�����
	//m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 7.0f), 2.67f, 254.0f));
	//m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 27.0f), 2.67f, 304.0f));
	//m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 29.0f), 2.67f, 311.0f));
	//m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 36.0f), 2.67f, 404.0f));
	//m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 36.0f), 2.67f, 410.0f));
	//m_TeamPosition.push_back(D3DXVECTOR3((NODE_POSITSIZEX + 15.0f), 2.67f, 498.0f));
}
void UnitBox::RandomSelectPosition()
{
	while (posit.size() < TeamSize)
	{
		bool same = false;
		int randint = rand() % TeamPositSize;

		if (posit.empty())
		{
			posit.push_back(randint);
			continue;
		}

		for (int i = 0; i < posit.size(); i++)
		{
			if (randint == posit[i])
			{
				same = true;
				break;
			}
			else
				same = false;
		}
		if (same == false)
			posit.push_back(randint);
	}
}
void UnitBox::RegenTeam()
{
	for (int i = 0; i < m_pTeam.size(); i++)
	{
		if (m_pTeam[i]->getHealth() <= 0)
		{
			m_pTeam[i]->setHealth(100);
			m_pTeam[i]->setStatus(1);
			if (posit[i] < 3)
			{
				m_pTeam[i]->SetPosition(&D3DXVECTOR3(211.0f, 2.67f, 190.0f));
			}
			else if (posit[i] < 5)
			{
				m_pTeam[i]->SetPosition(&D3DXVECTOR3(140.0f, 2.67f, 290.0f));
			}
			else if (posit[i] < 8)
			{
				m_pTeam[i]->SetPosition(&D3DXVECTOR3(140.0f, 2.67f, 354.0f));
			}
			else if (posit[i] < 12)
			{
				m_pTeam[i]->SetPosition(&D3DXVECTOR3(140.0f, 2.67f, 426.0f));
			}
			else
			{
				m_pTeam[i]->SetPosition(&D3DXVECTOR3(212.0f, 2.67f, 538.0f));
			}
			m_pTeam[i]->SetDestination(m_TeamPosition[posit[i]]);
			m_pTeam[i]->SetReady(0);
		}
	}
}
void UnitBox::CreateMob(int num)
{
	//g_pSoundManager->playMusic(1);
	//g_pSoundManager->effectSound(0);

	for (int i = 0; i < num; i++)
	{
		/*MobNum++;
		m_pMob.resize(MobNum);
		m_pMob[MobNum - 1] = new Mob;
		m_pMob[MobNum - 1]->Init();
		m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + (rand() % 40), 2.67f, GSM().mobPos.z + (rand() % 350)));
		if (m_pMob[MobNum - 1]->m_Act._moving == ��_�����̵� || m_pMob[MobNum - 1]->m_Act._reload == ��_������ || m_pMob[MobNum - 1]->m_Act._engage == ��_���󹰿�����)
		{
		FindHidingInTheWallLocation(MobNum - 1);
		}*/
		Mob* tempMob = new Mob;
		tempMob->Init();
		tempMob->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + (rand() % 40), 2.67f, GSM().mobPos.z + (rand() % 350)));
		bool check = false;
		while (1)
		{
			for (auto p : m_pMob)
			{
				if (D3DXVec3Length(&(tempMob->GetPosition() - p->GetPosition())) < 10.0f)
				{
					check = true;
					tempMob->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + (rand() % 40), 2.67f, GSM().mobPos.z + (rand() % 350)));
					break;
				}
				else
					check = false;
			}
			if (!check)
				break;
		}
		m_pMob.push_back(tempMob);
		if (tempMob->m_Act._moving == ��_�����̵� || tempMob->m_Act._reload == ��_������ || tempMob->m_Act._engage == ��_���󹰿�����)
		{
			FindHidingInTheWallLocation(m_pMob.back());
		}
	}
}

void UnitBox::ReSetMob()
{
	//���� ����ִ¸� + �ð��� ��������� ���� ���� ����
	int MaxAmount = m_game.MaxAmount;
	
	while(MaxAmount > 0)
	{
		if (m_pMob[MaxAmount]->getHealth() <= 0)
		{
			m_pMob[MaxAmount]->ResetAll();
			if (m_pMob[MaxAmount]->m_Act._moving == ��_�����̵� || m_pMob[MaxAmount]->m_Act._reload == ��_������ || m_pMob[MaxAmount]->m_Act._engage == ��_���󹰿�����)
			{
				FindHidingInTheWallLocation(m_pMob[MaxAmount]);
			}
		}
		MaxAmount--;
	}
}

int UnitBox::CheckNumberOfLivingAI(int _amount)
{
	/*for (auto p : m_pTeam)
	{
		NOL_Team += p->getStatus();
	}
	if (NOL_Team == 0)
	{
		for (auto p : m_pMob)
		{
			p->SetMoveSpeed(0);
		}
	}
	else
	{
		for (auto p : m_pMob)
		{
			p->SetMoveSpeed(GSM().mobSpeed);
		}
	}*/
	vector<int> NOL;
	int sum = 0;
	NOL.resize(_amount);
	for (int i = 0; i < _amount; i++)
	{
		if (m_pMob[i]->getHealth() <= 0)
			NOL[i] = 0;
		else
			NOL[i] = 1;
	}
	for (auto p : NOL)
	{
		sum += p;
	}
	return sum;
}

void UnitBox::LocationSharing()
{
	m_LocationList.resize(8);
	for (auto p : m_SaveLocation)
	{
		switch ((int)p.x)
		{
		case 268:
			m_LocationList[0].push_back(p);
			break;
		case 325:
			m_LocationList[2].push_back(p);
			break;
		case 353:
			m_LocationList[3].push_back(p);
			break;
		case 410:
			m_LocationList[5].push_back(p);
			break;
		case 439:
			m_LocationList[6].push_back(p);
			break;
		}
	}
	for (auto p : m_nWallLocation)
	{
		switch ((int)p.x)
		{
		case 296:
			m_LocationList[1].push_back(p);
			break;
		case 382:
			m_LocationList[4].push_back(p);
			break;
		case 467:
			m_LocationList[7].push_back(p);
			break;
		}
	}
}

void UnitBox::GameWaveSetting(int _Start)
{
	m_game.StartAmount = _Start;
	PlayWave();
}

void UnitBox::PlayWave()
{
	if (m_game.MaxAmount == 0)
		m_game.MaxAmount = CheckNumberOfLivingAI(m_game.StartAmount);
	else
		m_game.MaxAmount = CheckNumberOfLivingAI(m_game.MaxAmount) + m_game.StartAmount;

	ReSetMob();
}

int UnitBox::ClearWave()
{
	if (CheckNumberOfLivingAI(m_game.MaxAmount) == 0)
		return 1;
	else
	{
		int sum = 0;
		for (auto p : m_pMob)
		{
			if (p->GetPosition().x < 245.0f && p->getStatus() == 1)
				sum++;
		}
		if (sum > 5)
			return 2;
	}
}

void UnitBox::FindCanMoveroad()
{
	float maxLocation = NULL;
	for (auto p : m_pMob)
	{
		if (p->GetCollision() && p->GetAvoidObstDir() == 0)
		{
			for (int i = 0; i < m_LocationList.size(); i++)
			{
				if (p->GetPosition().x > m_LocationList[i].front().x)
				{
					maxLocation = i;
				}
				else
					break;
			}
			if (maxLocation != NULL)
			{
				for (int i = 0; i < m_LocationList[maxLocation].size(); i++)
				{
					if (abs(p->GetPosition().x - m_LocationList[maxLocation][i].x) < 20.0f && abs(p->GetPosition().z - m_LocationList[maxLocation][i].z) < 10.0f)
					{
						if (p->GetPosition().z - m_LocationList[maxLocation][i].z > 0)
						{
							p->FindCanMoveroad(2);
						}
						else
						{
							p->FindCanMoveroad(1);
						}
					}
				}
			}
		}
	}
}

vector<Mob*>* UnitBox::getPMob()
{
	return &m_pMob;
}

vector<TeamAI*>* UnitBox::getPTeam()
{
	return &m_pTeam;
}