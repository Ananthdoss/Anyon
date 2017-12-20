#pragma once

#include <sstream>
#include <iomanip>
#include <cstdint>
#include <cmath>
#include <algorithm>

namespace Anyon
{
    struct Color
    {
        union
        {
            struct
            {
                float r, g, b, a;
            };
            float rgba[4];
        };
        
        typedef float (&ref)[4];
        typedef const float (&cref)[4];
        
        inline constexpr Color():
        r(1.f), g(1.f), b(1.f), a(1.f) {}
        
        inline constexpr Color(uint32_t rgba):
        r((float)(rgba & 0xFF) / 0xFF),
        g((float)((rgba >> 8) & 0xFF) / 0xFF),
        b((float)((rgba >> 16) & 0xFF) / 0xFF),
        a((float)((rgba >> 24) & 0xFF) / 0xFF) {}
        
        inline constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
        r(r / 255.f), g(g / 255.f), b(b / 255.f), a(a / 255.f) {}
        
        inline constexpr Color(cref rgba):
        r(rgba[0]), g(rgba[1]), b(rgba[2]), a(rgba[3]) {}
        
        inline Color(Color &&) = default;
        inline Color(const Color &) = default;
        
        inline void Normalize()
        {
            std::clamp(r, 0.f, 1.f);
            std::clamp(g, 0.f, 1.f);
            std::clamp(b, 0.f, 1.f);
            std::clamp(a, 0.f, 1.f);
        }
        
        inline Color& operator = (const Color &) = default;
        inline Color& operator = (Color &&) = default;
        
        inline bool operator == (const Color &src) const
        {
            return r == src.r && g == src.g && b == src.b && a == src.a;
        }
        
        inline operator ref ()
        {
            return rgba;
        }
        
        inline operator cref () const
        {
            return rgba;
        }
        
        inline Color& operator += (const Color &col)
        {
            r += col.r;
            g += col.g;
            b += col.b;
            a += col.a;
            return *this;
        }
        
        inline Color operator + (const Color &col) const
        {
            return (Color)*this += col;
        }
        
        inline Color& operator *= (const Color &col)
        {
            r *= col.r;
            g *= col.g;
            b *= col.b;
            a *= col.a;
            return *this;
        }
        
        inline Color operator * (const Color &col) const
        {
            return (Color)*this *= col;
        }
        
        inline operator uint32_t() const
        {
            return ((uint32_t)(((uint8_t)(255 * r) | ((uint32_t)((uint8_t)(255 * g)) << 8)) | (((uint32_t)(uint8_t)(255 * b)) << 16) | (((uint32_t)(uint8_t)(255 * a)) << 24)));
        }
        
        inline operator std::string() const
        {
            static std::ostringstream s;
            s.clear();
            s << std::hex << "#" << (uint32_t)*this;
            return s.str();
        }
        
        friend std::ostream& operator << (std::ostream &stream, const Color &col)
        {
            stream << (std::string)col;
            return stream;
        }
    };
    
    static inline constexpr Color colorNone(0x00, 0x00, 0x00, 0);
    static inline constexpr Color colorWhite(0xFF, 0xFF, 0xFF, 0xFF);
    static inline constexpr Color colorBlack(0x00, 0x00, 0x00, 0xFF);
    static inline constexpr Color colorRed(0xFF, 0x00, 0x00, 0xFF);
    static inline constexpr Color colorGreen(0x00, 0xFF, 0x00, 0xFF);
    static inline constexpr Color colorBlue(0x00, 0x00, 0xFF, 0xFF);
    
