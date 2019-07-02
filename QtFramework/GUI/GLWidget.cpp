#include "GLWidget.h"
#include <GL/glu.h>

#include <iostream>

//
#include <Core/Exceptions.h>
#include "../Core/Materials.h"
//
#include "../Parametric/ParametricCurves3.h"
#include "../Core/GenericCurves3.h"
#include "../Core/CyclicCurve3.h"
#include "../Core/Matrices.h"
#include "../Test/TestFunctions.h"
#include "../Core/Constants.h"


using namespace std;
using namespace cagd; //?

#include <Core/Exceptions.h>
#include <Core/DCoordinates3.h>

namespace cagd
{
    //--------------------------------
    // special and default constructor
    //--------------------------------
    GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
    {
        _timer = new QTimer(this);//elefant
        _timer -> setInterval(0);
        connect(_timer, SIGNAL(timeout()), this, SLOT(_animate()));

    }

    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {
        //elefant
        glewInit();
        if(_elephant.LoadFromOFF("Models/elephant.off",true))
            if(_elephant.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                _angle = 0.0;
                _timer -> start();
            }

        if(_mouse.LoadFromOFF("Models/mouse.off",true))
            if(_mouse.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                _angle = 0.0;
                _timer -> start();
            }
        if(_sphere.LoadFromOFF("Models/sphere.off",true))
            if(_sphere.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                _angle = 0.0;
                _timer -> start();
            }
        //elefant vege

        //Shadersssssss

        try {
            if(!_shader1.InstallShaders("Shaders/reflection_lines.vert","Shaders/reflection_lines.frag",GL_TRUE)) {

            }
        } catch (Exception &e) {
            cerr << e << endl;
        }
        try {
            if(!_shader2.InstallShaders("Shaders/directional_light.vert","Shaders/directional_light.frag",GL_TRUE)) {

            }
        } catch (Exception &e) {
            cerr << e << endl;
        }
        try {
            if(!_shader3.InstallShaders("Shaders/toon.vert","Shaders/toon.frag",GL_TRUE)) {

            }
        } catch (Exception &e) {
            cerr << e << endl;
        }
        try {
            if(!_shader4.InstallShaders("Shaders/two_sided_lighting.vert","Shaders/two_sided_lighting.frag",GL_TRUE)) {

            }
        } catch (Exception &e) {
            cerr << e << endl;
        }

        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (float)width() / (float)height();
        _z_near = 1.0;
        _z_far = 1000.0;
        _fovy = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0, _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0, _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling depth test
        glEnable(GL_DEPTH_TEST);

        // setting the color of background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;
        //bicubic
        initializeAlgebraicHyperbolic();
        //parametric curves
        initializeParametricCurves();
        //cyclic curve
        //initializeCyclicCurve();
        InitializeCyclicCurve();
        //parametric surfaces
        initializeParametricSurfaces();
        //materials
        _materials.resize(7);
        _materials[0] = &MatFBBrass;
        _materials[1] = &MatFBGold;
        _materials[2] = &MatFBSilver;
        _materials[3] = &MatFBEmerald;
        _materials[4] = &MatFBPearl;
        _materials[5] = &MatFBRuby;
        _materials[6] = &MatFBTurquoise;

        //PROJETK
        initAHArc();
        initAHSurface();

        try
        {
            // initializing the OpenGL Extension Wrangler library
            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            // create and store your geometry in display lists or vertex buffer objects
            // ...
        }
        catch (Exception &e)
        {
            cout << e << endl;
        }
    }

    void GLWidget::initializeParametricSurfaces()
    {
        _ps_surface_count = 5;
        _ps.ResizeColumns(_ps_surface_count);
        _image_of_ps.ResizeColumns(_ps_surface_count);
        TriangularMatrix<ParametricSurface3::PartialDerivative> derivative(2);

        derivative(0,0) = Hyperboloid::d00;
        derivative(1,0) = Hyperboloid::d10;
        derivative(1,1) = Hyperboloid::d01;
        _ps[0] = new ParametricSurface3(derivative, Hyperboloid::u_min, Hyperboloid::u_max, Hyperboloid::v_min, Hyperboloid:: v_max);

        derivative(0,0) = torus::d00;
        derivative(1,0) = torus::d10;
        derivative(1,1) = torus::d01;
        _ps[1] = new ParametricSurface3(derivative, torus::u_min, torus::u_max, torus::v_min, torus:: v_max);

        derivative(0,0) = Cylindrical_helicoid::d00;
        derivative(1,0) = Cylindrical_helicoid::d10;
        derivative(1,1) = Cylindrical_helicoid::d01;
        _ps[2] = new ParametricSurface3(derivative, Cylindrical_helicoid::u_min, Cylindrical_helicoid::u_max, Cylindrical_helicoid::v_min, Cylindrical_helicoid:: v_max);


        derivative(0,0) = dini_surface::d00;
        derivative(1,0) = dini_surface::d10;
        derivative(1,1) = dini_surface::d01;
        _ps[3] = new ParametricSurface3(derivative, dini_surface::u_min, dini_surface::u_max, dini_surface::v_min, dini_surface:: v_max);

        derivative(0, 0) = KleinBottle::d00;
        derivative(1, 0) = KleinBottle::d10;
        derivative(1, 1) = KleinBottle::d01;
        _ps[4] = new ParametricSurface3(derivative, KleinBottle::u_min, KleinBottle::u_max,KleinBottle::v_min, KleinBottle::v_max);

        //200 100
        GLuint u_div_point_count = 50;
        GLuint v_div_point_count = 50;
        GLenum usage_flag = GL_STATIC_DRAW;

        for(GLuint i = 0;i < _ps_surface_count;i++)
        {
             _image_of_ps[i] = _ps[i] -> GenerateImage(u_div_point_count, v_div_point_count, usage_flag);
             _image_of_ps[i] -> UpdateVertexBufferObjects(usage_flag);
        }
    }


