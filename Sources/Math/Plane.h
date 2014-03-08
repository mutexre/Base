#ifndef header_F0FB70BE6E35
#define header_F0FB70BE6E35

#include <math.h>

namespace Math
{
    template <typename T>
    class Plane
    {
    public:
        T a;
        T b;
        T c;
        T d;
//        T c_rev = 1.0f / c;

        void init(const Vertex<T>& v1, const Vertex<T>& v2, const Vertex<T>& v3)
        {
    #if 0
            a = v2.y * v3.z + v1.y * v2.z + v3.y * v1.z - v2.y * v1.z - v1.y * v3.z - v2.z * v3.y; // 6 muls, 5 sub/add
            b = v1.x * v3.z + v2.z * v3.x + v2.x * v1.z - v1.z * v3.x - v2.x * v3.z - v1.x * v2.z; // 6 muls, 5 sub/add
            c = v1.x * v2.y + v1.y * v3.x + v2.x * v3.y - v2.y * v3.x - v2.x * v1.y - v3.y * v1.x; // 6 muls, 5 sub/add
            d = v1.z * v2.y * v3.x + v2.x * v1.y * v3.z + v3.y * v2.z * v1.x -
                v1.x * v2.y * v3.z - v1.y * v2.z * v3.x - v2.x * v3.y * v1.z; // 12 muls, 5 sub/add
    #else
            a = v1.y * (v2.z - v3.z) + v2.y * (v3.z - v1.z) + v3.y * (v1.z - v2.z); // 3 muls, 5 sub/add
            b = v1.z * (v2.x - v3.x) + v2.z * (v3.x - v1.x) + v3.z * (v1.x - v2.x); // 3 muls, 5 sub/add
            c = v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y); // 3 muls, 5 sub/add
            d = v1.x * (v3.y * v2.z - v2.y * v3.z) + v2.x * (v1.y * v3.z - v3.y * v1.z) + v3.x * (v2.y * v1.z - v1.y * v2.z); // 9 muls, 5 sub/add
            // Total: 18 muls, 20 sub/add
    #endif
        }

