#include <iostream>
#include <cmath>
#include <iomanip>

const double PI = 3.14159265358979323846;
const double EPS0 = 8.8541878128e-12; // permittivity of free space (F/m)
const double MU0 = 1.25663706212e-6; // permeability of free space (N/A^2)

// Base class: 3D field stored in dynamic array
// value[0] = x, value[1] = y, value[2] = z
class Field {
    protected:
        double *value;

    public:
        // Field initialized to 0
        Field() {
            value = new double[3];
            value[0] = value[1] = value[2] = 0.0;
        }

        // Constructor taking the 3 comps
        Field(double x, double y, double z) {
            value = new double[3];
            value[0] = x;
            value[1] = y;
            value[2] = z;
        }

         // Copy constructor with deep copy
         Field(const Field &other) {
             value = new double[3];
             for (int i = 0; i < 3; i++) { value[i] = other.value[i]; }
         }

          // Copy the assignment too
          Field &operator=(const Field &other) {
              if (this != &other) {
                  for (int i = 0; i < 3; i++) { value[i] = other.value[i]; }
              }

              return *this;
          }

          // Destructor to free dynamic memory (virtual since this is a base class)
          virtual ~Field() {
              delete[] value;
          }

          // Getters
          double getX() const { return value[0]; }
          double getY() const { return value[1]; }
          double getZ() const { return value[2]; }

          // Setters
          void setX(double x) { value[0] = x; }
          void setY(double y) { value[1] = y; }
          void setZ(double z) { value[2] = z; }

          // Magnitude
          double calculateMagnitude() const {
              return std::sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2]);
          }

          // Prints the 3 components (and the magnitude)
          void printMagnitude() const {
              std::cout << "x = " << value[0] << ", y = " << value[1] << ", z = "
                        << value[2] << "  (|F| = " << calculateMagnitude() << ")\n";
          }
};

// E.Field: inherits the dynamic array from Field
class Electric_Field : public Field {
    private:
        double calculatedE; // result from Gauss' law

    public:
        // Field initialized to 0
        Electric_Field() : Field(), calculatedE(0.0) {}

        Electric_Field(double x, double y, double z) : Field(x, y, z), calculatedE(0.0) {}

        // Copy it for dynamic memory
        Electric_Field(const Electric_Field &other) : Field(other), calculatedE(other.calculatedE) {}

        // Copy the assignment too
        Electric_Field &operator=(const Electric_Field &other) {
            if (this != &other) {
                Field::operator=(other);
                calculatedE = other.calculatedE;
            }

            return *this;
        }

        // Getters
        double getX() const { return value[0]; }
        double getY() const { return value[1]; }
        double getZ() const { return value[2]; }

        // Setters
        void setX(double x) { value[0] = x; }
        void setY(double y) { value[1] = y; }
        void setZ(double z) { value[2] = z; }
        void setComponents(double x, double y, double z) {
            value[0] = x;
            value[1] = y;
            value[2] = z;
        }

        // Magnitude (E = sqrt(Ex^2 + Ey^2 + Ez^2))
        double calculateMagnitude() const {
            return std::sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2]);
        }

        // Inner product of the field vector with itself: E * E
        double innerProduct() const {
            return value[0] * value[0] + value[1] * value[1] + value[2] * value[2];
        }

        // Inner product with another electric field: E1 * E2
        double innerProduct(const Electric_Field &other) const {
            return value[0] * other.value[0] + value[1] * other.value[1] + value[2] * other.value[2];
        }

        // Gauss' law for a spherical charge: E = Q / (4 pi r^2 eps0)
        double calculateElectricField(double Q, double r) {
            if (r <= 0.0) {
                std::cerr << "Error: distance r must be positive.\n";
                return calculatedE;
            }
            calculatedE = Q / (4.0 * PI * r * r * EPS0);
            return calculatedE;
        }

        double getCalculatedField() const { return calculatedE; }

        // + operator: component-wise sum
        Electric_Field operator+(const Electric_Field &rhs) const {
            return Electric_Field(value[0] + rhs.value[0],
                                  value[1] + rhs.value[1],
                                  value[2] + rhs.value[2]);
        }

        // << operator: prints (x, y, z)
        friend std::ostream &operator<<(std::ostream &os, const Electric_Field &e) {
            os << "(" << e.value[0] << ", " << e.value[1] << ", " << e.value[2] << ")";
            return os;
        }
};

// MField: inherits the dynamic array from Field
class Magnetic_Field : public Field {
    private:
        double calculatedB; // result from Ampere's law

