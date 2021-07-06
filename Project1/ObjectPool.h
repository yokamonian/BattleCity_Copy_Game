#pragma once
#include <stack>
#include "Missile.h"

class CObjectPool
{
private:
	std::stack<Missile*> _objects;
	int _maxSize; // �ִ� �迭 ũ��
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
		// ������Ʈ�� ���ٸ� Ȯ���Ѵ�.
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