    static inline constexpr Color colorAqua(0x00, 0xFF, 0xFF, 0xFF);
    static inline constexpr Color colorBrown(0xA5, 0x2A, 0x2A, 0xFF);
    static inline constexpr Color colorCyan(0x00, 0xFF, 0xFF, 0xFF);
    static inline constexpr Color colorFuchsia(0xFF, 0x00, 0xFF, 0xFF);
    static inline constexpr Color colorGray(0x80, 0x80, 0x80, 0xFF);
    static inline constexpr Color colorMagenta(0xFF, 0x00, 0xFF, 0xFF);
    static inline constexpr Color colorMaroon(0x80, 0x00, 0x00, 0xFF);
    static inline constexpr Color colorNavy(0x00, 0x00, 0x80, 0xFF);
    static inline constexpr Color colorOlive(0x80, 0x80, 0x00, 0xFF);
    static inline constexpr Color colorOrange(0xFF, 0xA5, 0x00, 0xFF);
    static inline constexpr Color colorPink(0xFF, 0xC0, 0xCB, 0xFF);
    static inline constexpr Color colorPurple(0x80, 0x00, 0x80, 0xFF);
    static inline constexpr Color colorSilver(0xC0, 0xC0, 0xC0, 0xFF);
    static inline constexpr Color colorTeal(0x00, 0x80, 0x80, 0xFF);
    static inline constexpr Color colorViolet(0xEE, 0x82, 0xEE, 0xFF);
    static inline constexpr Color colorYellow(0xFF, 0xFF, 0x00, 0xFF);
    
    static constexpr float toRad = (float)M_PI / 180.f;
    static constexpr float toDeg = 180.f / (float)M_PI;
    
    struct Vector2
    {
        union
        {
            struct
            {
                float x, y;
            };
            float xy[2];
        };
        
        typedef float (&ref)[2];
        typedef const float (&cref)[2];
        
        inline constexpr Vector2():
        x(0.f), y(0.f) {}
        
        inline constexpr Vector2(const float *f):
        x(f[0]), y(f[1]) {}
        
        inline constexpr Vector2(float x, float y):
        x(x), y(y) {}
        
        inline constexpr Vector2(cref xy):
        x(xy[0]), y(xy[1]) {}
        
        inline Vector2(Vector2 &&) = default;
        inline Vector2(const Vector2 &) = default;
        inline Vector2& operator = (const Vector2 &) = default;
        inline Vector2& operator = (Vector2 &&) = default;
        
        inline operator ref ()
        {
            return xy;
        }
        
        inline operator cref () const
        {
            return xy;
        }
        
        inline Vector2& operator += (const Vector2 &vec)
        {
            x += vec.x;
            y += vec.y;
            return *this;
        }
        
        inline Vector2 operator + (const Vector2 &vec) const
        {
            return (Vector2)*this += vec;
        }
        
        inline Vector2& operator -= (const Vector2 &vec)
        {
            x -= vec.x;
            y -= vec.y;
            return *this;
        }
        
        inline Vector2 operator - (const Vector2 &vec) const
        {
            return (Vector2)*this -= vec;
        }
        
        inline Vector2& operator *= (const Vector2 &vec)
        {
            x *= vec.x;
            y *= vec.y;
            return *this;
        }
        
        inline Vector2 operator * (const Vector2 &vec) const
        {
            return (Vector2)*this *= vec;
        }
        
        inline Vector2& operator *= (float val)
        {
            x *= val;
            y *= val;
            return *this;
        }
        
        inline Vector2 operator * (float val) const
        {
            return (Vector2)*this *= val;
        }
        
        inline Vector2& operator /= (const Vector2 &vec)
        {
            x /= vec.x;
            y /= vec.y;
            return *this;
        }
        
        inline Vector2 operator / (const Vector2 &vec) const
        {
            return (Vector2)*this /= vec;
        }
        
        inline Vector2& operator /= (float val)
        {
            x /= val;
            y /= val;
            return *this;
        }
        
        inline Vector2 operator / (float val) const
        {
            return Vector2(*this) /= val;
        }
        
        inline float Dot(const Vector2 &vec) const
        {
            return x * vec.x + y * vec.y;
        }
        
        inline float Cross(const Vector2 &vec) const
        {
            return x * vec.y - vec.x * y;
        }
        
        inline float DistTo(const Vector2 &vec) const
        {
            return std::hypot(vec.x - x, vec.y - y);
        }
        
        inline float DistToQ(const Vector2 &vec) const
        {
            return (vec - *this).LengthQ();
        }
        
        inline float LengthQ() const
        {
            return x * x + y * y;
        }
        
