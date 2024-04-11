function Home() {
  return (
    <div>
      <div class="bg-blue-500 text-white py-2 px-4 rounded-lg fixed top-0 left-0 w-full">
        <div class="max-w-7xl mx-auto flex justify-between items-center">
          <div class="text-lg font-semibold">HealthGuard Wear</div>
          <div class="flex space-x-4">
            <a href="#contact" class="hover:text-gray-300">
              Contact
            </a>
            <a href="#help" class="hover:text-gray-300">
              Help
            </a>
          </div>
        </div>
      </div>

      <div class="bg-cover h-screen flex items-center justify-center bg-white">
        <div class="p-8 rounded-lg text-blue-900 text-center">
          <h1 class="text-8xl font-bold mb-4">
            Bun venit la HealthGuard Wear.
          </h1>
          <h2 class="text-6xl font-bold mb-4 text-blue-800">
            Cum te putem ajuta?
          </h2>
          <button class="bg-blue-500 hover:bg-blue-600 text-white py-3 px-6 rounded mt-20">
            Intră în cont
          </button>
        </div>
      </div>
    </div>
  );
}

export default Home;
