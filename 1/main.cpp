#include <iostream>
#include <cmath>

class Vector
{
public:
    Vector ()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector (float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    operator float ()
    {
        return sqrt(x * x + y * y + z * z);
    }

    friend Vector operator+ (const Vector& v1, const Vector& v2)
    {
        return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    friend std::ostream& operator<< (std::ostream& out, const Vector& v)
    {
        out << ' ' << v.x << ' ' << v.y << ' ' << v.z;
        return out;
    }

    friend bool operator> (const Vector& v1, const Vector& v2)
    {
        return false;
    }

    /* operators *  */
    friend Vector operator* (float factor, const Vector& v1)
    {
        return Vector(factor * v1.x, factor * v1.y, factor * v1.z);
    }

    friend Vector operator* (const Vector& v1, float factor)
    {
        return Vector(factor * v1.x, factor * v1.y, factor * v1.z);
    }

    friend Vector operator- (const Vector& v1, const Vector& v2)
    {
        return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    friend std::istream& operator>> (std::istream& is, Vector& v1)
    {
        is >> v1.x >> v1.y >> v1.z;
        return is;
    }

private:
    float x;
    float y;
    float z;
};

int main()
{
    Vector a(0.1, 0.2, 0.3);
    Vector b;

    std::cin >> b;
    std::cout << 3.0 * a - b << std::endl;
    return 0;
}
