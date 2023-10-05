import React from "react";
import "../styles/styles.css"; // Import the CSS
import { useNavigate } from "react-router-dom";

function MenuBar({ setPage }) {
  const navigate = useNavigate();

  const handleWater = () => {
    navigate("/watersystem");
  };
  const handleDashboard = () => {
    navigate("/");
  };
  const handleTemperature = () => {
    navigate("/tempsystem");
  };
  const handleLight = () => {
    navigate("/lightsystem");
  };

  return (
    <div className="menu-bar">
      <ul>
        <li onClick={() => handleDashboard()}>Dashboard</li>
        <li onClick={() => handleWater()}>Water System</li>
        <li onClick={() => handleTemperature()}>Temperature System</li>
        <li onClick={() => handleLight()}>Lightning System</li>
      </ul>
    </div>
  );
}

export default MenuBar;
