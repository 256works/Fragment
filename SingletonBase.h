#pragma once

template <typename T>
class SingletonBase
{
protected:
	static T* singleton;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

template <typename T>
T* SingletonBase<T>::singleton = 0;

template <typename T>
T* SingletonBase<T>::GetSingleton()
{
	if (!singleton)
	{
		singleton = new T;
	}

	return singleton;
}

template <typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}