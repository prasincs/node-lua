#include<v8.h>
#include<node.h>
#include<node_version.h>
#include<string.h>
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


using namespace v8;
Handle<Value> RunLua(const Arguments &args);

// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}



Handle<Value> RunLua (const Arguments &args){
  v8::String::Utf8Value str(args[0]); // Convert first argument to V8 String
  const char* cstr = ToCString(str); // Convert V8 String to C string
  HandleScope scope;
  lua_State *L;
  L=lua_open();
  luaopen_base(L);       // load basic libs (eg. print) 
  
  char buff[1024];
  luaL_loadbuffer(L, cstr, strlen(cstr), buff );
  lua_pcall(L,0,0,0);
  lua_close(L);

  return scope.Close(args[0]->ToString());
}

extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;
  Handle<FunctionTemplate> RunLuaTpl = FunctionTemplate::New(RunLua);
  target->Set(String::New("runLua"), RunLuaTpl->GetFunction());
}