    void GLWidget::renderSelectedParametricSurface()
    {

        if (_image_of_ps[_surface_index]){
            glEnable(GL_LIGHTING);
            glEnable(GL_NORMALIZE);
            glEnable(GL_LIGHT0);
             _image_of_ps[_surface_index]->Render(GL_TRIANGLES);
            glDisable(GL_LIGHTING);
            glDisable(GL_NORMALIZE);
            glDisable(GL_LIGHT0);
            //_image_of_ps[_surface_index]->RenderNormals();
        }
    }

    void GLWidget::initializeParametricCurves() {


        GLuint div_point_count = 200;
        GLenum usage_flag = GL_STATIC_DRAW;
        _pc_curve_count = 5;
        _pc.ResizeColumns(_pc_curve_count);
        _image_of_pc.ResizeColumns(_pc_curve_count);
        RowMatrix<ParametricCurve3::Derivative> derivative(3);

        derivative(0) = hypocycloid::d0;
        derivative(1) = hypocycloid::d1;
        derivative(2) = hypocycloid::d2;
        _pc[0] = new ParametricCurve3(derivative,hypocycloid::u_min,hypocycloid::u_max);
        derivative(0) = rose::d0;
        derivative(1) = rose::d1;
        derivative(2) = rose::d2;
        _pc[1] = new ParametricCurve3(derivative,rose::u_min,rose::u_max);
        derivative(0) = lissajous::d0;
        derivative(1) = lissajous::d1;
        derivative(2) = lissajous::d2;
        _pc[2] = new ParametricCurve3(derivative,lissajous::u_min,lissajous::u_max);
        derivative(0) = torus_knot::d0;
        derivative(1) = torus_knot::d1;
        derivative(2) = torus_knot::d2;
        _pc[3] = new ParametricCurve3(derivative,torus_knot::u_min,torus_knot::u_max);
        derivative(0) = spiral_on_cone::d0;
        derivative(1) = spiral_on_cone::d1;
        derivative(2) = spiral_on_cone::d2;
        _pc[4] = new ParametricCurve3(derivative,spiral_on_cone::u_min,spiral_on_cone::u_max);

        for(GLuint i=0;i<_pc_curve_count;i++){
            _image_of_pc[i] = _pc[i] -> GenerateImage(div_point_count,usage_flag);
            _image_of_pc[i] -> UpdateVertexBufferObjects(usage_flag);
        }

    }

    void GLWidget::renderParametricCurve() {
        glPointSize(5.0);

        glColor3f(0.9,0.5,0.0);

        _image_of_pc[_index] ->RenderDerivatives(0,GL_LINE_STRIP);

        if(_show_velocity_vectors) {
            glColor3f(0.7,0.1,0.1);
            _image_of_pc[_index] ->RenderDerivatives(1,GL_LINES);
       }


        if(_show_acceleration_vectors) {
            glColor3f(0.1,0.1,0.7);
            _image_of_pc[_index] ->RenderDerivatives(2,GL_LINES);
       }
        glPointSize(1.0);
    }

