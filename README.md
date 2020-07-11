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

>`pb.loadufsfile`应该传递的是`FPaths::ProjectContentDir()` + proto文件相对于Content的路径，如`FPaths::Combine(FPaths::ProjectContentDir(),TEXT("Script/Msg.pb"))`。不过`FPaths::Combine`这个函数在UnLua官方版本里没有导出，我在[debugable-unlua](https://github.com/hxhb/debugable-unlua)里导出了。

**注意**:`pb.loadufsfile`只能用来加载`*.pb`的文件，不能用来加载`*.protoc`的文件。
`*pb`可以通过protobuf中的`protoc.exe`来生成：

```bash
protoc.exe -o Msg.pb Msg.protoc
```
如果想要直接加载`*.protoc`的文本可以通过下列方法：

```cpp
local filepath = UE4.FPaths.Combine(FPaths.ProjectContentDir(),"Script/TestMsg.proto")
local protoContent = UE4.FFileHelper.LoadFileToArray(filepath)
protoc:load(protoContent)
```
UnLua官方版本没有导出`UE4.FFileHelper.LoadFileToArray`这个符号到lua，我在[debugable-unlua](https://github.com/hxhb/debugable-unlua)里导出了。
