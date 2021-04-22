## Data structures

The main data structures are the following `float` arrays, defined in the `data.c` file:

- `accel_data`, which is an array of size <img src="svgs/aea3066e131899c6c8c7507a4a7fe991.svg?invert_in_darkmode" align=middle width=52.968029399999985pt height=21.18721440000001pt/> and stores the values sampled from the accelerometer;
- `gyro_data`, which is an array of size <img src="svgs/aea3066e131899c6c8c7507a4a7fe991.svg?invert_in_darkmode" align=middle width=52.968029399999985pt height=21.18721440000001pt/> and stores the values sampled from the gyroscope;
- `model_input`, which is an array of size <img src="svgs/4f984a23f833e67c6666c78106bd4f7b.svg?invert_in_darkmode" align=middle width=52.968029399999985pt height=21.18721440000001pt/> and implements the sliding window structure. Every element of this array has the following structure:

   ```
   model_input[i] = {a_x, a_y, a_z, g_x, g_y, g_z};
   ```
   
   where `a_x, a_y, a_z` are the accelerometer values sampled at a specific time <img src="svgs/4f4f4e395762a3af4575de74c019ebb5.svg?invert_in_darkmode" align=middle width=5.936097749999991pt height=20.221802699999984pt/> and `g_x, g_y, g_z` are the gyroscope values sampled at the same time <img src="svgs/4f4f4e395762a3af4575de74c019ebb5.svg?invert_in_darkmode" align=middle width=5.936097749999991pt height=20.221802699999984pt/>.

## Threads

In order to continue sampling from the two sensors while running an inference through the specific neural network, two threads have been used:

- <img src="svgs/b1aadae6dafc7da339f61626db58e355.svg?invert_in_darkmode" align=middle width=16.15873379999999pt height=22.465723500000017pt/>, which is the thread that samples from the sensors at 50Hz and stores the sampled values inside the `accel_data` and `gyro_data` buffers;
- <img src="svgs/b48cd4fc1cc1b8c602c81734763b31f0.svg?invert_in_darkmode" align=middle width=16.15873379999999pt height=22.465723500000017pt/>, which is the thread that copies a specific portion of the aforementioned buffers into `model_input`, runs the inference and updates the display.

## Workflow

The following picture shows the workflow of the specific application:

<p align="center">
  <img width="650" src="svgs/application_1.svg" />
</p>
<p align="center">
  <img width="465" src="svgs/application_2.svg" />
</p>

In particular, the <img src="svgs/44bc9d542a92714cac84e01cbbb7fd61.svg?invert_in_darkmode" align=middle width=8.68915409999999pt height=14.15524440000002pt/> and <img src="svgs/3cf4fbd05970446973fc3d9fa3fe3c41.svg?invert_in_darkmode" align=middle width=8.430376349999989pt height=14.15524440000002pt/> buffers correspond to the `accel_data` and `gyro_data` buffers defined in the `data.c` file, while the <img src="svgs/84c95f91a742c9ceb460a83f9b5090bf.svg?invert_in_darkmode" align=middle width=17.80826024999999pt height=22.465723500000017pt/> window corresponds to the `model_input` window.