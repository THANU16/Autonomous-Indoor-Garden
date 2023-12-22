import React, { useEffect, useState } from "react";
import MenuBar from "./Menubar";
import Speedometer from "./MySpeedometer";
import "../styles/styles.css";
import axios from "axios";

function Dashboard() {
  const [activePage, setActivePage] = useState("dashboard");
  const [sensorData, setSensorData] = useState({});
  useEffect(() => {
    axios
      .get("http://localhost:5000/sensorData")
      .then((res) => {
        setSensorData(res.data);
      })
      .catch((error) => {
        console.log("Error fetching creditSale data:", error);
      });
  });

  return (
    <div className="comp-nav">
      <div>
        <MenuBar />
      </div>

      <div className="dashboard">
        <div className="content">
          {activePage === "dashboard" && (
            <div className="speedometer-container">
              <div className="speedometer-row">
                <Speedometer
                  title="Temperature"
                  value={sensorData.temperature}
                  minValue={0}
                  maxValue={50}
                />
                <Speedometer
                  title="Moisture"
                  value={sensorData.moisture}
                  minValue={0}
                  maxValue={6000}
                />
                <Speedometer
                  title="pH"
                  value={sensorData.pH}
                  minValue={0}
                  maxValue={15}
                />
              </div>
            </div>
          )}
          {/* Add other content for different pages */}
        </div>
      </div>
    </div>
  );
}

export default Dashboard;