        inline float Length() const
        {
            return std::hypot(x, y);
        }
        
        inline Vector2& Normalize()
        {
            const float len = Length();
            x /= len, y /= len;
            return *this;
        }
        
        inline Vector2 Lerp(const Vector2 &vec, float coeff) const
        {
            return *this + (vec - *this) * coeff;
        }
        
        inline float Angle(const Vector2 &vec) const
        {
            return std::atan2(y - vec.y, x - vec.x);
        }
        
        inline Vector2 Rotate(float fAngle) const
        {
            const float s = std::sin(fAngle), c = std::cos(fAngle);
            return Vector2(x * c - y * s, x * s + y * c);
        }
        
        inline Vector2 Reflect(const Vector2 &normal) const
        {
            return *this - normal * (2.f * Dot(normal));
        }
        
        inline operator std::string() const
        {
            static std::ostringstream s;
            s.clear();
            s << std::fixed << std::setprecision(2) << "(" << x << "," << y << ")";
            return s.str();
        }
        
        friend std::ostream& operator << (std::ostream &stream, const Vector2 &vec)
        {
            stream << (std::string)vec;
            return stream;
        }
    };
    
    struct Rectangle
    {
        union
        {
            struct
            {
                float x, y, width, height;
            };
            float rect[4];
        };
        
        typedef float (&ref)[4];
        typedef const float (&cref)[4];
        
        inline constexpr Rectangle():
        x(0.f), y(0.f), width(0.f), height(0.f) {}
        
        inline constexpr Rectangle(float x, float y, float width, float height):
        x(x), y(y), width(width), height(height) {}
        
        inline constexpr Rectangle(const Vector2 &vecLeftTop, const Vector2 &vecRightBottom):
        x(vecLeftTop.x), y(vecLeftTop.y), width(vecRightBottom.x - vecLeftTop.x), height(vecRightBottom.y - vecLeftTop.y) {}
        
        inline Rectangle(Rectangle &&) = default;
        inline Rectangle(const Rectangle &) = default;
        inline Rectangle& operator = (const Rectangle &) = default;
        inline Rectangle& operator = (Rectangle &&) = default;
        
        inline operator ref ()
        {
            return rect;
        }
        
        inline operator cref () const
        {
            return rect;
        }
        
        inline bool Intersects(const Rectangle &rect) const
        {
            return (x < rect.x + rect.width && x + width > rect.x && y < rect.y + rect.height && y + height > rect.y) ||
            (rect.x + rect.width < x && rect.x > x + width && rect.y + rect.height < y && rect.y > y + height);
        }
        
        inline bool Include(const Vector2 &vec) const
        {
            return vec.x > x && vec.x < x + width && vec.y > y && vec.y < y + height;
        }
        
        inline bool Include(const Rectangle &rect) const
        {
            return rect.x < x && rect.y < y && rect.x + rect.width > x + width && rect.y + rect.height > y + height;
        }
        
        inline Rectangle Intersection(const Rectangle &rect) const
        {
            if (Intersects(rect))
            {
                Rectangle result = rect;
                
                if (x > rect.x) result.x = x;
                if (y > rect.y) result.y = y;
                
                const float rectr = x + width, strectr = rect.x + rect.width;
                result.width = (rectr > strectr ? strectr : rectr) - result.x;
                
                const float rectb = y + height, strectb = rect.y + rect.height;
                result.height = (rectb > strectb ? strectb : rectb) - result.y;
                
                return result;
            }
            else
                return Rectangle();
        }
        
        inline operator std::string() const
        {
            static std::ostringstream s;
            s.clear();
            s << std::fixed << std::setprecision(2) << "[" << x << "," << y << ":" << width << "," << height << "]";
            return s.str();
        }
        
        friend std::ostream& operator << (std::ostream &stream, const Rectangle &rec)
        {
            stream << (std::string)rec;
            return stream;
        }
    };
    
    struct Vector3
    {
        union
        {
            struct
            {
                float x, y, z;
            };
            float xyz[3];
        };
        
        typedef float (&ref)[3];
        typedef const float (&cref)[3];
        
