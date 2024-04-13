import React from "react";

function StartPage() {
  return (
    <div className="flex flex-col justify-center items-center h-screen">
      {/* Mesajul de bun venit */}
      <h1 className="text-3xl font-bold mb-6">
        Bine ai venit în contul HealthGuard Wear
      </h1>

      {/* Rândul pentru coloane */}
      <div className="flex flex-wrap justify-center gap-8">
        {/* Coloana stângă */}
        <div className="flex flex-col justify-start items-start gap-7">
          <div className="text-xl font-medium">Activitatea de azi</div>
          <div className="border border-blue-400 rounded-lg p-4">
            <div>Faceți mișcare minim 3km pe zi</div>
          </div>
          <div className="border border-blue-400 rounded-lg p-4">
            {/* Calendarul sau orice alte componente pentru activitate */}
            Calendarul
          </div>
        </div>

        {/* Coloana dreaptă */}
        <div className="flex flex-col justify-start items-start gap-7">
          <div className="text-xl font-medium">Recomandările medicului</div>
          <div className="border border-blue-400 rounded-lg p-4">
            <div>Consumați minim 2 litri de apă pe zi</div>
          </div>
          <div className="border border-blue-400 rounded-lg p-4">
            <div>Evitați consumul uleiului de semințe</div>
          </div>
          <div className="border border-blue-400 rounded-lg p-4">
            {/* Orice alte recomandări medicale */}
            Ritmul cardiac
          </div>
        </div>
      </div>
    </div>
  );
}

export default StartPage;
