![Continuous Integration](https://github.com/njoy/scion/workflows/Continuous%20Integration/badge.svg)

# scion
A toolkit for scientific interpretation, linearisation, differentiation and integration of nuclear data.

[ENDFtk](https://github.com/njoy/ENDFtk), [ACEtk](https://github.com/njoy/ACEtk) and similar data access components provide interfaces to raw nuclear data that need to be interpreted and/or processed before they can actually be used. Some data is represented as tabulated values using different interpolation schemes, as an analytical function, as a polynomial or even as a polynomial expansion (e.g., Legendre polynomials).

Scion is NJOY’s functional interpretation component that will provide the required functionality to convert raw nuclear data components into function-like object that allows a user to retrieve information from it directly (e.g., ask for a cross section value at a given energy) and/or as a basis for further operations (e.g., the input for linearisation and integration).

Processing components such as [codex](https://github.com/njoy/codex) for covariance data processing and [resonanceReconstruction](https://github.com/njoy/resonanceReconstruction) will use the functionality provided by scion to perform some of the processing operations that these components need to perform.

## LICENSE
The software contained in this repository is covered under the associated [LICENSE](LICENSE) file.
