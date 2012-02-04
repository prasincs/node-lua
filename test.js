var node_lua = require('./build/Release/node_lua')

node_lua.runLua("function double (x) \
                  return 2*x  \
                end  \
                print 'hello lua!' \
                print(double(2)) \
                ");
node_lua.runLua("print(1)");