        inline constexpr Vector3():
        x(0.f), y(0.f), z(0.f) {}
        
        inline constexpr Vector3(const float *f):
        x(f[0]), y(f[1]), z(f[2]) {}
        
        inline constexpr Vector3(float x, float y, float z):
        x(x), y(y), z(z) {}
        
        inline constexpr Vector3(cref xyz):
        x(xyz[0]), y(xyz[1]), z(xyz[2]) {}
        
        inline Vector3(Vector3 &&) = default;
        inline Vector3(const Vector3 &) = default;
        inline Vector3& operator = (const Vector3 &) = default;
        inline Vector3& operator = (Vector3 &&) = default;
        
        inline operator ref ()
        {
            return xyz;
        }
        
        inline operator cref () const
        {
            return xyz;
        }
        
        inline Vector3 &operator += (const Vector3 &vec)
        {
            x += vec.x;
            y += vec.y;
            z += vec.z;
            return *this;
        }
        
        inline Vector3 operator + (const Vector3 &vec) const
        {
            return (Vector3)*this += vec;
        }
        
        inline Vector3& operator -= (const Vector3 &vec)
        {
            x -= vec.x;
            y -= vec.y;
            z -= vec.z;
            return *this;
        }
        
        inline Vector3 operator - (const Vector3 &vec) const
        {
            return (Vector3)*this -= vec;
        }
        
        inline Vector3& operator *= (const Vector3 &vec)
        {
            x *= vec.x;
            y *= vec.y;
            z *= vec.z;
            return *this;
        }
        
        inline Vector3 operator * (const Vector3 &vec) const
        {
            return (Vector3)*this *= vec;
        }
        
        inline Vector3& operator *= (float val)
        {
            x *= val;
            y *= val;
            z *= val;
            return *this;
        }
        
        inline Vector3 operator * (float val) const
        {
            return (Vector3)*this *= val;
        }
        
        inline Vector3& operator /= (const Vector3 &vec)
        {
            x /= vec.x;
            y /= vec.y;
            z /= vec.z;
            return *this;
        }
        
        inline Vector3 operator / (const Vector3 &vec) const
        {
            return (Vector3)*this /= vec;
        }
        
        inline Vector3& operator /= (float val)
        {
            x /= val;
            y /= val;
            z /= val;
            return *this;
        }
        
        inline Vector3 operator / (float val) const
        {
            return (Vector3)*this /= val;
        }
        
        inline float Dot(const Vector3 &vec) const
        {
            return x * vec.x + y * vec.y + z * vec.z;
        }
        
        inline Vector3 Cross(const Vector3 &vec) const
        {
            return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
        }
        
        inline float FlatDistance(const Vector3 &vec) const
        {
            return std::hypot(vec.x - x, vec.y - y);
        }
        
        inline float Distance(const Vector3 &vec) const
        {
            return std::hypot(vec.x - x, vec.y - y, vec.z - z);
        }
        
        inline float DistanceQ(const Vector3 &vec) const
        {
            return (vec - *this).LengthQ();
        }
        
        inline float LengthQ() const
        {
            return x * x + y * y + z * z;
        }
        
        inline float Length() const
        {
            return std::hypot(x, y, z);
        }
        
        inline Vector3& Normalize()
        {
            const float len = Length();
            x /= len, y /= len; z /= len;
            return *this;
        }
        
        inline Vector3 Lerp(const Vector3 &vec, float coeff) const
        {
            return *this + (vec - *this) * coeff;
        }
        
        inline float Angle(const Vector3 &vec) const
        {
            return std::acos(Dot(vec) / std::sqrt(LengthQ() * vec.LengthQ()));
        }
        
        inline Vector3 Rotate(float fAngle, const Vector3 &axis) const
        {
            const float s = std::sin(fAngle), c = std::cos(fAngle);
            
            Vector3 v[3];
            v[0] = axis * Dot(axis);
            v[1] = *this - v[0];
            v[2] = axis.Cross(v[1]);
            
            return Vector3(v[0].x + v[1].x * c + v[2].x * s, v[0].y + v[1].y * c + v[2].y * s, v[0].z + v[1].z * c + v[2].z * s);
        }
        
