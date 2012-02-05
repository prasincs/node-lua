var node_lua = require('node_lua')
/*
 * GET home page.
*/

exports.index = function(req, res){
  res.render('index', { title: 'Express' })
};

exports.runLua = function(req, res){
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
