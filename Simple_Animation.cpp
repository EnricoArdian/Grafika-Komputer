#include <GL/freeglut.h>
#include <math.h>

// Posisi dan kecepatan
float shapeX = 20.0f;
float shapeSpeed = 0.75f;

// Batas layar
float leftBorder = 0.0f;
float rightBorder = 50.0f;

// Warna segilima 1 dan 2
float shape1Color[3] = { 1.0f, 0.0f, 0.0f }; // Merah awal
float shape2Color[3] = { 0.0f, 0.0f, 1.0f }; // Biru awal

// Simpan warna awal
float shape1InitialColor[3] = { 1.0f, 0.0f, 0.0f };
float shape2InitialColor[3] = { 0.0f, 0.0f, 1.0f };

// Warna pantulan kanan
float bounceRightColors[][3] = {
    {0.0f, 1.0f, 0.0f},   // Hijau
    {1.0f, 0.5f, 0.0f},   // Oranye
    {0.5f, 0.0f, 0.5f}    // Ungu
};

int bounceCount = 0;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 50, 0, 50);
}

// Gambar segilima
void drawPentagon(float centerX, float centerY, float radius, float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; ++i) {
        float angle = 2.0f * M_PI * i / 5;
        glVertex2f(centerX + radius * cos(angle), centerY + radius * sin(angle));
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Gambar dua segilima di atas dan bawah
    drawPentagon(shapeX + 2.5f, 12.5f, 2.5f, shape1Color);
    drawPentagon(shapeX + 2.5f, 27.5f, 2.5f, shape2Color);

    glutSwapBuffers();
}

void timer(int value) {
    shapeX += shapeSpeed;

    if (shapeX >= rightBorder - 5 || shapeX <= leftBorder) {
        shapeSpeed = -shapeSpeed;

        if (shapeX >= rightBorder - 5) {
            // Ganti warna ke salah satu warna pantulan kanan
            int colorIndex = bounceCount % 3;
            for (int i = 0; i < 3; ++i) {
                shape1Color[i] = bounceRightColors[colorIndex][i];
                shape2Color[i] = bounceRightColors[colorIndex][i];
            }
            bounceCount++;
        } else {
            // Kembali ke warna awal saat mantul kiri
            for (int i = 0; i < 3; ++i) {
                shape1Color[i] = shape1InitialColor[i];
                shape2Color[i] = shape2InitialColor[i];
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("tugas_grafkom1_672022038");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
