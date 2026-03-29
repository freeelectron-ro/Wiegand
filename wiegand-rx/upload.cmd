#list boards: arduino-cli board list

arduino-cli upload -p /dev/ttyACM0 --input-dir wrx/build --fqbn arduino:avr:uno wrx
#arduino-cli upload -p /dev/ttyUSB0 --input-dir wrx/build --fqbn arduino:avr:pro wrx