    void GLWidget::initializeAlgebraicHyperbolic(){
        _alpha = 3;
        algh_patch = nullptr;
        algh_patch = new AlgebraicHyperbolicPatch(_alpha);

        algh_patch->SetData(0, 0, -5.0, -4.0, -1.0);
        algh_patch->SetData(0, 1, -5.0, -4.0, -2.0);
        algh_patch->SetData(0, 2, -5.0, 5.0, -5.0);
        algh_patch->SetData(0, 3, -5.0, 7.0, -2.0);

        algh_patch->SetData(1, 0, -1.0, -2.0, 0.0);
        algh_patch->SetData(1, 1, -1.0, -1.0, 2.0);
        algh_patch->SetData(1, 2, -1.0, 1.0, 2.0);
        algh_patch->SetData(1, 3, -1.0, 2.0, 0.0);

        algh_patch->SetData(2, 0, 1.0, -2.0, 0.0);
        algh_patch->SetData(2, 1, 1.0, -1.0, 2.0);
        algh_patch->SetData(2, 2, 1.0, 1.0, 2.0);
        algh_patch->SetData(2, 3, 1.0, 2.0, 0.0);

        algh_patch->SetData(3, 0, 2.0, -2.0, 0.0);
        algh_patch->SetData(3, 1, 2.0, -1.0, 0.0);
        algh_patch->SetData(3, 2, 2.0, 1.0, 0.0);
        algh_patch->SetData(3, 3, 2.0, 2.0, 0.0);

         algh_patch->UpdateVertexBufferObjectsOfData();

        // generate the mesh of the surface patch
        algh_patch_before_interpolation = algh_patch->GenerateImage(30, 30, GL_STATIC_DRAW);

        if (algh_patch_before_interpolation)
            algh_patch_before_interpolation->UpdateVertexBufferObjects();

        // define an interpolation problem:
        // 1: create a knot vector in u-direction
        RowMatrix<GLdouble> algh_patch_u_knot_vector(4);
        algh_patch_u_knot_vector(0) = 0.0;
        algh_patch_u_knot_vector(1) = _alpha / 3.0;
        algh_patch_u_knot_vector(2) = 2.0 * _alpha / 3.0;
        algh_patch_u_knot_vector(3) = _alpha;

        // 2: create a knot vector in v-direction
        ColumnMatrix<GLdouble> algh_patch_v_knot_vector(4);
        algh_patch_v_knot_vector(0) = 0.0;
        algh_patch_v_knot_vector(1) = _alpha / 3.0;
        algh_patch_v_knot_vector(2) = 2.0 * _alpha / 3.0;
        algh_patch_v_knot_vector(3) = _alpha;


        ui = algh_patch->GenerateUIsoparametricLines(20, 1, 20);
        vi = algh_patch->GenerateVIsoparametricLines(20, 1, 20);
        for (GLuint j = 0; j < ui->GetColumnCount(); ++j){
            (*ui)[j]->UpdateVertexBufferObjects();
        }

        for (GLuint j = 0; j < vi->GetColumnCount(); ++j){
            (*vi)[j]->UpdateVertexBufferObjects();
        }

        // 3: define a matrix of data points, e.g. set them to the original control points
        Matrix<DCoordinate3> algh_patch_data_points_to_interpolate(4, 4);
        for (GLuint row = 0; row < 4; ++row)
            for (GLuint column = 0; column < 4; ++column)
                algh_patch->GetData(row, column, algh_patch_data_points_to_interpolate(row, column));

        // 4: solve the interpolation problem and generate the mesh of the interpolating patch
        if (algh_patch->UpdateDataForInterpolation(algh_patch_u_knot_vector, algh_patch_v_knot_vector, algh_patch_data_points_to_interpolate))
        {
            algh_patch_after_interpolation = algh_patch->GenerateImage(30, 30, GL_STATIC_DRAW);

            if (algh_patch_after_interpolation)
                algh_patch_after_interpolation->UpdateVertexBufferObjects();
        }


    }

