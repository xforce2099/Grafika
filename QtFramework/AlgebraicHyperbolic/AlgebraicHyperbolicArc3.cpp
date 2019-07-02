#include "AlgebraicHyperbolicArc3.h"

#include <cmath>

using namespace cagd;

AlgebraicHyperbolicArc3::AlgebraicHyperbolicArc3(GLdouble _alpha): LinearCombination3(0.0, _alpha, 4)
{
    this->alpha = _alpha;
}

GLboolean AlgebraicHyperbolicArc3::BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble>& values) const
{
    if (u < 0.0 || u > alpha)
        return GL_FALSE;

    values.ResizeColumns(4);

    values[0] = F0(u);
    values[1] = F1(u);
    values[2] = F2(u);
    values[3] = F3(u);
    return GL_TRUE;
}

GLboolean AlgebraicHyperbolicArc3::CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives &d) const
{
    if (u < 0.0 || u > alpha)
        return GL_FALSE;

    Matrix<GLdouble> dF(max_order_of_derivatives+1, 4);

    for (GLuint i = 0; i <= max_order_of_derivatives; i++)
    {
        if (i == 0)
        {
            dF(i,0) = F0(u);
            dF(i,1) = F1(u);
            dF(i,2) = F2(u);
            dF(i,3) = F3(u);
        }
        else if (i == 1)
        {
            dF(i,0) = dF0(u);
            dF(i,1) = dF1(u);
            dF(i,2) = dF2(u);
            dF(i,3) = dF3(u);
        }
        else if (i == 2)
        {
            dF(i,0) = ddF0(u);
            dF(i,1) = ddF1(u);
            dF(i,2) = ddF2(u);
            dF(i,3) = ddF3(u);
        }
    }

    d.ResizeRows(max_order_of_derivatives + 1);
    d.LoadNullVectors();

    for (GLuint r = 0; r <= max_order_of_derivatives; r++)
    {
        for (GLuint i = 0; i < _data.GetRowCount(); i++)
        {
            d[r] += _data[i] * dF(r, i);
        }
    }

    /*
    for (int i = 0; i < max_order_of_derivatives; i++)
        std::cout << d[i] << " ";
    std::cout << std::endl;
    */

    return GL_TRUE;
}

void AlgebraicHyperbolicArc3::set_alpha(double value)
{
    if (alpha != value)
        alpha = value;
}

double AlgebraicHyperbolicArc3::get_alpha()
{
    return alpha;
}
