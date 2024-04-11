function Login() {
  return (
    <div class="bg-cover h-screen flex items-center justify-center bg-white login-bg">
      <div class="p-8 rounded-lg text-blue-800 text-center max-w-xl mx-auto">
        <h1 class="text-3xl font-bold mb-4">Intrare în Cont</h1>
        <form>
          <div class="mb-6">
            <label
              class="block text-gray-700 text-sm font-bold mb-2"
              for="username"
            >
              Nume Utilizator
            </label>
            <input
              class="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
              id="username"
              type="text"
              placeholder="Nume Utilizator"
            />
          </div>
          <div class="mb-6">
            <label
              class="block text-gray-700 text-sm font-bold mb-2"
              for="password"
            >
              Parolă
            </label>
            <input
              class="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
              id="password"
              type="password"
              placeholder="**********"
            />
          </div>
          <div class="mb-6">
            <div class="flex justify-center">
              <button class="bg-blue-500 hover:bg-blue-600 text-white py-3 px-6 rounded">
                Login
              </button>
            </div>
          </div>
        </form>
      </div>
    </div>
  );
}

export default Login;
