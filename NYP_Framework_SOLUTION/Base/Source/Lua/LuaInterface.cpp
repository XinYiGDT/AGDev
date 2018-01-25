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

char CLuaInterface::getCharValue(const char * varName)
{
	lua_getglobal(theLuaState, varName);

	size_t len;
	const char* cstr = lua_tolstring(theLuaState, -1, &len);
	//if the string is not empty, then return the 1st char
	if (len > 0)
		return cstr[0];
	else //else return a default value of <SPACE>
		return '\n';
}

Vector3 CLuaInterface::getVector3Values(const char * varName)
{
	lua_getglobal(theLuaState, "CPlayerInfoStartPos");
	lua_rawgeti(theLuaState, -1, 1);
	int x = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	lua_rawgeti(theLuaState, -1, 2);
	int y = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	lua_rawgeti(theLuaState, -1, 3);
	int z = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);

	return Vector3(x, y, z);
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

void CLuaInterface::saveIntValue(char * varName, int value, bool overwrite)
{
	lua_getglobal(theLuaState, "SaveToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %d\n", varName, value);
	lua_pushstring(theLuaState, outputString);
	lua_pushinteger(theLuaState, overwrite);
	lua_call(theLuaState, 2, 0); cout << "................";
}

float CLuaInterface::getDistanceSquareValue(const char * varName, Vector3 source, Vector3 destination)
{
	lua_getglobal(theLuaState, varName);
	lua_pushnumber(theLuaState, source.x);
	lua_pushnumber(theLuaState, source.y);
	lua_pushnumber(theLuaState, source.z);
	lua_pushnumber(theLuaState, destination.x);
	lua_pushnumber(theLuaState, destination.y);
	lua_pushnumber(theLuaState, destination.z);
	lua_call(theLuaState, 6, 1);
	float distanceSquare = (float)lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	return distanceSquare;
}

int CLuaInterface::getVariableValues(const char * varName, int & a, int & b, int & c, int & d)
{
	lua_getglobal(theLuaState, varName);
	lua_pushnumber(theLuaState, 1000);
	lua_pushnumber(theLuaState, 2000);
	lua_pushnumber(theLuaState, 3000);
	lua_pushnumber(theLuaState, 4000);
	lua_call(theLuaState, 4, 4);
	a = lua_tonumber(theLuaState, -1); 
	lua_pop(theLuaState, 1);
	b = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	c = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	d = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);

	return true;
}

