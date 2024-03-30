#include "openglwidget.h"
#include <QOpenGLShader>

GLfloat vertexs[] = {
    -0.5,-0.5,0,
    0.5, -0.5,0,
    0,0.5,0
};

GLfloat rectangle[] = {
    //first
    0.5,0.5,0,
    0.5,-0.5,0,
    -0.5,0.5,0,
    //second
    -0.5,-0.5,0,
};

unsigned int indices[] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 2, // 第一个三角形
    1, 2, 3  // 第二个三角形
};



OpenglWidget::OpenglWidget(QWidget *parent):
    QOpenGLWidget(parent)
{

}

OpenglWidget::~OpenglWidget()
{
    makeCurrent();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    doneCurrent();
}


void OpenglWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //创建 VBO 和 VAO 赋予ID
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    //绑定
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
    //解释缓冲区里的数据格式 属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    //开启第一个属性值
    glEnableVertexAttribArray(0);

    //编译着色器
    initShaderByQt();

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //VAOh会记录EBO 绑定、解绑状态。
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //绑定默认的， 防止改动VAO和VBO
    //需要用VAO的时候绑定再使用。就可以不用重复设置顶点和属性  --状态机原理
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenglWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(shaderProgram);
    shaderPro.bind();
    glBindVertexArray(VAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenglWidget::resizeGL(int w, int h)
{
     Q_UNUSED(w);
     Q_UNUSED(h)
}

void OpenglWidget::initShaderByQt()
{
    shaderPro.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                      ":/Shaders/shaders/demo.vert");
    shaderPro.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                      ":/Shaders/shaders/demo.frag");
    shaderPro.link();
}

void OpenglWidget::initShaderByQpengl()
{
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "	gl_PointSize = 20.0f;\n"
        "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertex_shader);
    glCompileShader(frag_shader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, frag_shader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);
}
