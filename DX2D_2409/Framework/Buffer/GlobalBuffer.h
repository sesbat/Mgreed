#pragma once

class IntValueBuffer : public ConstBuffer
{
public:
	IntValueBuffer() : ConstBuffer(values, sizeof(int) * 4)
	{
	}

	int* Get() { return values; }

private:
	int values[4] = {};
};

class FloatValueBuffer : public ConstBuffer
{
public:
	FloatValueBuffer() : ConstBuffer(values, sizeof(int) * 4)
	{
	}

	float* Get() { return values; }

private:
	float values[4] = {};
};