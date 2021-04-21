## Data structures

The main data structures are the following `float` arrays, defined in the `data.c` file:

- `accel_data`, which is an array of size <img src="svgs/aea3066e131899c6c8c7507a4a7fe991.svg?invert_in_darkmode" align=middle width=52.968029399999985pt height=21.18721440000001pt/> and stores the values sampled from the accelerometer;
- `gyro_data`, which is an array of size <img src="svgs/aea3066e131899c6c8c7507a4a7fe991.svg?invert_in_darkmode" align=middle width=52.968029399999985pt height=21.18721440000001pt/> and stores the values sampled from the gyroscope;
- `model_input`, which is an array of size <img src="svgs/4f984a23f833e67c6666c78106bd4f7b.svg?invert_in_darkmode" align=middle width=52.968029399999985pt height=21.18721440000001pt/> and implements the sliding window structure. Every element of this array has the following structure:

   ```
   model_input[i] = {a_x, a_y, a_z, g_x, g_y, g_z};
   ```
   
   where `a_x, a_y, a_z` are the accelerometer values sampled at a specific time $t$ and `g_x, g_y, g_z` are the gyroscope values sampled at the same time $t$.

## Threads

## Workflow

<p align="center">
  <img width="650" src="svgs/application_1.svg" />
</p>
<p align="center">
  <img width="465" src="svgs/application_2.svg" />
</p>