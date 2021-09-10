var ip   = "127.0.0.1";
var port = 7788;
var http = require('http');
var shell = require('/usr/local/lib/node_modules/shelljs');

http.createServer(function (req, res) {
	res.writeHead(200, {'Content-Type': 'text/plain'});
	for (var i = 0; i < 3; i++) {
		//shell.exec('wakeonlan -i 10.2.0.195 00:11:22:33:44:99');
		shell.exec('wakeonlan -i 10.2.0.51 00:11:22:33:44:88');
		//shell.exec('wakeonlan -i 192.168.1.20 00:11:22:33:44:99');
		//shell.exec('wakeonlan -i 10.2.0.81 00:15:6D:01:02:03');
		console.log(new Date() + " => " + i + "-th");
	}
	res.end('WoooooooooooooooooW\n');
}).listen(port);

console.log("Server running at http://" + ip + ":" + port);
