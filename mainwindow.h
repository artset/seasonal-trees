#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <glwidget.h>
#include <QButtonGroup>

class DataBinding;

namespace Ui {
class MainWindow;
}

enum Season {
    SUMMER, FALL, WINTER, SPRING
};

class UniformWidget; class QBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadShader(QString vert, QString frag);

signals:
    void removeUniforms();

private slots:
    void init();

    void on_sphereButton_clicked();

    void on_cubeButton_clicked();

    void on_cylinderTreeButton_clicked();

    void on_coneTreeButton_clicked();

    void on_defaultShaderButton_clicked();

    void on_animMoveButton_clicked();

    void on_animNoneButton_clicked();

    void on_animScaleButton_clicked();

    void on_animScaleMoveButton_clicked();

    void on_animRotate1Button_clicked();

    void on_animRotate2Button_clicked();

    void on_wireframeCheckbox_toggled(bool checked);

    void on_tipsButton_clicked();

    void on_shader1Button_clicked();

    void on_shader2Button_clicked();

    void on_checkBox_toggled(bool checked);

    void on_summerRadioButton_clicked();

    void on_fallRadioButton_clicked();

    void on_winterRadioButton_clicked();

    void on_springRadioButton_clicked();

    void on_treeOptionsComboBox_activated(const QString &arg1);

    void on_treeOptionsComboBox_currentIndexChanged(int index);

public slots:
    void handleUniformDeleted(UniformWidget *deleted);
    void changeUniform(const UniformVariable *uniform, const QString &newVal);
    void changeUniform(const QString &name, const QString &newVal);
    void addUniform(UniformVariable::Type type, const QString &name, bool editable = false, int size = 1);
    void addUniform(UniformVariable *uniform, bool editable = false);
    void settingsChanged();

protected:
    void closeEvent(QCloseEvent *e);
private:
    Ui::MainWindow *ui;
    GLWidget *m_glwidget;
    QString m_oldVert, m_oldFrag;
    bool m_hasError;

    QList<UniformWidget *> m_uniforms;
    QString m_initShader;

    QWidget *m_uniformContainer;
    QBoxLayout *m_uniformLayout;

    void dataBind();
    QList<DataBinding*> m_bindings;
    QList<QButtonGroup*> m_buttonGroups;

    void updateCheckboxes(enum Season season, bool checked);

    void updateSeasonParameters(int season);
};

#endif // MAINWINDOW_H
