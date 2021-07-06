#pragma once
#include <stack>
#include "Missile.h"

class CObjectPool
{
private:
	std::stack<Missile*> _objects;
	int _maxSize; // 최대 배열 크기
public:
	CObjectPool() {}

	void AddObjectPool(Missile* newObject)
	{
		_objects.push(newObject);
	}

	~CObjectPool()
	{
		while (!_objects.empty()) {
			Missile* object = _objects.top();
			_objects.pop();
			delete object;
		}

		_maxSize = 0;
	}

	Missile* PopObject()
	{
		// 오브젝트가 없다면 확장한다.
		//if (_objects.empty()) {
		//	Expand();
		//}

		Missile* retVal = _objects.top();
		_objects.pop();
		return retVal;
	}

	void ReturnObject(Missile* object)
	{
	
		_objects.push(object);
	}

	int ReturnStackSize() { return _objects.size(); }
};