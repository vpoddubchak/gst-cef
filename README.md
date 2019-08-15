

# CEF Plugin

### Requirements Linux
* libgstreamer1.0-dev
* libgstreamer-plugins-base1.0-dev
* build-essential
* CMake >= 3.8

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


### Testing

```
gst-launch-1.0 cef url="https://google.com" width=1280 height=720 ! autovideosink
```
