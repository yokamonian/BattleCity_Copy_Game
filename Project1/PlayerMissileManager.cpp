#include "PlayerMissileManager.h"

HRESULT PlayerMissileManager::Init()
{
	for (int i = 0; i < 10; i++)
	{
		Missile* missile = new Missile();
		missile->Init();
		missilepool.AddObjectPool(missile);
	}

	return S_OK;
}

void PlayerMissileManager::Release()
{
	for (auto& it : vecMissile)
	{
		it->Release();
		SAFE_DELETE(it);
	}
	vecMissile.clear();
}

void PlayerMissileManager::Update()
{
	if ((vecMissile.size()) > 0)
	{
		Debug::GetSingleton()->Log("-----------------------");

		char buf[80];
		int i = 0;
		for (vector<Missile*>::iterator p = vecMissile.begin(); p != vecMissile.end(); p++)
		{
			(*p)->Update();
			//sprintf_s(buf, "%d: (%d)", i++, p);
			//Debug::GetSingleton()->Log(buf);

			if ((*p)->GetIsFire())
			{
				if ((*p)->GetPos().x < 227 || (*p)->GetPos().x > 1070 || (*p)->GetPos().y < 15 || (*p)->GetPos().y > 711)
				{
					(*p)->SetIsFire(false);
					missilepool.ReturnObject(*p);
					p = vecMissile.erase(p);
					if (p == vecMissile.end())
						break;
					// 여기서 vecMissile 리스트에서 지워줘야함
				}	

			}

		}
	}
}

void PlayerMissileManager::Render(HDC hdc)
{
	if ((vecMissile.size()) > 0)
	{
		for (auto& it : vecMissile)
		{
			it->Render(hdc);
		}
	}
}

bool PlayerMissileManager::Fire()
{
	
	if (missilepool.ReturnStackSize() > 0)
	{
		Missile* bullet;
		bullet = missilepool.PopObject();

		//char buf[80];
		//sprintf_s(buf, "BulletSpeed : %d / %d", bullet->idx, bullet);
		//Debug::GetSingleton()->Log(buf);

		vecMissile.push_back(bullet);

		for (auto& it : vecMissile)
		{
			if (it->GetIsFire())
			{
				continue;
			}

			it->SetIsFire(true);
			it->SetDirection(m_direction);
			it->SetPos(Pos);
			return true;
		}
	}


	return false;
}
