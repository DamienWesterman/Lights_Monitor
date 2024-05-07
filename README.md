# Purpose
This is Damien Westerman's solution for [Josh.ai's C++ coding challenge](https://github.com/jstarllc/JoshCodingChallenge).
# Usage
This solution was developed on Ubuntu and should work for Linux using g++ with C++14. Build system not tested on Windows/Mac and may not work without additional configuration. To build and run the program, navigate to the main directory and run `make run`. Other make options can be seen with `make help`. The final executable is compiled into `lights_monitor`. It does not need any arguments, but the usage can be seen by running `./lights_monitor -h`. Ensure that the [Lights Simulator](https://github.com/jstarllc/JoshCodingChallenge/releases/latest) is running to make proper use of this solution.
# Implementation
This solution makes use of the suggested header only libraries:
* [C++11 header-only HTTP/HTTPS client library](https://github.com/yhirose/cpp-httplib)
* [JSON for Modern C++](https://github.com/nlohmann/json)
* [Simple C++ command line parser](https://github.com/FlorianRappl/CmdParser)
<!-- end of the list -->
Simple docs can be found in the [doc folder](https://github.com/DamienWesterman/Lights_Monitor/tree/master/docs). This program queries the server at startup and saves all the existing lights. Then every second, it polls the server for any changes, printing and updating internal Light objects as necessary.
## Classes
Both classes take care to check all jsons and server responses (or lack thereof) and handle them gracefully.
### Light 
The Light class is responsible for holding the information relating to a simulated light as well as checking for and printing any changes in state.
### ServerClient 
The ServerClient class is an abstraction around the http library for interacting with and interpretting the server's responses. 
## Algorithm
Internally, the Light objects are held in a hash map (unordered_map) using their ID as key for quick access. A temporary hash map is created every iteration of checking the server, and initially swapped with the contents of the saved Lights. With the server's results, it will check if a light exists and if it does, it will check if the light was updated. The light is then added to the saved lights map, and removed from the temp map. If a light was not in temp map, it must be new and is added to saved lights map. At the end of checking the server's responses, any remaining lights in temp map must have been deleted and logged as deleted, and not put into the saved map. This keeps the time and space complexity of this algorithm at O(n).
# Thank you
This was a fun challenge. Feel free to reach out at damien.westerman@outlook.com.

