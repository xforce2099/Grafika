#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"
#include "../Core/DCoordinates3.h"
using namespace cagd;
using namespace std;

GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}

GLdouble torus_knot::u_min = 0;
GLdouble torus_knot::u_max = 6*PI;

DCoordinate3 torus_knot::d0(GLdouble u)
{
    return DCoordinate3((2.0 * cos(2.0*u/3.0))*cos(u), (2.0 * cos(2.0*u/3.0))* sin(u), sin(2.0*u/3.0));
}

DCoordinate3 torus_knot::d1(GLdouble u)
{
    GLdouble c = cos(2.0*u/3.0), s = sin(2.0*u/3.0);
    return DCoordinate3(-2.0*c*sin(u)-4.0/3.0*s*cos(u),2.0*c*cos(u)-4.0/3.0*s*sin(u), 2.0/3.0*c);
   // return DCoordinate3(0,0,0);
}

DCoordinate3 torus_knot::d2(GLdouble u)
{
   return DCoordinate3(-1.0/9.0*(25.0*cos(5.0*u/3.0)+cos(u/3.0)),
                        -1.0/9.0*(25.0*sin(5.0*u/3.0)+sin(u/3.0)),
                        -4/9 * sin(2.0*u/3.0));
    //return DCoordinate3(0,0,0);
}

GLdouble lissajous::u_min = 0;
GLdouble lissajous::u_max = +TWO_PI;
GLdouble lissajous::a = 5.0;
GLdouble lissajous::b = 4.0;
GLdouble lissajous::kx = 3.0;
GLdouble lissajous::ky = 7.0;

DCoordinate3 lissajous::d0(GLdouble u)
{
    return DCoordinate3(a * cos(kx*u), b * sin(ky*u),a * sin(kx*u));
}

DCoordinate3 lissajous::d1(GLdouble u)
{
    //GLdouble c = cos(u), s = sin(u);
    //return DCoordinate3(c - u * s, s + u * c, 1.0);
    return DCoordinate3(-kx*a*sin(kx*u),ky*b*cos(ky*u),kx*a*cos(kx*u));
}

DCoordinate3 lissajous::d2(GLdouble u)
{
   // GLdouble c = cos(u), s = sin(u);
    //return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
    return DCoordinate3(-kx*kx*a*cos(kx*u),-ky*ky*b*sin(ky*u),-kx*kx*a*sin(kx*u));
}

GLdouble  rose::u_min = 0.0;
GLdouble  rose::u_max = 5.0*TWO_PI;
GLdouble  rose::k = 4.0;

DCoordinate3 rose::d0(GLdouble u)
{
    return DCoordinate3(cos(k*u) * cos(u), cos(k*u) * sin(u), sin(u));
}

DCoordinate3  rose::d1(GLdouble u)
{
    return DCoordinate3(-k*cos(u)*sin(k*u)-sin(u)*cos(k*u),cos(u)*cos(k*u)-k*sin(u)*sin(k*u),cos(u));
}

DCoordinate3  rose::d2(GLdouble u)
{
    return DCoordinate3(2.0*sin(u)*sin(k*u)+(-1.0*(k*k)-1)*cos(u)*cos(k*u),(-1.0*(k*k)-1.0)*sin(u)*cos(k*u)-2.0*k*cos(u)*cos(k*u),-sin(u));
}

GLdouble  hypocycloid::u_min = -TWO_PI;
GLdouble  hypocycloid::u_max = TWO_PI;
GLdouble  hypocycloid::k = 10.0;
GLdouble  hypocycloid::r = 0.7;

DCoordinate3 hypocycloid::d0(GLdouble u)
{
    return DCoordinate3(r*(k-1)*cos(u) + r*cos((k-1)*u), r*(k-1)*sin(u) - r*sin((k-1)*u), cos((k-1)*u));
}

DCoordinate3  hypocycloid::d1(GLdouble u)
{
    return DCoordinate3(-(k-1)*r*(sin((k-1)*u)+sin(u)), -(k-1)*r*(cos((k-1)*u)-cos(u)), -(k-1)*sin((k-1)*u));
}

