
#pragma once

#include "../Core/TensorProductSurfaces3.h"

namespace cagd
{
    class AlgebraicHyperbolicPatch: public TensorProductSurface3
    {
    protected:
        // shape parameter
        GLdouble            alpha;
    public:
        AlgebraicHyperbolicPatch(GLdouble alpha);
        AlgebraicHyperbolicPatch();

        // we have to implement pure virtual methods introduced in class TensorProductSurface3
        GLboolean UBlendingFunctionValues(GLdouble u_knot, RowMatrix<GLdouble> &blending_values) const;
        GLboolean VBlendingFunctionValues(GLdouble v_knot, RowMatrix<GLdouble> &blending_values) const;
        GLboolean CalculatePartialDerivatives(GLuint maximum_order_of_partial_derivatives, GLdouble u, GLdouble v, PartialDerivatives &pd) const;
        // ...
        void AlgebraicHyperbolicPatch::set_alpha(double value);

        double AlgebraicHyperbolicPatch::get_alpha();
    private:
//        GLdouble F2(GLdouble u) const
//        {
//            return ((alpha - u + sinh(alpha - u) + sinh(u) - sinh(alpha) + u*cosh(alpha) - alpha*cosh(u))*sinh(alpha))
//                        /((alpha - sinh(alpha))*(2*sinh(alpha) - alpha - alpha*cosh(alpha)));
//        }

//        GLdouble F3(GLdouble u) const
//        {
//            return (u - sinh(u))/(alpha - sinh(alpha));
//        }

//        GLdouble dF2(GLdouble u) const
//        {
//            return (sinh(alpha)*(cosh(alpha) - cosh(alpha - u) - alpha * sinh(u) + cosh(u) - 1))
//                    /((alpha - sinh(alpha))*(-alpha + 2 * sinh(alpha) + alpha * (-cosh(alpha))));
//        }

//        GLdouble dF3(GLdouble u) const
//        {
//            return (1 - cosh(u))/(alpha - sinh(alpha));
//        }
        GLdouble H(GLdouble t) const
                {
                            return (((4-4*cos(alpha) - 2*alpha*sin(alpha))/((alpha*alpha-4*cos(alpha)-4*alpha*sin(alpha)+alpha*alpha*cos(alpha) + 4)*(alpha*alpha-4*cos(alpha)-4*alpha*sin(alpha)+alpha*alpha*cos(alpha) + 4))) * (2*alpha*(sin(t) - sin(alpha)) - 2*alpha*(1 - cos(alpha))*t + alpha*alpha + 2*alpha*sin(alpha-t) - alpha*alpha*cos(alpha-t)+ alpha*alpha*(cos(alpha) - cos(t)) + 2*(1-cos(alpha))*t*t + alpha*(alpha-t)*t*sin(alpha)));
                }
                GLdouble K(GLdouble t) const
                {
                    return ((2*(alpha-sin(alpha)))/((2*cos(alpha)+alpha*alpha-2)*(alpha*alpha-4*cos(alpha) - 4*alpha*sin(alpha) + alpha*alpha*cos(alpha)+4)) * (2*(alpha-t) + 2*(sin(t)-sin(alpha)) + 2*(t*cos(alpha) - alpha*cos(t)) + 2*sin(alpha - t) + alpha*alpha*(t-sin(t)) - (alpha - sin(alpha))*t*t));
                }
                GLdouble F2(GLdouble t) const
                {
                    return (1.0/2 * H(t) + K(t));
                }

                GLdouble F3(GLdouble t) const
                {
                    return ((1/(2*cos(alpha) + alpha*alpha - 2)) * (2*cos(t) + t*t -2));
                 }
                GLdouble dH(GLdouble t) const
                {
                    return (((4-4*cos(alpha) - 2*alpha*sin(alpha))/((alpha*alpha-4*cos(alpha)-4*alpha*sin(alpha)+alpha*alpha*cos(alpha) + 4)*(alpha*alpha-4*cos(alpha)-4*alpha*sin(alpha)+alpha*alpha*cos(alpha) + 4))) * (alpha*alpha*sin(alpha)-2*alpha+2*alpha*cos(alpha)+alpha*alpha*sin(t)-alpha*alpha*sin(alpha-t)-2*alpha*t*sin(alpha) + 2*alpha*cos(t)-2*alpha*cos(alpha-t)-4*t*cos(alpha)+4*t));
                }
                GLdouble dK(GLdouble t) const
                {
                    return ((2*(alpha-sin(alpha)))/((2*cos(alpha)+alpha*alpha-2)*(alpha*alpha-4*cos(alpha) - 4*alpha*sin(alpha) + alpha*alpha*cos(alpha)+4)) * (alpha*alpha+2*cos(alpha)-(alpha*alpha-2)*cos(t)-2*alpha*t+2*alpha*sin(t)+2*t*sin(alpha)-2*cos(alpha-t)-2));
                }

                GLdouble dF2(GLdouble t) const
                {
                            return (1.0/2 * dH(t) + dK(t));
                }
                GLdouble dF3(GLdouble t) const
                {
                            return ((1/(2*cos(alpha) + alpha*alpha - 2)) * (2*(t-sin(t))));
                }

    };

}
