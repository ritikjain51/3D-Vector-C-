#include<iostream>
#include<math.h>
#include<assert.h>
#include<stdlib.h>

class Vector;

class Distance
{
public:
	double EuclideanDistance(Vector&, Vector&);
	double ManhattaDistance(Vector&, Vector&);
};


class Vector
{
private:
	double x, y, z;

public:
	// Class Constructors
	Vector();
	Vector(double, double, double);
	Vector(const Vector &);
	Vector(const Vector*);

	// Vector Subtraction operation
	friend Vector operator -(const Vector &, const Vector &);
	friend Vector operator -(const Vector &, double);
	friend Vector operator -(double, const Vector&);

	// Vector Addition operation
	friend Vector operator +(const Vector &, const Vector &);
	friend Vector operator +(const Vector &, double);
	friend Vector operator +(double, const Vector&);

	// Vector Multiplication operation
	friend Vector operator *(const Vector &, double);
	friend Vector operator *(double, const Vector&);
	friend Vector operator* (const Vector&, const Vector&);
	Vector DotProduct(const Vector&);
	Vector CrossProduct(const Vector&);


	// Vector Division operation
	friend Vector operator / (const Vector&, double);
	friend Vector operator /(double, const Vector&);

	// Boolean Functions
	friend bool operator == (const Vector&, const Vector&);
	friend bool operator != (const Vector&, const Vector&);

	// Assignment Operator
	Vector operator= (const Vector& );

	// Print Function 
	friend std::ostream& operator << (std::ostream&, const Vector&);
	friend std::istream& operator >> (std::istream&, Vector&);
	void Set(double, double, double);

	// Distance Function
	double distance(Vector&, char*);

	//Get Values
	double X();
	double Y();
	double Z();

	// Linear interpolation
	Vector Lerp(const Vector&, double);

	// Maximum and Minimum Vector function
	Vector Max(const Vector&);
	Vector Min(const Vector&);

	//Maximum and Minimum between function

	friend bool operator > (const Vector&, const Vector&);
	friend bool operator < (const Vector&, const Vector&);
	bool MaxBetween(const Vector&);
	bool MinBetween(const Vector&);

};

inline double Distance::EuclideanDistance(Vector& v1, Vector& v2)
{
	double sqr = pow(v1.X() - v2.X(), 2) + pow(v1.Y() - v2.Y(), 2) + pow(v1.Z() - v2.Z(), 2);
	return sqrt(sqr);
}

inline double Distance::ManhattaDistance(Vector& v1, Vector& v2)
{
	double absolute = abs(v1.X() - v2.X()) + abs(v1.Y() - v2.Y()) + abs(v1.Z() - v2.Z());
	return absolute;
}


//Constructor Definition
Vector::Vector() : x(0), y(0), z(0) {}
Vector::Vector(double a, double b, double c) : x(a), y(b), z(c) {}
Vector::Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}

// Get Value Function
double Vector::X()
{
	return this->x;
}

double Vector::Y()
{
	return this->y;
}

double Vector::Z()
{
	return this->z;
}


// Addition Operator Defintion
inline Vector operator +(const Vector& v1, const Vector& v2)
{
	Vector temp(v1);
	temp.x += v2.x;
	temp.y += v2.y;
	temp.z += v2.z;
	return temp;
}

inline Vector operator +(const Vector &v, double scalar)
{
	Vector temp(v);
	temp.x += scalar;
	temp.y += scalar;
	temp.z += scalar;
	return temp;
}

inline Vector operator+ (const double scalar, const Vector& v)
{
	return v + scalar;
}


// Subtraction operator Definition
inline Vector operator -(const Vector& v1, const Vector& v2)
{
	Vector temp (v1);
	temp.x -= v2.x;
	temp.y -= v2.y;
	temp.z -= v2.z;
	return temp;
}

inline Vector operator- (const Vector& v, double scalar)
{
	Vector temp(v);
	temp.x -= scalar;
	temp.y -= scalar;
	temp.z -= scalar;
	return temp;
}

inline Vector operator- (double scalar, const Vector& v)
{
	Vector temp;
	temp.x = scalar - v.x;
	temp.y = scalar - v.y;
	temp.z = scalar - v.z;
	return temp;
}


