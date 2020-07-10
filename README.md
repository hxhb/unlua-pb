## What is this?

这是集成lua-ptorobuf到Unlua的Module。基于[392ace3](https://github.com/starwing/lua-protobuf/commit/392ace3abd4a46e5c386e52d2d16c9aade52e46d)

### Usage

1. 把本仓库clone之后放到Unlua的ThirdParty下；
2. 在`UnLua.uplugin`中的`Modules`下添加如下内容：

```json
{
  "Name": "LuaProtobuf",
  "Type": "Runtime",
  "LoadingPhase": "Default"
}
```

3. 在Unlua的`build.cs`中添加`LuaProtobuf`模块依赖；
4. 在`Unlua`的`LuaContext.cpp`中的`FLuaContext::CreateState`函数中调用`FLuaProtobuf::RegisterLuaLib`即可。

```cpp
FLuaProtobuf& LuaProtobuf = FModuleManager::LoadModuleChecked<FLuaProtobuf>(TEXT("LuaProtobuf"));
LuaProtobuf.RegisterLuaLib(L);
```

模块注册时已经把`protoc.lua`和`serpent.lua`都添加了，不需要再把他们放到`Content/Script`下。

**注意**：lua-protobuf官方版本在ue中当使用pb.loadfile的时候会用问题，它直接使用了fopen来打开传入的文件路径，这样不会基于ue的ufs来查找文件，所以会找不到pak里的文件，需要把lpb_loadfile这部分给改了，本项目内我已经修改支持，使用`pb.loadufsfile`即可。

>`pb.loadufsfile`应该传递的是`FPaths::ProjectContentDir()` + proto文件相对于Content的路径，如`FPaths::Combine(FPaths::ProjectContentDir(),TEXT("Script/Msg.proto"))`。不过`FPaths::Combine`这个函数在UnLua官方版本里没有导出，我在[debugable-unlua](https://github.com/hxhb/debugable-unlua)里导出了。
