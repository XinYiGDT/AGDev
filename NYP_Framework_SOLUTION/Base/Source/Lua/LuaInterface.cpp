#include "LuaInterface.h"
#include <iostream>
using namespace std;

//allocating the initializing CLuaInterface's static data member.
//the pointer is allocated but not the object's contructor
CLuaInterface *CLuaInterface::s_instance = 0;

CLuaInterface::CLuaInterface()
	: theLuaState(NULL)
{
}

CLuaInterface::~CLuaInterface()
{
}

bool CLuaInterface::Init()
{
	bool result = false;

	//1. create lua state
	theLuaState = lua_open();

	if (theLuaState)
	{
		//2. load lua auxiliary libraries
		luaL_openlibs(theLuaState);

		//3. load lua script
		luaL_dofile(theLuaState, "Image//DM2240.lua");

		result = true;
	}

	return result;
}

void CLuaInterface::Run()
{
	if (theLuaState == NULL)
		return;

	//4. read the variable
	//lua_getglobal(lua_State*, const char*)
	lua_getglobal(theLuaState, "title");
	//extra value, index -1 as varaible is already retrieved using lua_getglobal
	const char *title = lua_tostring(theLuaState, -1);

	lua_getglobal(theLuaState, "width");
	int width = lua_tointeger(theLuaState, -1);

	lua_getglobal(theLuaState, "height");
	int height = lua_tointeger(theLuaState, -1);

	//display on screen
	cout << title << endl;
	cout << "--------------------------------" << endl;
	cout << "Width of screen: " << width << endl;
	cout << "Height of screen: " << height << endl;
}

void CLuaInterface::Drop()
{
	if (theLuaState)
	{
		//close lua state
		lua_close(theLuaState);
	}
}

int CLuaInterface::getIntValue(char* text)
{
	lua_getglobal(theLuaState, text);
	int intValue = lua_tointeger(theLuaState, -1);

	return intValue;
}

void CLuaInterface::saveFloatValue(char * varName, float value, bool overwrite)
{
	lua_getglobal(theLuaState, "SaveToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %6.4f\n", varName, value);
	lua_pushstring(theLuaState, outputString);
	lua_pushinteger(theLuaState, overwrite);
	lua_call(theLuaState, 2, 0); cout << "................";
}

void CLuaInterface::saveIntValue(char * varName, float value, bool overwrite)
{
	lua_getglobal(theLuaState, "SaveToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %d\n", varName, value);
	lua_pushstring(theLuaState, outputString);
	lua_pushinteger(theLuaState, overwrite);
	lua_call(theLuaState, 2, 0); cout << "................";
}

