#ifndef _FIWARE_H
#define _FIWARE_H

#include <stdarg.h>
#include <Arduino.h>
#include <HTTPClient.h>

#define FIWARE_SERVER_STRING_MAXLEN    32
#define FIWARE_SERVER_RESPONSE_MAXLEN  512
#define FIWARE_CMD_MAX_LEN             128
#define FIWARE_CMD_CONFIG             "config"


class FIWARE
{
  private:   
    /**
     * FIWARE server URL
     */
    char server[FIWARE_SERVER_STRING_MAXLEN];

    /**
     * FIWARE UltraLight API port
     */
    uint16_t ulPort;

    /**
     * FIWARE entity API port
     */
    uint16_t queryPort;

    /**
     * FIWARE service
     */
    char service[FIWARE_SERVER_STRING_MAXLEN];

    /**
     * FIWARE service path
     */
    char servicePath[FIWARE_SERVER_STRING_MAXLEN];

    /**
     * Type of device
     */
    char deviceType[FIWARE_SERVER_STRING_MAXLEN];
    
    /**
     * Ultralight IoT agent API key
     */
    char apiKey[FIWARE_SERVER_STRING_MAXLEN];
        
  public:
    /**
     * Class constructor
     * 
     * @param fiwareServer FIWARE server URL or IP address
     * @param ulP Port for UltraLight API     
     * @param apiK UltraLight API key
     * @param qryP Port for NGSI entity API
     * @param serv FIWARE service
     * @param servPath FIWARE service path
     * @param devType Device type
     */
    inline FIWARE(const char *fiwareServer, const uint16_t ulP, const char *apiK, const uint16_t qryP = 0, const char* serv=NULL, const char* servPath=NULL, const char* devType= "RESPIRA")
    {
      strcpy(server, fiwareServer);
      ulPort = ulP;
      queryPort = qryP;
      strcpy(apiKey, apiK);
      strcpy(service, serv);
      strcpy(servicePath, servPath);
      strcpy(deviceType, devType);
    }

    /**
     * send
     * 
     * Send attribute value
     * 
     * @param entity Entity name
     * @param attributes Attributes following UltraLight format (attr1|val1#attr1|val2...)
     * 
     * @return True in case of success. Return false otherwise
     */
    inline bool send(char *entity, char *attributes)
    {
      HTTPClient http;
      
      bool ret = false;
      
      // Make a HTTP request:
      char url[128];
      sprintf(url, "http://%s:%d/iot/d?k=%s&i=%s&getCmd=1", server, ulPort, apiKey, entity);
      Serial.print("Dispositivo: ");
      Serial.println(entity);
               
      http.begin(url);
      http.addHeader("Content-Type", "text/plain");
      int httpCode = http.POST(attributes);

      Serial.print("HTTP response: ");
      Serial.println(httpCode);
      
      if (httpCode == HTTP_CODE_OK)         
        ret = true;

      http.end();
      
      return ret;
    }

    /**
     * querySettings
     * 
     * Query configuration settings
     * 
     * @param settings JSON string received from CB
     * @param entity Entity name
     * 
     * @return True in case of success. Return false otherwise
     */
    inline bool querySettings(char *settings, char *entity)
    {
      HTTPClient http;
      
      bool ret = false;
      
      if ((service == NULL) || (queryPort == 0))
        return false;
        
      // Make a HTTP request:
      char url[256];
      sprintf(url, "http://%s:%d/v2/entities/%s:%s/attrs/config/value", server, queryPort, deviceType, entity);

      http.begin(url);
      http.addHeader("fiware-service", service);
      http.addHeader("fiware-servicepath", servicePath);
      int httpCode = http.GET();
     
      if (httpCode == HTTP_CODE_OK)
      {
        String payload = http.getString();

        Serial.println("Response from server:");
        Serial.println(payload);

        if (payload.length() < FIWARE_SERVER_RESPONSE_MAXLEN)
          payload.toCharArray(settings, payload.length() + 1);
       
        ret = true;
      }

      http.end();
      
      return ret;
    }
};
#endif
