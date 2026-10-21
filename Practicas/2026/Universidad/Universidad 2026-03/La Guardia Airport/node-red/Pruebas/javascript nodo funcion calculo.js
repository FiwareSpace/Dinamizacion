let data = context.get('data') || {
    ax: 0, ay: 0, az: 9.81,
    gz: 0,
    yaw: 0,
    dist: 0,
    lastTime: Date.now(),
    offsetPitch: 0,
    offsetRoll: 0
};

// --- BOTÓN TARA ---
if (msg.topic === "calibrar") {
    let currentPitch = Math.atan2(data.ax, Math.sqrt(data.ay*data.ay + data.az*data.az)) * (180 / Math.PI);
    let currentRoll = Math.atan2(data.ay, data.az) * (180 / Math.PI);
    
    data.offsetPitch = currentPitch;
    data.offsetRoll = currentRoll;
    data.yaw = 0;
    
    context.set('data', data);
    
    return [
        { payload: "0.00", topic: "Cabeceo" },
        { payload: "0.00", topic: "Alabeo" },
        { payload: "0.00", topic: "Guiñada" },
        { payload: data.dist.toFixed(1), topic: "Distancia" }
    ];
}

// --- RECEPCIÓN DE DATOS ---
let p = parseFloat(msg.payload);

if (msg.topic === "la_guardia/aceleracion/x") data.ax = p;
else if (msg.topic === "la_guardia/aceleracion/y") data.ay = p;
else if (msg.topic === "la_guardia/aceleracion/z") data.az = p;
else if (msg.topic === "la_guardia/giroscopio/z") data.gz = p;
else if (msg.topic === "la_guardia/distancia") {
    data.dist = p;
    context.set('data', data);
    return [null, null, null, { payload: p.toFixed(1), topic: "Distancia" }];
}
else return null;

// --- GUIÑADA (Yaw) ---
let now = Date.now();
let dt = (now - data.lastTime) / 1000.0;
data.lastTime = now;

let gz_deg = data.gz * (180 / Math.PI);
if (Math.abs(gz_deg) > 1.0) {
    data.yaw += (gz_deg * dt);
}
if (data.yaw > 180) data.yaw -= 360;
else if (data.yaw < -180) data.yaw += 360;

// --- CABECEO Y ALABEO ---
let rawPitch = Math.atan2(data.ax, Math.sqrt(data.ay*data.ay + data.az*data.az)) * (180 / Math.PI);
let rawRoll = Math.atan2(data.ay, data.az) * (180 / Math.PI);

let finalPitch = rawPitch - data.offsetPitch;
let finalRoll = rawRoll - data.offsetRoll;

// NUEVO: Normalizador para evitar el salto a -300º
if (finalPitch > 180) finalPitch -= 360;
else if (finalPitch < -180) finalPitch += 360;

if (finalRoll > 180) finalRoll -= 360;
else if (finalRoll < -180) finalRoll += 360;

context.set('data', data);

return [
    { payload: finalPitch.toFixed(2), topic: "Cabeceo" },
    { payload: finalRoll.toFixed(2), topic: "Alabeo" },
    { payload: data.yaw.toFixed(2), topic: "Guiñada" },
    null
];