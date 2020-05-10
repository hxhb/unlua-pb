// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Features/IModularFeatures.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

struct lua_State;
#define LUA_LIB_FEATURE_NAME "LuaLibFeature"

class LUAPROTOBUF_API FLuaProtobuf : public IModuleInterface,public IModularFeature
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void SetupLuaProtobuf(lua_State* L);

	static inline FLuaProtobuf& Get()
	{
		return FModuleManager::LoadModuleChecked<FLuaProtobuf>("LuaProtobuf");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("LuaProtobuf");
	}

	virtual void RegisterLuaLib(lua_State* L);
	virtual void UnRegisterLuaLib(lua_State* L);
	virtual FName GetLibName()const;

protected:
	static int OpenLuaProtobuf(lua_State* L);
};
