#include <GL/glut.h> // Header untuk fungsi OpenGL dan GLUT

// Variabel global untuk menyimpan sudut rotasi shoulder (bahu) dan elbow (siku)
static int shoulder = 0, elbow = 0;

// Inisialisasi pengaturan awal OpenGL
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Mengatur warna latar belakang menjadi hitam
    glShadeModel(GL_FLAT); // Mengatur mode shading menjadi flat
}

// Fungsi untuk menggambar tampilan
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Membersihkan buffer warna
    glPushMatrix(); // Menyimpan matriks saat ini

    // Transformasi dan rotasi untuk bagian shoulder (bahu)
    glTranslatef(-1.0, 0.0, 0.0); // Geser ke kiri untuk memulai dari titik tertentu
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0); // Rotasi berdasarkan sudut shoulder di sumbu z
    glTranslatef(1.0, 0.0, 0.0); // Geser kembali ke posisi awal setelah rotasi
    
    glPushMatrix(); // Simpan matriks untuk bagian lengan atas
    glScalef(2.0, 0.4, 1.0); // Skala untuk membentuk lengan atas
    glutWireCube(1.0); // Gambar kubus wireframe sebagai lengan atas
    glPopMatrix(); // Kembalikan matriks

    // Transformasi dan rotasi untuk bagian elbow (siku)
    glTranslatef(1.0, 0.0, 0.0); // Geser ke kanan untuk posisi siku
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0); // Rotasi berdasarkan sudut elbow di sumbu z
    glTranslatef(1.0, 0.0, 0.0); // Geser kembali ke posisi awal setelah rotasi

    glPushMatrix(); // Simpan matriks untuk bagian lengan bawah
    glScalef(2.0, 0.4, 1.0); // Skala untuk membentuk lengan bawah
    glutWireCube(1.0); // Gambar kubus wireframe sebagai lengan bawah
    glPopMatrix(); // Kembalikan matriks

    glPopMatrix(); // Kembalikan matriks utama
    glutSwapBuffers(); // Tukar buffer untuk menghasilkan tampilan yang halus
}

// Fungsi untuk mengatur ulang tampilan saat ukuran jendela diubah
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // Mengatur viewport sesuai ukuran jendela

    glMatrixMode(GL_PROJECTION); // Beralih ke matriks proyeksi
    glLoadIdentity(); // Mereset matriks proyeksi
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // Mengatur perspektif dengan sudut 65 derajat

    glMatrixMode(GL_MODELVIEW); // Beralih ke matriks model-view
    glLoadIdentity(); // Mereset matriks model-view
    glTranslatef(0.0, 0.0, -5.0); // Geser objek ke dalam layar untuk tampilan lebih baik
}

// Fungsi untuk menangani input keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            shoulder = (shoulder + 5) % 360; // Tambah sudut rotasi shoulder
            glutPostRedisplay(); // Perbarui tampilan
            break;
        case 'S':
            shoulder = (shoulder - 5) % 360; // Kurangi sudut rotasi shoulder
            glutPostRedisplay(); // Perbarui tampilan
            break;
        case 'e':
            elbow = (elbow + 5) % 360; // Tambah sudut rotasi elbow
            glutPostRedisplay(); // Perbarui tampilan
            break;
        case 'E':
            elbow = (elbow - 5) % 360; // Kurangi sudut rotasi elbow
            glutPostRedisplay(); // Perbarui tampilan
            break;
        case 27:
            exit(0); // Keluar dari program jika tombol ESC ditekan
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inisialisasi GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Atur mode tampilan dengan double buffering dan warna RGB
    glutInitWindowSize(700, 600); // Atur ukuran jendela
    glutInitWindowPosition(100, 100); // Atur posisi jendela di layar
    glutCreateWindow(argv[0]); // Buat jendela dengan judul dari argumen

    init(); // Panggil fungsi inisialisasi

    glutDisplayFunc(display); // Tetapkan fungsi callback untuk menggambar
    glutReshapeFunc(reshape); // Tetapkan fungsi callback untuk perubahan ukuran jendela
    glutKeyboardFunc(keyboard); // Tetapkan fungsi callback untuk input keyboard

    glutMainLoop(); // Memulai loop utama GLUT untuk memproses event
    return 0; // Kembali dari fungsi utama
}

