#include "MainWindow.h"

namespace cagd
{
    MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    {
        setupUi(this);

    /*

      the structure of the main window's central widget

     *---------------------------------------------------*
     |                 central widget                    |
     |                                                   |
     |  *---------------------------*-----------------*  |
     |  |     rendering context     |   scroll area   |  |
     |  |       OpenGL widget       | *-------------* |  |
     |  |                           | | side widget | |  |
     |  |                           | |             | |  |
     |  |                           | |             | |  |
     |  |                           | *-------------* |  |
     |  *---------------------------*-----------------*  |
     |                                                   |
     *---------------------------------------------------*

    */
        _side_widget = new SideWidget(this);

        _scroll_area = new QScrollArea(this);
        _scroll_area->setWidget(_side_widget);
        _scroll_area->setSizePolicy(_side_widget->sizePolicy());
        _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        _gl_widget = new GLWidget(this);

        centralWidget()->setLayout(new QHBoxLayout());
        centralWidget()->layout()->addWidget(_gl_widget);
        centralWidget()->layout()->addWidget(_scroll_area);

        // creating a signal slot mechanism between the rendering context and the side widget
        connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
        connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
        connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

        connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

        connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
        connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
        connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));

        //TEST
        connect(_side_widget->spinBox, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_index(int)));
        connect(_side_widget->spinBox_2, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_index_surface(int)));
        connect(_side_widget->spinBox_3, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_index_animal(int)));

        connect(_side_widget->radioButton, SIGNAL(clicked()), _gl_widget, SLOT(show_velocity_vectors()));
        connect(_side_widget->radioButton_2, SIGNAL(clicked()), _gl_widget, SLOT(show_acceleration_vectors()));

        //TEST 2
        connect(_side_widget->toolBox, SIGNAL(currentChanged(int)), _gl_widget, SLOT(set_page(int)));
        connect(_side_widget->spinBox_4, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_index_shader(int)));

        //Toon color
        connect(_side_widget->doubleSpinBox_r, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_toon_r(double)));
        connect(_side_widget->doubleSpinBox_g, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_toon_g(double)));
        connect(_side_widget->doubleSpinBox_b, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_toon_b(double)));
        connect(_side_widget->doubleSpinBox_a, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_toon_a(double)));
        //masik shDeR
        connect(_side_widget->spinBox_scale_factor, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_scale_factor(int)));
        connect(_side_widget->spinBox_smoothing, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_smoothing(int)));
        connect(_side_widget->spinBox_shading, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_shading(int)));

        /**************************/
        /***ALGEBRAIC HYPERBOLIC CURVES***/
        /**************************/
        connect(_side_widget->spinBox_Curve1, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_arc1(int)));
        connect(_side_widget->spinBox_Curve2, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_arc2(int)));
        connect(_side_widget->spinBox_Direction1, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_dir1(int)));
        connect(_side_widget->spinBox_Direction2, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_dir2(int)));
        connect(_side_widget->doubleSpinBox_Alpha, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_alpha(double)));
        connect(_side_widget->spinBox_I, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_ith_datapoint(int)));

        connect(_side_widget->pushButton_Merge, SIGNAL(clicked(bool)), _gl_widget, SLOT(call_merge()));
        connect(_side_widget->pushButton_Join, SIGNAL(clicked(bool)), _gl_widget, SLOT(call_join()));
        connect(_side_widget->pushButton_Continue, SIGNAL(clicked(bool)), _gl_widget, SLOT(call_continue()));

        connect(_side_widget->checkBox_fod, SIGNAL(clicked(bool)), _gl_widget, SLOT(show_fod()));
        connect(_side_widget->checkBox_sod, SIGNAL(clicked(bool)), _gl_widget, SLOT(show_sod()));

        connect(_side_widget->pushButton_inc_x, SIGNAL(clicked(bool)), _gl_widget, SLOT(inc_x()));
        connect(_side_widget->pushButton_dec_x, SIGNAL(clicked(bool)), _gl_widget, SLOT(dec_x()));

        connect(_side_widget->pushButton_inc_y, SIGNAL(clicked(bool)), _gl_widget, SLOT(inc_y()));
        connect(_side_widget->pushButton_dec_y, SIGNAL(clicked(bool)), _gl_widget, SLOT(dec_y()));

        connect(_side_widget->pushButton_inc_z, SIGNAL(clicked(bool)), _gl_widget, SLOT(inc_z()));
        connect(_side_widget->pushButton_dec_z, SIGNAL(clicked(bool)), _gl_widget, SLOT(dec_z()));

        /**************************/
        /***ALGEBRAIC HYPERBOLIC SURFACES***/
        /**************************/
        connect(_side_widget->spinBox_Surface1, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_surface1(int)));
        connect(_side_widget->spinBox_Surface2, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_surface2(int)));
        connect(_side_widget->comboBox_Direction1, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_surf_dir1(int)));
        connect(_side_widget->comboBox_Direction2, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_surf_dir2(int)));

        connect(_side_widget->pushButton_SMerge, SIGNAL(clicked(bool)), _gl_widget, SLOT(call_surf_merge()));
        connect(_side_widget->pushButton_SJoin, SIGNAL(clicked(bool)), _gl_widget, SLOT(call_surf_join()));
        connect(_side_widget->pushButton_SContinue, SIGNAL(clicked(bool)), _gl_widget, SLOT(call_surf_continue()));

        connect(_side_widget->checkBox_sfod, SIGNAL(clicked(bool)), _gl_widget, SLOT(show_surf_fod()));
        connect(_side_widget->checkBox_ssod, SIGNAL(clicked(bool)), _gl_widget, SLOT(show_surf_sod()));
        connect(_side_widget->checkBox_uisoparametric, SIGNAL(clicked(bool)), _gl_widget, SLOT(show_surf_uisoparam()));
        connect(_side_widget->checkBox_visoparametric, SIGNAL(clicked(bool)), _gl_widget, SLOT(show_surf_visoparam()));

        connect(_side_widget->pushButton_inc_s_x, SIGNAL(clicked(bool)), _gl_widget, SLOT(inc_s_x()));
        connect(_side_widget->pushButton_dec_s_x, SIGNAL(clicked(bool)), _gl_widget, SLOT(dec_s_x()));

        connect(_side_widget->pushButton_inc_s_y, SIGNAL(clicked(bool)), _gl_widget, SLOT(inc_s_y()));
        connect(_side_widget->pushButton_dec_s_y, SIGNAL(clicked(bool)), _gl_widget, SLOT(dec_s_y()));

        connect(_side_widget->pushButton_inc_s_z, SIGNAL(clicked(bool)), _gl_widget, SLOT(inc_s_z()));
        connect(_side_widget->pushButton_dec_s_z, SIGNAL(clicked(bool)), _gl_widget, SLOT(dec_s_z()));

        connect(_side_widget->spinBox_set_s_i, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_s_i(int)));
        connect(_side_widget->spinBox_set_s_j, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_s_j(int)));



    }

    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}
