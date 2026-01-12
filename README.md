## MiG 21 Flight Simulator with DirectX 8.0

Demo project for flight simulation of the legendary `MiG 21` military jet. It's from a long time ago when I was just starting with C++ and 3D graphics. Although the code and graphics look rudimentary, the flight dynamics is enough realistic. The project also includes a simplistic but robust collision detection system.   

## Model

[MiG-21SMT Fishbed-K](https://sketchfab.com/3d-models/mig-21smt-fishbed-k-8cf77a2b596442778fa957a7a71c0cc4) by `Tim Samedov`.

### Build
The project is compatible with `VS 2022`. It requires `DirectX 8 NuGet` package(just add it in `VS`).

### Keyboard controls

### commands
- engine start/stop: `I`
- flaps `take-off/landing/off`: `F` (back and forth cycling)
- throttle up/down: `W/S`
- pitch `up/down`: arrows `down/up`
- roll `left/right`: arrows `left/right`
- yaw `left/right`: `</>`

### view
- cockpit: `F1`
- cockpit dynamic view: `F2` (erroneous)
- cinematic: `F3`

### Screenshots

![](./Screenshots/mig21_cockpit.png)
![](./Screenshots/mig21_exterior.png)

### [recording](./Screenshots/mig21_flight_720.mp4)