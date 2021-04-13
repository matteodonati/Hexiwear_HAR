# Human Activity Recognition on Hexiwear

```bash
mbed config root .
```

```bash
mbed deploy
```

```python
python -c 'import fileinput, glob;
for filename in glob.glob("mbed-os/tools/profiles/*.json"):
  for line in fileinput.input(filename, inplace=True):
    print(line.replace("\"-std=gnu++98\"","\"-std=c++11\", \"-fpermissive\""))'
```

```bash
mbed compile -m HEXIWEAR -t GCC_ARM
```

```bash
./BUILD/HEXIWEAR/GCC_ARM/application.bin
```