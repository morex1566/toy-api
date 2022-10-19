#pragma once

// for warning C4316
// �� ���� __declspec(align(byte))�� ���ĵǾ�� �ϴ� �����͸� member�� �����ų�, 
// �Ҵ��� �� ����� �����. For example, using XMMATRIX as a class member. 
template<size_t T>
class AlignedAllocationPolicy
{
public:
	static void* operator new(size_t size)
	{
		return _aligned_malloc(size, T);
	}

	static void operator delete(void* memory)
	{
		_aligned_free(memory);
	}
};
