# Emergent_Integration

## Build:

mkdir build

cd build

cmake ..

make

## Execute:

VSOMEIP_CONFIGURATION=../config/server-config.json ./TemperatureServer

VSOMEIP_CONFIGURATION=../config/client-config.json ./WeatherClient

