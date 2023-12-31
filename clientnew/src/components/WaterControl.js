import React, { useState } from "react";
import "../styles/styles.css";
import Speedometer from "./MySpeedometer";
import MenuBar from "./Menubar";

const WaterControl = ({ onWaterControl }) => {
  const [waterAmount, setWaterAmount] = useState(20);
  const [waterAmountSet, setWaterAmountSet] = useState(waterAmount);

  const handleIncrease = () => {
    setWaterAmountSet((prevAmount) => prevAmount + 1);
  };

  const handleDecrease = () => {
    if (waterAmountSet > 0) {
      setWaterAmountSet((prevAmount) => prevAmount - 1);
    }
  };

  const handleControl = () => {
    // Assuming you have an API endpoint to control the water system.
    // onWaterControl(waterAmount);
    console.log(waterAmountSet);
  };

  return (
    <div className="comp-nav">
      <div>
        <MenuBar />
      </div>
      <div className="water-control">
        <div className="water-control-1">
          <h2>Water Control</h2>
          <div className="water-control-buttons">
            <button onClick={handleDecrease}>-</button>
            <span>{waterAmountSet} cups</span>
            <button onClick={handleIncrease}>+</button>
          </div>
          <button onClick={handleControl}>Control Water System</button>
        </div>
        <div className="speedometer-container">
          <h3 className="speedometer-title">Water Level</h3>
          <Speedometer
            title=""
            value={waterAmount}
            minValue={0}
            maxValue={50}
          />
        </div>
      </div>
    </div>
  );
};

export default WaterControl;
