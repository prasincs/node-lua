$(document).ready(function(){
  var editor = CodeMirror.fromTextArea(document.getElementById("luaCodeBox"), {
    mode: "lua",
    tabMode: "indent",
    lineNumbers: true,
    lineWrapping: true,
    onCursorActivity: function() {
      editor.setLineClass(hlLine, null);
      hlLine = editor.setLineClass(editor.getCursor().line, "activeline");
    }
  });
  var hlLine = editor.setLineClass(0, "activeline");
  $("#runLua").click(function(){
    $.post("/submitJob", {"code": editor.getValue()}, function(data){
      $("#output").html(data);
    });
  });
});
