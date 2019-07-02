#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>

namespace cagd
{
    // forward declaration of template class Matrix
    template <typename T>
    class Matrix;

    // forward declaration of template class RowMatrix
    template <typename T>
    class RowMatrix;

    // forward declaration of template class ColumnMatrix
    template <typename T>
    class ColumnMatrix;

    // forward declaration of template class TriangularMatrix
    template <typename T>
    class TriangularMatrix;

    // forward declarations of overloaded and templated input/output from/to stream operators
    template <typename T>
    std::ostream& operator << (std::ostream& lhs, const Matrix<T>& rhs);

    template <typename T>
    std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs);

    template <typename T>
    std::istream& operator >>(std::istream& lhs, TriangularMatrix<T>& rhs);

    template <typename T>
    std::ostream& operator << (std::ostream& lhs, const TriangularMatrix<T>& rhs);

    //----------------------
    // template class Matrix
    //----------------------
    template <typename T>
    class Matrix
    {
        friend std::ostream& cagd::operator << <T>(std::ostream&, const Matrix<T>& rhs);
        friend std::istream& cagd::operator >> <T>(std::istream&, Matrix<T>& rhs);

    protected:
        GLuint                          _row_count;
        GLuint                          _column_count;
        std::vector< std::vector<T> >   _data;
    public:
        // special constructor (can also be used as a default constructor)
        Matrix(GLuint row_count = 1, GLuint column_count = 1);

        // copy constructor
        Matrix(const Matrix& m);

        // assignment operator
        Matrix& operator =(const Matrix& m);

        // get element by reference
        T& operator ()(GLuint row, GLuint column);

        // get copy of an element
        T operator ()(GLuint row, GLuint column) const;

        // get dimensions
        GLuint GetRowCount() const;
        GLuint GetColumnCount() const;

        // set dimensions
        virtual GLboolean ResizeRows(GLuint row_count);
        virtual GLboolean ResizeColumns(GLuint column_count);

        // update
        GLboolean SetRow(GLuint index, const RowMatrix<T>& row);
        GLboolean SetColumn(GLuint index, const ColumnMatrix<T>& column);

        // destructor
        virtual ~Matrix();
    };

    //-------------------------
    // template class RowMatrix
    //-------------------------
    template <typename T>
    class RowMatrix: public Matrix<T>
    {
    public:
        // special constructor (can also be used as a default constructor)
        RowMatrix(GLuint column_count = 1);

        // get element by reference
        T& operator ()(GLuint column);
        T& operator [](GLuint column);

        // get copy of an element
        T operator ()(GLuint column) const;
        T operator [](GLuint column) const;

        // a row matrix consists of a single row
        GLboolean ResizeRows(GLuint row_count);
    };

    //----------------------------
    // template class ColumnMatrix
    //----------------------------
    template <typename T>
    class ColumnMatrix: public Matrix<T>
    {
    public:
        // special constructor (can also be used as a default constructor)
        ColumnMatrix(GLuint row_count = 1);

        // get element by reference
        T& operator ()(GLuint row);
        T& operator [](GLuint row);

        // get copy of an element
        T operator ()(GLuint row) const;
        T operator [](GLuint row) const;

        // a column matrix consists of a single column
        GLboolean ResizeColumns(GLuint column_count);
    };

    //--------------------------------
    // template class TriangularMatrix
    //--------------------------------
    template <typename T>
    class TriangularMatrix
    {
        friend std::istream& cagd::operator >> <T>(std::istream&, TriangularMatrix<T>& rhs);
        friend std::ostream& cagd::operator << <T>(std::ostream&, const TriangularMatrix<T>& rhs);

    protected:
        GLuint                        _row_count;
        std::vector< std::vector<T> > _data;

    public:
        // special constructor (can also be used as a default constructor)
        TriangularMatrix(GLuint row_count = 1);

        // get element by reference
        T& operator ()(GLuint row, GLuint column);

        // get copy of an element
        T operator ()(GLuint row, GLuint column) const;

        // get dimension
        GLuint GetRowCount() const;

        // set dimension
        GLboolean ResizeRows(GLuint row_count);
    };

    //--------------------------------------------------
    // homework: implementation of template class Matrix
    //--------------------------------------------------
    template<typename T>

    Matrix<T>::Matrix(unsigned int row_count, unsigned int column_count):
       _row_count(row_count),
       _column_count(column_count),
       _data((row_count),std::vector<T>(column_count))
    {
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix &m):
            _row_count(m._row_count),
            _column_count(m._column_count),
            _data(m._data)
    {
    }
    template<typename T>
    Matrix<T>& Matrix<T>::operator =(const Matrix& m)
    {
        if (this != &m) {
            _column_count = m._column_count;
            _row_count = m._row_count;
            _data=m._data;
        }
        return *this;
    }

    template <typename T >
    T Matrix <T>::operator()(unsigned int row,unsigned int column)const {
        return _data[row][column];
    }

    template<typename T>
    T& Matrix<T>::operator ()(unsigned int row, unsigned int column)
    {
        return _data[row][column];
    }

    template <typename T>
    GLboolean Matrix<T>::ResizeRows(unsigned int row_count)
        {
            _data.resize(row_count);
            for (GLuint r = _row_count; r < row_count; ++r)
            {
                _data[r].resize(_column_count);
            }
            _row_count = row_count;
            return GL_TRUE;
        }

    template <typename T>
    GLboolean Matrix<T>::ResizeColumns(unsigned int column_count)
    {
        if(_column_count!=column_count){

                for (GLuint r = 0; r <_row_count; ++r)
                {
                    _data[r].resize(column_count);
                }
                _column_count = column_count;
                return GL_TRUE;
            }
        return GL_FALSE;
    }

    template<typename T>
    Matrix<T>::~Matrix(){
        _row_count=_column_count=0;
        _data.clear();
    }

    template<typename T>
    unsigned int Matrix<T>::GetRowCount() const
    {
        return _row_count;
    }

    template<typename T>
    unsigned int Matrix< T>::GetColumnCount() const
    {
        return _column_count;
    }
    template<typename T>
    GLboolean Matrix<T>::SetRow(unsigned int index, const RowMatrix<T>& row)
    {
        if(row._column_count==_column_count || index<_row_count)
        {
            for (GLuint c =0; c < _column_count; ++c)
            {
               _data[index][c]=row._data[0][c];
            }
            return GL_TRUE;
        }
            return GL_FALSE;
     }

    template<typename T>
    GLboolean Matrix< T>::SetColumn(unsigned int index, const ColumnMatrix<T>& column)
    {
      if(index<_column_count && column._row_count==_row_count)
         {
           for (GLuint r =0; r < _row_count; ++r)
            {
              _data[r][index]=column._data[r][0];
            }
               return GL_TRUE;
         }
      return GL_FALSE;
    }

    //-----------------------------------------------------
    // homework: implementation of template class RowMatrix
    //-----------------------------------------------------
    template<typename T>
    RowMatrix<T>::RowMatrix(unsigned int column_count):Matrix<T>(1,column_count)
    {
    }

    template<typename T>
    T& RowMatrix<T>::operator ()(unsigned int column)
    {
      return this->_data[0][column];
    }

    template<typename T>
    T& RowMatrix<T>::operator [](unsigned int column)
    {
      return this->_data[0][column];
    }

    template<typename T>
    T RowMatrix<T>::operator ()(unsigned int column) const
    {
      return this->_data[0][column];
    }

    template<typename T>
    T RowMatrix<T>::operator [](unsigned int column) const
    {
      return this->_data[0][column];
    }

    template<typename T>
    GLboolean RowMatrix<T>::ResizeRows(unsigned int row_count)
    {
      return (row_count == 1 ? GL_TRUE : GL_FALSE);
    }

    //--------------------------------------------------------
    // homework: implementation of template class ColumnMatrix
    //--------------------------------------------------------
    template<typename T>
    ColumnMatrix<T>::ColumnMatrix(unsigned int row_count):
            Matrix<T>(row_count,1)
    {
    }

    template<typename T>
    T& ColumnMatrix<T>::operator ()(unsigned int row)
    {
        return this->_data[row][0];
    }

    template<typename T>
    T& ColumnMatrix<T>::operator [](unsigned int row)
    {
        return this->_data[row][0];
    }

    template<typename T>
    T ColumnMatrix<T>::operator ()(unsigned int row) const
    {
        return this->_data[row][0];
    }

    template<typename T>
    T ColumnMatrix<T>::operator [](unsigned int row) const
    {
        return this->_data[row][0];
    }
    template<typename T>
    GLboolean ColumnMatrix<T>::ResizeColumns(unsigned int column_count)
    {
        return (column_count == 1 ? GL_TRUE : GL_FALSE);
    }

    //------------------------------------------------------------
    // homework: implementation of template class TriangularMatrix
    //------------------------------------------------------------
    template <typename T>
    TriangularMatrix<T>::TriangularMatrix(GLuint row_count):
       _row_count(row_count), _data(row_count)
    {
       GLuint column_count = 1;
       for (typename std::vector<std::vector<T>>::iterator row=_data.begin();row != _data.end();row++,column_count++)
           row -> resize(column_count);
    }

    template <typename T>
    T& TriangularMatrix<T>::operator ()(GLuint row, GLuint column)
    {
       return _data[row][column];
    }

    template <typename T>
    T TriangularMatrix<T>::operator ()(GLuint row, GLuint column) const
    {
       return _data[row][column];
    }

    template <typename T>
    GLuint TriangularMatrix<T>::GetRowCount() const
    {
       return _row_count;
    }

    template <typename T>
    GLboolean TriangularMatrix<T>::ResizeRows(GLuint row_count)
    {
       _data.resize(row_count);
       if (_row_count < row_count)
       {
           GLuint column_count = _row_count + 1;
           for (typename std::vector<std::vector<T>>::iterator row=_data.begin()+_row_count;row != _data.end();row++,column_count++)
               row -> resize(column_count);
       }
       _row_count = row_count;
       return true;
    }
    //------------------------------------------------------------------------------
    // definitions of overloaded and templated input/output from/to stream operators
    //------------------------------------------------------------------------------

    // output to stream
    template <typename T>
    std::ostream& operator <<(std::ostream& lhs, const Matrix<T>& rhs)
    {
        lhs << rhs._row_count << " " << rhs._column_count << std::endl;
        for (typename std::vector< std::vector<T> >::const_iterator row = rhs._data.begin();
             row != rhs._data.end(); ++row)
        {
            for (typename std::vector<T>::const_iterator column = row->begin();
                 column != row->end(); ++column)
                    lhs << *column << " ";
            lhs << std::endl;
        }
        return lhs;
    }

    // input from stream
    template <typename T>
    std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs)
    {
       //homework
       lhs >> rhs._row_count >> rhs._column_count;
       rhs._data.resize(rhs._row_count);
       for (typename std::vector < std::vector<T> >::iterator r = rhs._data.begin(); r !=rhs._data.end(); r++) {
           r->resize(rhs._column_count);
           for (typename std::vector<T>::iterator c = r->begin(); c != r->end(); c++) {
               lhs >> *c;
           }
       }
       return lhs;
    }

    //
    //  TriangularMatrix input-output from stream
    //
    template <typename T>
    std::ostream& operator <<(std::ostream& lhs, const TriangularMatrix<T>& rhs)
    {
        lhs << rhs._row_count << std::endl;
        for (typename std::vector< std::vector<T> >::const_iterator row = rhs._data.begin();
             row != rhs._data.end(); ++row)
        {
            for (typename std::vector<T>::const_iterator column = row->begin();
                 column != row->end(); ++column)
                    lhs << *column << " ";
            lhs << std::endl;
        }
        return lhs;
    }

    template <typename T>
    std::istream& operator >>(std::istream& lhs, TriangularMatrix<T>& rhs)
    {
        // homework
        lhs >> rhs._row_count;
        std::cout<<std::endl;
        rhs.ResizeRows(rhs._row_count);

        for (typename std::vector<std::vector<T>>::iterator row = rhs._data.begin();row!=rhs._data.end();row++)
        {
            for (typename std::vector<T>::iterator column =row -> begin();column != row->end();column++)
                lhs >> *column ;

         }
       return lhs;
    }
}