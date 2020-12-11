#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uniforms/uniformwidget.h"

#include <QMessageBox>
#include <QSettings>
#include "Databinding.h"
#include "Settings.h"

#include <iostream>
#include <QFileInfo>
#include <lib/common.h>

#ifndef Q_OS_LINUX
#include <QDesktopServices>
#include <QUrl>
#endif
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QGLFormat qglFormat;
    qglFormat.setVersion(4,0);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    ui->setupUi(this);
    m_glwidget = new GLWidget(qglFormat, this);
    m_glwidget->setMinimumSize(100,100);
    ui->verticalLayout_2->addWidget(m_glwidget);
    m_oldVert = QString("");
    m_oldFrag = QString("");

    dataBind();

    // Restore the UI settings
    QSettings qtSettings("CS123", "Lab10");
    restoreGeometry(qtSettings.value("geometry").toByteArray());
    restoreState(qtSettings.value("windowState").toByteArray());

    QObject::connect(m_glwidget, SIGNAL(addUniform(UniformVariable::Type,QString,bool,int)), this, SLOT(addUniform(UniformVariable::Type,QString,bool,int)));
    QObject::connect(m_glwidget, SIGNAL(addUniform(UniformVariable*,bool)), this, SLOT(addUniform(UniformVariable*,bool)));
    QObject::connect(m_glwidget, SIGNAL(changeUniform(const UniformVariable*,QString)), this, SLOT(changeUniform(const UniformVariable*,QString)));
    QObject::connect(m_glwidget, SIGNAL(changeUniform(QString,QString)), this, SLOT(changeUniform(QString,QString)));

    this->m_initShader = m_initShader;

    QTimer::singleShot(0, this, SLOT(init()));
    m_hasError = false;

#ifdef SHADER_1
    ui->editShaderButton->hide();
    ui->defaultShaderButton->hide();
    ui->loadShaderButton->hide();
    ui->refreshShaderButton->hide();
#endif

#ifdef SHADER_1
    ui->shader1Button->setText(SHADER_1);
    ui->shader1Button->show();
#endif
#ifdef SHADER_2
    ui->shader2Button->setText(SHADER_2);
    ui->shader2Button->show();
#endif
}

MainWindow::~MainWindow()
{
    foreach (DataBinding *b, m_bindings)
        delete b;
    foreach (QButtonGroup *bg, m_buttonGroups)
        delete bg;
    foreach (UniformWidget * u, m_uniforms) {
        delete u;
    }
    m_uniforms.clear();

    delete ui;
    delete m_glwidget;
}

void MainWindow::on_sphereButton_clicked() {
    m_glwidget->changeRenderMode(SHAPE_SPHERE);
}


void MainWindow::on_treeButton_clicked() {
    m_glwidget->changeRenderMode(SHAPE_TREE);
}

void MainWindow::loadShader(QString vert, QString frag) {
    QString error;
    if (m_oldFrag != "" && !m_hasError)
        m_glwidget->saveUniforms(m_oldFrag);

    emit removeUniforms();

    if (!m_glwidget->loadShader(vert, frag, &error)) {
        std::cout << error.toStdString() << std::endl;
        QMessageBox::warning(this, tr("Failed to Load Shader"), "Error:\n" + error);
        m_oldFrag = frag;
        m_oldVert = vert;
        m_hasError = true;
    } else {
        m_oldFrag = frag;
        m_oldVert = vert;

        m_glwidget->loadUniforms(frag);
        m_hasError = false;
    }
}

void MainWindow::init()
{
#ifdef SHADER_1
    loadShader(SHADER_1_VERT, SHADER_1_FRAG);
    changeRenderType(SHAPE_SPHERE);
    return;
#endif
    if (!qstrcmp(m_initShader, "")) {
        QFileInfo info = QFileInfo(m_initShader);
        loadShader(info.absolutePath() + "/" + info.baseName() + ".vert",
                   info.absolutePath() + "/" + info.baseName() + ".frag");
    } else {
        loadShader(":/shaders/light.vert", ":/shaders/light.frag");
    }

    ui->treeOptionsComboBox->addItem("Binary Tree");
    ui->treeOptionsComboBox->addItem("Arrow Weed");
    ui->treeOptionsComboBox->addItem("Fuzzy Weed");
    ui->treeOptionsComboBox->addItem("Wavy Seaweed");
    ui->treeOptionsComboBox->addItem("Twiggy Weed");
    ui->treeOptionsComboBox->addItem("Stochastic Fuzzy Weed");
}

void MainWindow::handleUniformDeleted(UniformWidget *deleted)
{
    m_glwidget->uniformDeleted(deleted->getUniform());
    m_uniforms.removeAll(deleted);
}

void MainWindow::changeUniform(const UniformVariable *uniform, const QString &newVal)
{
    foreach (UniformWidget *w, m_uniforms) {
        if (w->getUniform() == uniform) {
            w->updateUniform(newVal);
        }
    }
}

void MainWindow::changeUniform(const QString &name, const QString &newVal)
{
    foreach (UniformWidget *w, m_uniforms) {
        if (!w->getUniform()->getName().compare(name)) {
            w->updateUniform(newVal);
        }
    }
}

void MainWindow::addUniform(UniformVariable::Type type, const QString &name, bool editable, int size)
{
    UniformWidget *newWidget = new UniformWidget(m_glwidget->context()->contextHandle(), m_glwidget, type, name, editable, size);
    QObject::connect(newWidget, SIGNAL(deleted(UniformWidget*)), this, SLOT(handleUniformDeleted(UniformWidget*)));
    QObject::connect(this, SIGNAL(removeUniforms()), newWidget, SLOT(deleteUniform()));
    m_glwidget->uniformAdded(newWidget->getUniform());
    m_uniforms.append(newWidget);

}

