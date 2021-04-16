# Human Activity Recognition on Hexiwear

This application is an example of neural networks usage on a microcontroller based device such as Hexiwear. In particular, a specific convolutional neural network has been trained and used to create a human activity recognition application which is able to classifiy a certain activity.

![Hexiwear_HAR](https://user-images.githubusercontent.com/57544668/115050006-9cc33f80-9edb-11eb-8de6-0d8e4ced8e1c.png)

## Hexiwear

Hexiwear is a wearable IoT, microcontroller based device which can be used either as a smartwatch or as a standard development platform thanks to its docking station and the multiple expansion boards available for this product.

It is packed with two Arm Cortex-M based microcontrollers and multiple sensors. For this specific application the following hardware has been used:

- NXP Kinetis K64x MCU (Arm Cortex-M4, 120MHz, 1MB Flash, 256kB SRAM);
- NXP FXOS8700CQ (triaxial accelerometer);
- NXP FXAS21002 (triaxial gyroscope).

More about Hexiwear: [(1)](https://www.mikroe.com/hexiwear), [(2)](https://github.com/MikroElektronika/HEXIWEAR).

## Mbed OS

Arm Mbed OS is an open source, easy-to-use operating system for IoT devices. This specific operating system allows developers to create custom firmwares for their embedded platforms and offers, for each supported device, a code repository in which developers can upload libraries and code examples.

Mbed OS supports Hexiwear by giving access to some of the most useful libraries for this device (i.e. hardware drivers).

More about Mbed OS: [(1)](https://os.mbed.com/mbed-os/), [(2)](https://github.com/ARMmbed/mbed-os), [(3)](https://os.mbed.com/platforms/Hexiwear/).

## TensorFlow Lite for Microcontrollers

TensorFlow Lite for Microcontrollers is designed to run machine learning models on microcontrollers and other devices with only few kB of memory. It doesn't require operating system support but, in order to simplify the development of this application, Mbed OS has been used.

More about TensorFlow Lite for Microcontrollers: [(1)](https://www.tensorflow.org/lite/microcontrollers), [(2)](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro).

## Requirements

- [Arm Mbed CLI 1](https://os.mbed.com/docs/mbed-os/v6.9/build-tools/mbed-cli-1.html).

## Usage

In order to compile the application and produce the binary `.bin` file follow the steps listed below:

1. Clone the GitHub project:

   ```
   git clone https://github.com/MatteoDonati/Hexiwear_HAR.git
   ```

2. Move to the `application` directory:

   ```
   cd application
   ```

3. Configure the root directory of the Mbed project:

   ```
   mbed config root .
   ```

4. Download the dependencies:

   ```
   mbed deploy
   ```

5. Run the following Python snippet to modify the Mbed configuration files so that it uses `C++11`:

   ```python
   python -c 'import fileinput, glob;
   for filename in glob.glob("mbed-os/tools/profiles/*.json"):
     for line in fileinput.input(filename, inplace=True):
       print(line.replace("\"-std=gnu++98\"","\"-std=c++11\", \"-fpermissive\""))'
   ```

6. Compile the application:

   ```
   mbed compile -m HEXIWEAR -t GCC_ARM
   ```

7. Find and flash the produced binary file:

   ```
   ./BUILD/HEXIWEAR/GCC_ARM/application.bin
   ```

## License

[MIT License](https://github.com/MatteoDonati/Hexiwear_HAR/blob/main/LICENSE).
