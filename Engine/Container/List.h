#pragma once

#include <iostream>

template <typename T>
class List
{
public:
	//List()
	//{
	//	ReAllocate(2); //이게 오류나서 같은코드로
	//}
	List()
		:capacity(2)
	{
		data = new T[capacity];  //@세윤쌤 : 여기도 메모리 릭 오류
		memset(data,0,sizeof(T)*capacity);
	}

	~List()
	{
		if(data != nullptr)
		{
			delete[] data;
		}
	}

	void PushBack(const T& value)
	{
		if(size == capacity)
		{
			ReAllocate(capacity * 2);
		}

		data[size] = value;
		size++;
	}

	void PushBack(T&& value)
	{
		if(size == capacity)
		{
			ReAllocate(capacity * 2);
		}

		data[size] = std::move(value);
		size++;
	}

	void Clear()
	{
		size = 0;
		capacity = 2;
		data = new T[capacity];    //@세윤쌤 : 여기도 메모리 릭 오류
		memset(data,0,sizeof(T)*capacity);
	}

	void Erase(int index)
	{
		if(index < 0 || index >= size)					// 예외 처리.
		{
			__debugbreak();
		}
		for(int ix = index; ix < size-1; ix++)			// 삭제한 데이터의 인덱스 다음 위치를 한칸 앞으로 모두 이동.
		{
			data[ix] =std::move(data[ix+1]);
		}

		--size;											//삭제 후 크기 줄이기
	}

	int Size() const
	{
		return size;
	}

	int Capacity() const
	{
		return capacity;
	}

	const T& operator[](int index) const
	{
		if(index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	T& operator[](int index)
	{
		if(index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	T* begin() const
	{
		return data;
	}
	T* end() const
	{
		return data+size;
	}

private:
	void ReAllocate(int newCapacity)
	{
		// 1. allocate a new block of memory.
		// 2. copy/move old elements into new block.
		// 3. delete.

		T* newBlock = new T[newCapacity];
		memset(newBlock,0,sizeof(T) * newCapacity);

		if(newCapacity < size)
		{
			size = newCapacity;
		}

		memcpy(newBlock,data,sizeof(T) * capacity);
		//for (int ix = 0; ix < size; ++ix)
		//{
		//    // newBlock[ix] = data[ix];
		//    newBlock[ix] = std::move(data[ix]);
		//}

		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

private:
	T* data = nullptr;
	int size = 0;
	int capacity = 0;
};