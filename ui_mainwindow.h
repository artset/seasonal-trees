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
#include <QtWidgets/QComboBox>
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
    QPushButton *shader2Button;
    QFrame *line;
    QLabel *label_2;
    QPushButton *sphereButton;
    QPushButton *treeButton;
    QSpacerItem *horizontalSpacer_4;
    QLabel *treeOptionsLabel;
    QComboBox *treeOptionsComboBox;
    QSpacerItem *horizontalSpacer_5;
    QGridLayout *sliderGrid;
    QLabel *recursionsLabel;
    QLineEdit *angleTextbox;
    QLineEdit *leafSizeTextbox;
    QSlider *recursionsSlider;
    QSlider *angleSlider;
    QLabel *leafSizeLabel;
    QLabel *angleLabel;
    QLineEdit *recursionsTextbox;
    QSlider *leafSizeSlider;
    QLabel *seasonLabel;
    QRadioButton *summerRadioButton;
    QRadioButton *fallRadioButton;
    QRadioButton *winterRadioButton;
    QRadioButton *springRadioButton;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *bumpMapCheckbox;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(978, 849);
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
        verticalLayout->setContentsMargins(-1, 0, -1, 0);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        defaultShaderButton = new QPushButton(centralWidget);
        defaultShaderButton->setObjectName(QString::fromUtf8("defaultShaderButton"));
        defaultShaderButton->setIconSize(QSize(16, 16));
        defaultShaderButton->setAutoDefault(false);

        verticalLayout->addWidget(defaultShaderButton);

        shader2Button = new QPushButton(centralWidget);
        shader2Button->setObjectName(QString::fromUtf8("shader2Button"));

        verticalLayout->addWidget(shader2Button);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        sphereButton = new QPushButton(centralWidget);
        sphereButton->setObjectName(QString::fromUtf8("sphereButton"));

        verticalLayout->addWidget(sphereButton);

        treeButton = new QPushButton(centralWidget);
        treeButton->setObjectName(QString::fromUtf8("treeButton"));

        verticalLayout->addWidget(treeButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_4);

        treeOptionsLabel = new QLabel(centralWidget);
        treeOptionsLabel->setObjectName(QString::fromUtf8("treeOptionsLabel"));

        verticalLayout->addWidget(treeOptionsLabel);

        treeOptionsComboBox = new QComboBox(centralWidget);
        treeOptionsComboBox->setObjectName(QString::fromUtf8("treeOptionsComboBox"));

        verticalLayout->addWidget(treeOptionsComboBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_5);

        sliderGrid = new QGridLayout();
        sliderGrid->setSpacing(6);
        sliderGrid->setObjectName(QString::fromUtf8("sliderGrid"));
        sliderGrid->setSizeConstraint(QLayout::SetMinAndMaxSize);
        sliderGrid->setHorizontalSpacing(4);
        sliderGrid->setContentsMargins(-1, 5, -1, 5);
        recursionsLabel = new QLabel(centralWidget);
        recursionsLabel->setObjectName(QString::fromUtf8("recursionsLabel"));

        sliderGrid->addWidget(recursionsLabel, 0, 0, 1, 1);

        angleTextbox = new QLineEdit(centralWidget);
        angleTextbox->setObjectName(QString::fromUtf8("angleTextbox"));

        sliderGrid->addWidget(angleTextbox, 3, 1, 1, 1);

        leafSizeTextbox = new QLineEdit(centralWidget);
        leafSizeTextbox->setObjectName(QString::fromUtf8("leafSizeTextbox"));

        sliderGrid->addWidget(leafSizeTextbox, 5, 1, 1, 1);

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

        leafSizeLabel = new QLabel(centralWidget);
        leafSizeLabel->setObjectName(QString::fromUtf8("leafSizeLabel"));

        sliderGrid->addWidget(leafSizeLabel, 4, 0, 1, 1);

        angleLabel = new QLabel(centralWidget);
        angleLabel->setObjectName(QString::fromUtf8("angleLabel"));

        sliderGrid->addWidget(angleLabel, 2, 0, 1, 1);

        recursionsTextbox = new QLineEdit(centralWidget);
        recursionsTextbox->setObjectName(QString::fromUtf8("recursionsTextbox"));
        recursionsTextbox->setMaxLength(100);

        sliderGrid->addWidget(recursionsTextbox, 1, 1, 1, 1);

        leafSizeSlider = new QSlider(centralWidget);
        leafSizeSlider->setObjectName(QString::fromUtf8("leafSizeSlider"));
        leafSizeSlider->setMaximum(5);
        leafSizeSlider->setOrientation(Qt::Horizontal);

        sliderGrid->addWidget(leafSizeSlider, 5, 0, 1, 1);

        sliderGrid->setColumnStretch(0, 2);
        sliderGrid->setColumnStretch(1, 1);

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

        bumpMapCheckbox = new QCheckBox(centralWidget);
        bumpMapCheckbox->setObjectName(QString::fromUtf8("bumpMapCheckbox"));

        verticalLayout->addWidget(bumpMapCheckbox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_2->setContentsMargins(0, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(200, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        horizontalLayout->addLayout(verticalLayout_3);

        horizontalLayout->setStretch(1, 3);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        defaultShaderButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Shader Visualizer", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Shaders:", nullptr));
        defaultShaderButton->setText(QCoreApplication::translate("MainWindow", "Default", nullptr));
        shader2Button->setText(QCoreApplication::translate("MainWindow", "Load Island", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Shapes:", nullptr));
        sphereButton->setText(QCoreApplication::translate("MainWindow", "Sphere", nullptr));
        treeButton->setText(QCoreApplication::translate("MainWindow", "Tree", nullptr));
        treeOptionsLabel->setText(QCoreApplication::translate("MainWindow", "Tree Options:", nullptr));
        recursionsLabel->setText(QCoreApplication::translate("MainWindow", "Number of recursions:", nullptr));
        leafSizeLabel->setText(QCoreApplication::translate("MainWindow", "Leaf Size:", nullptr));
        angleLabel->setText(QCoreApplication::translate("MainWindow", "Angle (degrees)", nullptr));
        seasonLabel->setText(QCoreApplication::translate("MainWindow", "Season:", nullptr));
        summerRadioButton->setText(QCoreApplication::translate("MainWindow", "Summer", nullptr));
        fallRadioButton->setText(QCoreApplication::translate("MainWindow", "Fall", nullptr));
        winterRadioButton->setText(QCoreApplication::translate("MainWindow", "Winter", nullptr));
        springRadioButton->setText(QCoreApplication::translate("MainWindow", "Spring", nullptr));
        bumpMapCheckbox->setText(QCoreApplication::translate("MainWindow", "Bump Mapping", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
