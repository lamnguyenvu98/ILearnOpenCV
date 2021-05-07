#include <iostream>
#include <opencv2/opencv.hpp>
#include <GL/gl.h>

using namespace std;
using namespace cv;

Mat frame;
GLfloat angle = 0.0;
GLuint texture;
VideoCapture camera;

int loadTexture()
{
    if (frame.data == NULL) return -1;
    glBindTexture(GL_TEXTURE_2D, texture); // bind the texture to it's array
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, frame.data);
    return 0;
}

void on_opengl(void* param)
{
    glLoadIdentity();
    // load texture
    glBindTexture(GL_TEXTURE_2D, texture);
    // Rotate plane
    glRotatef(angle, 1.0f, 1.0f, 1.0f);
    // create the plate
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(-1.0, -1.0);
    glTexCoord2d(1.0,0.0); glVertex2d(+1.0, -1.0);
    glTexCoord2d(1.0,1.0); glVertex2d(+1.0, +1.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-1.0, +1.0);
    glEnd();
}

int main()
{
    // Open webcam
    camera.open(0);
    if (!camera.isOpened())
    {
        cout << "Failed to read webcam...\n";
        return -1;
    }
    namedWindow("webcam", WINDOW_OPENGL);

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);

    setOpenGlDrawCallback("webcam", on_opengl);
    while(waitKey(1) != 'q')
    {
        camera >> frame;
        loadTexture();
        updateWindow("webcam");
        angle += 4;
    }
    destroyAllWindows();
    return 0;
}