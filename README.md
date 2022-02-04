# Lora-Firmware
This project is prototype project for STM32WL Lora device. <br />

On here, test several functions such as:

1.- the MCU wakeup every 15 minutes,. <br />
2.- MCU takes the values of vibration x,y,z, of accelerometer, using 5Khz and 2g configuration, The values are Stored in a matrix "Vibration"(4096 Datas per axes).<br />
3.- Calc Furier Matrix of "Vibration" of each axes (that is all)<br />
4.- Takes the RMS Sound from microphone store in the matrix "SOUND"" (1024 datas), configured in 20KHZ reading speed.<br />
5.- Calc Furier matrix of "Sound" (that is all)<br />
7.- Get temperature from NPT. (temp1)<br />
8.- Get temperature from DS18B20. (temp2)<br />
6.- Send in the payload the (some data Vibration) + (some data Sound) + temp1 + temp2 to LoraWAN TTN network.<br />
7.- No wait answer from lorawan server<br />
8.- sleep for 15 minutes<br />