// Multiplication operator Definition 
inline Vector Vector:: DotProduct(const Vector& v)
{
	Vector temp(v);
	temp.x *= this->x;
	temp.y *= this->y;
	temp.z *= this->z;
	return temp;
}

inline Vector operator* (const Vector& v, double scalar)
{
	Vector temp(v);
	temp.x *= scalar;
	temp.y *= scalar;
	temp.z *= scalar;
	return temp;
}

inline Vector operator* (double scalar, const Vector& v)
{
	return v * scalar;
}

inline Vector Vector::CrossProduct(const Vector& v)
{
	Vector temp;
	temp.x = this->y * v.z - this->z * v.y;
	temp.y = this->z * v.x - this->x * v.z;
	temp.z = this->x * v.y - this->y * v.x;
	return temp;
}

inline Vector operator* (const Vector& v1, const Vector& v2)
{
	Vector temp(v1);
	temp.x *= v2.x;
	temp.y *= v2.y;
	temp.z *= v2.z;
	return temp;
}


// Division operator Definition
inline Vector operator / (const Vector& v, double scalar)
{
	assert(scalar != 0);
	scalar = 1.0 / scalar;
	Vector temp(v);
	temp.x *= scalar;
	temp.y *= scalar;
	temp.z *= scalar;
	return temp;
}

inline Vector operator / (double scalar, const Vector& v)
{
	return v / scalar;
}


// Assignment operator Definition
inline Vector Vector::operator=(const Vector &v)
{
	return Vector(v.x, v.y, v.z);
}

// Input & Printing Function Definition
inline std::ostream& operator << (std::ostream & out, const Vector& v)
{
	out << "(" << v.x << "," << v.y << "," << v.z << ")";
	return out;
}

inline std::istream& operator >> (std::istream& in, Vector& v)
{
	in >> v.x >> v.y >> v.z;
	return in;
}

inline void Vector::Set(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//Boolean Operator Definition
inline bool operator == (const Vector& v1, const Vector& v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

inline bool operator != (const Vector& v1, const Vector& v2)
{
	return (v1.x != v2.x || v1.y != v2.y || v1.z != v2.z);
}


inline Vector Vector:: Lerp(const Vector& v2, double per)
{
	/*
		Formula v = alpha * a + (1-alpha) * b
	*/
	double alpha = per / 100;
	return (*this * alpha) + (v2 * (1 - alpha));
}

inline double Vector::distance(Vector& v2, char* dst = "euclidean")
{
	Distance* obj = new Distance();
	if (dst == "euclidean")
		return obj->EuclideanDistance(*this, v2);
	else if (dst == "manhattan")
		return obj->ManhattaDistance(*this, v2);
	else
		assert("Sorry this type is not found");
	return NULL;
}

// Maximum and Minimum Function 
inline Vector Vector::Max(const Vector& v)
{
	Vector temp;
	temp.x = this->x > v.x ? this->x : v.x;
	temp.y = this->y > v.y ? this->y : v.y;
	temp.z = this->z > v.z ? this->y : v.z;
	return temp;
}

inline Vector Vector::Min(const Vector& v)
{
	Vector temp;
	temp.x = this->x > v.x ? this->x : v.x;
	temp.y = this->y > v.y ? this->y : v.y;
	temp.z = this->z > v.z ? this->y : v.z;
	return temp;
}


// Maximum and Minimum operator and Functon 
inline bool operator > (const Vector& v1, const Vector& v2)
{
	return (((v1.x > v2.x) || (v1.y > v2.y) || (v1.z > v2.z)) ? 1 : 0);
}

inline bool operator < (const Vector& v1, const Vector& v2)
{
	return (((v1.x < v2.x) || (v1.y < v2.y) || (v1.z < v2.z)) ? 1 : 0);
}

inline bool Vector::MaxBetween(const Vector& v)
{
	return *this > v;
}

inline bool Vector::MinBetween(const Vector& v)
{
	return *this < v;
}


int main()
{
	Vector v;
	std::cout << "Enter values of 3d Vector:" << std::endl;
	std:: cin >> v;
	Vector v1(10, 20, 30);
	std::cout << "Maximum value: " << (v > v1) << std::endl;
	std::cout << "Minimum value: " << (v < v1) << std::endl;
	std::cout << "V vector" << v << std::endl;
	v.Set(10, 20, 30);
	std::cout << "V after reset " << v;
	system("pause");
}