        void initWithoutCalculationOfD(const Vertex<T>& v1, const Vertex<T>& v2, const Vertex<T>& v3)
        {
    #if 0
            a = v2.y * v3.z + v1.y * v2.z + v3.y * v1.z - v2.y * v1.z - v1.y * v3.z - v2.z * v3.y; // 6 muls, 5 sub/add
            b = v1.x * v3.z + v2.z * v3.x + v2.x * v1.z - v1.z * v3.x - v2.x * v3.z - v1.x * v2.z; // 6 muls, 5 sub/add
            c = v1.x * v2.y + v1.y * v3.x + v2.x * v3.y - v2.y * v3.x - v2.x * v1.y - v3.y * v1.x; // 6 muls, 5 sub/add
    #else
            a = v1.y * (v2.z - v3.z) + v2.y * (v3.z - v1.z) + v3.y * (v1.z - v2.z); // 3 muls, 5 sub/add
            b = v1.z * (v2.x - v3.x) + v2.z * (v3.x - v1.x) + v3.z * (v1.x - v2.x); // 3 muls, 5 sub/add
            c = v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y); // 3 muls, 5 sub/add
            // Total: 18 muls, 20 sub/add
    #endif
        }

        void init(const Vertex<T>* v1, const Vertex<T>* v2, const Vertex<T>* v3)
        {
    #if 0
            a = v2->y * v3->z + v1->y * v2->z + v3->y * v1->z - v2->y * v1->z - v1->y * v3->z - v2->z * v3->y; // 6 muls, 5 sub/add
            b = v1->x * v3->z + v2->z * v3->x + v2->x * v1->z - v1->z * v3->x - v2->x * v3->z - v1->x * v2->z; // 6 muls, 5 sub/add
            c = v1->x * v2->y + v1->y * v3->x + v2->x * v3->y - v2->y * v3->x - v2->x * v1->y - v3->y * v1->x; // 6 muls, 5 sub/add
            d = v1->z * v2->y * v3->x + v2->x * v1->y * v3->z + v3->y * v2->z * v1->x -
                v1->x * v2->y * v3->z - v1->y * v2->z * v3->x - v2->x * v3->y * v1->z; // 12 muls, 5 sub/add
    #else
            a = v1->y * (v2->z - v3->z) + v2->y * (v3->z - v1->z) + v3->y * (v1->z - v2->z); // 3 muls, 5 sub/add
            b = v1->z * (v2->x - v3->x) + v2->z * (v3->x - v1->x) + v3->z * (v1->x - v2->x); // 3 muls, 5 sub/add
            c = v1->x * (v2->y - v3->y) + v2->x * (v3->y - v1->y) + v3->x * (v1->y - v2->y); // 3 muls, 5 sub/add
            d = v1->x * (v3->y * v2->z - v2->y * v3->z) + v2->x * (v1->y * v3->z - v3->y * v1->z) + v3->x * (v2->y * v1->z - v1->y * v2->z); // 9 muls, 5 sub/add
            // Total: 18 muls, 20 sub/add
    #endif
        }

        void initWithoutCalculationOfD(const Vertex<T>* v1, const Vertex<T>* v2, const Vertex<T>* v3)
        {
    #if 0
            a = v2->y * v3->z + v1->y * v2->z + v3->y * v1->z - v2->y * v1->z - v1->y * v3->z - v2->z * v3->y; // 6 muls, 5 sub/add
            b = v1->x * v3->z + v2->z * v3->x + v2->x * v1->z - v1->z * v3->x - v2->x * v3->z - v1->x * v2->z; // 6 muls, 5 sub/add
            c = v1->x * v2->y + v1->y * v3->x + v2->x * v3->y - v2->y * v3->x - v2->x * v1->y - v3->y * v1->x; // 6 muls, 5 sub/add
    #else
            a = v1->y * (v2->z - v3->z) + v2->y * (v3->z - v1->z) + v3->y * (v1->z - v2->z); // 3 muls, 5 sub/add
            b = v1->z * (v2->x - v3->x) + v2->z * (v3->x - v1->x) + v3->z * (v1->x - v2->x); // 3 muls, 5 sub/add
            c = v1->x * (v2->y - v3->y) + v2->x * (v3->y - v1->y) + v3->x * (v1->y - v2->y); // 3 muls, 5 sub/add
            // Total: 18 muls, 20 sub/add
    #endif
        }

        float rvalue(Vertex<T>* vertex) const
        {
            return a * vertex->x + b * vertex->y + c * vertex->z + d;
        }

        float intersectionWithLine(Vertex<T>* v0, Vertex<T>* v1_minus_v0)
        {
            return -rvalue(v0) / (a * v1_minus_v0->x + b * v1_minus_v0->y + c * v1_minus_v0->z);
        }

        void intersectionWithLine(Vertex<T>* v0, Vertex<T>* v1_minus_v0, Vertex<T>* result)
        {
            T t = intersectionWithLine(v0, v1_minus_v0);
            result->x = v0->x + t * v1_minus_v0->x;
            result->y = v0->y + t * v1_minus_v0->y;
            result->z = v0->z + t * v1_minus_v0->z;
        }

        void calcNormal(Vector<T>& normal)
        {
            T normalInverseLength = T(1) / sqrtf(a * a + b * b + c * c);
            normal.x = a * normalInverseLength;
            normal.y = b * normalInverseLength;
            normal.z = c * normalInverseLength;
        }

        void calcNormal(Vector<T>* normal)
        {
            T normalInverseLength = T(1) / sqrtf(a * a + b * b + c * c);
            normal->x = a * normalInverseLength;
            normal->y = b * normalInverseLength;
            normal->z = c * normalInverseLength;
        }

        const T* getData() const { return (T*)this; }

        float getZ(T x, T y) const
        {
            return (d - a * x - b * y) / c;
        }

        static char getZSortValue(const Plane<T>* a, const Plane<T>* b, T x, T y)
        {
            auto az = a->getZ(x, y);
            auto bz = b->getZ(x, y);

            if (az > bz) return +1;
            if (az < bz) return -1;

            return 0;
        }

        void print() const
        {
            printf("%f %f %f %f\n", a, b, c, d);
        }
    };
}

#endif
