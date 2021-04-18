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
- Each element of the convolutional layers' output matrix is a vector of length <img src="svgs/d612794104394c6d9670a9dbcc29b251.svg?invert_in_darkmode" align=middle width=134.35471994999997pt height=22.465723500000017pt/>, where <img src="svgs/e199a3f3e8cbb1a900d72c03cfbc1883.svg?invert_in_darkmode" align=middle width=13.33055954999999pt height=22.465723500000017pt/> is the length of the specific input vectors and <img src="svgs/c414c0b5764ffbe3e5c3b94c2b5697a2.svg?invert_in_darkmode" align=middle width=162.22786799999997pt height=24.65753399999998pt/> is the choosen kernel size constant;
- Each element of the pooling layers' output matrix is a vector of length <img src="svgs/bb78f6da7ec4f4aec4a3a2c962699bcf.svg?invert_in_darkmode" align=middle width=54.066886499999995pt height=24.65753399999998pt/>, where <img src="svgs/0bf57f275046228f98c5e32bb92f7ead.svg?invert_in_darkmode" align=middle width=159.92763929999998pt height=24.65753399999998pt/> is the choosen pool size constant;
- The first fully connected layer, <img src="svgs/929ed909014029a206f344a28aa47d15.svg?invert_in_darkmode" align=middle width=17.73978854999999pt height=22.465723500000017pt/>, is composed of <img src="svgs/1526e5aded7ca1842ff9ec0baafda054.svg?invert_in_darkmode" align=middle width=59.591198699999985pt height=22.465723500000017pt/> neurons;
- The second fully connected layer, <img src="svgs/4327ea69d9c5edcc8ddaf24f1d5b47e4.svg?invert_in_darkmode" align=middle width=17.73978854999999pt height=22.465723500000017pt/>, is composed of <img src="svgs/380e6fd85b60a4f7433079072e4276db.svg?invert_in_darkmode" align=middle width=43.06147724999999pt height=22.465723500000017pt/> neurons.

## Training and validation

## Model creation