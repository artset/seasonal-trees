#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "shapes/openglshape.h"
#include "camera/camera.h"
#include "uniforms/uniformvariable.h"
#include <QTimer>
#include "shapes/Shape.h"
#include "shapes/Cylinder.h"
#include "tree/Tree.h"
#include "Settings.h"

class Cube;

class QGLShaderProgram;

#define colorToArgs(floatArray) floatArray[0], floatArray[1], floatArray[2], floatArray[3]

enum RenderType { SHAPE_SPHERE, SHAPE_CUBE, SHAPE_CYLINDER, SHAPE_CONE, SHAPE_ISLAND, SHAPE_LEAF};

enum AnimType { ANIM_NONE, ANIM_MOVE, ANIM_SCALE, ANIM_MOVE_AND_SCALE, ANIM_ROTATE, ANIM_ROTATE_2};

enum WireframeType { WIREFRAME_NORMAL, WIREFRAME_VERT };

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QGLFormat format, QWidget *parent = 0);
    virtual ~GLWidget();

    bool saveUniforms(QString path);
    bool loadUniforms(QString path);

    static UniformVariable* s_skybox;
    static UniformVariable* s_model;
    static UniformVariable* s_view;
    static UniformVariable* s_projection;
    static UniformVariable* s_mvp;
    static UniformVariable* s_time;
    static UniformVariable* s_size;
    static UniformVariable* s_mouse;

    static std::vector<UniformVariable*> *s_staticVars;

signals:
    void addUniform(UniformVariable::Type type, const QString &name, bool editable = true, int size = 1);
    void addUniform(UniformVariable *uniform, bool editable = true);
    void changeUniform(const UniformVariable *uniform, const QString &newVal);
    void changeUniform(const QString &name, const QString &newVal);


public slots:
    void changeRenderMode(RenderType mode);
    void changeAnimMode(AnimType mode);
    void toggleDrawWireframe(bool draw);
    void setWireframeMode(WireframeType mode);
    bool loadShader(QString vert, QString frag, QString *errors = 0);
    void uniformDeleted(const UniformVariable *uniform);
    void uniformAdded(const UniformVariable *uniform);
    void viewChanged(const glm::mat4 &modelview);
    void projectionChanged(const glm::mat4 &projection);
    void modelviewProjectionChanged(const glm::mat4 &modelviewProjection);
    void modelChanged(const glm::mat4 &modelview);
    void setPaused(bool paused);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void buildTree();
    void bindAndUpdateShader(QGLShaderProgram *shader);
    void releaseShader(QGLShaderProgram *shader);

    void renderWireframe();
    void renderBranches();
    void renderLeaves();
    void renderSkybox();
    void renderIsland();
    void renderSingleLeaf();
    void renderPhongLighting();
    bool hasSettingsChanged();

private:
    std::unique_ptr<OpenGLShape> m_leaf;
    std::unique_ptr<OpenGLShape> m_sphere;
    std::unique_ptr<OpenGLShape> m_cylinder;
    std::unique_ptr<OpenGLShape> m_cube;
    std::unique_ptr<OpenGLShape> m_cone;
    std::unique_ptr<OpenGLShape> m_roundedCylinder;
    std::unique_ptr<OpenGLShape> m_island;


    OpenGLShape *m_shape;
    Camera *camera;
    std::unique_ptr<OpenGLShape> skybox_cube;
    QGLShaderProgram *skybox_shader;
    QGLShaderProgram *wireframe_shader;
    QGLShaderProgram *wireframe_shader2;
    QGLShaderProgram *current_shader;
    QGLShaderProgram *phong_shader;
    QGLShaderProgram *default_shader;

    QGLShaderProgram *leaf_shader;
    QGLShaderProgram *island_shader;


    QList<const UniformVariable*> *activeUniforms;
    QList<const UniformVariable*> permUniforms;

    QOpenGLFunctions gl;

    QTimer *timer;

    glm::mat4 model;

    AnimType animMode;
    glm::vec3 pos, dir;
    float scale, dscale;
    float angle, dangle;

    bool drawWireframe;
    WireframeType wireframeMode;

    void handleAnimation();

    RenderType m_renderMode;

    bool mouseDown;
    std::unique_ptr<Tree> m_tree;// Tree with L System
    Settings m_settings;  // Local version of settings to keep track of changes.

};

#endif // GLWIDGET_H
