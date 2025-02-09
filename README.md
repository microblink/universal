# Universal: a header-only C++ template library for universal number arithmetic


| **System** | **Status** | **More information** |
|------------|------------|----------------------|
| [Codacy Code Quality](https://app.codacy.com/gh/stillwater-sc/universal/dashboard) | [![Codacy Badge](https://api.codacy.com/project/badge/Grade/25452f0319d34bc2a553cd1857d7dfae)](https://app.codacy.com/gh/stillwater-sc/universal?utm_source=github.com&utm_medium=referral&utm_content=stillwater-sc/universal&utm_campaign=Badge_Grade_Dashboard) | Code Quality Assessment |
| [FOSSA Status](https://app.fossa.com/projects/git%2Bgithub.com%2Fstillwater-sc%2Funiversal) | [![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fstillwater-sc%2Funiversal.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2Fstillwater-sc%2Funiversal?ref=badge_shield) | Open-source license dependency scanner |
| [Codeship](https://app.codeship.com/projects/286490)  | ![Codeship Status for stillwater-sc/universal](https://app.codeship.com/projects/22533f00-252a-0136-2ba6-6657a5454f61/status?branch=master) | Docker container build and regression |
| [GitHub Actions](https://github.com/stillwater-sc/universal/actions) | [![Build Status](https://github.com/stillwater-sc/universal/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/stillwater-sc/universal) | Latest Linux/MacOS/Windows builds and regression tests |
| [Development Branch](https://github.com/stillwater-sc/universal/actions) | ![Development Branch Status](https://github.com/stillwater-sc/universal/actions/workflows/cmake.yml/badge.svg?branch=v3.61) | Development Branch |
| [Regression Status](https://github.com/stillwater-sc/universal/actions) | ![Regression Status](https://github.com/stillwater-sc/universal/actions/workflows/cmake.yml/badge.svg?event=push) | Regression Status |
| [Code Coverage](https://coveralls.io) | [![Coverage Status](https://coveralls.io/repos/github/stillwater-sc/universal/badge.svg?branch=master)](https://coveralls.io/github/stillwater-sc/universal?branch=master) | Code coverage scanner |
| [Docker Pulls](https://hub.docker.com/r/stillwater/universal) | [![Docker Pulls](https://img.shields.io/docker/pulls/stillwater/universal.svg)](https://hub.docker.com/r/stillwater/universal) | Container pulls |
| [Awesome C++](https://github.com/fffaraz/awesome-cpp) | [![Awesome Cpp](https://awesome.re/mentioned-badge.svg)](https://github.com/fffaraz/awesome-cpp#math) | Awesome C++ Libraries |
| [JOSS Markdown](https://joss.theoj.org) | [![status](https://joss.theoj.org/papers/932fdfc2735a85422e4431f27ebfc0d0/status.svg)](https://joss.theoj.org/papers/932fdfc2735a85422e4431f27ebfc0d0)  | Journal of Open-Source Software paper |
-------------------------------


The goal of the Universal Numbers Library is to offer applications alternatives to IEEE floating-point for experimentation and development. In addition, tailoring the arithmetic types to the application's precision and dynamic range requirements enables a new level of mixed-precision algorithm development and optimization, particularly valuable for embedded applications that require high computational density and efficiency.
Deep Learning provides another example where alternative formats and precisions, such as half-floats and bfloats yield speed-ups of two to three orders of magnitude, making rapid innovation in AI possible.




The Universal Library is a ready-to-use header-only library that provides a plug-in replacement for native types and a low-friction environment to explore alternatives to IEEE floating-point in algorithms.

The basic use pattern is as simple as:

```code
#include <universal/number/posit/posit.hpp>

template<typename Real>
Real MyKernel(const Real& a, const Real& b) {
    return a * b;  // replace this with your kernel computation
}

constexpr double pi = 3.14159265358979323846;

int main() {
    using Real = sw::universal::posit<32,2>;  

    Real a = sqrt(2);
    Real b = pi;
    std::cout << "Result: " << MyKernel(a, b) << std::endl;  
}
```

The library contains fast implementations of special IEEE-754 formats that do not have universal hardware implementations across x86, ARM, POWER, RISC-V, and GPUs. Special formats such as quarter precision, `quarter`, half precision, `half`, or quad precision, `quad`, are provided, as well as vendor specific extensions, such as NVIDIA `TensorFloat`, Google's Brain Float, `bfloat16`, or TI DSP fixed-points, `fixpnt`. In addition to these often used specializations, *Universal* supports static and elastic integers, decimals, fixed-points, rationals, linear floats, tapered floats, logarithmic, interval and adaptive-precision integers and floats. There are example number system skeletons to get you started quickly if you desire to add your own.

## Communication channels

* [GitHub Issue](https://github.com/stillwater-sc/universal/issues): bug reports,
  feature requests, etc.
* [Forum](https://groups.google.com/u/1/g/unum-computing): discussion of alternatives to IEEE-754 for computational science.
* [Slack](https://fptalks.slack.com): online chats, discussions,
  and collaboration with other users, researchers and developers.

## Citation

Please cite [our work](https://arxiv.org/abs/2012.11011) if you use _Universal_.

```bib
@inproceedings{Omtzigt:2022,
  title={Universal: Reliable, Reproducible, and Energy-Efficient Numerics},
  author={E. Theodore L. Omtzigt and James Quinlan},
  booktitle={Conference on Next Generation Arithmetic},
  pages={100--116},
  year={2022},
  organization={Springer}
}

@article{Omtzigt2020,
    author    = {E. Theodore L. Omtzigt and Peter Gottschling and Mark Seligman and William Zorn},
    title     = {{Universal Numbers Library}: design and implementation of a high-performance reproducible number systems library},
    journal   = {arXiv:2012.11011},
    year      = {2020},
}
```

## Quick start

If you just want to experiment with the number system tools and test suites, and don't want to bother cloning and building the source code, there is a Docker container to get started:

```text
> docker pull stillwater/universal
> docker run -it --rm stillwater/universal bash
stillwater@b3e6708fd732:~/universal/build$ ls
CMakeCache.txt       Makefile      cmake-uninstall.cmake  playground  universal-config-version.cmake
CMakeFiles           applications  cmake_install.cmake    tests       universal-config.cmake
CTestTestfile.cmake  c_api         education              tools       universal-targets.cmake
```

## How to build

If you do want to work with the code, the universal numbers software library is built using cmake version v3.23. 
Install the latest [cmake](https://cmake.org/download).
There are interactive installers for MacOS and Windows. 
For Linux, a portable approach downloads the shell archive and installs it at /usr/local:

```text
> wget https://github.com/Kitware/CMake/releases/download/v3.23.1/cmake-3.23.1-Linux-x86_64.sh 
> sudo sh cmake-3.23.1-Linux-x86_64.sh --prefix=/usr/local --exclude-subdir
```

For Ubuntu, snap will install the latest cmake, and would be the preferred method:

```text
> sudo snap install cmake --classic
```

The Universal Library is a pure C++ template library without any further dependencies, even for the regression test suites,
to enable hassle-free installation and use.

Clone the GitHub repo, and you are ready to build the different components of the Universal library.  
The library contains tools for using integers, decimals, fixed-points, floats, posits, valids, and logarithmic
number systems. It includes educational programs that showcase simple use cases to familiarize yourself with
different number systems and application examples to highlight the use of other number systems to gain performance
or numerical accuracy. Finally, each number system offers its verification suite. 

The easiest way to become familiar with all the options in the build process is to fire up the CMake GUI (or ccmake if you are on a headless server). The CMake output will summarize which options have been set.  
The output will look something like this:

```text
$ git clone https://github.com/stillwater-sc/universal
$ cd universal
$ mkdir build
$ cd build
$ cmake ..
```

The build options are enabled/disabled as follows:

```text
> cmake -DBUILD_EDUCATION=OFF -DBUILD_NUMBER_POSITS=ON ..

```

After building, issue the command _make test_ to run the complete test suite of all the enabled components, 
as a regression capability when you are modifying the source code. This will take touch all the corners of the code.

```text
> git clone https://github.com/stillwater-sc/universal
> cd universal
> mkdir build
> cd build
> cmake ..
> make -j $(nproc)
> make test
```

For Windows and Visual Studio, there are `CMakePredefinedTargets` that accomplish the same tasks:

```text
    - ALL_BUILD will compile all the projects
    - INSTALL   will install the Universal library
    - RUN_TESTS will run all tests
```

![visual-studio-project](docs/img/visual-studio-project.png)

# Installation and usage

After cloning the library, building and testing it in your environment, you can install it via:

```text
> cd universal/build
> cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/your/installation/path
> cmake --build . --config Release --target install -- -j $(nproc)
```

or manually via the Makefile target in the build directory:

```text
> make -j $(nproc) install
```

The default install directory is `/usr/local` under Linux.  There is also an uninstall

```text
> make uninstall
```

If you want to use the number systems provided by Universal in your own project, 
you can use the following CMakeLists.txt structure:

```code
project("my-numerical-experiment")

find_package(UNIVERSAL CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/mymain.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} universal::universal)
```

## Controlling the build to include different components

The default build configuration will build the command line tools, a playground, educational and application examples.
If you want to build the full regression suite across all the number systems, use the following cmake command:

```text
cmake -DBUILD_ALL=ON ..
```

For performance, the build configuration can enable specific x86 instruction sets (SSE/AVX/AVX2). For example, if your processor supports the AVX2 instruction set, you can build the test suites and educational examples with the AVX2 flag turned on. This typically yields a 20% performance boost.

```text
cmake -DBUILD_ALL=on -DUSE_AVX2=ON ..
```

The library builds a set of useful command utilities to inspect native IEEE float/double/long double numbers as well as
the custom number systems provided by Universal. Assuming you have build and installed the library, the commands are

```text
    ieee           -- show the components (sign, scale, fraction) of the full set of IEEE floating point values
    signedint      -- show the components (sign, scale, fraction) of a signed integer value
    unsignedint    -- show the components (sign, scale, fraction) of an unsigned integer value
    float          -- show the components (sign, scale, fraction) of a float value
    double         -- show the components (sign, scale, fraction) of a double value
    longdouble     -- show the components (sign, scale, fraction) of a long double value
    fixpnt         -- show the components (sign, scale, fraction) of a fixed-point value
    posit          -- show the components (sign, scale, fraction) of a posit value
    lns            -- show the components (sign, scale, fraction) of a logarithmic number system value

    float2posit    -- show the conversion process of a Real value to a posit

    propenv        -- show the properties of the execution (==compiler) environment that built the library
    propp          -- show numerical properties of a posit environment including the associated quire
    propq          -- show numerical properties of a quire
```

For example:

```text
$ ieee 1.234567890123456789012
compiler              : 7.5.0
float precision       : 23 bits
double precision      : 52 bits
long double precision : 63 bits

Decimal representations
input value:             1.23456789012
      float:                1.23456788
     double:        1.2345678901199999
long double:    1.23456789011999999999

Hex representations
input value:             1.23456789012
      float:                1.23456788    hex: 0.7f.1e0652
     double:        1.2345678901199999    hex: 0.3ff.3c0ca428c1d2b
long double:    1.23456789011999999999    hex: 0.3fff.1e06521460e95b9a

Binary representations:
      float:                1.23456788    bin: 0.01111111.00111100000011001010010
     double:        1.2345678901199999    bin: 0.01111111111.0011110000001100101001000010100011000001110100101011
long double:    1.23456789011999999999    bin: 0.011111111111111.001111000000110010100100001010001100000111010010101101110011010

Native triple representations (sign, scale, fraction):
      float:                1.23456788    triple: (+,0,00111100000011001010010)
     double:        1.2345678901199999    triple: (+,0,0011110000001100101001000010100011000001110100101011)
long double:    1.23456789011999999999    triple: (+,0,001111000000110010100100001010001100000111010010101101110011010)

Universal triple representation (sign, scale, fraction):
input value:             1.23456789012
      float:                1.23456788    triple: (+,0,00111100000011001010010)
     double:        1.2345678901199999    triple: (+,0,0011110000001100101001000010100011000001110100101011)
long double:    1.23456789011999999999    triple: (+,0,001111000000110010100100001010001100000111010010101101110011010)
      exact: TBD
```

This _ieee_ command is very handy to quickly determine how your development environment represents (truncates) a specific value. 

The specific commands _float_, _double_, and _longdouble_ focus on float, double, and long double representations respectively.

There is also a command _posit_ to help you visualize and compare the posit component fields for a given value, for example:

```text
$ posit 1.234567890123456789012
posit< 8,0> = s0 r10 e f01000 qNE v1.25
posit< 8,1> = s0 r10 e0 f0100 qNE v1.25
posit< 8,2> = s0 r10 e00 f010 qNE v1.25
posit< 8,3> = s0 r10 e000 f01 qNE v1.25
posit<16,1> = s0 r10 e0 f001111000001 qNE v1.234619140625
posit<16,2> = s0 r10 e00 f00111100000 qNE v1.234375
posit<16,3> = s0 r10 e000 f0011110000 qNE v1.234375
posit<32,1> = s0 r10 e0 f0011110000001100101001000011 qNE v1.2345678918063641
posit<32,2> = s0 r10 e00 f001111000000110010100100001 qNE v1.2345678880810738
posit<32,3> = s0 r10 e000 f00111100000011001010010001 qNE v1.2345678955316544
posit<48,1> = s0 r10 e0 f00111100000011001010010000101000110001011010 qNE v1.2345678901234578
posit<48,2> = s0 r10 e00 f0011110000001100101001000010100011000101101 qNE v1.2345678901234578
posit<48,3> = s0 r10 e000 f001111000000110010100100001010001100010110 qNE v1.2345678901233441
posit<64,1> = s0 r10 e0 f001111000000110010100100001010001100010110011111101100000000 qNE v1.2345678901234567
posit<64,2> = s0 r10 e00 f00111100000011001010010000101000110001011001111110110000000 qNE v1.2345678901234567
posit<64,3> = s0 r10 e000 f0011110000001100101001000010100011000101100111111011000000 qNE v1.2345678901234567
```

The fields are prefixed by their first characters, for example, "posit<16,2> = s0 r10 e00 f00111100000 qNE v1.234375"

-   sign     field = s0, indicating a positive number
-   regime   field = r10, indicates the first positive regime, named regime 0
-   exponent field = e00, indicates two bits of exponent, both 0
-   fraction field = f00111100000, a full set of fraction bits

The field values are followed by a quadrant descriptor and a value representation in decimal:

-   qNE            = North-East Quadrant, representing a number in the range "[1, maxpos]"
-   v1.234375      = the value representation of the posit projection


The positive regime for a posit shows a very specific structure, as can be seen in the image blow:
![regime structure](docs/img/positive_regimes.png)

## Motivation

Modern AI applications have demonstrated the inefficiencies of the 64-bit format. Both Google and Microsoft have jettisoned IEEE floating point for their AI cloud services to gain two orders of magnitude better performance. Similarly, AI applications for mobile and embedded applications are shifting away from the IEEE floating point as well. But, AI applications are only some of the applications that expose the limitations of floating points.  Inefficiencies in numeric storage and operations can also limit cloud scale, IoT, embedded control, and HPC applications. A simple change to a new number system may improve the scale and cost of these applications by orders of magnitude.

For example, when performance and power efficiency are the differentiating attributes for a use case, number systems that are tailored to the needs of the application are desired.


In particular, there are two primary concerns of the IEEE floating point formats: 

-   inefficient representation of the reals
-   irreproducibility in the context of concurrency

More specifically, 

1.   **Wasted Bit Patterns** 
    -   32-bit IEEE floating point has around eight million ways to represent NaN (Not-A-Number), while the 64-bit floating point has two quadrillion, which is approximately 2.251x10^15 to be more exact.  A NaN is an exceptional value to represent undefined or invalid results, such as the result of a division by zero.
2.   **Mathematically Incorrect** 
    -   The format specifies two zeroes, a negative and positive zero, which have different behaviors. 
    -   Loss of associative and distributive law due to rounding after each operation.  This loss of associative and distributive arithmetic behavior creates an irreproducible result of concurrent programs that use the IEEE floating point.  This is particularly problematic for embedded and control applications.
3.   **Overflows to ± inf and underflows to 0** 
    -   Overflowing to ± inf increases the relative error by an infinite factor, while underflowing to 0 loses sign information.
4.   **Unused dynamic range** 
    -   The dynamic range of double precision floats is a whopping 2^2047, whereas most numerical software is architected to operate around 1.0.
5.   **Complicated Circuitry** 
    -   Denormalized floating point numbers have a hidden bit of 0 instead of 1.  This creates
a host of special handling requirements that complicate compliant hardware implementations.
6.   **No Gradual Overflow and Fixed Accuracy** 
    -   If accuracy is defined as the number of significand bits, the IEEE floating point has fixed accuracy for all numbers except denormalized numbers because the number of signficand digits is fixed.  Denormalized numbers are characterized by decreased significand digits when the value approaches zero due to having a zero hidden bit.  Denormalized numbers fill the underflow gap (i.e., between zero and the least non-zero values).  The counterpart for gradual underflow is gradual overflow which does not exist in IEEE floating points.

In contrast, for example, the _posit_ number system has the following features: 


1.   **Economical** 
    -   No bit patterns are redundant.  There is one representation for infinity denoted as ± inf and zero.  All other bit patterns are valid distinct non-zero real numbers. ± inf serves as a replacement for NaN.
2.   **Perserves Mathematical Properites** 
    -   There is only one representation for zero, and the encoding is symmetric around 1.0.  Associative and distributive laws are supported through deferred rounding via the quire, enabling reproducible linear algebra algorithms in any concurrency environment.
3.   **Tapered Accuracy** 
    -   Tapered accuracy is when values with small exponents have more precision and values with large exponents have fewer digits of accuracy.  This concept was first introduced by Morris (1971) in his paper ”Tapered Floating Point: A New Floating-Point Representation”.
4.   **Parameterized precision and dynamic range** 
    -   posits are defined by a size, _nbits_, and the number of exponent bits, _es_. This enables system designers the freedom to pick the right precision and dynamic range required for the application.  For example, we may pick 5- or 6-bit posits without any exponent bits for AI applications to improve performance.  For embedded DSP applications, such as 5G base stations, we may select a 16-bit posit with one exponent bit to improve performance per Watt.
5.   **Simpler Circuitry** 
    -   There are only two exceptional cases, Not a Real and Zero.  No denormalized numbers, overflow, or underflow. 




## Goals of the library

The _Universal_ library started as a bit-level arithmetic reference implementation of the evolving unum Type III (posit and valid) standard.
However, the demands for supporting number systems, such as adaptive-precision integers to solve large factorials, adaptive-precision 
floats to act as Oracles, or comparing linear and tapered floats provided the opportunity to create a complete platform for
numerical analysis and computational mathematics. With this _Universal_ platform, we enable a new direction for optimizing algorithms 
to take advantage of mixed precision to maximize performance and minimize energy demands. Energy efficiency is going to be the
key differentiator for embedded intelligence applications.

As a reference library, _Universal_ offers an extensive test infrastructure to validate number system arithmetic operations, and there is 
a host of utilities to inspect the internal encodings and operations of the different number systems.

The design space for custom arithmetic is vast, and any contribution to expanding the capability of the _Universal_ library is encouraged. 





## Contributing to universal

We are happy to accept pull requests via GitHub. The only requirement is that the entire regression test suite passes.

[![Stargazers over time](https://starchart.cc/stillwater-sc/universal.svg)](https://starchart.cc/stillwater-sc/universal)

## Verification Suite

Typically, the verification suite is run as part of the build directory's _make test_ command. However, it is possible to run specific test suite components, for example, to validate algorithmic changes to more complex arithmetic functions, such as square root, exponent, logarithm, and trigonometric functions.

Here is an example:

```text
>:~/dev/universal/build$ make posit_32bit_posit
Scanning dependencies of target posit_32bit_posit
[100%] Building CXX object tests/posit/CMakeFiles/posit_32bit_posit.dir/32bit_posit.cpp.o
[100%] Linking CXX executable posit_32bit_posit
[100%] Built target posit_32bit_posit
>:~/dev/universal/build$ tests/posit/posit_32bit_posit
Standard posit<32,2> configuration tests
 posit< 32,2> useed scale     4     minpos scale       -120     maxpos scale        120

Arithmetic tests 200000 randoms each
 posit<32,2> addition       PASS
 posit<32,2> subtraction    PASS
 posit<32,2> multiplication PASS
 posit<32,2> division       PASS
```

## Structure of the tree

The universal library contains a set of functional groups to organize the development and validation of different number systems. 
In the examples shown above, we have seen the ".../universal/include/universal/number/posit/posit.hpp" group and its test suite, ".../universal/tests/posit". 

Here is a complete list:

### fixed-sized configurations

- *universal/number/integer* - arbitrary configuration fixed-size integer
- *universal/number/fixpnt* - arbitrary configuration fixed-size fixed-point number system
- *universal/number/areal* - arbitrary configuration fixed-size faithful floating-point with uncertainty bit
- *universal/number/cfloat* - arbitrary configuration fixed-size classic floating-point number system
- *universal/number/posit* - arbitrary configuration fixed-size posit number system, a tapered floating-point
- *universal/number/valid* - arbitrary configuration fixed-size valid number system, a tapered floating-point interval number system
- *universal/number/quire* - arbitrary configuration fixed-size super accumulator number system (add/sub/abs/sqrt)
- *universal/number/unum* - flexible configuration unum Type 1 number system
- *universal/number/unum2* - flexible configuration unum Type 2 number system
- *universal/number/lns* - logarithmic number system
- *universal/number/float* - contains the implementation of the IEEE floating point augmentations for reproducible computation

### adaptive precision configurations

- *universal/number/decimal* - adaptive-precision decimal
- *universal/number/rational* - adaptive-precision rational number system
- *universal/number/adaptiveint* - adaptive-precision binary integer
- *universal/number/adaptivefloat* - adaptive-precision linear floating-point
- *universal/number/adaptiveposit* - adaptive-precision tapered floating-point

And each of these functionality groups have an associated test suite located in ".../universal/tests/..."




## Background information

Universal numbers, unums for short, express real numbers and ranges of real numbers. There are two modes of operation, selectable by the programmer, _posit_ mode and _valid_ mode.

In _posit_ mode, a unum behaves like a floating-point number of fixed size, rounding to the nearest expressible value if the result of a calculation is not expressible exactly.
A posit offers more accuracy and a wider dynamic range than floats with the same number of bits.

In _valid_ mode, a unum represents a range of real numbers and can be used to bound answers rigorously, much as interval arithmetic does.

Posit configurations have a specific relationship to one another. When expanding a posit, the new value falls 'between' the old values of the smaller posit. The new value is the arithmetic mean of the two numbers if the expanding bit is a fraction bit, and it is the geometric mean of the two numbers if the expanding bit is a regime or exponent bit. 
This [page](docs/PositRefinementViz.md) shows a visualization of the expansion of _posit<2,0>_ to _posit<7,1>_:



## Public Domain and community resources

The unum format is a public domain specification and a collection of web resources to manage information and discussions using unums.

[Posit Hub](https://posithub.org)

[Unum-computing Google Group](https://groups.google.com/forum/#!forum/unum-computing)





## Projects that leverage posits

[Matrix Template Library](http://simunova.com/#en-mtl4-index-html)

The Matrix Template Library incorporates modern C++ programming techniques to provide an easy and intuitive interface to users while enabling optimal performance. The natural mathematical notation in MTL4 empowers all engineers and scientists to implement their algorithms and models in minimal time. All technical aspects are encapsulated in the library. Think of it as MATLAB for applications.

[G+SMO](http://gs.jku.at/gismo) 

G+Smo (Geometry + Simulation Modules, pronounced "gismo") is a new open-source C++ library that brings together mathematical tools for geometric design and numerical simulation. It is developed mainly by researchers and PhD students. It implements the relatively new paradigm of isogeometric analysis, which suggests the use of a unified framework in the design and analysis pipeline. G+Smo is an object-oriented, cross-platform, template C++ library and follows the generic programming principle, with a focus on both efficiency and ease of use. The library is partitioned into smaller entities, called modules. Examples of available modules include the dimension-independent NURBS module, the data fitting and solid segmentation module, the PDE discretization module and the adaptive spline module, based on hierarchical splines of arbitrary dimension and polynomial degree. 

[FEniCS](https://fenicsproject.org/)

FEniCS is a popular open-source (LGPLv3) computing platform for solving partial differential equations (PDEs). FEniCS enables users to quickly translate scientific models into efficient finite element code. With the high-level Python and C++ interfaces to FEniCS, it is easy to get started, but FEniCS offers also powerful capabilities for more experienced programmers. FEniCS runs on a multitude of platforms ranging from laptops to high-performance clusters.


[ODEINT-v2](http://headmyshoulder.github.io/odeint-v2/)

Odeint is a modern C++ library for numerically solving Ordinary Differential Equations. It is developed in a generic way using Template Metaprogramming which leads to extraordinary high flexibility at top performance. The numerical algorithms are implemented independently of the underlying arithmetics. This results in an incredible applicability of the library, especially in non-standard environments. For example, odeint supports matrix types, arbitrary precision arithmetics and even can be easily run on CUDA GPUs.

Several AI and Deep Learning libraries are being reengineered to enable the use of posits for both training and inference. They will be announced as they are released.


## License
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fstillwater-sc%2Funiversal.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2Fstillwater-sc%2Funiversal?ref=badge_large)