        inline Vector3 Reflect(const Vector3 &normal) const
        {
            return *this - normal * (2.f * Dot(normal));
        }
        
        inline operator std::string() const
        {
            static std::ostringstream s;
            s.clear();
            s << std::fixed << std::setprecision(4) << "(" << x << "," << y << "," << z << ")";
            return s.str();
        }
        
        friend std::ostream& operator << (std::ostream &stream, const Vector3 &vec)
        {
            stream << (std::string)vec;
            return stream;
        }
    };
    
    struct Matrix4
    {
        union
        {
            struct
            {
                float
                _00, _01, _02, _03,
                _10, _11, _12, _13,
                _20, _21, _22, _23,
                _30, _31, _32, _33;
            };
            float _1D[16];
            float _2D[4][4];
        };
        
        typedef float (&ref)[16];
        typedef const float (&cref)[16];
        
        inline constexpr Matrix4():
        _00(0), _01(0), _02(0), _03(0),
        _10(0), _11(0), _12(0), _13(0),
        _20(0), _21(0), _22(0), _23(0),
        _30(0), _31(0), _32(0), _33(0) {}
        
        inline constexpr Matrix4(
                       float _00, float _01, float _02, float _03,
                       float _10, float _11, float _12, float _13,
                       float _20, float _21, float _22, float _23,
                       float _30, float _31, float _32, float _33):
        _00(_00), _01(_01), _02(_02), _03(_03),
        _10(_10), _11(_11), _12(_12), _13(_13),
        _20(_20), _21(_21), _22(_22), _23(_23),
        _30(_30), _31(_31), _32(_32), _33(_33) {}
        
        inline operator ref ()
        {
            return _1D;
        }
        
        inline operator cref () const
        {
            return _1D;
        }
        
        inline Matrix4(Matrix4 &&) = default;
        inline Matrix4(const Matrix4 &) = default;
        inline Matrix4& operator = (const Matrix4 &) = default;
        inline Matrix4& operator = (Matrix4 &&) = default;
        
        inline Matrix4& operator += (float right)
        {
            for (int i = 0; i < 16; ++i)
                _1D[i] += right;
            return *this;
        }
        
        inline Matrix4& operator -= (float right)
        {
            for (int i = 0; i < 16; ++i)
                _1D[i] -= right;
            return *this;
        }
        
        inline Matrix4& operator *= (float right)
        {
            for (int i = 0; i < 16; ++i)
                _1D[i] *= right;
            return *this;
        }
        
        inline Matrix4& operator /= (float right)
        {
            for (int i = 0; i < 16; ++i)
                _1D[i] /= right;
            return *this;
        }
        
        inline Matrix4& operator += (const Matrix4 &right)
        {
            for (int i = 0; i < 16; ++i)
                _1D[i] += right._1D[i];
            return *this;
        }
        
        inline Matrix4& operator -= (const Matrix4 &right)
        {
            for (int i = 0; i < 16; ++i)
                _1D[i] -= right._1D[i];
            return *this;
        }
        
        inline Matrix4& operator *= (const Matrix4 &right)
        {
            return *this = *this * right;
        }
        
        inline Matrix4 operator + (float right) const
        {
            return (Matrix4)*this += right;
        }
        
        inline Matrix4 operator - (float right) const
        {
            return (Matrix4)*this -= right;
        }
        
        inline Matrix4 operator * (float right) const
        {
            return (Matrix4)*this *= right;
        }
        
        inline Matrix4 operator / (float right) const
        {
            return (Matrix4)*this /= right;
        }
        
        inline Matrix4 operator + (const Matrix4 &right) const
        {
            return (Matrix4)*this += right;
        }
        
        inline Matrix4 operator - (const Matrix4 &right) const
        {
            return (Matrix4)*this -= right;
        }
        