DCoordinate3  hypocycloid::d2(GLdouble u)
{
    return DCoordinate3(-(k-1)*r*((k-1)*cos((k-1)*u)+cos(u)),(k-1)*r*((k-1)*sin((k-1)*u)-sin(u)),-(k-1)*(k-1)*cos((k-1)*u));
}

/*GLdouble right_conoid::u_min = -TWO_PI;
GLdouble right_conoid::u_max = TWO_PI;
GLdouble right_conoid::v_min = -TWO_PI;
GLdouble right_conoid::v_max = TWO_PI;
GLdouble right_conoid::parameter1 = 2;

DCoordinate3 right_conoid::d00(GLdouble u, GLdouble v)
{
    GLdouble s = sin(u),c = cos(u);
    return DCoordinate3(v * c, v * s, parameter1 * s);
}

DCoordinate3 right_conoid::d01(GLdouble u, GLdouble v)
{
    GLdouble s = sin(u),c = cos(u);
    return DCoordinate3(- v * s, v * c, parameter1 *c);
}

DCoordinate3 right_conoid::d10(GLdouble u, GLdouble v)
{
    GLdouble s = sin(u),c = cos(u);
    return DCoordinate3(s,  c, 0);
}
*/

GLdouble Hyperboloid::u_min = 0;
GLdouble Hyperboloid::u_max = 3;
GLdouble Hyperboloid::v_min = 0;
GLdouble Hyperboloid::v_max = TWO_PI;

DCoordinate3 Hyperboloid::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((1 + cosh(u-3.0/2))*sin(v),
                        (1+ cosh(u-3.0/2))*cos(v),
                        sinh(u-3.0/2));
}
DCoordinate3 Hyperboloid::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(sinh(3.0/2-u)*(-sin(v)),
                        sinh(3.0/2-u)*(-cos(v)),
                        cosh(3.0/2-u));
}
DCoordinate3 Hyperboloid::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3((cosh(3.0/2-u)+1)*cos(v),
                        -(cosh(3.0/2-u)+1)*sin(v),
                        0);
}

GLdouble torus::u_min = 0;
GLdouble torus::u_max = TWO_PI;
GLdouble torus::v_min = 0;
GLdouble torus::v_max = TWO_PI;
GLdouble torus::r = 2;
GLdouble torus::R = 4;

DCoordinate3 torus::d00(GLdouble u, GLdouble v)
{
    GLdouble c2 = cos(v),c = cos(u),s = sin(v),s2 = sin(u);
    return DCoordinate3((R+r*s2)*c2, (R+r*s2) * s, r * c);
}

DCoordinate3 torus::d01(GLdouble u, GLdouble v)
{
    GLdouble s2 = sin(v), c = cos(u), c2 = cos(v), s=sin(u);
    return DCoordinate3(-s2 * (R + r * s), c2 * (R + r * s), 0);
}

DCoordinate3 torus::d10(GLdouble u, GLdouble v)
{
    GLdouble s = sin(u),s2 = sin(v), c = cos(u), c2 = cos(v);
    return DCoordinate3(r * c * c2,  r * c * s2, -s * r);
}

//sphere
/*GLdouble sphere::u_min = 0;
GLdouble sphere::u_max = TWO_PI;
GLdouble sphere::v_min = 0;
GLdouble sphere::v_max = PI;
GLdouble sphere::r = 2;
GLdouble sphere::x0 = 0;
GLdouble sphere::y0 = 0;
GLdouble sphere::z0 = 0;

DCoordinate3 sphere::d00(GLdouble u, GLdouble v)
{
    GLdouble c2 = cos(v),c = cos(u),s = sin(v),s2 = sin(u);
    return DCoordinate3(x0 + r * c * s, y0 + r * s2 * s, z0 + r * c2);
}

DCoordinate3 sphere::d01(GLdouble u, GLdouble v)
{
    GLdouble s = sin(u), s2 = sin(v), c = cos(u), c2 = cos(v);
    return DCoordinate3(r * c * c2, r * s * c2, -r * s2);
}

DCoordinate3 sphere::d10(GLdouble u, GLdouble v)
{
    GLdouble s = sin(u),s2 = sin(v), c = cos(u);
    return DCoordinate3(-r * s * s2, r * c * s2, 0);
}*/

