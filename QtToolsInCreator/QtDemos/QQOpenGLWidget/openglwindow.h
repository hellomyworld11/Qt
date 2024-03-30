#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H
#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Compatibility>
#include <qelapsedtimer.h>
class QOpenGLShaderProgram;

//绘制窗口
class OpenGlWindow : public QOpenGLWindow, protected QOpenGLFunctions_4_5_Compatibility
{
public:
    explicit OpenGlWindow(UpdateBehavior updateBehavior = NoPartialUpdate,
                 QWindow *parent = nullptr);
public:
    void DrwTrangle(bool bDrw);
    void SetTrangleAngle(double angle);
    void AutoRatate();

    void DrwCube(bool bDrw);
protected:

    void initializeGL() override;

    void paintGL() override;

    void resizeGL(int w, int h) override;
private:
    void DrwTrangle();
    void DrwCube();
private:
     int m_dAngle = 0;                            //旋转的角度
     QOpenGLShaderProgram* m_program = nullptr;  // 使用QOpenGLShaderProgram链接和使用OpenGL着色器程序
     int  m_matrixUniform;
     int  m_posAttr;                             // 顶点坐标属性位置
     int  m_colAttr;                             // 顶点颜色属性位置
     bool m_bTrangle = false;
     bool m_bCube = false;
};

#endif // OPENGLWINDOW_H
