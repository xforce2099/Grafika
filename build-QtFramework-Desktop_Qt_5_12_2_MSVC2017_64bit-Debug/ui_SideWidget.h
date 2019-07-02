/********************************************************************************
** Form generated from reading UI file 'SideWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEWIDGET_H
#define UI_SIDEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideWidget
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *rotate_x_slider;
    QLabel *label_2;
    QSlider *rotate_y_slider;
    QLabel *label_3;
    QSlider *rotate_z_slider;
    QLabel *label_4;
    QDoubleSpinBox *zoom_factor_spin_box;
    QLabel *label_5;
    QDoubleSpinBox *trans_x_spin_box;
    QLabel *label_6;
    QDoubleSpinBox *trans_y_spin_box;
    QLabel *label_7;
    QDoubleSpinBox *trans_z_spin_box;
    QToolBox *toolBox;
    QWidget *page;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QWidget *layoutWidget1;
    QFormLayout *formLayout_2;
    QLabel *label_8;
    QSpinBox *spinBox;
    QWidget *page_2;
    QSpinBox *spinBox_2;
    QLabel *label_10;
    QWidget *page_5;
    QLabel *label_9;
    QSpinBox *spinBox_3;
    QLabel *label_11;
    QSpinBox *spinBox_4;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_r;
    QDoubleSpinBox *doubleSpinBox_g;
    QDoubleSpinBox *doubleSpinBox_b;
    QDoubleSpinBox *doubleSpinBox_a;
    QLabel *label_13;
    QSpinBox *spinBox_scale_factor;
    QSpinBox *spinBox_smoothing;
    QSpinBox *spinBox_shading;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QWidget *page_6;
    QWidget *page_3;
    QWidget *page_4;
    QSpinBox *spinBox_Curve1;
    QSpinBox *spinBox_Curve2;
    QLabel *label_17;
    QLabel *label_18;
    QSpinBox *spinBox_Direction1;
    QLabel *label_19;
    QLabel *label_20;
    QSpinBox *spinBox_Direction2;
    QPushButton *pushButton_Merge;
    QPushButton *pushButton_Join;
    QPushButton *pushButton_Continue;
    QCheckBox *checkBox_fod;
    QCheckBox *checkBox_sod;
    QDoubleSpinBox *doubleSpinBox_Alpha;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QSpinBox *spinBox_I;
    QPushButton *pushButton_dec_x;
    QPushButton *pushButton_inc_x;
    QPushButton *pushButton_dec_y;
    QPushButton *pushButton_inc_y;
    QPushButton *pushButton_dec_z;
    QPushButton *pushButton_inc_z;
    QWidget *page_7;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QSpinBox *spinBox_Surface1;
    QSpinBox *spinBox_Surface2;
    QComboBox *comboBox_Direction1;
    QComboBox *comboBox_Direction2;
    QCheckBox *checkBox_sfod;
    QCheckBox *checkBox_ssod;
    QCheckBox *checkBox_uisoparametric;
    QCheckBox *checkBox_visoparametric;
    QPushButton *pushButton_SJoin;
    QPushButton *pushButton_SMerge;
    QPushButton *pushButton_SContinue;
    QLabel *label_31;
    QSpinBox *spinBox_set_s_i;
    QSpinBox *spinBox_set_s_j;
    QLabel *label_32;
    QLabel *label_33;
    QPushButton *pushButton_dec_s_x;
    QPushButton *pushButton_inc_s_x;
    QPushButton *pushButton_inc_s_y;
    QPushButton *pushButton_dec_s_z;
    QPushButton *pushButton_inc_s_z;
    QPushButton *pushButton_dec_s_y;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QString::fromUtf8("SideWidget"));
        SideWidget->resize(289, 1106);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideWidget->sizePolicy().hasHeightForWidth());
        SideWidget->setSizePolicy(sizePolicy);
        SideWidget->setMinimumSize(QSize(269, 0));
        groupBox = new QGroupBox(SideWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 271, 261));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 21, 261, 230));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rotate_x_slider = new QSlider(layoutWidget);
        rotate_x_slider->setObjectName(QString::fromUtf8("rotate_x_slider"));
        rotate_x_slider->setMinimum(-180);
        rotate_x_slider->setMaximum(180);
        rotate_x_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, rotate_x_slider);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        rotate_y_slider = new QSlider(layoutWidget);
        rotate_y_slider->setObjectName(QString::fromUtf8("rotate_y_slider"));
        rotate_y_slider->setMinimum(-180);
        rotate_y_slider->setMaximum(180);
        rotate_y_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, rotate_y_slider);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rotate_z_slider = new QSlider(layoutWidget);
        rotate_z_slider->setObjectName(QString::fromUtf8("rotate_z_slider"));
        rotate_z_slider->setMinimum(-180);
        rotate_z_slider->setMaximum(180);
        rotate_z_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, rotate_z_slider);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        zoom_factor_spin_box = new QDoubleSpinBox(layoutWidget);
        zoom_factor_spin_box->setObjectName(QString::fromUtf8("zoom_factor_spin_box"));
        zoom_factor_spin_box->setDecimals(5);
        zoom_factor_spin_box->setMinimum(0.000100000000000);
        zoom_factor_spin_box->setMaximum(10000.000000000000000);
        zoom_factor_spin_box->setSingleStep(0.100000000000000);
        zoom_factor_spin_box->setValue(1.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, zoom_factor_spin_box);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        trans_x_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_x_spin_box->setObjectName(QString::fromUtf8("trans_x_spin_box"));
        trans_x_spin_box->setMinimum(-100.000000000000000);
        trans_x_spin_box->setMaximum(100.000000000000000);
        trans_x_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(4, QFormLayout::FieldRole, trans_x_spin_box);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        trans_y_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_y_spin_box->setObjectName(QString::fromUtf8("trans_y_spin_box"));
        trans_y_spin_box->setMinimum(-100.000000000000000);
        trans_y_spin_box->setMaximum(100.000000000000000);
        trans_y_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, trans_y_spin_box);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        trans_z_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_z_spin_box->setObjectName(QString::fromUtf8("trans_z_spin_box"));
        trans_z_spin_box->setMinimum(-100.000000000000000);
        trans_z_spin_box->setMaximum(100.000000000000000);
        trans_z_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(6, QFormLayout::FieldRole, trans_z_spin_box);

        toolBox = new QToolBox(SideWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setGeometry(QRect(10, 270, 271, 721));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 271, 532));
        radioButton = new QRadioButton(page);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 30, 131, 17));
        radioButton_2 = new QRadioButton(page);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 60, 151, 17));
        layoutWidget1 = new QWidget(page);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 0, 251, 22));
        formLayout_2 = new QFormLayout(layoutWidget1);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_8);

        spinBox = new QSpinBox(layoutWidget1);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(4);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinBox);

        toolBox->addItem(page, QString::fromUtf8("ParametricCurves"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 271, 532));
        spinBox_2 = new QSpinBox(page_2);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(90, 0, 42, 22));
        spinBox_2->setMaximum(4);
        label_10 = new QLabel(page_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 0, 101, 16));
        toolBox->addItem(page_2, QString::fromUtf8("Surfaces"));
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        page_5->setGeometry(QRect(0, 0, 271, 532));
        label_9 = new QLabel(page_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 0, 81, 16));
        spinBox_3 = new QSpinBox(page_5);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(90, 0, 42, 22));
        spinBox_3->setMaximum(2);
        label_11 = new QLabel(page_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 30, 81, 16));
        spinBox_4 = new QSpinBox(page_5);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(100, 30, 42, 22));
        spinBox_4->setMinimum(1);
        spinBox_4->setMaximum(4);
        label_12 = new QLabel(page_5);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(100, 70, 71, 16));
        doubleSpinBox_r = new QDoubleSpinBox(page_5);
        doubleSpinBox_r->setObjectName(QString::fromUtf8("doubleSpinBox_r"));
        doubleSpinBox_r->setGeometry(QRect(0, 90, 62, 22));
        doubleSpinBox_r->setMaximum(1.000000000000000);
        doubleSpinBox_r->setSingleStep(0.010000000000000);
        doubleSpinBox_g = new QDoubleSpinBox(page_5);
        doubleSpinBox_g->setObjectName(QString::fromUtf8("doubleSpinBox_g"));
        doubleSpinBox_g->setGeometry(QRect(70, 90, 62, 22));
        doubleSpinBox_g->setMaximum(1.000000000000000);
        doubleSpinBox_g->setSingleStep(0.010000000000000);
        doubleSpinBox_b = new QDoubleSpinBox(page_5);
        doubleSpinBox_b->setObjectName(QString::fromUtf8("doubleSpinBox_b"));
        doubleSpinBox_b->setGeometry(QRect(140, 90, 62, 22));
        doubleSpinBox_b->setMaximum(1.000000000000000);
        doubleSpinBox_b->setSingleStep(0.010000000000000);
        doubleSpinBox_a = new QDoubleSpinBox(page_5);
        doubleSpinBox_a->setObjectName(QString::fromUtf8("doubleSpinBox_a"));
        doubleSpinBox_a->setGeometry(QRect(210, 90, 62, 22));
        doubleSpinBox_a->setMaximum(1.000000000000000);
        doubleSpinBox_a->setSingleStep(0.010000000000000);
        label_13 = new QLabel(page_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(100, 120, 47, 13));
        spinBox_scale_factor = new QSpinBox(page_5);
        spinBox_scale_factor->setObjectName(QString::fromUtf8("spinBox_scale_factor"));
        spinBox_scale_factor->setGeometry(QRect(10, 170, 42, 22));
        spinBox_scale_factor->setMaximum(10);
        spinBox_smoothing = new QSpinBox(page_5);
        spinBox_smoothing->setObjectName(QString::fromUtf8("spinBox_smoothing"));
        spinBox_smoothing->setGeometry(QRect(110, 170, 42, 22));
        spinBox_smoothing->setMaximum(10);
        spinBox_shading = new QSpinBox(page_5);
        spinBox_shading->setObjectName(QString::fromUtf8("spinBox_shading"));
        spinBox_shading->setGeometry(QRect(210, 170, 42, 22));
        spinBox_shading->setMaximum(10);
        label_14 = new QLabel(page_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 150, 61, 16));
        label_15 = new QLabel(page_5);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(110, 150, 61, 16));
        label_16 = new QLabel(page_5);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(210, 150, 47, 13));
        toolBox->addItem(page_5, QString::fromUtf8("Animals"));
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        page_6->setGeometry(QRect(0, 0, 271, 532));
        toolBox->addItem(page_6, QString::fromUtf8("Interpolating cyclic curve"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 271, 532));
        toolBox->addItem(page_3, QString::fromUtf8("Algebraic Hyperbolic"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 271, 532));
        spinBox_Curve1 = new QSpinBox(page_4);
        spinBox_Curve1->setObjectName(QString::fromUtf8("spinBox_Curve1"));
        spinBox_Curve1->setGeometry(QRect(60, 0, 42, 22));
        spinBox_Curve1->setMaximum(2);
        spinBox_Curve2 = new QSpinBox(page_4);
        spinBox_Curve2->setObjectName(QString::fromUtf8("spinBox_Curve2"));
        spinBox_Curve2->setGeometry(QRect(60, 30, 42, 22));
        spinBox_Curve2->setMaximum(2);
        label_17 = new QLabel(page_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(0, 0, 47, 13));
        label_18 = new QLabel(page_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(0, 30, 47, 13));
        spinBox_Direction1 = new QSpinBox(page_4);
        spinBox_Direction1->setObjectName(QString::fromUtf8("spinBox_Direction1"));
        spinBox_Direction1->setGeometry(QRect(60, 60, 42, 22));
        spinBox_Direction1->setMaximum(1);
        label_19 = new QLabel(page_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(0, 60, 47, 13));
        label_20 = new QLabel(page_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(0, 90, 47, 13));
        spinBox_Direction2 = new QSpinBox(page_4);
        spinBox_Direction2->setObjectName(QString::fromUtf8("spinBox_Direction2"));
        spinBox_Direction2->setGeometry(QRect(60, 90, 42, 22));
        pushButton_Merge = new QPushButton(page_4);
        pushButton_Merge->setObjectName(QString::fromUtf8("pushButton_Merge"));
        pushButton_Merge->setGeometry(QRect(150, 20, 75, 23));
        pushButton_Join = new QPushButton(page_4);
        pushButton_Join->setObjectName(QString::fromUtf8("pushButton_Join"));
        pushButton_Join->setGeometry(QRect(150, 50, 75, 23));
        pushButton_Continue = new QPushButton(page_4);
        pushButton_Continue->setObjectName(QString::fromUtf8("pushButton_Continue"));
        pushButton_Continue->setGeometry(QRect(150, 80, 75, 23));
        checkBox_fod = new QCheckBox(page_4);
        checkBox_fod->setObjectName(QString::fromUtf8("checkBox_fod"));
        checkBox_fod->setGeometry(QRect(0, 190, 161, 17));
        checkBox_sod = new QCheckBox(page_4);
        checkBox_sod->setObjectName(QString::fromUtf8("checkBox_sod"));
        checkBox_sod->setGeometry(QRect(0, 210, 161, 17));
        doubleSpinBox_Alpha = new QDoubleSpinBox(page_4);
        doubleSpinBox_Alpha->setObjectName(QString::fromUtf8("doubleSpinBox_Alpha"));
        doubleSpinBox_Alpha->setGeometry(QRect(60, 130, 62, 22));
        doubleSpinBox_Alpha->setMaximum(10.000000000000000);
        doubleSpinBox_Alpha->setSingleStep(0.500000000000000);
        label_21 = new QLabel(page_4);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(0, 130, 47, 13));
        label_22 = new QLabel(page_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(0, 270, 16, 16));
        label_23 = new QLabel(page_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(0, 300, 16, 16));
        label_24 = new QLabel(page_4);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(0, 330, 16, 16));
        label_25 = new QLabel(page_4);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(0, 240, 271, 16));
        label_26 = new QLabel(page_4);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(130, 270, 71, 16));
        spinBox_I = new QSpinBox(page_4);
        spinBox_I->setObjectName(QString::fromUtf8("spinBox_I"));
        spinBox_I->setGeometry(QRect(210, 270, 42, 22));
        spinBox_I->setMaximum(3);
        pushButton_dec_x = new QPushButton(page_4);
        pushButton_dec_x->setObjectName(QString::fromUtf8("pushButton_dec_x"));
        pushButton_dec_x->setGeometry(QRect(20, 270, 21, 23));
        pushButton_inc_x = new QPushButton(page_4);
        pushButton_inc_x->setObjectName(QString::fromUtf8("pushButton_inc_x"));
        pushButton_inc_x->setGeometry(QRect(50, 270, 21, 23));
        pushButton_dec_y = new QPushButton(page_4);
        pushButton_dec_y->setObjectName(QString::fromUtf8("pushButton_dec_y"));
        pushButton_dec_y->setGeometry(QRect(20, 300, 21, 23));
        pushButton_inc_y = new QPushButton(page_4);
        pushButton_inc_y->setObjectName(QString::fromUtf8("pushButton_inc_y"));
        pushButton_inc_y->setGeometry(QRect(50, 300, 21, 23));
        pushButton_dec_z = new QPushButton(page_4);
        pushButton_dec_z->setObjectName(QString::fromUtf8("pushButton_dec_z"));
        pushButton_dec_z->setGeometry(QRect(20, 330, 21, 23));
        pushButton_inc_z = new QPushButton(page_4);
        pushButton_inc_z->setObjectName(QString::fromUtf8("pushButton_inc_z"));
        pushButton_inc_z->setGeometry(QRect(50, 330, 21, 23));
        toolBox->addItem(page_4, QString::fromUtf8("Algebraic Hyperbolic Composite Curves"));
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        page_7->setGeometry(QRect(0, 0, 271, 532));
        label_27 = new QLabel(page_7);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(0, 10, 61, 16));
        label_28 = new QLabel(page_7);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(0, 40, 47, 13));
        label_29 = new QLabel(page_7);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(0, 80, 61, 16));
        label_30 = new QLabel(page_7);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(0, 120, 61, 16));
        spinBox_Surface1 = new QSpinBox(page_7);
        spinBox_Surface1->setObjectName(QString::fromUtf8("spinBox_Surface1"));
        spinBox_Surface1->setGeometry(QRect(60, 10, 42, 22));
        spinBox_Surface1->setMaximum(2);
        spinBox_Surface2 = new QSpinBox(page_7);
        spinBox_Surface2->setObjectName(QString::fromUtf8("spinBox_Surface2"));
        spinBox_Surface2->setGeometry(QRect(60, 40, 42, 22));
        spinBox_Surface2->setMaximum(2);
        comboBox_Direction1 = new QComboBox(page_7);
        comboBox_Direction1->addItem(QString());
        comboBox_Direction1->addItem(QString());
        comboBox_Direction1->addItem(QString());
        comboBox_Direction1->addItem(QString());
        comboBox_Direction1->setObjectName(QString::fromUtf8("comboBox_Direction1"));
        comboBox_Direction1->setGeometry(QRect(60, 80, 69, 22));
        comboBox_Direction2 = new QComboBox(page_7);
        comboBox_Direction2->addItem(QString());
        comboBox_Direction2->addItem(QString());
        comboBox_Direction2->addItem(QString());
        comboBox_Direction2->addItem(QString());
        comboBox_Direction2->setObjectName(QString::fromUtf8("comboBox_Direction2"));
        comboBox_Direction2->setGeometry(QRect(60, 120, 69, 22));
        checkBox_sfod = new QCheckBox(page_7);
        checkBox_sfod->setObjectName(QString::fromUtf8("checkBox_sfod"));
        checkBox_sfod->setGeometry(QRect(0, 160, 201, 17));
        checkBox_ssod = new QCheckBox(page_7);
        checkBox_ssod->setObjectName(QString::fromUtf8("checkBox_ssod"));
        checkBox_ssod->setGeometry(QRect(0, 190, 211, 17));
        checkBox_uisoparametric = new QCheckBox(page_7);
        checkBox_uisoparametric->setObjectName(QString::fromUtf8("checkBox_uisoparametric"));
        checkBox_uisoparametric->setGeometry(QRect(0, 220, 201, 17));
        checkBox_visoparametric = new QCheckBox(page_7);
        checkBox_visoparametric->setObjectName(QString::fromUtf8("checkBox_visoparametric"));
        checkBox_visoparametric->setGeometry(QRect(0, 250, 171, 17));
        pushButton_SJoin = new QPushButton(page_7);
        pushButton_SJoin->setObjectName(QString::fromUtf8("pushButton_SJoin"));
        pushButton_SJoin->setGeometry(QRect(180, 0, 75, 23));
        pushButton_SMerge = new QPushButton(page_7);
        pushButton_SMerge->setObjectName(QString::fromUtf8("pushButton_SMerge"));
        pushButton_SMerge->setGeometry(QRect(180, 30, 75, 23));
        pushButton_SContinue = new QPushButton(page_7);
        pushButton_SContinue->setObjectName(QString::fromUtf8("pushButton_SContinue"));
        pushButton_SContinue->setGeometry(QRect(180, 60, 75, 23));
        label_31 = new QLabel(page_7);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(30, 270, 201, 20));
        spinBox_set_s_i = new QSpinBox(page_7);
        spinBox_set_s_i->setObjectName(QString::fromUtf8("spinBox_set_s_i"));
        spinBox_set_s_i->setGeometry(QRect(130, 300, 42, 22));
        spinBox_set_s_j = new QSpinBox(page_7);
        spinBox_set_s_j->setObjectName(QString::fromUtf8("spinBox_set_s_j"));
        spinBox_set_s_j->setGeometry(QRect(130, 330, 42, 22));
        label_32 = new QLabel(page_7);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(100, 300, 16, 16));
        QFont font;
        font.setPointSize(12);
        label_32->setFont(font);
        label_33 = new QLabel(page_7);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(100, 330, 16, 16));
        label_33->setFont(font);
        pushButton_dec_s_x = new QPushButton(page_7);
        pushButton_dec_s_x->setObjectName(QString::fromUtf8("pushButton_dec_s_x"));
        pushButton_dec_s_x->setGeometry(QRect(30, 300, 21, 23));
        pushButton_inc_s_x = new QPushButton(page_7);
        pushButton_inc_s_x->setObjectName(QString::fromUtf8("pushButton_inc_s_x"));
        pushButton_inc_s_x->setGeometry(QRect(60, 300, 21, 23));
        pushButton_inc_s_y = new QPushButton(page_7);
        pushButton_inc_s_y->setObjectName(QString::fromUtf8("pushButton_inc_s_y"));
        pushButton_inc_s_y->setGeometry(QRect(60, 330, 21, 23));
        pushButton_dec_s_z = new QPushButton(page_7);
        pushButton_dec_s_z->setObjectName(QString::fromUtf8("pushButton_dec_s_z"));
        pushButton_dec_s_z->setGeometry(QRect(30, 360, 21, 23));
        pushButton_inc_s_z = new QPushButton(page_7);
        pushButton_inc_s_z->setObjectName(QString::fromUtf8("pushButton_inc_s_z"));
        pushButton_inc_s_z->setGeometry(QRect(60, 360, 21, 23));
        pushButton_dec_s_y = new QPushButton(page_7);
        pushButton_dec_s_y->setObjectName(QString::fromUtf8("pushButton_dec_s_y"));
        pushButton_dec_s_y->setGeometry(QRect(30, 330, 21, 23));
        label_34 = new QLabel(page_7);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(0, 300, 47, 13));
        label_35 = new QLabel(page_7);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(0, 330, 47, 13));
        label_36 = new QLabel(page_7);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(0, 360, 47, 13));
        toolBox->addItem(page_7, QString::fromUtf8("Algebraic Hyperbolic Composite Surfaces"));
#ifndef QT_NO_SHORTCUT
        label->setBuddy(rotate_x_slider);
        label_2->setBuddy(rotate_y_slider);
        label_3->setBuddy(rotate_z_slider);
        label_4->setBuddy(zoom_factor_spin_box);
        label_5->setBuddy(trans_x_spin_box);
        label_6->setBuddy(trans_y_spin_box);
        label_7->setBuddy(trans_z_spin_box);
        label_8->setBuddy(spinBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(SideWidget);

        toolBox->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(SideWidget);
    } // setupUi

    void retranslateUi(QWidget *SideWidget)
    {
        SideWidget->setWindowTitle(QApplication::translate("SideWidget", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("SideWidget", "Transformations", nullptr));
        label->setText(QApplication::translate("SideWidget", "Rotate around x", nullptr));
        label_2->setText(QApplication::translate("SideWidget", "Rotate around y", nullptr));
        label_3->setText(QApplication::translate("SideWidget", "Rotate around z", nullptr));
        label_4->setText(QApplication::translate("SideWidget", "Zoom factor", nullptr));
#ifndef QT_NO_TOOLTIP
        zoom_factor_spin_box->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("SideWidget", "Translate along x", nullptr));
        label_6->setText(QApplication::translate("SideWidget", "Translate along y", nullptr));
        label_7->setText(QApplication::translate("SideWidget", "Translate along z", nullptr));
        radioButton->setText(QApplication::translate("SideWidget", "Show velocity vectors", nullptr));
        radioButton_2->setText(QApplication::translate("SideWidget", "Show acceleration vectors", nullptr));
        label_8->setText(QApplication::translate("SideWidget", "TextLabel", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("SideWidget", "ParametricCurves", nullptr));
        label_10->setText(QApplication::translate("SideWidget", "Change surfaces", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("SideWidget", "Surfaces", nullptr));
        label_9->setText(QApplication::translate("SideWidget", "Change animal", nullptr));
        label_11->setText(QApplication::translate("SideWidget", "Change Shader", nullptr));
        label_12->setText(QApplication::translate("SideWidget", "Toon RGBA", nullptr));
        label_13->setText(QApplication::translate("SideWidget", "Reflection", nullptr));
        label_14->setText(QApplication::translate("SideWidget", "scale factor", nullptr));
        label_15->setText(QApplication::translate("SideWidget", "smoothing", nullptr));
        label_16->setText(QApplication::translate("SideWidget", "shading", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_5), QApplication::translate("SideWidget", "Animals", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_6), QApplication::translate("SideWidget", "Interpolating cyclic curve", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("SideWidget", "Algebraic Hyperbolic", nullptr));
        label_17->setText(QApplication::translate("SideWidget", "Curve 1", nullptr));
        label_18->setText(QApplication::translate("SideWidget", "Curve 2", nullptr));
        label_19->setText(QApplication::translate("SideWidget", "Direction1", nullptr));
        label_20->setText(QApplication::translate("SideWidget", "Direction2", nullptr));
        pushButton_Merge->setText(QApplication::translate("SideWidget", "Merge", nullptr));
        pushButton_Join->setText(QApplication::translate("SideWidget", "Join", nullptr));
        pushButton_Continue->setText(QApplication::translate("SideWidget", "Continue", nullptr));
        checkBox_fod->setText(QApplication::translate("SideWidget", "Show first order derivatives", nullptr));
        checkBox_sod->setText(QApplication::translate("SideWidget", "Show second order derivatives", nullptr));
        label_21->setText(QApplication::translate("SideWidget", "Alpha", nullptr));
        label_22->setText(QApplication::translate("SideWidget", "X", nullptr));
        label_23->setText(QApplication::translate("SideWidget", "Y", nullptr));
        label_24->setText(QApplication::translate("SideWidget", "Z", nullptr));
        label_25->setText(QApplication::translate("SideWidget", "Move i-th data point of the selected Curve 1", nullptr));
        label_26->setText(QApplication::translate("SideWidget", "i-th data point", nullptr));
        pushButton_dec_x->setText(QApplication::translate("SideWidget", "<", nullptr));
        pushButton_inc_x->setText(QApplication::translate("SideWidget", ">", nullptr));
        pushButton_dec_y->setText(QApplication::translate("SideWidget", "<", nullptr));
        pushButton_inc_y->setText(QApplication::translate("SideWidget", ">", nullptr));
        pushButton_dec_z->setText(QApplication::translate("SideWidget", "<", nullptr));
        pushButton_inc_z->setText(QApplication::translate("SideWidget", ">", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("SideWidget", "Algebraic Hyperbolic Composite Curves", nullptr));
        label_27->setText(QApplication::translate("SideWidget", "Surface 1", nullptr));
        label_28->setText(QApplication::translate("SideWidget", "Surface 2", nullptr));
        label_29->setText(QApplication::translate("SideWidget", "Direction 1", nullptr));
        label_30->setText(QApplication::translate("SideWidget", "Direction 2", nullptr));
        comboBox_Direction1->setItemText(0, QApplication::translate("SideWidget", "West", nullptr));
        comboBox_Direction1->setItemText(1, QApplication::translate("SideWidget", "North", nullptr));
        comboBox_Direction1->setItemText(2, QApplication::translate("SideWidget", "East", nullptr));
        comboBox_Direction1->setItemText(3, QApplication::translate("SideWidget", "South", nullptr));

        comboBox_Direction2->setItemText(0, QApplication::translate("SideWidget", "West", nullptr));
        comboBox_Direction2->setItemText(1, QApplication::translate("SideWidget", "North", nullptr));
        comboBox_Direction2->setItemText(2, QApplication::translate("SideWidget", "East", nullptr));
        comboBox_Direction2->setItemText(3, QApplication::translate("SideWidget", "South", nullptr));

        checkBox_sfod->setText(QApplication::translate("SideWidget", "Show u-partial derivatives", nullptr));
        checkBox_ssod->setText(QApplication::translate("SideWidget", "Show v-partial derivates", nullptr));
        checkBox_uisoparametric->setText(QApplication::translate("SideWidget", "Show u-isoparametric curves", nullptr));
        checkBox_visoparametric->setText(QApplication::translate("SideWidget", "Show v-isoparametric curves", nullptr));
        pushButton_SJoin->setText(QApplication::translate("SideWidget", "Join", nullptr));
        pushButton_SMerge->setText(QApplication::translate("SideWidget", "Merge", nullptr));
        pushButton_SContinue->setText(QApplication::translate("SideWidget", "Continue", nullptr));
        label_31->setText(QApplication::translate("SideWidget", "Move the [i,j]-th point of Surface1", nullptr));
        label_32->setText(QApplication::translate("SideWidget", "I", nullptr));
        label_33->setText(QApplication::translate("SideWidget", "J", nullptr));
        pushButton_dec_s_x->setText(QApplication::translate("SideWidget", "<", nullptr));
        pushButton_inc_s_x->setText(QApplication::translate("SideWidget", ">", nullptr));
        pushButton_inc_s_y->setText(QApplication::translate("SideWidget", ">", nullptr));
        pushButton_dec_s_z->setText(QApplication::translate("SideWidget", "<", nullptr));
        pushButton_inc_s_z->setText(QApplication::translate("SideWidget", ">", nullptr));
        pushButton_dec_s_y->setText(QApplication::translate("SideWidget", "<", nullptr));
        label_34->setText(QApplication::translate("SideWidget", "X", nullptr));
        label_35->setText(QApplication::translate("SideWidget", "Y", nullptr));
        label_36->setText(QApplication::translate("SideWidget", "Z", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_7), QApplication::translate("SideWidget", "Algebraic Hyperbolic Composite Surfaces", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H
