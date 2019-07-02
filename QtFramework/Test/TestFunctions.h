#pragma once

#include "../Core/DCoordinates3.h"

namespace cagd
{
    namespace spiral_on_cone
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace torus_knot
    {
        extern GLdouble u_min, u_max;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace lissajous
    {
        extern GLdouble u_min, u_max;
        extern GLdouble a, b,kx,ky ;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace rose {
        extern GLdouble u_min, u_max,k;

        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    namespace hypocycloid {
        extern GLdouble u_min, u_max,k,r;
        DCoordinate3 d0(GLdouble);
        DCoordinate3 d1(GLdouble);
        DCoordinate3 d2(GLdouble);
    }

    /*namespace right_conoid{
        extern GLdouble parameter1;
        extern GLdouble u_min, u_max, v_min, v_max;

        DCoordinate3 d00(GLdouble u, GLdouble v);
        DCoordinate3 d10(GLdouble u, GLdouble v);  //u
        DCoordinate3 d01(GLdouble u, GLdouble v);  //v
    }*/

    namespace Hyperboloid{
        extern GLdouble u_min, u_max, v_min, v_max;
        DCoordinate3 d00(GLdouble u, GLdouble v);
        DCoordinate3 d10(GLdouble u, GLdouble v);
        DCoordinate3 d01(GLdouble u, GLdouble v);
    }

    namespace torus{
        extern GLdouble r,R;
        extern GLdouble u_min, u_max, v_min, v_max;

        DCoordinate3 d00(GLdouble u, GLdouble v);
        DCoordinate3 d10(GLdouble u, GLdouble v);  //u
        DCoordinate3 d01(GLdouble u, GLdouble v);  //v
    }

    /*namespace sphere{
        extern GLdouble r;
        extern GLdouble u_min, u_max, v_min, v_max, x0, y0, z0;

        DCoordinate3 d00(GLdouble u, GLdouble v);
        DCoordinate3 d10(GLdouble u, GLdouble v);  //u
        DCoordinate3 d01(GLdouble u, GLdouble v);  //v
    }*/

    namespace Cylindrical_helicoid{
        extern GLdouble u_min, u_max, v_min, v_max;
        DCoordinate3 d00(GLdouble u, GLdouble v);
        DCoordinate3 d10(GLdouble u, GLdouble v);
        DCoordinate3 d01(GLdouble u, GLdouble v);
    }

    namespace dini_surface{
        extern GLdouble a,b;
        extern GLdouble u_min, u_max, v_min, v_max, a, b;

        DCoordinate3 d00(GLdouble u, GLdouble v);
        DCoordinate3 d10(GLdouble u, GLdouble v);  //u
        DCoordinate3 d01(GLdouble u, GLdouble v);  //v
    }

    namespace KleinBottle
    {
        // definition domain
        extern GLdouble u_min, u_max,
                        v_min, v_max;
        DCoordinate3 d00(GLdouble u, GLdouble v);
        DCoordinate3 d10(GLdouble u, GLdouble v);
        DCoordinate3 d01(GLdouble u, GLdouble v);
    }
}
