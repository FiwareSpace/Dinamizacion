/**
 * Application name
 */
const char APP_NAME[] = "RESPIRA";

/**
 * FIWARE settings
 */
const char FIWARE_SERVER[] = "calidadmedioambiental.org";

// NGSI setings
const uint16_t FIWARE_QRY_PORT = 80; // NGSI entity query port
const char FIWARE_SERVICE[] = "openiot";
const char FIWARE_SERVICE_PATH[] = "/4x4ei"; // Prueba Miguel

// UltraLight setings
const uint16_t FIWARE_UL_PORT = 80; //7896;  // UltraLight port
const char FIWARE_APIKEY[] = "f3ps82t2qhqypQI25ivUq8yQZm"; // Prueba Miguel

/**
 * Sampling interval in msec
 */
const uint32_t SAMPLING_INTERVAL = 10000; // 10 sec

/**
 * Transmission interval in msec
 */
const uint32_t TX_INTERVAL = 20000; // 20 sec

/**
 * Factor de corrección lecutras NO2
 */
float factor_correccion = 0.18;
