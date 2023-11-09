#pragma once
#include <string>

class Object
{
public:
	Object() { ++count; }

	virtual std::string toString() = 0;

	~Object() { --count; }

	uint32_t GetCount() { return count; }

private:
	static inline uint32_t count = 0;
};

class Task : Object
{
public:
	std::string toString() { return "This is an unnamed task."; }
protected:
	std::string result;
};

class Named : Object
{
	std::string toString() { return "This is a named object."; }
protected:
	std::string name;
};

class Equation : Task, Named
{
public:
	Equation(float const & _first, float const & _second, char const & _operation, std::string const & _name) : 
		first(_first), second(_second), operation(_operation)
	{
		switch (operation)
		{
		case '+': result = std::to_string(first + second); break;
		case '-': result = std::to_string(first - second); break;
		case '*': result = std::to_string(first * second); break;
		case '/': result = std::to_string(first / second); break;
		default: result = "Wrong operation."; break;
		}

		name = _name;
	}

	std::string toString()
	{
		return "This is the task named \"" + name + "\": " + 
			std::to_string(first) + " " + operation + " " + std::to_string(second) + " = " + result;
	}

private:
	float first;
	float second;
	char operation;
};