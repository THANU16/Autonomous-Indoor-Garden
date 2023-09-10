import React from "react";
import "../styles/styles.css"; // Import the CSS

function MenuBar({ setPage }) {
  const handlePageChange = (page) => {
    setPage(page);
  };

  return (
    <div className="menu-bar">
      <ul>
        <li onClick={() => handlePageChange("dashboard")}>Dashboard</li>
        <li onClick={() => handlePageChange("watersystem")}>Water System</li>
        <li onClick={() => handlePageChange("temperaturesystem")}>
          Temperature System
        </li>
        <li onClick={() => handlePageChange("lightningsystem")}>
          Lightning System
        </li>
      </ul>
    </div>
  );
}

export default MenuBar;
