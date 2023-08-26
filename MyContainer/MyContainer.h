#pragma once

template<typename T> class MyVector;
template<typename T> class MyStack;
template<typename T> class MyQueue_DynamicCircle;
template<typename T> class MyQueue_FixedCircle;
template<typename T> class MyQueue_DynamicArray;

class MyContainer
{
public:
	void Main();
private:

	void PrintMyVector(MyVector<int>& vector);
	void TestMyVector();

	void PrintMyStack(MyStack<int>& stack);
	void TestMyStack();

	void PrintMyQueue_DynamicCircle(MyQueue_DynamicCircle<int>& queue);
	void TestMyQueue_DynamicCircle();

	void PrintMyQueue_FixedCircle(MyQueue_FixedCircle<int>& queue);
	void TestMyQueue_FixedCircle();

	void PrintMyQueue_DynamicArray(MyQueue_DynamicArray<int>& queue);
	void TestMyQueue_DynamicArray();
};