void MainWindow::addUniform(UniformVariable *uniform, bool editable)
{
    UniformWidget *newWidget = new UniformWidget(uniform, m_glwidget, editable);
    QObject::connect(newWidget, SIGNAL(deleted(UniformWidget*)), this, SLOT(handleUniformDeleted(UniformWidget*)));
    QObject::connect(this, SIGNAL(removeUniforms()), newWidget, SLOT(deleteUniform()));
    QObject::connect(newWidget, SIGNAL(changed(const UniformVariable*)), m_glwidget, SLOT(uniformChanged(const UniformVariable*)));
    m_glwidget->uniformAdded(newWidget->getUniform());
    m_uniforms.append(newWidget);
}

void MainWindow::closeEvent(QCloseEvent *e) {
    (void)e;
    m_glwidget->saveUniforms(m_oldFrag);
}

void MainWindow::on_defaultShaderButton_clicked()
{
    loadShader(":/shaders/light.vert", ":/shaders/light.frag");
}


QString tipsText = "<h2>Attributes</h2>\n"
        "The following attributes (<b>in</b> variables) are available for use:\n"
        "<ul><li><b>vec3 position</b>: The position of the vertex in object space</li>"
        "<li><b>vec3 normal</b>: The normal of the vertex in object space</li>"
        "<li><b>vec2 texCoord</b>: The 2D texture coordinate of the vertex</li></ul>"
        "<h2>Uniforms</h2>\n"
        "There are built in uniform values that can be sent as the value "
        "to an existing uniform by using the following string values:\n"
        "<ul><li><b>float</b> values:"
        "<ul><li><b>&lt;time&gt;</b>: The elapsed time since the shader was loaded, in seconds</li></ul>"
        "</li><li><b>mat4</b> values:"
        "<ul><li><b>&lt;model&gt;</b>: The model matrix of the rendered object</li>"
        "<li><b>&lt;view&gt;</b>: The view matrix of the camera</li>"
        "<li><b>&lt;projection&gt;</b>: The projection matrix of the camera</li>"
        "<li><b>&lt;mvp&gt;</b>: The combined model, view, and projection matrices</li></ul>"
        "</li><li><b>samplerCube</b> values:"
        "<ul><li><b>&lt;skybox&gt;</b>: The skybox of the scene as a cubemap</li></ul>"
        "</li><li><b>vec2</b> values:"
        "<ul><li><b>&lt;size&gt;</b>: The size of the viewport</li></ul>"
        "</li><li><b>vec3</b> values:"
        "<ul><li><b>&lt;mouse&gt;</b>: The location of the mouse (0,0 is upper left). z=1 if mouse is pressed, 0 if not.</li></ul>"
        "</li></ul>"
        "<p>Any questions or bugs can be emailed to the cs123 tas (cs123tas@cs.brown.edu).</p>";

void MainWindow::on_shader2Button_clicked()
{
    loadShader(":/shaders/glass.vert", ":/shaders/glass.frag");
}

void MainWindow::on_summerRadioButton_clicked(){
    settings.season = 0;
    updateSeasonParameters(settings.season);
}

void MainWindow::on_fallRadioButton_clicked(){
    settings.season = 1;
    updateSeasonParameters(settings.season);
}

void MainWindow::on_winterRadioButton_clicked(){
    settings.season = 2;
    updateSeasonParameters(settings.season);
}

void MainWindow::on_springRadioButton_clicked(){
    settings.season = 3;
    updateSeasonParameters(settings.season);
}

void MainWindow::on_bumpMapCheckbox_clicked()
{
   settings.ifBumpMap = !settings.ifBumpMap;
}

void MainWindow::updateSeasonParameters(int season){
    switch (season){
        //Summer
        case 0:
            settings.leafSize = 0.8f;
            //Update slider
            ui->leafSizeTextbox->setText("2.5");
            break;
        //Fall
        case 1:
            settings.leafSize = 0.8f;
            ui->leafSizeTextbox->setText("0.8");
            //Different colored leaves
            break;
        //Winter
        case 2:
            //Get rid of leaves
            settings.leafSize = 0.f;
            ui->leafSizeTextbox->setText("0");
            break;
        //Spring
        case 3:
            //Smaller leaves
            settings.leafSize = 0.5f;
            ui->leafSizeTextbox->setText("0.5");
            break;
    }
}

void MainWindow::dataBind(){
#define BIND(b) { \
    DataBinding *_b = (b); \
    m_bindings.push_back(_b); \
    assert(connect(_b, SIGNAL(dataChanged()), this, SLOT(settingsChanged()))); \
}
    QButtonGroup *seasonButtonGroup = new QButtonGroup;
    m_buttonGroups.push_back(seasonButtonGroup);

    BIND(IntBinding::bindSliderAndTextbox(
        ui->recursionsSlider, ui->recursionsTextbox, settings.recursions, 0, 10));
    BIND(FloatBinding::bindSliderAndTextbox(
        ui->angleSlider, ui->angleTextbox, settings.angle, 10, 90));

    BIND(FloatBinding::bindSliderAndTextbox(
        ui->leafSizeSlider, ui->leafSizeTextbox, settings.leafSize, 0, 7));

    BIND(ChoiceBinding::bindRadioButtons(seasonButtonGroup, 4, settings.season, ui->summerRadioButton, ui->fallRadioButton, ui->winterRadioButton, ui->springRadioButton));
}

void MainWindow::settingsChanged(){

}

void MainWindow::on_treeOptionsComboBox_activated(const QString &arg1)
{

}

void MainWindow::on_treeOptionsComboBox_currentIndexChanged(int index)
{
    settings.treeOption = index;
}
