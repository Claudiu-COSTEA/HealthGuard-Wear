import { Link } from "react-router-dom";
import Menu from "./Menu";

function Login() {
  return (
    <div>
      <Menu />
      <div
        className="bg-cover h-screen flex items-center justify-center bg-white"
        style={{ backgroundImage: "url('src/assets/login-background.PNG')" }}
      >
        <div className="bg-cover h-screen flex items-center justify-center bg-white login-bg m-0">
          {" "}
          <div className="p-8 rounded-lg text-blue-800 text-left mx-auto">
            <div style={{ width: "488px", height: "283px" }}>
              <h1 className="text-3xl font-bold mb-10 text-center">
                Intrare în Cont
              </h1>

              <form className="w-full">
                <div className="mb-10">
                  <label
                    className="block text-gray-700 text-sm font-bold mb-2"
                    htmlFor="username"
                  >
                    Nume Utilizator
                  </label>
                  <input
                    className="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                    id="username"
                    type="text"
                    placeholder="Nume Utilizator"
                  />
                </div>
                <div className="mb-10">
                  <label
                    className="block text-gray-700 text-sm font-bold mb-2"
                    htmlFor="password"
                  >
                    Parolă
                  </label>
                  <input
                    className="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
                    id="password"
                    type="password"
                    placeholder="**********"
                  />
                </div>
                <div className="mb-10">
                  <div className="flex justify-center w-full">
                    <Link to="/startpage">
                      <button className="bg-blue-500 hover:bg-blue-600 text-white py-2 px-3 rounded w-full">
                        Login
                      </button>
                    </Link>
                  </div>
                </div>
              </form>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}

export default Login;
