## Dataset

The `dataset/raw_data.csv` file contains 1,800,000 raw samples obtained by sampling from the two sensors at <img src="svgs/83b7f25a9600297d9d0e80a554e48126.svg?invert_in_darkmode" align=middle width=39.80600909999999pt height=22.465723500000017pt/>. Each sample is a tuple of seven elements:

<p align="center">
  <img src="svgs/451a52815ff570363d97588e4241b90e.svg?invert_in_darkmode" align=middle width=200.14085189999997pt height=26.085962100000025pt/>
</p>

In particular:

- <img src="svgs/c37d977adcc59115176465022970836a.svg?invert_in_darkmode" align=middle width=104.99908814999998pt height=26.085962100000025pt/>, are the accelerometer values sampled at time <img src="svgs/4f4f4e395762a3af4575de74c019ebb5.svg?invert_in_darkmode" align=middle width=5.936097749999991pt height=20.221802699999984pt/>;
- <img src="svgs/19a05c4e32ba41a1aab1f98c0b3f3848.svg?invert_in_darkmode" align=middle width=104.74029059999998pt height=26.085962100000025pt/>, are the gyroscope values sampled at time <img src="svgs/4f4f4e395762a3af4575de74c019ebb5.svg?invert_in_darkmode" align=middle width=5.936097749999991pt height=20.221802699999984pt/>;
- <img src="svgs/8b1889b619bf76febc10748bb662486c.svg?invert_in_darkmode" align=middle width=10.19413724999999pt height=26.085962100000025pt/>, is the label associated with the <img src="svgs/cff16106492e4d77e402f96ebdba8e5d.svg?invert_in_darkmode" align=middle width=12.67127234999999pt height=26.085962100000025pt/> sample.

The neural network codomain is represented by the following set of activities:

<p align="center">
  <img src="svgs/e15cecf2f7e077bfd13c108ac9f21e86.svg?invert_in_darkmode" align=middle width=396.14441789999995pt height=50.37427230000001pt/>
</p>

Therefore, <img src="svgs/f98f72b6f242892bf537af7359380930.svg?invert_in_darkmode" align=middle width=83.52962969999999pt height=26.085962100000025pt/>.

## Neural network

The specific convolutional neural network is composed of the following layers:

- <img src="svgs/59eade25fc346af563e897d3eb8e1651.svg?invert_in_darkmode" align=middle width=14.771756999999988pt height=15.296829900000011pt/>, <img src="svgs/34b59bc9c01ed8321674afcb30320f74.svg?invert_in_darkmode" align=middle width=14.771756999999988pt height=15.296829900000011pt/>, <img src="svgs/69b95110f4cd6a8dd9e728f29c94cc36.svg?invert_in_darkmode" align=middle width=14.771756999999988pt height=15.296829900000011pt/>, which are the convolutional layers. Each of these layers uses <img src="svgs/d6328eaebbcd5c358f426dbea4bdbf70.svg?invert_in_darkmode" align=middle width=15.13700594999999pt height=22.465723500000017pt/> kernels to filter the received input;
- <img src="svgs/968584ab74f9fd823ce245a469682401.svg?invert_in_darkmode" align=middle width=34.84590944999999pt height=22.465723500000017pt/>, <img src="svgs/5760f187ce6326abd9a762a190569e01.svg?invert_in_darkmode" align=middle width=34.84590944999999pt height=22.465723500000017pt/>, <img src="svgs/b8c6e1bb7a92cddb5d91be9300da6618.svg?invert_in_darkmode" align=middle width=34.84590944999999pt height=22.465723500000017pt/>, which are the pooling layers. Each of these layers reduces the size of the received input;
- <img src="svgs/929ed909014029a206f344a28aa47d15.svg?invert_in_darkmode" align=middle width=17.73978854999999pt height=22.465723500000017pt/>, <img src="svgs/4327ea69d9c5edcc8ddaf24f1d5b47e4.svg?invert_in_darkmode" align=middle width=17.73978854999999pt height=22.465723500000017pt/>, which are fully connected layers.

The overall structure of the network is the following:

<p align="center">
  <img width="650" src="svgs/convolutional_neural_network.svg" />
</p>

In particular:

- Each convolutional layer uses a set of <img src="svgs/ed311fe6d679fe024f6701fc8f158e65.svg?invert_in_darkmode" align=middle width=53.49304949999999pt height=22.465723500000017pt/> kernels;
- Each element of the convolutional layers' output matrix is a vector of length <img src="svgs/d612794104394c6d9670a9dbcc29b251.svg?invert_in_darkmode" align=middle width=134.35471994999997pt height=22.465723500000017pt/>, where <img src="svgs/e199a3f3e8cbb1a900d72c03cfbc1883.svg?invert_in_darkmode" align=middle width=13.33055954999999pt height=22.465723500000017pt/> is the length of the specific input vectors and <img src="svgs/dc579bae2bd28702ec36b89d4ee9f9d1.svg?invert_in_darkmode" align=middle width=159.48808259999998pt height=24.65753399999998pt/> is the chosen kernel size constant;
- Each element of the pooling layers' output matrix is a vector of length <img src="svgs/bb78f6da7ec4f4aec4a3a2c962699bcf.svg?invert_in_darkmode" align=middle width=54.066886499999995pt height=24.65753399999998pt/>, where <img src="svgs/0f2b4587612a45ec41fc05bac6461ca6.svg?invert_in_darkmode" align=middle width=157.18785555pt height=24.65753399999998pt/> is the chosen pool size constant;
- The first fully connected layer, <img src="svgs/929ed909014029a206f344a28aa47d15.svg?invert_in_darkmode" align=middle width=17.73978854999999pt height=22.465723500000017pt/>, is composed of <img src="svgs/1526e5aded7ca1842ff9ec0baafda054.svg?invert_in_darkmode" align=middle width=59.591198699999985pt height=22.465723500000017pt/> neurons;
- The second fully connected layer, <img src="svgs/4327ea69d9c5edcc8ddaf24f1d5b47e4.svg?invert_in_darkmode" align=middle width=17.73978854999999pt height=22.465723500000017pt/>, is composed of <img src="svgs/380e6fd85b60a4f7433079072e4276db.svg?invert_in_darkmode" align=middle width=43.06147724999999pt height=22.465723500000017pt/> neurons.

## Training and validation

## Model creation