        inline Matrix4 operator * (const Matrix4 &right) const
        {
            Matrix4 product;
            
            product._2D[0][0] = _2D[0][0] * right._2D[0][0] + _2D[0][1] * right._2D[1][0] + _2D[0][2] * right._2D[2][0] + _2D[0][3] * right._2D[3][0];
            product._2D[1][0] = _2D[1][0] * right._2D[0][0] + _2D[1][1] * right._2D[1][0] + _2D[1][2] * right._2D[2][0] + _2D[1][3] * right._2D[3][0];
            product._2D[2][0] = _2D[2][0] * right._2D[0][0] + _2D[2][1] * right._2D[1][0] + _2D[2][2] * right._2D[2][0] + _2D[2][3] * right._2D[3][0];
            product._2D[3][0] = _2D[3][0] * right._2D[0][0] + _2D[3][1] * right._2D[1][0] + _2D[3][2] * right._2D[2][0] + _2D[3][3] * right._2D[3][0];
            product._2D[0][1] = _2D[0][0] * right._2D[0][1] + _2D[0][1] * right._2D[1][1] + _2D[0][2] * right._2D[2][1] + _2D[0][3] * right._2D[3][1];
            product._2D[1][1] = _2D[1][0] * right._2D[0][1] + _2D[1][1] * right._2D[1][1] + _2D[1][2] * right._2D[2][1] + _2D[1][3] * right._2D[3][1];
            product._2D[2][1] = _2D[2][0] * right._2D[0][1] + _2D[2][1] * right._2D[1][1] + _2D[2][2] * right._2D[2][1] + _2D[2][3] * right._2D[3][1];
            product._2D[3][1] = _2D[3][0] * right._2D[0][1] + _2D[3][1] * right._2D[1][1] + _2D[3][2] * right._2D[2][1] + _2D[3][3] * right._2D[3][1];
            product._2D[0][2] = _2D[0][0] * right._2D[0][2] + _2D[0][1] * right._2D[1][2] + _2D[0][2] * right._2D[2][2] + _2D[0][3] * right._2D[3][2];
            product._2D[1][2] = _2D[1][0] * right._2D[0][2] + _2D[1][1] * right._2D[1][2] + _2D[1][2] * right._2D[2][2] + _2D[1][3] * right._2D[3][2];
            product._2D[2][2] = _2D[2][0] * right._2D[0][2] + _2D[2][1] * right._2D[1][2] + _2D[2][2] * right._2D[2][2] + _2D[2][3] * right._2D[3][2];
            product._2D[3][2] = _2D[3][0] * right._2D[0][2] + _2D[3][1] * right._2D[1][2] + _2D[3][2] * right._2D[2][2] + _2D[3][3] * right._2D[3][2];
            product._2D[0][3] = _2D[0][0] * right._2D[0][3] + _2D[0][1] * right._2D[1][3] + _2D[0][2] * right._2D[2][3] + _2D[0][3] * right._2D[3][3];
            product._2D[1][3] = _2D[1][0] * right._2D[0][3] + _2D[1][1] * right._2D[1][3] + _2D[1][2] * right._2D[2][3] + _2D[1][3] * right._2D[3][3];
            product._2D[2][3] = _2D[2][0] * right._2D[0][3] + _2D[2][1] * right._2D[1][3] + _2D[2][2] * right._2D[2][3] + _2D[2][3] * right._2D[3][3];
            product._2D[3][3] = _2D[3][0] * right._2D[0][3] + _2D[3][1] * right._2D[1][3] + _2D[3][2] * right._2D[2][3] + _2D[3][3] * right._2D[3][3];
            
            return product;
        }
        
        inline Vector3 ApplyToVector(const Vector3 &vec) const
        {
            return Vector3(vec.xyz[0] * _2D[0][0] + vec.xyz[1] * _2D[1][0] + vec.xyz[2] * _2D[2][0],
                           vec.xyz[0] * _2D[0][1] + vec.xyz[1] * _2D[1][1] + vec.xyz[2] * _2D[2][1],
                           vec.xyz[0] * _2D[0][2] + vec.xyz[1] * _2D[1][2] + vec.xyz[2] * _2D[2][2]);
        }
        
