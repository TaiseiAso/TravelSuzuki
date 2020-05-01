#ifndef point_h
#define point_h

namespace util
{
    template <typename T>
    class Point
    {
    public:
        Point() { Point(0, 0); }
        Point(T x, T y) { x_ = x; y_ = y; }
        ~Point() {};

        Point& operator=(Point& point) { x_ = point.x_; y_ = point.y_; return *this; }
        Point& operator+=(Point& point) { x_ += point.x_; y_ += point.y_; return *this; }
        Point& operator-=(Point& point) { x_ -= point.x_; y_ -= point.y_; return *this; }

        Point operator+(Point point) { return Point(x_ + point.x_, y + point.y_); }
        Point operator-(Point point) { return Point(x_ - point.x_, y - point.y_); }

        bool operator==(Point point) { return x_ == point.x_ && y_ == point.y_; }

        T getX() { return x_; }
        T getY() { return y_; }

        void setX(T x) { x_ = x; }
        void setY(T y) { y_ = y; }
        void set(T x, T y) { x_ = x; y_ = y; }

        static Point GetPoint(T x, T y) { Point point(x, y); return point; }

    private:
        T x_; // xç¿ïW
        T y_; // yç¿ïW
    };
}

#endif // !point_h