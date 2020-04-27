/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QWidget *centralwidget;
    QLabel *labelTop;
    QProgressBar *progressBar;
    QFrame *line;
    GLWidget *openGLWidget;
    QComboBox *renderTechnique;
    QLabel *label_renderTechnique;
    QLabel *label_transforamtion;
    QLabel *label_translation;
    QSlider *translationX;
    QSlider *translationY;
    QSlider *translationZ;
    QLabel *label_rotation;
    QSlider *rotationY;
    QSlider *rotationX;
    QSlider *rotationZ;
    QLabel *label_zoom;
    QSlider *zoom;
    QLabel *label_gama;
    QSlider *gamma;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSlider *schichtenEinblenden;
    QLabel *label_schichtenEinblenden;
    QLabel *label_ambient;
    QSlider *ambient;
    QLabel *label_diffuse;
    QSlider *diffuse;
    QLabel *label_specular;
    QSlider *specular;
    QComboBox *gradientModeCalc;
    QComboBox *gradientModeTarget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 700);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelTop = new QLabel(centralwidget);
        labelTop->setObjectName(QStringLiteral("labelTop"));
        labelTop->setGeometry(QRect(20, 20, 1001, 16));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(false);
        progressBar->setGeometry(QRect(787, 20, 201, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 50, 1011, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        openGLWidget = new GLWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 60, 791, 641));
        openGLWidget->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        renderTechnique = new QComboBox(centralwidget);
        renderTechnique->setObjectName(QStringLiteral("renderTechnique"));
        renderTechnique->setGeometry(QRect(900, 70, 91, 22));
        label_renderTechnique = new QLabel(centralwidget);
        label_renderTechnique->setObjectName(QStringLiteral("label_renderTechnique"));
        label_renderTechnique->setGeometry(QRect(800, 70, 91, 21));
        label_transforamtion = new QLabel(centralwidget);
        label_transforamtion->setObjectName(QStringLiteral("label_transforamtion"));
        label_transforamtion->setGeometry(QRect(800, 390, 91, 16));
        label_translation = new QLabel(centralwidget);
        label_translation->setObjectName(QStringLiteral("label_translation"));
        label_translation->setGeometry(QRect(800, 410, 71, 16));
        translationX = new QSlider(centralwidget);
        translationX->setObjectName(QStringLiteral("translationX"));
        translationX->setGeometry(QRect(810, 430, 181, 22));
        translationX->setSliderPosition(49);
        translationX->setOrientation(Qt::Horizontal);
        translationY = new QSlider(centralwidget);
        translationY->setObjectName(QStringLiteral("translationY"));
        translationY->setGeometry(QRect(810, 460, 181, 22));
        translationY->setSliderPosition(49);
        translationY->setOrientation(Qt::Horizontal);
        translationZ = new QSlider(centralwidget);
        translationZ->setObjectName(QStringLiteral("translationZ"));
        translationZ->setGeometry(QRect(810, 490, 181, 22));
        translationZ->setSliderPosition(49);
        translationZ->setOrientation(Qt::Horizontal);
        label_rotation = new QLabel(centralwidget);
        label_rotation->setObjectName(QStringLiteral("label_rotation"));
        label_rotation->setGeometry(QRect(800, 520, 71, 16));
        rotationY = new QSlider(centralwidget);
        rotationY->setObjectName(QStringLiteral("rotationY"));
        rotationY->setGeometry(QRect(810, 570, 181, 22));
        rotationY->setSliderPosition(49);
        rotationY->setOrientation(Qt::Horizontal);
        rotationX = new QSlider(centralwidget);
        rotationX->setObjectName(QStringLiteral("rotationX"));
        rotationX->setGeometry(QRect(810, 540, 181, 22));
        rotationX->setSliderPosition(49);
        rotationX->setOrientation(Qt::Horizontal);
        rotationZ = new QSlider(centralwidget);
        rotationZ->setObjectName(QStringLiteral("rotationZ"));
        rotationZ->setGeometry(QRect(810, 600, 181, 22));
        rotationZ->setSliderPosition(49);
        rotationZ->setOrientation(Qt::Horizontal);
        label_zoom = new QLabel(centralwidget);
        label_zoom->setObjectName(QStringLiteral("label_zoom"));
        label_zoom->setGeometry(QRect(800, 630, 71, 16));
        zoom = new QSlider(centralwidget);
        zoom->setObjectName(QStringLiteral("zoom"));
        zoom->setGeometry(QRect(810, 650, 181, 22));
        zoom->setSliderPosition(49);
        zoom->setOrientation(Qt::Horizontal);
        label_gama = new QLabel(centralwidget);
        label_gama->setObjectName(QStringLiteral("label_gama"));
        label_gama->setGeometry(QRect(800, 100, 47, 13));
        gamma = new QSlider(centralwidget);
        gamma->setObjectName(QStringLiteral("gamma"));
        gamma->setGeometry(QRect(810, 120, 181, 22));
        gamma->setSliderPosition(49);
        gamma->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(800, 460, 47, 13));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(800, 490, 47, 13));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(800, 430, 47, 13));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(800, 540, 47, 13));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(800, 600, 47, 13));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(800, 570, 47, 13));
        schichtenEinblenden = new QSlider(centralwidget);
        schichtenEinblenden->setObjectName(QStringLiteral("schichtenEinblenden"));
        schichtenEinblenden->setGeometry(QRect(810, 170, 181, 22));
        schichtenEinblenden->setValue(0);
        schichtenEinblenden->setSliderPosition(0);
        schichtenEinblenden->setOrientation(Qt::Horizontal);
        label_schichtenEinblenden = new QLabel(centralwidget);
        label_schichtenEinblenden->setObjectName(QStringLiteral("label_schichtenEinblenden"));
        label_schichtenEinblenden->setGeometry(QRect(800, 150, 101, 16));
        label_ambient = new QLabel(centralwidget);
        label_ambient->setObjectName(QStringLiteral("label_ambient"));
        label_ambient->setGeometry(QRect(800, 200, 47, 13));
        ambient = new QSlider(centralwidget);
        ambient->setObjectName(QStringLiteral("ambient"));
        ambient->setGeometry(QRect(810, 220, 181, 22));
        ambient->setMaximum(99);
        ambient->setValue(10);
        ambient->setSliderPosition(10);
        ambient->setOrientation(Qt::Horizontal);
        label_diffuse = new QLabel(centralwidget);
        label_diffuse->setObjectName(QStringLiteral("label_diffuse"));
        label_diffuse->setGeometry(QRect(800, 250, 47, 13));
        diffuse = new QSlider(centralwidget);
        diffuse->setObjectName(QStringLiteral("diffuse"));
        diffuse->setGeometry(QRect(810, 270, 181, 22));
        diffuse->setValue(10);
        diffuse->setSliderPosition(10);
        diffuse->setOrientation(Qt::Horizontal);
        label_specular = new QLabel(centralwidget);
        label_specular->setObjectName(QStringLiteral("label_specular"));
        label_specular->setGeometry(QRect(800, 300, 47, 13));
        specular = new QSlider(centralwidget);
        specular->setObjectName(QStringLiteral("specular"));
        specular->setGeometry(QRect(810, 320, 181, 22));
        specular->setValue(10);
        specular->setSliderPosition(10);
        specular->setOrientation(Qt::Horizontal);
        gradientModeCalc = new QComboBox(centralwidget);
        gradientModeCalc->setObjectName(QStringLiteral("gradientModeCalc"));
        gradientModeCalc->setGeometry(QRect(800, 360, 121, 22));
        gradientModeTarget = new QComboBox(centralwidget);
        gradientModeTarget->setObjectName(QStringLiteral("gradientModeTarget"));
        gradientModeTarget->setGeometry(QRect(930, 360, 61, 22));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Visualisierung 1", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open ...", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        labelTop->setText(QApplication::translate("MainWindow", "No data loaded", 0));
        renderTechnique->clear();
        renderTechnique->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "MIP", 0)
         << QApplication::translate("MainWindow", "Alpha", 0)
         << QApplication::translate("MainWindow", "Average", 0)
         << QApplication::translate("MainWindow", "MIDA", 0)
         << QApplication::translate("MainWindow", "First Hit", 0)
         << QApplication::translate("MainWindow", "Gradient", 0)
         << QApplication::translate("MainWindow", "Pass through", 0)
        );
        label_renderTechnique->setText(QApplication::translate("MainWindow", "Render Technique", 0));
        label_transforamtion->setText(QApplication::translate("MainWindow", "Transformation", 0));
        label_translation->setText(QApplication::translate("MainWindow", "Translation", 0));
        label_rotation->setText(QApplication::translate("MainWindow", "Rotate", 0));
        label_zoom->setText(QApplication::translate("MainWindow", "Zoom", 0));
        label_gama->setText(QApplication::translate("MainWindow", "gamma", 0));
        label_2->setText(QApplication::translate("MainWindow", "y", 0));
        label_3->setText(QApplication::translate("MainWindow", "z", 0));
        label_4->setText(QApplication::translate("MainWindow", "x", 0));
        label_5->setText(QApplication::translate("MainWindow", "x", 0));
        label_6->setText(QApplication::translate("MainWindow", "z", 0));
        label_7->setText(QApplication::translate("MainWindow", "y", 0));
        label_schichtenEinblenden->setText(QApplication::translate("MainWindow", "schichten Einblenden", 0));
        label_ambient->setText(QApplication::translate("MainWindow", "Ambient", 0));
        label_diffuse->setText(QApplication::translate("MainWindow", "Diffuse", 0));
        label_specular->setText(QApplication::translate("MainWindow", "Specular", 0));
        gradientModeCalc->clear();
        gradientModeCalc->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Sobel", 0)
         << QApplication::translate("MainWindow", "CentralDifference", 0)
        );
        gradientModeTarget->clear();
        gradientModeTarget->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "CPU", 0)
         << QApplication::translate("MainWindow", "GPU", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
