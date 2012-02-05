var zmq = require('zmq')
, sock = zmq.socket('push');

  var pub = zmq.socket('push');
  pub.bindSync('tcp://*:4000');

var sub = zmq.socket('pull');
  sub.connect('tcp://127.0.0.1:4001');
  sub.on ('message', function(data){
    console.log(data);
    //res.send(data);
    //res.end();
  });

/*
 * GET home page.
*/

exports.index = function(req, res){
  res.render('index', { title: 'Express' })
};

exports.runLua = function(req, res){
  var node_lua = require('node_lua')
  output = "";
  node_lua.outputCallback(function( msg){
    //res.send(msg);
    //console.log(msg);
    output += msg;
    output +="\n";
  });

  code = req.body.code;
  //console.log(code);
  node_lua.runLua(code);
  res.send(output);
  res.end();
};

exports.submitJob = function(req, res){
  pub.send(req.body.code);
}