GLdouble Cylindrical_helicoid::u_min = 0;
GLdouble Cylindrical_helicoid::u_max = 2;
GLdouble Cylindrical_helicoid::v_min = 0;
GLdouble Cylindrical_helicoid::v_max = TWO_PI;

DCoordinate3 Cylindrical_helicoid::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((2+u)*cos(v),
                        (2+u)*sin(v),
                        v);
}
DCoordinate3 Cylindrical_helicoid::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(v),
                        sin(v),
                        0);
}
DCoordinate3 Cylindrical_helicoid::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-(u+2)*sin(v),
                        (u+2)*cos(v),
                        1);
}


//dini_surface
GLdouble dini_surface::u_min = 0;
GLdouble dini_surface::u_max = TWO_PI;
GLdouble dini_surface::v_min = 0;
GLdouble dini_surface::v_max = PI;
GLdouble dini_surface::a = 1;
GLdouble dini_surface::b = 0.15;

DCoordinate3 dini_surface::d00(GLdouble u, GLdouble v)
{
    GLdouble c2 = cos(v),c = cos(u),s = sin(v),s2 = sin(u);
    return DCoordinate3(a * c * s, a * s2 * s, a * (c2 + log(tan(v / 2))) + b * u);
}

DCoordinate3 dini_surface::d01(GLdouble u, GLdouble v)
{
    GLdouble s = sin(u), s2 = sin(v), c = cos(u), c2 = cos(v);
    return DCoordinate3(a * c * c2, a * s * c2, -a * s2 - (2 * a * s2) / (cos(2 * v) - 1));
}

DCoordinate3 dini_surface::d10(GLdouble u, GLdouble v)
{
    GLdouble s = sin(u),s2 = sin(v), c = cos(u);
    return DCoordinate3(-a * s * s2, a * c * s2, b);
}

/*kutya*/
GLdouble KleinBottle::u_min = 0.0;
GLdouble KleinBottle::u_max = TWO_PI;
GLdouble KleinBottle::v_min = 0.0;
GLdouble KleinBottle::v_max = TWO_PI;

DCoordinate3 KleinBottle::d00(GLdouble u, GLdouble v)
{
        return DCoordinate3(3 * cos(u) + 1.0/2.0 * (1 + cos(2 * u)) * sin(v) - 1/2 * sin(2 * u) * sin(2 * v),
                                                3 * sin(u) + 1/2 * sin(2 * u) * sin(v) - 1.0/2.0 * (1 - cos(2 * u)) * sin(2 * v),
                                                cos(u) * sin(2 * v) + sin(u) * sin(v));
}

DCoordinate3 KleinBottle::d10(GLdouble u, GLdouble v)
{
        return DCoordinate3(-3 * sin(u) + (1/2 - sin(2 * u)) * sin(v) + cos(2 * u) * sin(2 * v),
                                                3 * cos(u) + cos(2 * u) * sin(v) -(1.0/2.0 + sin(2 * u)) * sin(2 * v),
                                                -sin(u) * sin(2 * v) + cos(u) * sin(v));
}

DCoordinate3 KleinBottle::d01(GLdouble u, GLdouble v)
{
        return DCoordinate3(3 * cos(u) + 1/2 * (1 + cos(2 * u)) * cos(v) - sin(2 * u) * cos(2 * v),
                                                3 * sin(u) + 1.0/2.0 * sin(2 * u) * cos(v) + (1 - cos(2 * u)) * cos(2 * v),
                                                2 * cos(u) * cos(2 * v) + sin(u) * cos(v));
}
