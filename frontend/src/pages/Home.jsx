import { Link } from "react-router-dom";
import Menu from "./Menu";

function Home() {
  return (
    <div>
      <Menu />

      <div
        className="bg-cover h-screen flex items-center justify-center bg-white"
        style={{ backgroundImage: "url('src/assets/homepagefade.png')" }}
      >
        <div className="p-8 rounded-lg text-blue-900 text-center">
          <h1 className="text-8xl font-bold mb-4">
            Bun venit la HealthGuard Wear.
          </h1>
          <h2 className="text-6xl font-bold mb-20 text-blue-800">
            Cum te putem ajuta?
          </h2>
          <Link
            to="/login"
            className="bg-blue-500 hover:bg-blue-600 text-white py-3 px-6 rounded mt-20 "
          >
            Intră în cont
          </Link>
        </div>
      </div>
    </div>
  );
}

export default Home;
