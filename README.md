# determinant-calculator

The determinant calculator generates a square matrix and calculates the determinant. Matrices are generated with a number range from -1000 to 1000.
The initial matrix state is saved to file, before calculation.
After the calculation, the determinant is printed out into the console with time for calculation.
As a demonstration, the data is tested in the set, which is increasing up to a matrix size of 1000x1000.

## Implementation

The method used for calculation is the improved gauss elimination method, which is composed of cycles of N iterations.
These iterations are independent of each other, which made their separation into parallel threads possible.
Where N is the size of the square matrix.

The calculator accepts only one argument, which can be 'single', 'multi' or '--help'.
For any other state error message will be thrown.

## Measurement output
```
Matrix size: 1000x1000
Matrix range: <-1000,1000>

ST Determinant calculation time difference = 9877ms (9s)
MP Determinant calculation time difference = 4338ms (4s)
```
