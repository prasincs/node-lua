#include<v8.h>
#include<node.h>
#include<node_version.h>
#include<string.h>
#include <iostream>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


using namespace v8;
Handle<Value> RunLua(const Arguments &args);

Persistent<Function> outputCallback;

/*************************************************************/
/*                     Lua Code                              */
/*************************************************************/

static int l_my_print(lua_State* L) {
  HandleScope scope;
  int nargs = lua_gettop(L);
  for (int i=1; i <= nargs; i++) {
    if (lua_isstring(L, i)) {
      char* printString = const_cast<char*> (lua_tostring(L,i));  
      // For the life of me I can't remember how to check if outputCallback is initialized
      const unsigned argc = 1;
        Local<Value> argv[argc] = { Local<Value>::New(String::New(printString)) };
        outputCallback->Call(Context::GetCurrent()->Global(), argc, argv);
        
      //String::New(lua_tostring(L,i));


      //puts(lua_tostring(L,i));
      /* Pop the next arg using lua_tostring(L, i) and do your print */
    }
    else {
      /* Do something with non-strings if you like */
    }
  }

  return 0;
}

static const struct luaL_reg printlib [] = {
  {"print", l_my_print},
  {NULL, NULL} /* end of array */
};

extern int luaopen_luamylib(lua_State *L)
{
  lua_getglobal(L, "_G");
  luaL_register(L, NULL, printlib);
  lua_pop(L, 1);
}

/*************************************************************/
/*                     NodeJS/V8 code                        */
/*************************************************************/


// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}




Handle<Value> RunLua (const Arguments &args){
  v8::String::Utf8Value str(args[0]); // Convert first argument to V8 String
  const char* cstr = ToCString(str); // Convert V8 String to C string
  HandleScope scope;
  lua_State *L;
  int error;
  L=lua_open();
  luaopen_base(L);       // load basic libs (eg. print) 

  luaopen_luamylib(L);   //load my overloaded print function
  char buff[1024];
  error = luaL_loadbuffer(L, cstr, strlen(cstr), "line" ) || lua_pcall(L,0,0,0);
  if (error)
  {
    fprintf (stderr, "%s", lua_tostring (L, -1));
    lua_pop (L, 1);
  }  

  lua_close(L);

  return scope.Close(args[0]->ToString());
}

Handle<Value> RunCallback(const Arguments& args) {
  HandleScope scope;
  Local<Function> cb = Local<Function>::Cast(args[0]);

  outputCallback = Persistent<Function>::New(cb);
  //const unsigned argc = 1;
  //Local<Value> argv[argc] = { Local<Value>::New(String::New("hello world")) };
  //cb->Call(Context::GetCurrent()->Global(), argc, argv);

  return scope.Close(Undefined());
}

  extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;
  Handle<FunctionTemplate> RunLuaTpl = FunctionTemplate::New(RunLua);
  target->Set(String::NewSymbol("runLua"), RunLuaTpl->GetFunction());

  target->Set(String::NewSymbol("outputCallback"),
      FunctionTemplate::New(RunCallback)->GetFunction());
}






