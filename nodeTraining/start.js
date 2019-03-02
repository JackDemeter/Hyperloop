//start.js
var http  = require('http');
var spawn = require('child_process').spawn;
var fs = require('fs');
var py    = spawn('python', ['./hyperloop_collection.py']);
var dataString = ""

py.stdout.on('data', function(data){
  dataString = data.toString();
});

py.stdin.write(JSON.stringify([1,2,3]));
py.stdin.end();

//create a server object:
http.createServer(function (req, res) {
  fs.readFile('page.html', function(err, data) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data); //write a response to the client
    res.end(); //end the response
  });
}).listen(8080); //the server object listens on port 8080
