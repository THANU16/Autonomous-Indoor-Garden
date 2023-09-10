const express = require("express");
const mqtt = require("mqtt");

const router = express.Router();

const mqttServer = "mqtt://YOUR_MQTT_SERVER_IP";
const mqttPort = 1883;

const client = mqtt.connect(mqttServer, { port: mqttPort });

console.log("sensorData Connected");

client.on("connect", () => {
  console.log("Connected to MQTT broker");
  client.subscribe("moistrue");
  client.subscribe("temperature");
  client.subscribe("pH");
});

router.use(express.static("public"));

router.get("/", (req, res) => {
  // console.log(req);
  // res.setHeader("Content-Type", "text/event-stream");
  // res.setHeader("Cache-Control", "no-cache");
  // res.setHeader("Connection", "keep-alive");
  // res.setHeader("Access-Control-Allow-Origin", "*");
  const sendSensorData = (data) => {
    // res.send(`data: ${JSON.stringify(data)}\n\n`);
    res.send(data);
  };

  const data = {
    moistrue: 500,
    temperature: 32,
    pH: 7.8,
  };
  sendSensorData(data);

  client.on("message", (topic, message) => {
    const data = {
      topic: topic,
      value: JSON.parse(message.toString()),
    };
    sendSensorData(data);
  });

  req.on("close", () => {
    client.removeListener("message", sendSensorData);
  });
});

module.exports = router;
