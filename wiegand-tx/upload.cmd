#list boards: arduino-cli board list



#arduino-cli upload -p /dev/ttyACM0 --input-dir wtx/build --fqbn arduino:avr:uno wtx
arduino-cli upload -p /dev/ttyUSB0 --input-dir wtx/build --fqbn arduino:avr:pro wtx