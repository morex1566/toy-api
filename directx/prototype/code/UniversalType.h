#pragma once

#include <string>	
#include <vector>	
#include <memory>

using namespace std;

class GameObject;

struct ModelType
{
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
};

template <typename T>
void DestroyVector(vector<T>& vector_)
{
	vector_.clear();
	vector<T>().swap(vector_);
}