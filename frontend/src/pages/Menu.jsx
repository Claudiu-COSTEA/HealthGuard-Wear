import React from "react";

function Menu() {
  return (
    <div className="bg-blue-500 text-white py-2 px-4 rounded-lg fixed top-0 left-0 w-full">
      <div className="max-w-7xl mx-auto flex justify-between items-center">
        <div className="text-lg font-semibold">HealthGuard Wear</div>
        <div className="flex space-x-4">
          <a href="#contact" className="hover:text-gray-300">
            Contact
          </a>
          <a href="#help" className="hover:text-gray-300">
            Help
          </a>
        </div>
      </div>
    </div>
  );
}

export default Menu;
