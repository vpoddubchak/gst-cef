

# CEF Plugin

### Requirements Linux
* libgstreamer1.0-dev
* libgstreamer-plugins-base1.0-dev
* build-essential
* CMake >= 3.8 
Update cmake for ubuntu 16:
```
version=3.15
build=2
mkdir ~/temp
cd ~/temp
wget https://cmake.org/files/v$version/cmake-$version.$build.tar.gz
tar -xzvf cmake-$version.$build.tar.gz
cd cmake-$version.$build/

./bootstrap
make -j4
sudo make install

cmake --version
```



```
mkdir build && cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release .. -DUSE_SANDBOX=0
sudo make
```

# running it on linux
```
export LD_LIBRARY_PATH=/usr/local/cef/lib
export DISPLAY=:0
Xvfb :0 -screen 0 1280x720x16 &
```
The .exe file that launches the gstreamer pipeline must be in the same directory as the cef resources.  Therefore, copy gst-launch-1.0 into the build/dist directory.
```
cp `which gst-launch-1.0` Release/
```

### Testing

```
GST_PLUGIN_PATH=$PWD/Release:$GST_PLUGIN_PATH Release/gst-launch-1.0 -v gstcef url="https://google.com" width=1280 height=720 ! queue ! videoconvert ! autovideosink
```
