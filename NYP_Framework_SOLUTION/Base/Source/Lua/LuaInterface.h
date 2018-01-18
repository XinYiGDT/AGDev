#pragma once

//includes the lua headers
#include <lua.hpp>

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
	void saveFloatValue(char* varName, float value, bool overwrite = false);
	void saveIntValue(char* varName, float value, bool overwrite = false);

	//Pointer to the lua state
	lua_State *theLuaState;

};