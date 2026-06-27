# Software raytracer (Now modern* C++)

Port from my [Go implementation](https://github.com/alvinobarboza/go-ray-demo) with some tweaks. The goal here is to use this
as part of my learning process with C++.

* Camera movement is now using mouse(as expected anywhere)
* Sky color: blend between 3 color to simulate sky scattering.
    * Just linear interpolating colors from 0 to 0.5 and 0.5 to 1.(Gray -> Blue -> Darkblue)
* Colors are now Vec3, only convert them at the very end.
* New refraction formular, with better visual results(thanks roblox forum**)
  * Still not considering medium, so the refraction doesn't take into account the inner part of the object. (Visually incorrect compared to real world)
* Working on multithread...

# Screenshots

## Single threaded implementation

![frame](/single_threaded.png?raw=true 'frame')

