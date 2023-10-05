import React from "react";
import Speedometer from "react-d3-speedometer";
import "../styles/styles.css"; // Import the CSS

function MySpeedometer({ title, value, minValue, maxValue }) {
  return (
    <div>
      <div className="speedometer">
        <h1>{title}</h1>
        <div className="speedometer-container">
          <Speedometer
            minValue={minValue}
            maxValue={maxValue}
            value={value}
            endColor="green"
            needleColor="blue"
            currentValueText={`Current Value: ${value}`}
          />
        </div>
      </div>
    </div>
  );
}

export default MySpeedometer;