    void GLWidget::renderAlgebraicHyperbolic(){

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

            if (algh_patch_before_interpolation)
            {

                MatFBRuby.Apply();

                glPointSize(5.0);
                glColor3f(1.0, 0.0, 0.4);
                algh_patch->RenderData();
                algh_patch->RenderData(GL_POINTS);

                algh_patch_before_interpolation->Render();

            }
            if (algh_patch_after_interpolation)
            {

                glEnable(GL_BLEND);
                glDepthMask(GL_FALSE);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                    MatFBTurquoise.Apply();
                   algh_patch_after_interpolation->Render();
                glDepthMask(GL_TRUE);
                glDisable(GL_BLEND);



            }


        glDisable(GL_LIGHTING);
        glDisable(GL_NORMALIZE);

        glColor3f(1.0f, 1.0f, 0.0f);
        for (GLuint j = 0; j < ui->GetColumnCount(); ++j){
            (*ui)[j]->RenderDerivatives(0, GL_LINE_STRIP);
        }

        for (GLuint j = 0; j < vi->GetColumnCount(); ++j){
            (*vi)[j]->RenderDerivatives(0, GL_LINE_STRIP);
        }

    }

//test
    void GLWidget::PaintCyclicCurves(){


        GLenum render_mode = GL_LINE_LOOP;
        if (_cc)
        {
            glColor3f(1.0,1.0,0.0);
            if(_control_cc)
            {
                _cc->RenderData(render_mode);
            }
            if(true)
            {
                 glColor3f(1.0,0.0,0.0);
               _image_cc_i->RenderDerivatives(0,render_mode);
               _image_cc_i->RenderDerivatives(0,GL_LINE_STRIP);
               _cc->RenderData(GL_LINE_LOOP);
            }
        }
        if (_image_cc)
        {
            glColor3f(0.0,1.0,0.0);
            _image_cc->RenderDerivatives(0,render_mode);
            _image_cc_i->RenderDerivatives(0,GL_LINE_STRIP);
           // _image_cc->RenderData(render_mode);
            if (true)
            {
                glPointSize(5.0);
                glColor3f (0.0,0.0,1.0);
                _image_cc->RenderDerivatives(1,GL_LINES);
                _image_cc->RenderDerivatives(1,GL_POINTS);
                glPointSize(1.0);
            }
            if (true)
            {
                glPointSize(5.0);
                glColor3f (1.0,0.0,1.0);
                _image_cc->RenderDerivatives(2,GL_LINES);
                _image_cc->RenderDerivatives(2,GL_POINTS);
                glPointSize(1.0);
            }
        }


    }
//test

void GLWidget::InitializeCyclicCurve() //lab2
{
    _fod_cc=true;
    _sod_cc=true;
    _cc_index=0;
    _control_cc=true;


    GLdouble n=2;//ciklikus gorbe rendje ketszer ennyi a kontrol poligon csucspontjainak szama
    _knot_vector = new ColumnMatrix<GLdouble>(2 * n + 1);
    _points_to_interpolate = new ColumnMatrix<DCoordinate3>(2 * n + 1);
    _cc = new (nothrow) CyclicCurve3(n);
    GLenum usage_flag= GL_STATIC_DRAW;
    if (!_cc)
    {

    }

    GLdouble u_min;
    GLdouble u_max;
    _cc->GetDefinitionDomain(u_min,u_max);
    GLdouble step = (u_max - u_min)/(2*n+1);

    for (GLuint i =0;i<=2*n;i++)
    {
        GLdouble u = min(u_min+i*step,u_max);
        (*_knot_vector)[i]=u;
        (*_cc)[i][0]=sin(u);
        (*_cc)[i][1]=cos(u);
        (*_cc)[i][2]=0.0;
        (*_points_to_interpolate)[i][0]=(*_cc)[i][0];
        (*_points_to_interpolate)[i][1]=(*_cc)[i][1];
        (*_points_to_interpolate)[i][2]=(*_cc)[i][2];
    }

    try{
        if (!_cc->UpdateVertexBufferObjectsOfData(usage_flag))
        {
            throw "Nem";
        }

        _image_cc = _cc->GenerateImage(n,100,usage_flag);//annyi rendu derivaltat lehet kiszamolni amennyi a kontrol poligon csucspontjainak a szama/2

        if (!_image_cc->UpdateVertexBufferObjects(usage_flag))
        {
            throw("Nem");
        }
        _cc_i = new (nothrow)CyclicCurve3(n);
        if(!_cc_i->UpdateDataForInterpolation(*_knot_vector,*_points_to_interpolate))
        {
            if(_cc_i)
            {
                delete _cc_i, _cc_i = 0;
            }
            throw Exception("Could not update the VBOs of the cyclic curve's interpolation!");
        }
        if(!_cc_i->UpdateVertexBufferObjectsOfData())
        {
            if(_cc_i)
            {
                delete _cc_i, _cc_i = 0;
            }
            throw Exception("Could not update the VBOs of the cyclic curve's control polygon!-interpolation");
        }
        GLuint _div = 100;
        GLuint _mod = 3;
        _image_cc_i = _cc_i->GenerateImage(_mod, _div,usage_flag);

        if(!_image_cc_i)
        {
            if(_cc_i)
            {
                delete _cc_i, _cc_i = 0;
            }
            throw Exception("Could not generate the image of the cyclic curve!-interpolation");
        }
        if (!_image_cc_i->UpdateVertexBufferObjects())
        {
            if(_cc_i)
            {
                delete _cc_i, _cc_i = 0;
            }
            throw Exception("Could not update the VBOs of the cyclic curve's image!-inetpolataion");
        }

    }
    catch(Exception ex)
    {

    }
}



    //test

