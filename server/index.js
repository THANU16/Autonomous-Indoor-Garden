const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const { WebSocketServer } = require("ws");

const app = express();
const port = 5000; // Replace with your desired port

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(cors());

// Initialize an array to store received data
const receivedDataArray = [];
var lastReceivedData = {};
const clientConnection = new Map();

// Create a function to handle WebSocket connections.
function handleWebSocketConnections(server) {
  const wsServer = new WebSocketServer({ server });

  wsServer.on("connection", (socket, req) => {
    console.log("WebSocket client connected");

    // Extract query parameters from the request URL.
    const { query } = url.parse(req.url, true);
    const sessionToken = query.sessionToken;
    // console.log(sessionToken);
    const typeID = query.typeID;

    const clientID = decodedUserId(sessionToken);

    // console.log(clientID, typeID, sessionToken);

    // Check if the session token is valid (you should implement your validation logic here).
    if (clientID) {
      // console.log(" connected");
      clientConnection.set(clientID, socket);
      
      socket.on("message", (message) => {
        console.log(`Received message: ${message}`);
      });

      socket.on("close", () => {
        console.log("WebSocket client disconnected");

        // Remove the WebSocket connection from the map when the client disconnects.
        // clientConnection.delete(clientID);
      });
    } else {
      // If the session token is invalid, close the WebSocket connection.
      console.log("Invalid session token. Closing WebSocket connection.");
      socket.close();
    }
  });
}



  

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
});




app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
