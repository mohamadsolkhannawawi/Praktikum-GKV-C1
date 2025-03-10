#include <GL/glut.h> // Header untuk menggunakan library OpenGL Utility Toolkit.
#include <cmath>     // Header untuk menggunakan fungsi matematika seperti sin dan cos.

// Fungsi untuk menggambar lingkaran
void drawCircle(float cx, float cy, float r, int num_segments, float rColor, float gColor, float bColor) {
    glBegin(GL_TRIANGLE_FAN); // Memulai penggambaran lingkaran menggunakan metode triangle fan.
    glColor3f(rColor, gColor, bColor); // Menetapkan warna lingkaran berdasarkan parameter RGB.
    glVertex2f(cx, cy); // Titik pusat lingkaran.

    // Loop untuk menggambar titik-titik keliling lingkaran.
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); // Hitung sudut setiap segmen.
        float x = r * cosf(theta); // Hitung posisi x titik pada lingkaran.
        float y = r * sinf(theta); // Hitung posisi y titik pada lingkaran.
        glVertex2f(cx + x, cy + y); // Tambahkan titik ke lingkaran dengan offset terhadap pusat.
    }
    glEnd(); // Selesai menggambar lingkaran.
}

// Fungsi untuk menggambar kurva tebal (digunakan untuk mulut dan alis)
void drawThickCurve(float cx, float cy, float r, float startAngle, float endAngle, float thickness) {
    glLineWidth(thickness); // Set ketebalan garis.
    glBegin(GL_LINE_STRIP); // Mulai menggambar garis berurutan.
    glColor3f(0.0, 0.0, 0.0); // Warna garis hitam.

    // Loop untuk menggambar titik-titik pada kurva.
    for (int i = 0; i <= 50; i++) {
        float theta = startAngle + (endAngle - startAngle) * float(i) / 50.0f; // Hitung sudut setiap segmen.
        float x = r * cosf(theta) + cx; // Hitung posisi x dari titik kurva.
        float y = r * sinf(theta) + cy; // Hitung posisi y dari titik kurva.
        glVertex2f(x, y); // Tambahkan titik ke kurva.
    }
    glEnd(); // Selesai menggambar kurva.
    glLineWidth(1.0); // Reset ketebalan garis ke default.
}

// Fungsi untuk menggambar emoji
void drawEmoji() {
    // Wajah Emoji (warna kuning)
    glPushMatrix(); // Simpan state transformasi saat ini.
    drawCircle(0.0, 0.0, 0.5, 100, 1.0, 0.85, 0.0); // Gambar lingkaran utama (wajah).
    glPopMatrix(); // Kembalikan state transformasi.

    // Mata kiri
    glPushMatrix();
    drawCircle(-0.17, 0.05, 0.08, 50, 0.0, 0.0, 0.0); // Bola mata (hitam).
    drawCircle(-0.17, 0.08, 0.03, 30, 1.0, 1.0, 1.0); // Sorotan mata (putih).
    drawCircle(-0.17, 0.02, 0.04, 30, 0.0, 0.3, 1.0); // Detail bawah mata (biru).
    glPopMatrix();

    // Mata kanan
    glPushMatrix();
    drawCircle(0.17, 0.05, 0.08, 50, 0.0, 0.0, 0.0); // Bola mata (hitam).
    drawCircle(0.17, 0.08, 0.03, 30, 1.0, 1.0, 1.0); // Sorotan mata (putih).
    drawCircle(0.17, 0.02, 0.04, 30, 0.0, 0.3, 1.0); // Detail bawah mata (biru).
    glPopMatrix();

    // Mulut (kurva melengkung)
    glPushMatrix();
    drawThickCurve(0.0, -0.15, 0.15, 3.14, 2.0 * 3.14, 3.0); // Mulut setengah lingkaran.
    glPopMatrix();

    // Alis kiri
    glPushMatrix();
    drawThickCurve(-0.17, 0.17, 0.12, 3.14, 2.0 * 3.14, 3.0); // Alis melengkung di atas mata kiri.
    glPopMatrix();

    // Alis kanan
    glPushMatrix();
    drawThickCurve(0.17, 0.17, 0.12, 3.14, 2.0 * 3.14, 3.0); // Alis melengkung di atas mata kanan.
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Bersihkan buffer warna.
    drawEmoji(); // Gambar emoji.
    glFlush(); // Paksa OpenGL untuk menampilkan semua yang telah digambar.
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inisialisasi GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set mode tampilan: single buffer dan RGB.
    glutInitWindowSize(500, 500); // Set ukuran jendela tampilan.
    glutCreateWindow("Lingkaran_Emoji_24060123120020"); // Membuat jendela dengan judul.

    glClearColor(1.0, 1.0, 1.0, 1.0); // Set warna latar belakang jendela menjadi putih.
    glMatrixMode(GL_PROJECTION); // Set mode matriks ke proyeksi.
    glLoadIdentity(); // Reset matriks proyeksi.
    gluOrtho2D(-1, 1, -1, 1); // Set sistem koordinat 2D (dari -1 hingga 1 di sumbu x dan y).

    glutDisplayFunc(display); // Daftarkan fungsi display untuk menggambar saat diperlukan.
    glutMainLoop(); // Masuk ke loop utama GLUT untuk menjalankan aplikasi.
    
    return 0; // Keluar dari program.
}