    void GLWidget::_animate() {
        GLfloat *vertex = _mouse.MapVertexBuffer(GL_READ_WRITE);
        GLfloat *normal = _mouse.MapNormalBuffer(GL_READ_ONLY);

        _angle += (DEG_TO_RADIAN);
        if(_angle >= TWO_PI) _angle -= TWO_PI;

        GLfloat scale = sin(_angle) / 3000.0;
        for(GLuint i = 0; i < _mouse.VertexCount(); ++i) {
            for(GLuint coordinate = 0; coordinate < 3; ++coordinate, ++vertex, ++normal)
                *vertex += scale * (*normal);
        }

        _mouse.UnmapVertexBuffer();
        _mouse.UnmapNormalBuffer();

        updateGL();
    }

    void GLWidget::renderSelectedAnimal() {
        if(_animal_index == 0) {
            _mouse.Render();
        }
        if(_animal_index == 1) {
            _elephant.Render();
        }
        if(_animal_index == 2) {
            _sphere.Render();
        }


    }

    void GLWidget::join()
    {
        int index = _arc1;
        int index2 = _arc2;
        int direction = _dir1;
        int direction2 = _dir2;
        _alg_comp_curve->joinArcs(index, index2, direction, direction2);

    }

    void GLWidget::merge() {
        int index = _arc1;
        int index2 = _arc2;
        int direction = _dir1;
        int direction2 = _dir2;
        _alg_comp_curve->mergeArcs(index, index2, direction, direction2);
    }

    void GLWidget::_continue() {
        int index = _arc1;
        int direction = _dir1;
        bool a = _dir1==1?true:false;
        _alg_comp_curve->continueArc(_arc1, a);
    }

    /*Merg join and continue patches*/

    void GLWidget::merge_surf() {
        _alg_comp_surf->mergePatches(_surface1, _surface2, _surf_dir1, _surf_dir2);
    }
    void GLWidget::join_surf() {
        ShaderProgram* ss = (&_shader4);
        _alg_comp_surf->joinPatches(_surface1, _surface2, _surf_dir1, _surf_dir2, ss);
    }
    void GLWidget::continue_surf() {
        _alg_comp_surf->continuePatch(_surface1, _surf_dir1);
    }

