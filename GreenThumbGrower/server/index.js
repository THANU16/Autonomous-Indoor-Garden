var http = require("http");
const express = require("express");
const app = express();
const cors = require("cors");
app.use(cors());

const sensorData = require("./component/sensorData");

server = http.createServer((req, res) => {
  res.setHeader("Content-Type", "text/plain");
});

// Set up body parsing middleware
app.use(express.json());

app.use("/sensorData", sensorData);

app.listen(5000, () => {
  console.log("Listen port 5000");
});