        void Decompose(Vector3 &scale, Matrix4 &rotation, Vector3 &translation) const
        {
            translation.x = _2D[3][0];
            translation.y = _2D[3][1];
            translation.z = _2D[3][2];
            
            scale.x = (std::signbit(_2D[0][0] * _2D[0][1] * _2D[0][2] * _2D[0][3]) ? -1.f : 1.f) * Vector3(_2D[0][0], _2D[0][1], _2D[0][2]).Length();
            scale.y = (std::signbit(_2D[1][0] * _2D[1][1] * _2D[1][2] * _2D[1][3]) ? -1.f : 1.f) * Vector3(_2D[1][0], _2D[1][1], _2D[1][2]).Length();
            scale.z = (std::signbit(_2D[2][0] * _2D[2][1] * _2D[2][2] * _2D[2][3]) ? -1.f : 1.f) * Vector3(_2D[2][0], _2D[2][1], _2D[2][2]).Length();
            
            if (scale.x == 0.f || scale.x == 0.f || scale.x == 0.f)
            {
                rotation = Matrix4();
                return;
            }
            
            rotation = Matrix4(
                               _2D[0][0] / scale.x, _2D[0][1] / scale.x, _2D[0][2] / scale.x, 0.f,
                               _2D[1][0] / scale.y, _2D[1][1] / scale.y, _2D[1][2] / scale.y, 0.f,
                               _2D[2][0] / scale.z, _2D[2][1] / scale.z, _2D[2][2] / scale.z, 0.f,
                               0.f, 0.f, 0.f, 1.f);
        }
        
        inline Matrix4 Inverse() const
        {
            float mat[4][8] =
            {
                {_2D[0][0], _2D[0][1], _2D[0][2], _2D[0][3], 1, 0, 0, 0},
                {_2D[1][0], _2D[1][1], _2D[1][2], _2D[1][3], 0, 1, 0, 0},
                {_2D[2][0], _2D[2][1], _2D[2][2], _2D[2][3], 0, 0, 1, 0},
                {_2D[3][0], _2D[3][1], _2D[3][2], _2D[3][3], 0, 0, 0, 1}
            };
            float *rows[4] = { mat[0], mat[1], mat[2], mat[3] };
            int i, r;
            
            for (i = 0; i < 4; ++i)
            {
                int row_num = i;
                float major = fabs(rows[i][i]);
                
                for (r = i + 1; r < 4; ++r)
                {
                    const float cur_abs = fabs(rows[r][i]);
                    if (cur_abs > major)
                    {
                        major = cur_abs;
                        row_num = r;
                    }
                }
                
                if (row_num != i)
                {
                    (uintptr_t &)rows[i] ^= (uintptr_t)rows[row_num];
                    (uintptr_t &)rows[row_num] ^= (uintptr_t)rows[i];
                    (uintptr_t &)rows[i] ^= (uintptr_t)rows[row_num];
                }
                
                for (r = i + 1; r < 4; ++r)
                {
                    const float factor = rows[r][i] / rows[i][i];
                    for (int c = i; c < 8; ++c)
                        rows[r][c] -= factor * rows[i][c];
                }
            }
            
            for (i = 3; i > 0; --i)
                for (r = 0; r < i; ++r)
                {
                    const float factor = rows[r][i] / rows[i][i];
                    for (int c = 4; c < 8; ++c)
                        rows[r][c] -= factor * rows[i][c];
                }
            
            return Matrix4(
                           rows[0][4] / rows[0][0], rows[0][5] / rows[0][0], rows[0][6] / rows[0][0], rows[0][7] / rows[0][0],
                           rows[1][4] / rows[1][1], rows[1][5] / rows[1][1], rows[1][6] / rows[1][1], rows[1][7] / rows[1][1],
                           rows[2][4] / rows[2][2], rows[2][5] / rows[2][2], rows[2][6] / rows[2][2], rows[2][7] / rows[2][2],
                           rows[3][4] / rows[3][3], rows[3][5] / rows[3][3], rows[3][6] / rows[3][3], rows[3][7] / rows[3][3]);
        }
        
