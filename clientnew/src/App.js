import React from "react";
import Dashboard from "./components/Dashboard";
import WaterControl from "./components/WaterControl";
import "./styles/styles.css";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import MenuBar from "./components/Menubar";

function App() {
  return (
    <div className="app">
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Dashboard />} />
          <Route path="watersystem" element={<WaterControl />} />
        </Routes>
      </BrowserRouter>
      {/* <Dashboard /> */}
      <WaterControl />
    </div>
  );
}

export default App;
