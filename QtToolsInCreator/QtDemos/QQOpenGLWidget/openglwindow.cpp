#include "openglwindow.h"
#include <QOpenGLShaderProgram>

OpenGlWindow::OpenGlWindow(QOpenGLWindow::UpdateBehavior updateBehavior, QWindow *parent)
    :QOpenGLWindow(updateBehavior, parent)
{

}

void OpenGlWindow::DrwTrangle(bool bDrw)
{
    m_bTrangle = bDrw;
}

void OpenGlWindow::SetTrangleAngle(double angle)
{
    m_dAngle = angle;
}

void OpenGlWindow::AutoRatate()
{
    m_dAngle++;
    this->update();
    if(m_dAngle % 360 == 0)
    {
      //  qDebug() << "QOpenGLWindow：" << m_timer.elapsed();
     //   m_timer.start();
           m_dAngle = 0;
    }
    AutoRatate();
}

void OpenGlWindow::DrwCube(bool bDrw)
{
    m_bCube = bDrw;
}

void OpenGlWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);          // 提前设置背景色，需要使用glClear
    glClearDepth(1.0);                         // 设置清除深度，1.0是最大深度([0.0,1.0])

    // 加载shader脚本(顶点和片元)
    m_program = new QOpenGLShaderProgram(this);
    // 直接通过文件加载Shader脚本，如果加载返回false则加载失败，如果提示ERROR: error(#60) Unknown char: "???"，
    // 可以使用Notepad++打开vsh/fsh文件看一下文件编码是不是utf-8，如果不是或者时utf-8 DOM就不行
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertexShader.vsh");         // 加载顶点着色器
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragmentShader.fsh");     // 加载片段着色器
    m_program->link();   // 编译链接着色器

    // 返回属性名称在此着色器程序的参数列表中的位置。如果名称不是此着色器程序的有效属性，则返回-1。
    m_posAttr = m_program->attributeLocation("qt_Vertex");
    m_colAttr = m_program->attributeLocation("qt_MultiTexCoord0");
    // 返回统一变量名称在此着色器程序的参数列表中的位置。如果名称不是此着色器程序的有效统一变量，则返回-1。
    m_matrixUniform = m_program->uniformLocation("qt_ModelViewProjectionMatrix");
}

// 需要绘制的顶点坐标（x, y），范围[-1, 1]
const GLfloat vertices[] = {
    0.0f,  0.7f,
    -0.5f, -0.5f,
    0.5f,  -0.5f
};
// 需要绘制的顶点颜色(r, g, b)，范围[0, 1]
const GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};
void OpenGlWindow::paintGL()
{
    if(m_bTrangle)
    {
        DrwTrangle();
    }
    if(m_bCube)
    {
        DrwCube();
    }
}

void OpenGlWindow::resizeGL(int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)

    update();
}

void OpenGlWindow::DrwTrangle()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 清除缓冲区并使用glClearColor的颜色设置背景, GL_COLOR_BUFFER_BIT:指示当前为颜色写入启用的缓冲区;GL_DEPTH_BUFFER_BIT：指示深度缓冲区

    const qreal retinaScale = devicePixelRatio();   // 返回窗口的物理像素与设备无关像素之间的比率。此值取决于窗口所在的屏幕，并可能在移动窗口时更改。
    glViewport(0, 0, GLsizei(this->width() * retinaScale), GLsizei(this->height() * retinaScale));  // 设置视图大小
    m_program->bind();                              // 将此着色器程序绑定到活动的QOpenGLContext，并使其成为当前着色器程序

    // 表示3D空间中的4x4变换矩阵
    QMatrix4x4 matrix;
    matrix.perspective(40.0f,                               // 透视投影, verticalAngle: 垂直角度(也就是裁剪窗口的高度),值越大,那么物体越小
                       this->width() / this->height(),      // 纵横比(由视口的宽除以高所得)
                       0.1f,                                // 设置近平面的距离(一般设置为0.1)
                       100.0f);                             // 设置远平面的距离(一般设置为100)
    matrix.translate(0, 0, -2);       // 坐标沿Z轴偏移
    matrix.rotate(m_dAngle, 0, 1, 0);    // 绕着Y轴旋转

    m_program->setUniformValue(m_matrixUniform, matrix);   // 将当前上下文中位置处的统一变量设置为value。

    // 设置顶点坐标
    glVertexAttribPointer(GLuint(m_posAttr),    // 指定属性的索引
                          2,                    // 指定每个通用顶点属性的组件数。必须是 1、2、3、4
                          GL_FLOAT,             // 指定数组中的数据类型
                          GL_FALSE,             // 指定在访问定点数据值时是否应归一化(GL_TRUE)
                          0,                    // 指定连续通用顶点属性之间的字节偏移量。如果 stride 为 0，则通用顶点属性被理解为紧密封装在数组中。初始值为0
                          vertices);            // 顶点数组指针
    // 设置顶点颜色
    glVertexAttribPointer(GLuint(m_colAttr), 3, GL_FLOAT, GL_FALSE, 0, colors);

    // 启用顶点数组
    glEnableVertexAttribArray(GLuint(m_posAttr));    // 属性索引是从调用glGetAttribLocation接收的，或者传递给glBindAttribLocation，在Qt里就是通过attributeLocation()获取的索引
    glEnableVertexAttribArray(GLuint(m_colAttr));

    // 提供绘制功能，从数组数据中提取数据渲染基本图元
    glDrawArrays(GL_TRIANGLES,     // 图元类型
                 0,                // 从数组中哪一位开始
                 3);               // 数组中顶点的数量

    // 禁用顶点属性数组
    glDisableVertexAttribArray(GLuint(m_posAttr));
    glDisableVertexAttribArray(GLuint(m_colAttr));

    m_program->release();         // 从当前QOpenGLContext中释放活动着色器程序。
}

