#pragma once

#include "../Core/LinearCombination3.h"

namespace cagd
{

    class AlgebraicHyperbolicArc3: public LinearCombination3
    {
    protected:
        GLdouble            alpha;

        GLdouble F0(GLdouble u) const
        {
            return F3(alpha - u);
        }

        GLdouble F1(GLdouble u) const
        {
            return F2(alpha - u);
        }

        GLdouble F2(GLdouble u) const
        {
            return ((alpha - u + sinh(alpha - u) + sinh(u) - sinh(alpha) + u*cosh(alpha) - alpha*cosh(u))*sinh(alpha))
                        /((alpha - sinh(alpha))*(2*sinh(alpha) - alpha - alpha*cosh(alpha)));
        }

        GLdouble F3(GLdouble u) const
        {
            return (u - sinh(u))/(alpha - sinh(alpha));
        }


        GLdouble dF0(GLdouble u) const
        {
            return dF3(alpha - u) * (-1);
        }

        GLdouble dF1(GLdouble u) const
        {
            return dF2(alpha - u) * (-1);
        }

        GLdouble dF2(GLdouble u) const
        {
            return (sinh(alpha)*(cosh(alpha) - cosh(alpha - u) - alpha * sinh(u) + cosh(u) - 1))
                    /((alpha - sinh(alpha))*(-alpha + 2 * sinh(alpha) + alpha * (-cosh(alpha))));
        }

        GLdouble dF3(GLdouble u) const
        {
            return (1 - cosh(u))/(alpha - sinh(alpha));
        }

        GLdouble ddF0(GLdouble u) const
        {
            return ddF3(alpha - u);
        }

        GLdouble ddF1(GLdouble u) const
        {
            return ddF2(alpha - u);
        }

        GLdouble ddF2(GLdouble u) const
        {
            return (sinh(alpha)*(-sinh(u - alpha) - alpha*cosh(u) + sinh(u)))
                    /((alpha - sinh(alpha))*(-alpha + 2*sinh(alpha) + alpha*(-cosh(alpha))));
        }

        GLdouble ddF3(GLdouble u) const
        {
            return (sinh(u))/(sinh(alpha) - alpha);
        }

    public:
        AlgebraicHyperbolicArc3(GLdouble _alpha);
        GLboolean BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble>& values) const;
        GLboolean CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives &d) const;
        void set_alpha(double value);
        double get_alpha();
    };
}
