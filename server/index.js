const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");

const app = express();
const port = 5000; // Replace with your desired port

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(cors());

// Initialize an array to store received data
const receivedDataArray = [];
var lastReceivedData = {};

// Define an API route to receive data from the ESP32
app.post("/data", (req, res) => {
  console.log("Received POST request to /data");
  console.log("Request body:", req.body);

  const receivedData = req.body;

  // Process or store the received data in the array
  receivedDataArray.push(receivedData);
  lastReceivedData = receivedData;
  // Send a response (optional)
  res.status(200).send("Data received successfully");
});

// Define a route to retrieve the last stored data
app.get("/sensorData", (req, res) => {
  res.json(lastReceivedData);
  // // Check if there is data in the array
  // if (receivedDataArray.length > 0) {
  //   // Get the last item (last received data)
  //   const lastReceivedData = receivedDataArray[receivedDataArray.length - 1];
  //   receivedDataArray.pop();

  //   // Return the last received data
  //   res.json(lastReceivedData);
  // } else {
  //   // If no data is available, return an empty object or an appropriate response
  //   res.json({});
  // }
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
