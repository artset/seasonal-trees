/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *defaultShaderButton;
    QPushButton *shader1Button;
    QPushButton *shader2Button;
    QFrame *line;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QPushButton *sphereButton;
    QPushButton *cubeButton;
    QPushButton *cylinderTreeButton;
    QPushButton *coneTreeButton;
    QFrame *line_2;
    QGridLayout *sliderGrid;
    QSlider *recursionsSlider;
    QSlider *angleSlider;
    QLineEdit *recursionsTextbox;
    QSlider *leafSizeSlider;
    QLineEdit *angleTextbox;
    QLabel *leafSizeLabel;
    QLabel *angleLabel;
    QLabel *recursionsLabel;
    QLineEdit *leafSizeTextbox;
    QLabel *seasonLabel;
    QRadioButton *summerRadioButton;
    QRadioButton *fallRadioButton;
    QRadioButton *winterRadioButton;
    QRadioButton *springRadioButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QPushButton *animNoneButton;
    QPushButton *animMoveButton;
    QPushButton *animScaleButton;
    QPushButton *animScaleMoveButton;
    QPushButton *animRotate1Button;
    QPushButton *animRotate2Button;
    QFrame *line_3;
    QLabel *label_4;
    QFrame *line_4;
    QLabel *label_5;
    QCheckBox *wireframeCheckbox;
    QCheckBox *checkBox;
    QFrame *line_5;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QPushButton *tipsButton;
    QVBoxLayout *uniformContainerUI;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1100, 700);
        MainWindow->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 2, -1, 2);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        defaultShaderButton = new QPushButton(centralWidget);
        defaultShaderButton->setObjectName(QString::fromUtf8("defaultShaderButton"));

        verticalLayout->addWidget(defaultShaderButton);

        shader1Button = new QPushButton(centralWidget);
        shader1Button->setObjectName(QString::fromUtf8("shader1Button"));

        verticalLayout->addWidget(shader1Button);

        shader2Button = new QPushButton(centralWidget);
        shader2Button->setObjectName(QString::fromUtf8("shader2Button"));

        verticalLayout->addWidget(shader2Button);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));

        verticalLayout->addLayout(verticalLayout_4);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        sphereButton = new QPushButton(centralWidget);
        sphereButton->setObjectName(QString::fromUtf8("sphereButton"));

        verticalLayout->addWidget(sphereButton);

        cubeButton = new QPushButton(centralWidget);
        cubeButton->setObjectName(QString::fromUtf8("cubeButton"));

        verticalLayout->addWidget(cubeButton);

        cylinderTreeButton = new QPushButton(centralWidget);
        cylinderTreeButton->setObjectName(QString::fromUtf8("cylinderTreeButton"));

        verticalLayout->addWidget(cylinderTreeButton);

        coneTreeButton = new QPushButton(centralWidget);
        coneTreeButton->setObjectName(QString::fromUtf8("coneTreeButton"));

        verticalLayout->addWidget(coneTreeButton);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        sliderGrid = new QGridLayout();
        sliderGrid->setSpacing(6);
        sliderGrid->setObjectName(QString::fromUtf8("sliderGrid"));
        sliderGrid->setSizeConstraint(QLayout::SetMinAndMaxSize);
        sliderGrid->setHorizontalSpacing(6);
        sliderGrid->setContentsMargins(-1, 5, -1, 5);
        recursionsSlider = new QSlider(centralWidget);
        recursionsSlider->setObjectName(QString::fromUtf8("recursionsSlider"));
        recursionsSlider->setMinimum(1);
        recursionsSlider->setMaximum(10);
        recursionsSlider->setOrientation(Qt::Horizontal);

        sliderGrid->addWidget(recursionsSlider, 1, 0, 1, 1);

        angleSlider = new QSlider(centralWidget);
        angleSlider->setObjectName(QString::fromUtf8("angleSlider"));
        angleSlider->setMinimum(10);
        angleSlider->setMaximum(90);
        angleSlider->setOrientation(Qt::Horizontal);

        sliderGrid->addWidget(angleSlider, 3, 0, 1, 1);

        recursionsTextbox = new QLineEdit(centralWidget);
        recursionsTextbox->setObjectName(QString::fromUtf8("recursionsTextbox"));
        recursionsTextbox->setMaxLength(100);

        sliderGrid->addWidget(recursionsTextbox, 1, 1, 1, 1);

        leafSizeSlider = new QSlider(centralWidget);
        leafSizeSlider->setObjectName(QString::fromUtf8("leafSizeSlider"));
        leafSizeSlider->setMaximum(5);
        leafSizeSlider->setOrientation(Qt::Horizontal);

        sliderGrid->addWidget(leafSizeSlider, 5, 0, 1, 1);

        angleTextbox = new QLineEdit(centralWidget);
        angleTextbox->setObjectName(QString::fromUtf8("angleTextbox"));

        sliderGrid->addWidget(angleTextbox, 3, 1, 1, 1);

        leafSizeLabel = new QLabel(centralWidget);
        leafSizeLabel->setObjectName(QString::fromUtf8("leafSizeLabel"));

        sliderGrid->addWidget(leafSizeLabel, 4, 0, 1, 1);

        angleLabel = new QLabel(centralWidget);
        angleLabel->setObjectName(QString::fromUtf8("angleLabel"));

        sliderGrid->addWidget(angleLabel, 2, 0, 1, 1);

        recursionsLabel = new QLabel(centralWidget);
        recursionsLabel->setObjectName(QString::fromUtf8("recursionsLabel"));

        sliderGrid->addWidget(recursionsLabel, 0, 0, 1, 1);

        leafSizeTextbox = new QLineEdit(centralWidget);
        leafSizeTextbox->setObjectName(QString::fromUtf8("leafSizeTextbox"));

        sliderGrid->addWidget(leafSizeTextbox, 5, 1, 1, 1);

        sliderGrid->setColumnStretch(0, 3);
        sliderGrid->setColumnStretch(1, 1);
        sliderGrid->setColumnMinimumWidth(0, 2);

        verticalLayout->addLayout(sliderGrid);

        seasonLabel = new QLabel(centralWidget);
        seasonLabel->setObjectName(QString::fromUtf8("seasonLabel"));

        verticalLayout->addWidget(seasonLabel);

        summerRadioButton = new QRadioButton(centralWidget);
        summerRadioButton->setObjectName(QString::fromUtf8("summerRadioButton"));

        verticalLayout->addWidget(summerRadioButton);

        fallRadioButton = new QRadioButton(centralWidget);
        fallRadioButton->setObjectName(QString::fromUtf8("fallRadioButton"));

        verticalLayout->addWidget(fallRadioButton);

        winterRadioButton = new QRadioButton(centralWidget);
        winterRadioButton->setObjectName(QString::fromUtf8("winterRadioButton"));

        verticalLayout->addWidget(winterRadioButton);

        springRadioButton = new QRadioButton(centralWidget);
        springRadioButton->setObjectName(QString::fromUtf8("springRadioButton"));

        verticalLayout->addWidget(springRadioButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        animNoneButton = new QPushButton(centralWidget);
        animNoneButton->setObjectName(QString::fromUtf8("animNoneButton"));

        verticalLayout->addWidget(animNoneButton);

        animMoveButton = new QPushButton(centralWidget);
        animMoveButton->setObjectName(QString::fromUtf8("animMoveButton"));

        verticalLayout->addWidget(animMoveButton);

        animScaleButton = new QPushButton(centralWidget);
        animScaleButton->setObjectName(QString::fromUtf8("animScaleButton"));

        verticalLayout->addWidget(animScaleButton);

        animScaleMoveButton = new QPushButton(centralWidget);
        animScaleMoveButton->setObjectName(QString::fromUtf8("animScaleMoveButton"));

        verticalLayout->addWidget(animScaleMoveButton);

        animRotate1Button = new QPushButton(centralWidget);
        animRotate1Button->setObjectName(QString::fromUtf8("animRotate1Button"));

        verticalLayout->addWidget(animRotate1Button);

        animRotate2Button = new QPushButton(centralWidget);
        animRotate2Button->setObjectName(QString::fromUtf8("animRotate2Button"));

        verticalLayout->addWidget(animRotate2Button);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        wireframeCheckbox = new QCheckBox(centralWidget);
        wireframeCheckbox->setObjectName(QString::fromUtf8("wireframeCheckbox"));
        wireframeCheckbox->setFocusPolicy(Qt::StrongFocus);
        wireframeCheckbox->setChecked(true);
        wireframeCheckbox->setTristate(false);

        verticalLayout->addWidget(wireframeCheckbox);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(200, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tipsButton = new QPushButton(centralWidget);
        tipsButton->setObjectName(QString::fromUtf8("tipsButton"));

        verticalLayout_3->addWidget(tipsButton);

        uniformContainerUI = new QVBoxLayout();
        uniformContainerUI->setSpacing(6);
        uniformContainerUI->setObjectName(QString::fromUtf8("uniformContainerUI"));

        verticalLayout_3->addLayout(uniformContainerUI);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Shader Visualizer", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Shaders:", nullptr));
        defaultShaderButton->setText(QCoreApplication::translate("MainWindow", "Default", nullptr));
        shader1Button->setText(QCoreApplication::translate("MainWindow", "Metal", nullptr));
        shader2Button->setText(QCoreApplication::translate("MainWindow", "Glass", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Shapes:", nullptr));
        sphereButton->setText(QCoreApplication::translate("MainWindow", "Sphere", nullptr));
        cubeButton->setText(QCoreApplication::translate("MainWindow", "Cube", nullptr));
        cylinderTreeButton->setText(QCoreApplication::translate("MainWindow", "Cylinder", nullptr));
        coneTreeButton->setText(QCoreApplication::translate("MainWindow", "Cone", nullptr));
        leafSizeLabel->setText(QCoreApplication::translate("MainWindow", "Leaf Size:", nullptr));
        angleLabel->setText(QCoreApplication::translate("MainWindow", "Angle (degrees)", nullptr));
        recursionsLabel->setText(QCoreApplication::translate("MainWindow", "Number of recursions:", nullptr));
        seasonLabel->setText(QCoreApplication::translate("MainWindow", "Season:", nullptr));
        summerRadioButton->setText(QCoreApplication::translate("MainWindow", "Summer", nullptr));
        fallRadioButton->setText(QCoreApplication::translate("MainWindow", "Fall", nullptr));
        winterRadioButton->setText(QCoreApplication::translate("MainWindow", "Winter", nullptr));
        springRadioButton->setText(QCoreApplication::translate("MainWindow", "Spring", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Animations:", nullptr));
        animNoneButton->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        animMoveButton->setText(QCoreApplication::translate("MainWindow", "Move", nullptr));
        animScaleButton->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        animScaleMoveButton->setText(QCoreApplication::translate("MainWindow", "Move + Scale", nullptr));
        animRotate1Button->setText(QCoreApplication::translate("MainWindow", "Rotate1", nullptr));
        animRotate2Button->setText(QCoreApplication::translate("MainWindow", "Rotate2", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Options:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Wireframe:", nullptr));
        wireframeCheckbox->setText(QCoreApplication::translate("MainWindow", "Enabled", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Use Vertex Shader", nullptr));
        tipsButton->setText(QCoreApplication::translate("MainWindow", "Tips", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
