#pragma once
#include <map>

enum eBlackboardDataType
{
	type_float,
	type_int,
	type_char,
	type_bool,
	type_pointer
};
struct BlackBoardData
{
	eBlackboardDataType type;
	union 
	{
		float floatValue;
		int intValue;
		char charValue;
		bool boolValue;
		void* pointerValue;
	};
};

class BlackBoard
{
public:
	bool getEntry(int id, BlackBoardData value);
	bool setEntry(int id, BlackBoardData value);
	bool hasEntry(int id);

	BlackBoardData contains(int id);
	eBlackboardDataType getType(int id);

private:
	std::map<int, BlackBoardData> data;
};