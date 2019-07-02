#include <QApplication>
#include "GUI/MainWindow.h"

#include "Core/Matrices.h"
#include "Core/RealSquareMatrices.h"
#include <iostream>
#include <fstream>

using namespace cagd;


using namespace std;

void test() {
    Matrix<int> M(3,5);


    for(GLuint r = 0;r < M.GetRowCount();r++) {
        for(GLuint c=0;c<M.GetColumnCount();c++) {
            M(r,c) = r*M.GetColumnCount()+c;
        }

    }

    ofstream f("log.txt");
    f << M << endl;
    f.close();



    ifstream g("log.txt");
    Matrix<int> N;
    g >> N;
    N.ResizeRows(7);
    N(6,3)=1;
    cout<<N;
    g.close();



    //A*[x0 x1 x2] = [b0 b1 b2]
    // xi= -1, 2, 1
    // x0 + x1 + x2=2
    // 2x0 - 3x1 -x2 = -9
    // 3x0 + x1 + 2x2 = 1
    // det A = -5-7+11=-1

    RealSquareMatrix A(3);
    A(0,0)=A(0,1)=A(0,2)=1.0;
    A(1,0)=2.0;A(1,1)=-3.0;A(1,2)=-1.0;
    A(2,0)=3.0;A(2,1)=1.0;A(2,2)=2.0;

    ColumnMatrix<GLdouble> B(3);
    B[0]=2.0; B[1]=-9.0; B[2]=1;

    ColumnMatrix<GLdouble> X;

    A.SolveLinearSystem(B,X);
    cout<<"Eredmeny:"<<endl;
    cout<<X<<endl;


    TriangularMatrix<int> Tr(4);
    ifstream t("tmatrix.txt");

    t >> Tr;
    cout<<endl<<"Triangular matrix"<<endl;
    cout<<Tr;

}

int main(int argc, char **argv)
{
   // QApplication app(argc,argv);



     QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);

    // creating an application object and setting one of its attributes
    QApplication app(argc, argv);

    // if you have installed a different version of Qt, it may happen that
    // the application attribute Qt::AA_UseDesktopOpenGL is not recognized
    // on Windows its existence is critical for our applications
    // on Linux or Mac you can uncomment this line
    app.setAttribute(Qt::AA_UseDesktopOpenGL, true);

    // creating a main window object
    MainWindow mwnd;
    mwnd.showMaximized();

    // running the application

    return app.exec();
}
