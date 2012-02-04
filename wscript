import Options, Utils
from os import unlink, symlink, chdir, environ
from os.path import exists, lexists
import sys


srcdir = '.'
blddir = 'build'

VERSION = '0.0.1'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')
  conf.check_cxx(lib="lua", errmsg="liblua needs to be installed.")
  #conf.check_cxx(lib="ldl", errmsg="libdl needs to be installed.")
    

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = 'node_lua'
  obj.source = 'node_lua.cpp'
  #if 'SERVER' in environ:
  obj.cxxflags = [ "../liblua.a" , "-I../include"]
  #bld.env.append_value('LINKFLAGS', [ srcpath()+'/heroku/lib/liblua.a'])
  #bld.env.append_value('INCPATHS', [ srcpath()+'/heroku/include'])
  #else:
  #  bld.env.append_value('LINKFLAGS', '-llua -ldl'.split())
