QT += core gui widgets opengl

win32 {
    message("Windows platform...")

    CONFIG += console

    INCLUDEPATH += $$PWD/Dependencies/Include
    DEPENDPATH += $$PWD/Dependencies/Include

    LIBS += -lopengl32 -lglu32

    CONFIG(release, debug|release): {
        contains(QT_ARCH, i386) {
            message("x86 (i.e., 32-bit) release build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x86/" -lglew32
        } else {
            message("x86_64 (i.e., 64-bit) release build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x86_64/" -lglew32
        }
    } else: CONFIG(debug, debug|release): {
        contains(QT_ARCH, i386) {
            message("x86 (i.e., 32-bit) debug build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x86/" -lglew32
        } else {
            message("x86_64 (i.e., 64-bit) debug build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x86_64" -lglew32
        }
    }

    msvc {
      QMAKE_CXXFLAGS += -openmp -arch:AVX -D "_CRT_SECURE_NO_WARNINGS"
      QMAKE_CXXFLAGS_RELEASE *= -O2
    }
}

mac {
    # for GLEW installed into /usr/lib/libGLEW.so or /usr/lib/glew.lib
    LIBS += -lGLEW -lGLU
}

unix {
    # for GLEW installed into /usr/lib/libGLEW.so or /usr/lib/glew.lib
    LIBS += -lGLEW -lGLU
}

FORMS += \
    GUI/MainWindow.ui \
    GUI/SideWidget.ui

HEADERS += \
    GUI/GLWidget.h \
    GUI/MainWindow.h \
    GUI/SideWidget.h \
    Core/Exceptions.h \
    Core/DCoordinates3.h \
    Core/Matrices.h \
    Core/RealSquareMatrices.h \
    Core/Constants.h \
    Core/CyclicCurve3.h \
    Core/GenericCurves3.h \
    Core/LinearCombination3.h \
    Dependencies/Include/GL/glew.h \
    Parametric/ParametricCurves3.h \
    Test/TestFunctions.h \
    Core/Colors4.h \
    Core/HCoordinates3.h \
    Core/Lights.h \
    Core/Materials.h \
    Core/TCoordinates4.h \
    Core/TriangularFaces.h \
    Core/TriangulatedMeshes3.h \
    Parametric/ParametricSurfaces3.h \
    Core/TensorProductSurfaces3.h \
    Core/ShaderPrograms.h \
    AlgebraicHyperbolic/AlgebraicHyperbolic.h \
    AlgebraicHyperbolic/AlgebraicHyperbolicArc3.h \
    AlgebraicHyperbolic/AlgebraicHyperbolicCompositeCurves3.h \
    AlgebraicHyperbolic/AlgebraicHyperbolicCompositeSurfaces3.h

SOURCES += \
    GUI/GLWidget.cpp \
    GUI/MainWindow.cpp \
    GUI/SideWidget.cpp \
    main.cpp \
    Core/RealSquareMatrices.cpp \
    Core/CyclicCurve3.cpp \
    Core/GenericCurves3.cpp \
    Core/LinearCombination3.cpp \
    Parametric/ParametricCurves3.cpp \
    Test/TestFunctions.cpp \
    Core/Lights.cpp \
    Core/Materials.cpp \
    Core/TriangulatedMeshes3.cpp \
    Parametric/ParametricSurfaces3.cpp \
    Core/TensorProductSurfaces3.cpp \
    Core/ShaderPrograms.cpp \
    AlgebraicHyperbolic/AlgebraicHyperbolic.cpp \
    AlgebraicHyperbolic/AlgebraicHyperbolicArc3.cpp \

DISTFILES += \
    Models/elephant.off \
    Models/mouse.off \
    Models/sphere.off