        inline Matrix4 Transpose() const
        {
            return Matrix4(
                           _2D[0][0], _2D[1][0], _2D[2][0], _2D[3][0],
                           _2D[0][1], _2D[1][1], _2D[2][1], _2D[3][1],
                           _2D[0][2], _2D[1][2], _2D[2][2], _2D[3][2],
                           _2D[0][3], _2D[1][3], _2D[2][3], _2D[3][3]);
        }
        
        inline Matrix4 Billboard() const
        {
            return Matrix4(
                           (std::signbit(_2D[0][0] * _2D[0][1] * _2D[0][2] * _2D[0][3]) ? -1.f : 1.f) * Vector3(_2D[0][0], _2D[0][1], _2D[0][2]).Length(), 0.f, 0.f, _2D[0][3],
                           0.f, (std::signbit(_2D[1][0] * _2D[1][1] * _2D[1][2] * _2D[1][3]) ? -1.f : 1.f) * Vector3(_2D[1][0], _2D[1][1], _2D[1][2]).Length(), 0.f, _2D[1][3],
                           0.f, 0.f, (std::signbit(_2D[2][0] * _2D[2][1] * _2D[2][2] * _2D[2][3]) ? -1.f : 1.f) * Vector3(_2D[2][0], _2D[2][1], _2D[2][2]).Length(), _2D[2][3],
                           _2D[3][0], _2D[3][1], _2D[3][2], _2D[3][3]);
        }
        
        static inline constexpr Matrix4 Identity()
        {
            return Matrix4(
                           1.f, 0.f, 0.f, 0.f,
                           0.f, 1.f, 0.f, 0.f,
                           0.f, 0.f, 1.f, 0.f,
                           0.f, 0.f, 0.f, 1.f);
        }
        
        static inline constexpr Matrix4 MatrixScale(const Vector3 &vec)
        {
            return Matrix4(
                           vec.x, 0.f, 0.f, 0.f,
                           0.f, vec.y, 0.f, 0.f,
                           0.f, 0.f, vec.z, 0.f,
                           0.f, 0.f, 0.f, 1.f);
        }
        
        static inline constexpr Matrix4 MatrixTranslate(const Vector3 &vec)
        {
            return Matrix4(
                           1.f, 0.f, 0.f, 0.f,
                           0.f, 1.f, 0.f, 0.f,
                           0.f, 0.f, 1.f, 0.f,
                           vec.x, vec.y, vec.z, 1.f);
        }
        
        static inline Matrix4 MatrixRotate(float angle, Vector3 axis)
        {
            axis.Normalize();
            const float s = std::sin(angle), c = std::cos(angle), t = 1.f - c;
            return Matrix4(
                           (1.f - axis.x * axis.x) * c + axis.x * axis.x,   axis.z * s + axis.x * axis.y * t,               axis.x * axis.z * t - axis.y * s,               0.f,
                           axis.x * axis.y * t - axis.z * s,                (1.f - axis.y * axis.y) * c + axis.y * axis.y,  axis.y * axis.z * t + axis.x * s,               0.f,
                           axis.x * axis.z * t + axis.y * s,                axis.y * axis.z * t - axis.x * s,               (1.f - axis.z * axis.z) * c + axis.z * axis.z,  0.f,
                           0.f, 0.f, 0.f, 1.f);
        }
        
        inline operator std::string() const
        {
            static std::ostringstream s;
            s.clear();
            s << std::fixed << std::setprecision(4) << std::endl;
            s << "|" << _2D[0][0] << " " << _2D[1][0] << " " << _2D[2][0] << " " << _2D[3][0] << "|" << std::endl;
            s << "|" << _2D[0][1] << " " << _2D[1][1] << " " << _2D[2][1] << " " << _2D[3][1] << "|" << std::endl;
            s << "|" << _2D[0][2] << " " << _2D[1][2] << " " << _2D[2][2] << " " << _2D[3][2] << "|" << std::endl;
            s << "|" << _2D[0][3] << " " << _2D[1][3] << " " << _2D[2][3] << " " << _2D[3][3] << "|" << std::endl;
            return s.str();
        }
        
        friend std::ostream& operator << (std::ostream &stream, const Matrix4 &mat)
        {
            stream << (std::string)mat;
            return stream;
        }
    };
}

