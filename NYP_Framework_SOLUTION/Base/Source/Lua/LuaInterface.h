#pragma once

//includes the lua headers
#include <lua.hpp>
#include "Vector3.h"

class CLuaInterface
{
protected:
	static CLuaInterface *s_instance;
	CLuaInterface();
	
public:
	static CLuaInterface *GetInstance()
	{
		if (!s_instance)
			s_instance = new CLuaInterface;
		return s_instance;
	}
	static bool DropInstance()
	{
		if (s_instance)
		{
			//drop the lua interface class
			s_instance->Drop();

			delete s_instance;
			s_instance = NULL;
			return true;
		}
		return false;
	}
	virtual ~CLuaInterface();

	//initialisation of the lua interface class
	bool Init();

	// run the lua interface class
	void Run();

	//Drop the lua interface class
	void Drop();

	int getIntValue(char* text);

	//get a char value through the Lua Interface Class
	char getCharValue(const char* varName);
	//get Vector3 values through the Lua Interface Class
	Vector3 getVector3Values(const char* varName);

	void saveFloatValue(char* varName, float value, bool overwrite = false);
	void saveIntValue(char* varName, int value, bool overwrite = false);

	//Pointer to the lua state
	lua_State *theLuaState;
	lua_State *theErrorState;

	//Get distance square value through the lua interface class
	float getDistanceSquareValue(const char* varName, Vector3 source, Vector3 destination);

	//Get Variable number of values through the Lua Interface Class
	int getVariableValues(const char* varName, int &a, int &b, int &c, int &d);

	//Extract a field from a table
	float GetField(const char *key);

	//Get error message using an error code
	void error(const char *errorCode);

};