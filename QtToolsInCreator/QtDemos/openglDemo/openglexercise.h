#ifndef OPENGLEXERCISE_H
#define OPENGLEXERCISE_H
#include <QOpenGLWidget>
#include <qopenglfunctions_4_5_core.h>



//opengl 练习

class OpenGLExercise : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
public:
    explicit OpenGLExercise(QWidget *parent = nullptr);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    //通用
    //着色器
    void initShaderProGram();

    //1.1 两个相连的三角形
    void init_1_1();
    void exercise_1_1();
    //1.2 两个相同的三角形，但是VAO和VBO不同
    void init_1_2();
    void exercise_1_2();

private:
    GLuint VAO1_1;
    GLuint VBO1_1;

    GLuint VAO1_2[2];
    GLuint VBO1_2[2];

    GLuint shaderProgram;

};

#endif // OPENGLEXERCISE_H
