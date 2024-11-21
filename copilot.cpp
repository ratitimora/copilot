#include <google-maps-device-locator.h>
//#include <carloop.h>
#include "Particle.h"
#include "cellular_hal.h"

SerialLogHandler logHandler(LOG_LEVEL_INFO);

GoogleMapsDeviceLocator locator;

STARTUP(cellular_credentials_set("hologram", "", "", NULL));
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
ApplicationWatchdog wd(1800000, System.reset);

void locationCallback(float lat, float lon, float accuracy)
{
    Log.info("callback");
    Particle.publish("googlemaps-data", "{ \"device\": \"" + String(System.deviceID()) + "\", \"lat\":\"" + String(lat) + "\", \"lon\":\"" + String(lon) + "\", \"satellites\":\"" + String(accuracy) + "\"}", PRIVATE);    
}

void setup()
{
    locator.withSubscribe(locationCallback).withLocatePeriodic(3600);
}

void loop()
{
    locator.loop();
}
