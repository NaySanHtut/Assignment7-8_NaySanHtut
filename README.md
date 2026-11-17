# Assignment7&8_NaySanHtut

# Electric and Magnetic Field Classes

A base class `Field` stores a 3D vector in a dynamically allocated array of 3 doubles. `Electric_Field` and `Magnetic_Field` inherit from it. The electric class calculates a field with Gauss' law and the magnetic class with Ampere's law. Both overload `+` and `<<`.

## Files

- `main.cpp`: class definitions and test driver

## Build and Run

```
g++ -std=c++11 -o main main.cpp
./main
```

## Output

```
=== Components ===
Electric field: x = 0, y = 100000, z = 1000  (|F| = 100005)
Magnetic field: x = 0.002, y = 0, z = 0.0005  (|F| = 0.00206155)

=== Gauss' Law ===
Q = 2e-06 C, r = 0.5 m
E = 71900.4 N/C

=== Ampere's Law ===
I = 10 A, r = 0.05 m
B = 4e-05 T

=== Operator Overloads ===
e2 = (1, 2, 3)
e3 = (10, 20, 30)
e1 = e2 + e3 = (11, 22, 33)
b2 = (0.1, 0.2, 0.3)
b3 = (0.5, 0.4, 0.3)
b1 = b2 + b3 = (0.6, 0.6, 0.6)
```
