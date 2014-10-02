This project is kind of old now, I might fix it at some point but buyers beware.


- Install node.js and lua

- `node-waf configure build install`

- `node test.js`


If you want to run the express server, `node app.js`

TODO:

* Review other alternatives for FFI to Lua
* Maybe just use docker with tiny lua embedded
* Or, run Rump microkernel with Lua on a NetBSD Box [Hardcore]
* More and more I like the idea of just writing this kind of stuff over some kind of RPC protocol instead.
