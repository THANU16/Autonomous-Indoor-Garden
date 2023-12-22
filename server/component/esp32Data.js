const express = require("express");
const mqtt = require("mqtt");

const router = express.Router();

console.log("esp32 data Connected");

router.use(express.static("public"));

router.post("/", (req, res) => {
  sensorData = req.body;
  // console.log(req.body);
  // console.log(req);
  // res.setHeader("Content-Type", "text/event-stream");
  // res.setHeader("Cache-Control", "no-cache");
  // res.setHeader("Connection", "keep-alive");
  // res.setHeader("Access-Control-Allow-Origin", "*");
});

module.exports = router;