void OpenGlWindow::DrwCube()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 清除缓冲区并使用glClearColor的颜色设置背景, GL_COLOR_BUFFER_BIT:指示当前为颜色写入启用的缓冲区;GL_DEPTH_BUFFER_BIT：指示深度缓冲区

    const qreal retinaScale = devicePixelRatio();   // 返回窗口的物理像素与设备无关像素之间的比率。此值取决于窗口所在的屏幕，并可能在移动窗口时更改。
    glViewport(0, 0, GLsizei(this->width() * retinaScale), GLsizei(this->height() * retinaScale));  // 设置视图大小
    m_program->bind();                              // 将此着色器程序绑定到活动的QOpenGLContext，并使其成为当前着色器程序

    // 表示3D空间中的4x4变换矩阵
    QMatrix4x4 matrix;
    matrix.perspective(40.0f,                               // 透视投影, verticalAngle: 垂直角度(也就是裁剪窗口的高度),值越大,那么物体越小
                       this->width() / this->height(),      // 纵横比(由视口的宽除以高所得)
                       0.1f,                                // 设置近平面的距离(一般设置为0.1)
                       100.0f);                             // 设置远平面的距离(一般设置为100)
    matrix.translate(0, 0, -2);       // 坐标沿Z轴偏移
    matrix.rotate(m_dAngle, 0, 1, 0);    // 绕着Y轴旋转

    m_program->setUniformValue(m_matrixUniform, matrix);   // 将当前上下文中位置处的统一变量设置为value。

    // 设置顶点坐标
    glVertexAttribPointer(GLuint(m_posAttr),    // 指定属性的索引
                          2,                    // 指定每个通用顶点属性的组件数。必须是 1、2、3、4
                          GL_FLOAT,             // 指定数组中的数据类型
                          GL_FALSE,             // 指定在访问定点数据值时是否应归一化(GL_TRUE)
                          0,                    // 指定连续通用顶点属性之间的字节偏移量。如果 stride 为 0，则通用顶点属性被理解为紧密封装在数组中。初始值为0
                          vertices);            // 顶点数组指针
    // 设置顶点颜色
    glVertexAttribPointer(GLuint(m_colAttr), 3, GL_FLOAT, GL_FALSE, 0, colors);

    // 启用顶点数组
    glEnableVertexAttribArray(GLuint(m_posAttr));    // 属性索引是从调用glGetAttribLocation接收的，或者传递给glBindAttribLocation，在Qt里就是通过attributeLocation()获取的索引
    glEnableVertexAttribArray(GLuint(m_colAttr));

    // 提供绘制功能，从数组数据中提取数据渲染基本图元
    glDrawArrays(GL_TRIANGLES,     // 图元类型
                 0,                // 从数组中哪一位开始
                 3);               // 数组中顶点的数量

    // 禁用顶点属性数组
    glDisableVertexAttribArray(GLuint(m_posAttr));
    glDisableVertexAttribArray(GLuint(m_colAttr));

    m_program->release();         // 从当前QOpenGLContext中释放活动着色器程序。
}