    public:
        // Initial constructor where field is initialized to 0
        Magnetic_Field() : Field(), calculatedB(0.0) {}

        // Constructor taking the 3 comps
        Magnetic_Field(double x, double y, double z) : Field(x, y, z), calculatedB(0.0) {}

        // Copy constructor with deep copy
        Magnetic_Field(const Magnetic_Field &other) : Field(other), calculatedB(other.calculatedB) {}

        // Copy assingment with deep copy
        Magnetic_Field &operator=(const Magnetic_Field &other) {
            if (this != &other) {
                Field::operator=(other);
                calculatedB = other.calculatedB;
            }

            return *this;
        }

        // Getters
        double getX() const { return value[0]; }
        double getY() const { return value[1]; }
        double getZ() const { return value[2]; }

        // Setters
        void setX(double x) { value[0] = x; }
        void setY(double y) { value[1] = y; }
        void setZ(double z) { value[2] = z; }
        void setComponents(double x, double y, double z) {
            value[0] = x;
            value[1] = y;
            value[2] = z;
        }

        // Magnitude same formula but for B
        double calculateMagnitude() const {
            return std::sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2]);
        }

        // Unit vector B/|B| to return as MField obj.
        // field = 0 vector means unit vector is undefined
        // so when that happens, 0 vector returned instead of dividing by 0
        
        Magnetic_Field calculateUnitVector() const {
            double mag = calculateMagnitude();
            if (mag == 0.0) {
                std::cerr << "Warning: 0 m.field has no unit vector.\n";
                return Magnetic_Field(0.0, 0.0, 0.0);
            }
            return Magnetic_Field(value[0] / mag, value[1] / mag, value[2] / mag);
        }

        // Ampere's law for a long straight wire: B = I / (2 pi r mu0)
        double calculateMagneticField(double I, double r) {
            if (r <= 0.0) {
                std::cerr << "Error: distance r must be positive.\n";
                return calculatedB;
            }
            calculatedB = I / (2.0 * PI * r * MU0);
            return calculatedB;
        }

        double getCalculatedField() const { return calculatedB; }

        // + operator: component-wise sum
        Magnetic_Field operator+(const Magnetic_Field &rhs) const {
            return Magnetic_Field(value[0] + rhs.value[0],
                                  value[1] + rhs.value[1],
                                  value[2] + rhs.value[2]);
        }

        // << operator: prints (x, y, z)
        friend std::ostream &operator<<(std::ostream &os, const Magnetic_Field &b) {
            os << "(" << b.value[0] << ", " << b.value[1] << ", " << b.value[2] << ")";
            return os;
        }
};

int main() {
    std::cout << std::setprecision(6);

    // Constructors and printMagnitude
    Electric_Field E(0, 1e5, 1e3);
    Magnetic_Field B(2e-3, 0, 5e-4);

    std::cout << "=== Components ===\n";
    std::cout << "Electric field: ";
    E.printMagnitude();
    std::cout << "Magnetic field: ";
    B.printMagnitude();

    // Gauss' law: Q = 2 microC, r = 0.5 m
    Electric_Field E_sphere;
    double Q = 2e-6, rE = 0.5;
    E_sphere.calculateElectricField(Q, rE);
    std::cout << "\n=== Gauss' Law ===\n";
    std::cout << "Q = " << Q << " C, r = " << rE << " m\n";
    std::cout << "E = " << E_sphere.getCalculatedField() << " N/C\n";

    // Ampere's law: I = 10 A, r = 0.05 m
    Magnetic_Field B_wire;
    double I = 10.0, rB = 0.05;
    B_wire.calculateMagneticField(I, rB);
    std::cout << "\n=== Ampere's Law ===\n";
    std::cout << "I = " << I << " A, r = " << rB << " m\n";
    std::cout << "B = " << B_wire.getCalculatedField() << " T\n";

    // Operator overloads
    Electric_Field e1, e2(1, 2, 3), e3(10, 20, 30);
    e1 = e2 + e3;
    std::cout << "\n=== Operator Overloads ===\n";
    std::cout << "e2 = " << e2 << std::endl;
    std::cout << "e3 = " << e3 << std::endl;
    std::cout << "e1 = e2 + e3 = " << e1 << std::endl;

    Magnetic_Field b1, b2(0.1, 0.2, 0.3), b3(0.5, 0.4, 0.3);
    b1 = b2 + b3;
    std::cout << "b2 = " << b2 << std::endl;
    std::cout << "b3 = " << b3 << std::endl;
    std::cout << "b1 = b2 + b3 = " << b1 << std::endl;

    return 0;
}
