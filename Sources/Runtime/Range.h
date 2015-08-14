#ifndef header_6F28A25EE055
#define header_6F28A25EE055

namespace Rt
{
#pragma pack(4)
    template<typename T>
    class Range
    {
    public:
        T a, b;
        inline Range() {}
        inline Range(T x) : a(x), b(x) {}
        inline Range(const Range& range) : a(range.a), b(range.b) {}
        inline Range(T _start, T _length) : a(_start), b(_start + _length) {}
        inline ~Range() {}

        T getA() const { return a; }
        T getB() const { return b; }

        inline bool operator!() const { return (a == b); }
        inline bool operator==(const Range& range) const { return ((a == range.a) && (b == range.b)); }
        inline bool operator!=(const Range& range) const { return ((a != range.a) || (b != range.b)); }
        inline bool operator<(const Range& range) const { return (b <= range.a); };
        inline bool operator>(const Range& range) const { return (a >= range.b); };

        inline Range operator<<(const T& n) const { return Range(a << n, length() << n); }
        inline Range operator>>(const T& n) const { return Range(a >> n, length() >> n); }

        inline Range& operator<<=(const T& n) {
            a <<= n;
            b <<= n;
            return *this;
        }

        inline Range& operator>>=(const T& n) {
            a >>= n;
            b >>= n;
            return *this;
        }

        inline T length() const { return (b - a); }
        inline void setLength(T newLength) { b = a + newLength; }

        inline bool isInside(T x) const {
            return (x > a && x < b);
        }

        static inline bool doIntersect(const Range& a, const Range& b) {
            return !((b.b <= a.a) || (b.a >= a.b));
        }

        inline Option<Range> intersection(T a, T b) const {
            if ((b <= this->a) || (a >= this->b)) return Option<Range>();
            return Option<Range>(Range(std::max(a, this->a), std::min(b, this->b) - std::max(a, this->a)));
        }

        inline Option<Range> intersection(const Range* range) const {
            return intersection(range->a, range->b);
        }

        inline Option<Range> intersection(const Range range) const {
            return intersection(range.a, range.b);
        }

        inline void intersectWith(T _a, T _b) {
            if ((_b <= a) || (_a >= b)) {
                a = b = 0;
            }
            else {
                a = max(_a, a);
                b = min(_b, b);
            }
        }

        inline void intersectWith(const Range* range) {
            intersectWith(range->a, range->b);
        }

        inline void intersectWith(Range range) {
            intersectWith(range.a, range.b);
        }

        inline Range* intersect(T _a, T _b) {
            intersectWith(_a, _b);
            return this;
        }

        inline Range* intersect(const Range* range) {
            return intersect(range->a, range->b);
        }

        inline Range* intersect(Range range) {
            return intersect(range.a, range.b);
        }

        inline void mergeWith(T _start, T _length) {
            T _b = _start + _length;

            if ((_b < a) || (_start > b)) return;

            a = min(_start, a);
            b = max(_b, b);
        }

        inline void mergeWith(const Range* range) {
            mergeWith(range->a, range->length());
        }

        inline void mergeWith(Range range) {
            mergeWith(range.a, range.length());
        }

        inline Range* merge(T _start, T _length) {
            mergeWith(_start, _length);
            return this;
        }

        inline Range* merge(const Range* range) {
            return merge(range->a, range->length());
        }

        inline Range* merge(Range range) {
            return merge(range.a, range.length());
        }
    };
#pragma pack()
}

#endif
