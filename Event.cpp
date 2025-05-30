#include <GL/glut.h>
#include <vector>

struct Titik {
    float posisiX, posisiY;
};

std::vector<Titik> daftarTitik;
bool modeIsi = true;
int modeWarna = 0;

void inisialisasi() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

void tampil() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& titik : daftarTitik) {

        if (modeWarna == 0)
            glColor3f(1.0, 1.0, 1.0);
        else if (modeWarna == 1)
            glColor3f(0.8, 0.0, 0.0);
        else if (modeWarna == 2)
            glColor3f(0.0, 0.4, 1.0);
        else if (modeWarna == 3)
            glColor3f(0.0, 1.0, 0.3);
        else if (modeWarna == 4)
            glColor3f(1.0, 1.0, 0.0);

        if (modeIsi) {
            glPointSize(5.0);
            glBegin(GL_POINTS);
            glVertex2f(titik.posisiX, titik.posisiY);
            glEnd();
        }

        else {
            glBegin(GL_LINE_LOOP);
            glVertex2f(titik.posisiX - 1, titik.posisiY - 1);
            glVertex2f(titik.posisiX + 1, titik.posisiY - 1);
            glVertex2f(titik.posisiX + 1, titik.posisiY + 1);
            glVertex2f(titik.posisiX - 1, titik.posisiY + 1);
            glEnd();
        }
    }

    glFlush();
}

void tekanKeyboard(unsigned char tombol, int, int) {
    switch (tombol) {
        case 'a':
        case 'A':
            modeWarna = (modeWarna + 1) % 5;
            break;
        case 's':
        case 'S':
            modeWarna = 0;
            break;
        case 'd':
        case 'D':
            modeIsi = !modeIsi;
            break;
    }
    glutPostRedisplay();
}

void klikMouse(int tombol, int status, int posisiX, int posisiY) {
    if (tombol == GLUT_LEFT_BUTTON && status == GLUT_DOWN) {
        int lebar = glutGet(GLUT_WINDOW_WIDTH);
        int tinggi = glutGet(GLUT_WINDOW_HEIGHT);
        float xOrtho = (posisiX / (float)lebar) * 200.0f - 100.0f;
        float yOrtho = ((tinggi - posisiY) / (float)tinggi) * 200.0f - 100.0f;
        daftarTitik.push_back({xOrtho, yOrtho});
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("TUGAS 1 GRAFKOM");

    inisialisasi();

    glutDisplayFunc(tampil);
    glutKeyboardFunc(tekanKeyboard);
    glutMouseFunc(klikMouse);

    glutMainLoop();
    return 0;
}
