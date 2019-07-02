#pragma once

#include <GL/glew.h>
#include <QGLWidget>
#include <QGLFormat>
#include <QTimer>

#include "../Parametric/ParametricCurves3.h"
#include "../Core/GenericCurves3.h"
#include "../Core/CyclicCurve3.h"
#include "../Core/Matrices.h"
#include "../Test/TestFunctions.h"
#include "../Core/Constants.h"
#include "../Core/TriangulatedMeshes3.h"
#include "../Parametric/ParametricSurfaces3.h"
#include "../AlgebraicHyperbolic/AlgebraicHyperbolic.h"
#include "../Core/ShaderPrograms.h"
#include "../AlgebraicHyperbolic/AlgebraicHyperbolicArc3.h"
#include "../AlgebraicHyperbolic/AlgebraicHyperbolicCompositeCurves3.h"
#include "../AlgebraicHyperbolic/AlgebraicHyperbolicCompositeSurfaces3.h"

namespace cagd
{
    class GLWidget: public QGLWidget
    {
        Q_OBJECT

    private:

        //tobb kep, parametric curves
        bool _show_velocity_vectors = false;
        bool _show_acceleration_vectors = false;
        int _pc_curve_count = 0;
        RowMatrix<ParametricCurve3*> _pc;
        RowMatrix<GenericCurve3*> _image_of_pc;
        int _index = 0;
/*
        //ciyclic curve
        GLuint _n_icc; //order of cyclic curve
        CyclicCurve3 *_icc; //image of the cyclic curve;
        GLuint _max_order_of_derivatives;
        GLuint _div_point_count;
        GenericCurve3 *_img_icc;
        ColumnMatrix<GLdouble> _u;
        ColumnMatrix<DCoordinate3> _d;

        //cyclic curve plusz
        ColumnMatrix<GLdouble> _knot_vektor;
        ColumnMatrix<DCoordinate3> _points_to_interpolate;
        CyclicCurve3 _cc;
*/

        GLint                               _cc_index;
        GLint                               _cp_index;
        CyclicCurve3*                       _cc;
        GenericCurve3*                      _image_cc;
        ColumnMatrix<GLdouble>*             _knot_vector;
        ColumnMatrix<DCoordinate3>*         _points_to_interpolate;
        GLint                               _cp_x,_cp_y,_cp_z;
        GLboolean                           _control_cc;
        GLboolean                           _fod_cc;
        GLboolean                           _sod_cc;
        //interpolacio
        CyclicCurve3*                       _cc_i;
        GenericCurve3*                      _image_cc_i;
        GLboolean                           _interpolalo;

        /*Parametric surfaces*/
        int _surface_index=0;
        GLuint _ps_surface_count;
        RowMatrix<ParametricSurface3*> _ps;
        RowMatrix<TriangulatedMesh3*> _image_of_ps;

        /*Allatok*/
        QTimer* _timer; //ok
        GLfloat _angle; //ok

        int _animal_index=0;
        TriangulatedMesh3 _mouse;
        TriangulatedMesh3 _elephant;
        TriangulatedMesh3 _sphere;
        //materials
        std::vector<Material*> _materials;

        //BicubicBezierPatch
        AlgebraicHyperbolicPatch _patch;
        TriangulatedMesh3 *_before_iterpolation, *_after_interpolation;

        //Algebraic Zsiraf
        TriangulatedMesh3   *algh_patch_before_interpolation, *algh_patch_after_interpolation;
        int _alpha = 1;
        AlgebraicHyperbolicPatch  *algh_patch;
        //TEST
        RowMatrix<GLdouble> u;
        ColumnMatrix<GLdouble> v;



        ShaderProgram* _shader;
        //Shaders
        ShaderProgram _shader1;
        ShaderProgram _shader2;
        ShaderProgram _shader3;
        ShaderProgram _shader4;
        int _shader_index;

        //Toon colors
        double r;
        double g;
        double b;
        double a;
        //Reflection prop.
        int scale_factor;
        int smoothing;
        int shading;