    void GLWidget::initAHSurface(){
        // elore beallitott patch-ek
            // 0
            _alg_comp_surf = new AlgebraicHyperbolicCompositeSurface3();
            AlgebraicHyperbolicPatch* _temp_patch;
            _temp_patch = new AlgebraicHyperbolicPatch(1.0);

            _temp_patch->SetData(0, 0, -2.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(0, 1, -2.0/2, -1.0/2, 0.0);
            _temp_patch->SetData(0, 2, -2.0/2, 1.0/2, 0.0);
            _temp_patch->SetData(0, 3, -2.0/2, 2.0/2, 0.0);

            _temp_patch->SetData(1, 0, -1.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(1, 1, -1.0/2, -1.0/2, 2.0/2);
            _temp_patch->SetData(1, 2, -1.0/2, 1.0/2, 2.0/2);
            _temp_patch->SetData(1, 3, -1.0/2, 2.0/2, 0.0);

            _temp_patch->SetData(2, 0, 1.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(2, 1, 1.0/2, -1.0/2, 2.0/2);
            _temp_patch->SetData(2, 2, 1.0/2, 1.0/2, 2.0/2);
            _temp_patch->SetData(2, 3, 1.0/2, 2.0/2, 0.0);

            _temp_patch->SetData(3, 0, 2.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(3, 1, 2.0/2, -1.0/2, 0.0);
            _temp_patch->SetData(3, 2, 2.0/2, 1.0/2, 0.0);
            _temp_patch->SetData(3, 3, 2.0/2, 2.0/2, 0.0);

            Material* m = new Material(MatFBRuby);
                   ShaderProgram* ss = (&_shader4);
                   _alg_comp_surf->insertPatch(_temp_patch, m, ss);

            delete _temp_patch;


            // 1
            _temp_patch = new AlgebraicHyperbolicPatch(_alpha);

            _temp_patch->SetData(0, 0, 6.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(0, 1, 6.0/2, -1.0/2, 0.0);
            _temp_patch->SetData(0, 2, 6.0/2, 1.0/2, 0.0);
            _temp_patch->SetData(0, 3, 6.0/2, 2.0/2, 0.0);

            _temp_patch->SetData(1, 0, 7.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(1, 1, 7.0/2, -1.0/2, 2.0/2);
            _temp_patch->SetData(1, 2, 7.0/2, 1.0/2, 2.0/2);
            _temp_patch->SetData(1, 3, 7.0/2, 2.0/2, 0.0);

            _temp_patch->SetData(2, 0, 9.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(2, 1, 9.0/2, -1.0/2, 2.0/2);
            _temp_patch->SetData(2, 2, 9.0/2, 1.0/2, 2.0/2);
            _temp_patch->SetData(2, 3, 9.0/2, 2.0/2, 0.0);

            _temp_patch->SetData(3, 0, 10.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(3, 1, 10.0/2, -1.0/2, 0.0);
            _temp_patch->SetData(3, 2, 10.0/2, 1.0/2, 0.0);
            _temp_patch->SetData(3, 3, 10.0/2, 2.0/2, 0.0);

            Material* mm = new Material(MatFBEmerald);


            _alg_comp_surf->insertPatch(_temp_patch, mm,ss);

            delete _temp_patch;


            // 2
            _temp_patch = new AlgebraicHyperbolicPatch(_alpha);

            _temp_patch->SetData(0, 0, -10.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(0, 1, -10.0/2, -1.0/2, 0.0);
            _temp_patch->SetData(0, 2, -10.0/2, 1.0/2, 0.0);
            _temp_patch->SetData(0, 3, -10.0/2, 2.0/2, 0.0);

            _temp_patch->SetData(1, 0, -9.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(1, 1, -9.0/2, -1.0/2, 2.0/2);
            _temp_patch->SetData(1, 2, -9.0/2, 1.0/2, -2.0/2);
            _temp_patch->SetData(1, 3, -9.0/2, 2.0/2, 0.0);

            _temp_patch->SetData(2, 0, -7.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(2, 1, -7.0/2, -1.0/2, 2.0/2);
            _temp_patch->SetData(2, 2, -7.0/2, 1.0/2, 2.0/2);
            _temp_patch->SetData(2, 3, -7.0/2, 2.0/2, -2.0/2);

            _temp_patch->SetData(3, 0, -6.0/2, -2.0/2, 0.0);
            _temp_patch->SetData(3, 1, -6.0/2, -1.0/2, 0.0);
            _temp_patch->SetData(3, 2, -6.0/2, 1.0/2, -3.0/2);
            _temp_patch->SetData(3, 3, -6.0/2, 2.0/2, 0.0);

            Material* mmm = new Material(MatFBSilver);

            _alg_comp_surf->insertPatch(_temp_patch, mmm,ss);

            delete _temp_patch;
    }

    void GLWidget::renderAHSurface() {
      glPointSize(4.0);
      glColor3f(1.0,0.0,1.0);

      if(_show_surf_fod) {
          _alg_comp_surf->renderUPartialDerivatives();
      }

      if(_show_surf_sod) {
          _alg_comp_surf->renderVPartialDerivatives();
      }

      if(_show_surf_uisoparam) {
          _alg_comp_surf->renderUIsoparametric();
      }

      if(_show_surf_visoparam) {
          _alg_comp_surf->renderVIsoparametric();
      }

      if(true) {
          glPointSize(4.0);
          _alg_comp_surf->RenderData(GL_POINTS);
      }

        _alg_comp_surf->Render();
        _alg_comp_surf->RenderControlNet();
    }

    void GLWidget::initAHArc() {
        _alg_comp_curve = new AlgebraicHyperbolicCompositeCurve3();
        AlgebraicHyperbolicArc3* _temp_arc;
        _temp_arc = new AlgebraicHyperbolicArc3(2.0);
        GLdouble step3 = TWO_PI/7;
        GLdouble t3 = 0;

        for (int i = 0; i < 4; i++, t3 += step3)
        {
            DCoordinate3 &cp = (*_temp_arc)[i];
            cp.x() = cos(t3);
            cp.y() = sin(t3);
            cp.z() = 0;
        }

        Color4* c = new Color4();
        c->r() = 0.0;
        c->g() = 0.0;
        c->b() = 1.0;

        _alg_comp_curve->insertArc(_temp_arc, c);

        delete _temp_arc;
        delete c;


        // 2
        _temp_arc = new AlgebraicHyperbolicArc3(2.0);
        GLdouble step5 = TWO_PI/7;
        GLdouble t5 = TWO_PI/2;

        for (int i = 0; i < 4; i++, t5 += step5)
        {
            DCoordinate3 &cp = (*_temp_arc)[i];
            cp.x() = cos(t5) - 2.0;
            cp.y() = sin(t5) + 1.0;
            cp.z() = 0;
        }

        c = new Color4();
        c->r() = 0.0;
        c->g() = 1.0;
        c->b() = 0.0;



        _alg_comp_curve->insertArc(_temp_arc, c);

        delete _temp_arc;
        delete c;


        // 3
        _temp_arc = new AlgebraicHyperbolicArc3(2.0);
        GLdouble step4 = TWO_PI/7;
        GLdouble t4 = TWO_PI/2;

        for (int i = 0; i < 4; i++, t4 += step4)
        {
            DCoordinate3 &cp = (*_temp_arc)[i];
            cp.x() = cos(t4);
            cp.y() = sin(t4);
            cp.z() = 0;
        }

        c = new Color4();
        c->r() = 1.0;
        c->g() = 0.0;
        c->b() = 0.0;

        _alg_comp_curve->insertArc(_temp_arc, c);

        delete _temp_arc;
        delete c;

    }


    void GLWidget::renderAHArc() {
        glPointSize(3.0);
        _alg_comp_curve->RenderData(GL_POINTS);
        _alg_comp_curve->RenderDerivatives(0, GL_LINE_STRIP);
        if(_show_fod) _alg_comp_curve->RenderDerivatives(1, GL_LINES);
        if(_show_sod) _alg_comp_curve->RenderDerivatives(2, GL_LINES);
    }

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();

            // applying transformations
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);


            switch(_page_index) {
                case 0:
                    renderParametricCurve();
                break;
                case 1:
                    MatFBRuby.Apply();
                    glEnable(GL_LIGHTING);
                    glEnable(GL_LIGHT0);
                    glEnable(GL_NORMALIZE);
                    renderSelectedParametricSurface();
                    glDisable(GL_LIGHTING);
                break;
                case 2:
                     switch(_shader_index) {
                         case 1:
                            _shader1.Enable(GL_TRUE);
                            _shader1.SetUniformVariable1f("scale_factor",scale_factor);
                            _shader1.SetUniformVariable1f("smoothing",smoothing);
                            _shader1.SetUniformVariable1f("shading",shading);
                          break;
                         case 2:
                            _shader2.Enable(GL_TRUE);
                          break;
                         case 3:
                            _shader3.Enable(GL_TRUE);
                            _shader3.SetUniformVariable4f("default_outline_color",r,g,b,a);
                            //ide kell valami
                          break;
                         case 4:
                            _shader4.Enable(GL_TRUE);
                          break;
                     }
                    MatFBGold.Apply();
                    glEnable(GL_LIGHTING);
                    glEnable(GL_LIGHT0);
                    glEnable(GL_NORMALIZE);
                    renderSelectedAnimal();
                    glDisable(GL_LIGHTING);

                    _shader1.Disable();
                    _shader2.Disable();
                    _shader3.Disable();
                    _shader4.Disable();
                break;
                case 3:
                    //renderInterpolatingCyclicCurve();
                    PaintCyclicCurves();
                break;
                case 4:
                    renderAlgebraicHyperbolic();
                break;
                case 5:
                    renderAHArc();
                break;
                case 6:
                    renderAHSurface();
                break;
            }  

        glPopMatrix();
    }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (float)w / (float)h;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        updateGL();
    }

    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            updateGL();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_x(double value)
    {
        if (_trans_x != value)
        {
            _trans_x = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            updateGL();
        }
    }
    void GLWidget::set_index(int index)
    {
        _index = index;
        updateGL();
    }

    void GLWidget::show_velocity_vectors(){

        _show_velocity_vectors = !_show_velocity_vectors;
        updateGL();
    };
    void GLWidget::show_acceleration_vectors(){

        _show_acceleration_vectors = !_show_acceleration_vectors;
        updateGL();
    };
    void GLWidget::set_index_surface(int index) {
        _surface_index = index;
        updateGL();
    };
    void GLWidget::set_index_animal(int index) {
        _animal_index = index;
        updateGL();
    };
    void GLWidget::set_page(int index) {
        _page_index = index;
        updateGL();
    };
    void GLWidget::set_index_shader(int index) {
        _shader_index = index;
        updateGL();
    };
    void GLWidget::set_toon_r(double c) {
        r = c;
        updateGL();
    };
    void GLWidget::set_toon_g(double c) {
        g = c;
        updateGL();
    };
    void GLWidget::set_toon_b(double c) {
        b = c;
        updateGL();
    };
    void GLWidget::set_toon_a(double c) {
        a = c;
        updateGL();
    };
    void GLWidget::set_scale_factor(int q) {
        scale_factor = q;
        updateGL();
    };
    void GLWidget::set_smoothing(int q) {
        smoothing = q;
        updateGL();
    };
    void GLWidget::set_shading(int q) {
        shading = q;
        updateGL();
    };

    //Algebraic Hyperfaszom

    void GLWidget::set_arc1(int n){
        _arc1 = n;
        updateGL();
    };
    void GLWidget::set_arc2(int n){
        _arc2 = n;
        updateGL();
    };
    void GLWidget::set_dir1(int n){
        _dir1 = n;
        updateGL();
    };
    void GLWidget::set_dir2(int n){
        _dir2 = n;
        updateGL();
    };
    void GLWidget::set_alpha(double n){
        _alg_comp_curve->set_alpha(n);
        updateGL();
    };

    void GLWidget::set_ith_datapoint(int n){
        _ith_datapoint = n;
        updateGL();
    };

    void GLWidget::inc_x(){
        double temp = _alg_comp_curve->x(_arc1, _ith_datapoint);
        temp+=0.1;
        _alg_comp_curve->x(temp, _arc1, _ith_datapoint);
        updateGL();
    };
    void GLWidget::inc_y(){
        double temp = _alg_comp_curve->y(_arc1, _ith_datapoint);
        temp+=0.1;
        _alg_comp_curve->y(temp, _arc1, _ith_datapoint);
        updateGL();
    };
    void GLWidget::inc_z(){
        double temp = _alg_comp_curve->z(_arc1, _ith_datapoint);
        temp+=0.1;
        _alg_comp_curve->z(temp, _arc1, _ith_datapoint);
        updateGL();
    };

    void GLWidget::dec_x(){
        double temp = _alg_comp_curve->x(_arc1, _ith_datapoint);
        temp+=-0.1;
        _alg_comp_curve->x(temp, _arc1, _ith_datapoint);
        updateGL();
    };
    void GLWidget::dec_y(){
        double temp = _alg_comp_curve->y(_arc1, _ith_datapoint);
        temp+=-0.1;
        _alg_comp_curve->y(temp, _arc1, _ith_datapoint);
        updateGL();
    };
    void GLWidget::dec_z(){
        double temp = _alg_comp_curve->z(_arc1, _ith_datapoint);
        temp+=-0.1;
        _alg_comp_curve->z(temp, _arc1, _ith_datapoint);
        updateGL();
    };


    void GLWidget::call_join(){
        join();
        updateGL();
    };

    void GLWidget::call_merge(){
        merge();
        updateGL();
    };


    void GLWidget::call_continue(){
        _continue();
        updateGL();
    };


    void GLWidget::show_fod(){
        _show_fod = !_show_fod;
        updateGL();
    };
    void GLWidget::show_sod(){
        _show_sod = !_show_sod;
        updateGL();
    };

    void GLWidget::set_surface1(int n){
        _surface1 = n;
        updateGL();
    };
    void GLWidget::set_surface2(int n){
        _surface2 = n;
        updateGL();
    };
    void GLWidget::set_surf_dir1(int n){
        _surf_dir1 = n;
        updateGL();
    };
    void GLWidget::set_surf_dir2(int n){
        _surf_dir2 = n;
        updateGL();
    };

    void GLWidget::call_surf_merge(){
        merge_surf();
        updateGL();
    };
    void GLWidget::call_surf_join(){
        join_surf();
        updateGL();
    };
    void GLWidget::call_surf_continue(){
        continue_surf();
        updateGL();
    };

    void GLWidget::show_surf_fod(){
        _show_surf_fod = !_show_surf_fod;
        updateGL();
    };
    void GLWidget::show_surf_sod(){
        _show_surf_sod = !_show_surf_sod;
        updateGL();
    };
    void GLWidget::show_surf_uisoparam(){
        _show_surf_uisoparam = !_show_surf_uisoparam;
        updateGL();
    };
    void GLWidget::show_surf_visoparam(){
        _show_surf_visoparam = !_show_surf_visoparam;
        updateGL();
    };

    //move points of surface
    void GLWidget::inc_s_x(){
        double temp = _alg_comp_surf->x(_surface1, _s_i, _s_j);
        temp+=0.1;
        _alg_comp_surf->x(temp,_surface1, _s_i, _s_j);
        updateGL();
    }
    void GLWidget::inc_s_y(){
        double temp = _alg_comp_surf->y(_surface1, _s_i, _s_j);
        temp+=0.1;
        _alg_comp_surf->y(temp,_surface1, _s_i, _s_j);
        updateGL();
    }
    void GLWidget::inc_s_z(){
        double temp = _alg_comp_surf->z(_surface1, _s_i, _s_j);
        temp+=0.1;
        _alg_comp_surf->z(temp,_surface1, _s_i, _s_j);
        updateGL();
    }

    void GLWidget::dec_s_x(){
        double temp = _alg_comp_surf->x(_surface1, _s_i, _s_j);
        temp-=0.1;
        _alg_comp_surf->x(temp,_surface1, _s_i, _s_j);
        updateGL();
    }
    void GLWidget::dec_s_y(){
        double temp = _alg_comp_surf->y(_surface1, _s_i, _s_j);
        temp-=0.1;
        _alg_comp_surf->y(temp,_surface1, _s_i, _s_j);
        updateGL();
    }
    void GLWidget::dec_s_z(){
        double temp = _alg_comp_surf->z(_surface1, _s_i, _s_j);
        temp-=0.1;
        _alg_comp_surf->z(temp,_surface1, _s_i, _s_j);
        updateGL();
    }

    void GLWidget::set_s_i(int n) {
        _s_i = n;
    }

    void GLWidget::set_s_j(int n) {
        _s_j= n;
    }


}
