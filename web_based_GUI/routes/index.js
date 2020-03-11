var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

// Initialize pod server
const dgram = require('dgram');
const server = dgram.createSocket('udp4');
server.connect(3000, "192.168.8.20");
// sends message via udp to the pod server
function send_via_udp(message) {
  var buf = Buffer.from([parseInt(message)]);
  server.send(buf);
};

// Handles posts to /send-status (executed in a loop from the front end)
router.post('/send-status', function(req, res, next) {
  send_via_udp(req.body.status);
});

module.exports = router;
