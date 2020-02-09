var express = require('express');
var router = express.Router();

const dgram = require('dgram');
const server = dgram.createSocket('udp4');
server.connect(3000, "192.168.8.20");

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

function send_via_udp(message) {
  var buf = Buffer.from(message);
  console.log(buf);
  server.send(buf);
};

router.post('/send-status', function(req, res, next) {
  send_via_udp(req.body.status);
});

module.exports = router;
