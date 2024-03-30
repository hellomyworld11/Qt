#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>


class OpenglWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
public:
    explicit OpenglWidget(QWidget *parent = nullptr);
    ~OpenglWidget();

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    void initShaderByQt();
    void initShaderByQpengl();

private:
    unsigned int VBO;   //顶点缓冲对象
    unsigned int VAO;   //顶点数组对象
    unsigned int EBO;   //元素缓冲对象
    GLuint shaderProgram;  //着色器程序

    QOpenGLShaderProgram shaderPro;
};

#endif // OPENGLWIDGET_H