        /*page*/
         int _page_index = 0;

        // variables defining the projection matrix
        float       _aspect;            // aspect ratio of the rendering window
        float       _fovy;              // field of view in direction y
        float       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        float       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // your other declarations

        RowMatrix<GenericCurve3*>* vi;
        RowMatrix<GenericCurve3*>* ui;

        //PROJEKT!!!!!!!!!!!!!!!!
        AlgebraicHyperbolicArc3* _comp_arc;
        //GenericCurve3* _image_of_arc;

        //compositeCurve
        AlgebraicHyperbolicCompositeCurve3* _alg_comp_curve;

        /*********************************/
        /**********KONTROL****************/
        /*********************************/

        int _arc1 = 0;
        int _arc2 = 0;

        int _dir1 = 0;
        int _dir2 = 0;

        int _ith_datapoint = 0;
        float _arc_x=0;
        float _arc_y=0;
        float _arc_z=0;

        bool _show_fod = false;
        bool _show_sod = false;

        int _surface1 = 0;
        int _surface2 = 0;

        int _surf_dir1 = 0;
        int _surf_dir2 = 0;

        bool _show_surf_fod = false;
        bool _show_surf_sod = false;
        bool _show_surf_uisoparam = false;
        bool _show_surf_visoparam = false;

        int _s_i = 0;
        int _s_j = 0;

        //AH Surface
        AlgebraicHyperbolicPatch* _temp_patch;
        TriangulatedMesh3* _temp_patch_image;

        AlgebraicHyperbolicCompositeSurface3* _alg_comp_surf;


    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);
        void initializeParametricCurves();
        void renderParametricCurve();
        void initializeParametricSurfaces();
        void renderSelectedParametricSurface();
        void InitializeCyclicCurve();
        void PaintCyclicCurves();
        void renderCyclicCurve();
        void initMouse();
        void renderMouse();
        void renderSelectedAnimal();
        void renderInterpolatingCyclicCurve();
        void initializeAlgebraicHyperbolic();
        void renderAlgebraicHyperbolic();
        void initAHArc();
        void initAHSurface();
        void renderAHArc();
        void renderAHSurface();
        void join();
        void merge();
        void _continue();

        void merge_surf();
        void join_surf();
        void continue_surf();
    public slots:
        // public event handling methods/slots
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);
        void set_index(int index);
        void set_index_surface(int index);
        void set_index_animal(int index);
        void show_velocity_vectors();
        void show_acceleration_vectors();
        void set_index_shader(int index);
        //toon
        void set_toon_r(double c);
        void set_toon_g(double c);
        void set_toon_b(double c);
        void set_toon_a(double c);
        //masik shader
        void set_scale_factor(int q);
        void set_smoothing(int q);
        void set_shading(int q);
        void set_page(int index);
        void _animate(); //elefanthoz

        /**** ALGEBRAIC HYPERBOLIC CURVES ****/
        void set_arc1(int n);
        void set_arc2(int n);
        void set_dir1(int n);
        void set_dir2(int n);
        void set_alpha(double n);

        void set_ith_datapoint(int n);

        void inc_x();
        void inc_y();
        void inc_z();

        void dec_x();
        void dec_y();
        void dec_z();

        void inc_s_x();
        void inc_s_y();
        void inc_s_z();

        void dec_s_x();
        void dec_s_y();
        void dec_s_z();

        void set_s_i(int n);
        void set_s_j(int n);

        void call_merge();
        void call_join();
        void call_continue();

        void show_fod();
        void show_sod();

        /**** ALGEBRAIC HYPERBOLIC SURFACES ****/
        void set_surface1(int n);
        void set_surface2(int n);
        void set_surf_dir1(int n);
        void set_surf_dir2(int n);

        void call_surf_merge();
        void call_surf_join();
        void call_surf_continue();

        void show_surf_fod();
        void show_surf_sod();
        void show_surf_uisoparam();
        void show_surf_visoparam();

    };
}
