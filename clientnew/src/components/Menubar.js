// import React from "react";
// import "../styles/styles.css"; // Import the CSS
// import { useNavigate } from "react-router-dom";

// function MenuBar({ setPage }) {
//   const navigate = useNavigate();

//   const handleWater = () => {
//     navigate("/watersystem");
//   };
//   const handleDashboard = () => {
//     navigate("/");
//   };
//   const handleTemperature = () => {
//     navigate("/tempsystem");
//   };
//   const handleLight = () => {
//     navigate("/lightsystem");
//   };

//   return (
//     <div className="menu-bar">
//       <ul>
//         <li onClick={() => handleDashboard()}>Dashboard</li>
//         <li onClick={() => handleWater()}>Water System</li>
//         <li onClick={() => handleTemperature()}>Temperature System</li>
//         <li onClick={() => handleLight()}>Lightning System</li>
//       </ul>
//     </div>
//   );
// }

// export default MenuBar;

import React, { useState, useContext } from "react";
import "../styles/styles.css";
import { Link, Outlet, NavLink } from "react-router-dom";

import { useNavigate } from "react-router-dom";

function NavAndHeder() {

  return (
    <div class="wrapper">
      <nav id="sidebar">
        <div class="sidebar-header">
          <h3>Indoor Garden</h3>
        </div>
        <ul class="list-unstyled components">
          <li class="active">
            <a
              href="/"
              data-toggle="collapse"
              aria-expanded="false"
              class="dropdown-toggle"
            >
              Home
            </a>
          </li>
          <li>
            <a href="/watersystem">Water</a>
          </li>
          <li>
            <a
              href="#pageSubmenu"
              data-toggle="collapse"
              aria-expanded="false"
              class="dropdown-toggle"
            >
              Pages
            </a>
          </li>
          <li>
            <a href="temperature">Temperature</a>
          </li>
          <li>
            <a href="lightning">lightning</a>
          </li>

          <li>
            <a href="#">Contact</a>
          </li>
        </ul>
      </nav>
    </div>
  );
}

export default NavAndHeder;
