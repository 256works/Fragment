#pragma once

#define PI 3.1415f

inline float PointDistance(const FPOINT pos1, const FPOINT pos2)
{
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

inline int PointDistance(const POINT pos1, const POINT pos2)
{
	return (int)sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

inline POINT GetRectCenter(const RECT rect)
{
	int x = rect.left + (rect.right - rect.left) / 2;
	int y = rect.top + (rect.bottom - rect.top) / 2;
	return POINT({ x, y });
}

inline int PointDistance(const RECT rect1, const RECT rect2)
{
	POINT pos1, pos2;
	pos1 = GetRectCenter(rect1);
	pos2 = GetRectCenter(rect2);

	return (int)sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

inline float PointDirection(const FPOINT pos1, const FPOINT pos2)
{
	return atan2(pos2.y - pos1.y, -(pos2.x - pos1.x)) * 180.0f / (float)PI + 180.0f;
}

inline bool _IsCollision(const RECT rc1, const RECT rc2)
{
	if (rc1.right > rc2.left && rc1.left < rc2.right)
	{
		if (rc1.top < rc2.bottom && rc1.bottom > rc2.top)
		{
			return true;
		}
	}

	return false;
}


inline float DegToRad(float deg)
{
	return deg * (PI / 180.0f);
}

inline float Dsin(float deg)
{
	return sin(DegToRad(deg));
}

inline float Dcos(float deg)
{
	return cos(DegToRad(deg));
}

inline float LengthdirX(float length, float dir)
{
	return Dcos(dir)*length;
}

inline float LengthdirY(float length, float dir)
{
	return -Dsin(dir)*length;
}

inline int Irand(const int val1, const int val2)
{
	int maxVal;
	int minVal;
	if (val1 > val2)
	{
		maxVal = val1;
		minVal = val2;
	}
	else
	{
		maxVal = val2;
		minVal = val1;
	}
	int res = (rand() % ((maxVal + 1) - minVal)) + minVal;
	return res;
}

inline float Clamp(const float val, const float min, const float max)
{
	float res = val;
	if (res > max)
		res = max;
	if (res < min)
		res = min;
	return res;
}