#include <GL/glut.h>
#include <cmath> // Mengimpor library C++ untuk fungsi matematika seperti cos() dan sin() yang digunakan dalam perhitungan koordinat lingkaran.

void drawCloud(float x, float y, float scale) { // Fungsi untuk menggambar awan dengan posisi (x, y) dan ukuran (scale).
    glPushMatrix(); // Menyimpan matriks transformasi saat ini agar tidak mempengaruhi objek lain.

    glTranslatef(x, y, 0.0); // Menerjemahkan (memindahkan) posisi awan ke koordinat (x, y). Sumbu z tetap di 0 karena ini adalah gambar 2D.
    glScalef(scale, scale, 1.0); // Menskalakan ukuran awan. Sumbu x dan y diskalakan sesuai parameter 'scale', sedangkan z tetap 1 karena 2D.

    glColor3f(1.0, 1.0, 1.0); // Menetapkan warna awan menjadi putih (RGB: 1,1,1).

    for (int i = 0; i < 3; i++) { // Melakukan loop untuk membuat tiga lingkaran kecil yang akan membentuk awan.
        glPushMatrix(); // Menyimpan matriks transformasi sebelum menerapkan transformasi baru.

        glTranslatef(i * 0.1f, 0.0, 0.0); 
        // Menggeser setiap lingkaran sejauh 0.1 unit ke kanan pada sumbu x untuk membentuk susunan awan yang memanjang.

        glBegin(GL_POLYGON); // Memulai penggambaran bentuk poligon yang akan menjadi lingkaran.

        for (int angle = 0; angle < 360; angle += 10) { // Loop untuk membuat lingkaran dengan iterasi setiap 10 derajat.
            float rad = angle * 3.14159 / 180; // Mengonversi sudut dari derajat ke radian karena fungsi cos() dan sin() menggunakan radian.
            glVertex2f(cos(rad) * 0.1, sin(rad) * 0.05); 
            // Menentukan titik-titik lingkaran. 
            // cos(rad) * 0.1 memberikan lebar lingkaran sebesar 0.1 unit.
            // sin(rad) * 0.05 memberikan tinggi lingkaran sebesar 0.05 unit, sehingga lingkaran tampak oval (memanjang di sumbu x).
        }

        glEnd(); // Mengakhiri penggambaran poligon.
        glPopMatrix(); // Mengembalikan matriks transformasi sebelumnya untuk memastikan transformasi tidak mempengaruhi lingkaran berikutnya.
    }

    glPopMatrix(); // Mengembalikan matriks transformasi utama agar transformasi awan tidak mempengaruhi objek lain di luar fungsi ini.
}


void display() { 
    glClear(GL_COLOR_BUFFER_BIT); // Membersihkan buffer warna agar layar kosong sebelum menggambar objek baru.

    // Background - Sky
        glColor3f(0.529, 0.808, 0.922); // Menentukan warna biru langit dengan RGB (0.529, 0.808, 0.922).
    glBegin(GL_QUADS); // Memulai penggambaran bentuk segi empat (persegi panjang).
    glVertex2f(-1.0, 0.0); // Titik kiri bawah langit pada koordinat (-1.0, 0.0).
    glVertex2f(1.0, 0.0);  // Titik kanan bawah langit pada koordinat (1.0, 0.0).
    glVertex2f(1.0, 1.0);  // Titik kanan atas langit pada koordinat (1.0, 1.0).
    glVertex2f(-1.0, 1.0); // Titik kiri atas langit pada koordinat (-1.0, 1.0).
    glEnd(); // Mengakhiri penggambaran segi empat.
    
    // Sun
    glColor3f(1.0, 1.0, 0.0); // Warna kuning untuk matahari.
    glBegin(GL_POLYGON); // Memulai penggambaran bentuk poligon untuk membentuk lingkaran matahari.
    for (int i = 0; i < 360; i += 10) // Iterasi dari 0° hingga 360° dengan interval 10°.
        glVertex2f(0.7 + 0.1 * cos(i * 3.14159 / 180), 0.7 + 0.1 * sin(i * 3.14159 / 180)); 
        // Membuat titik-titik lingkaran dengan pusat di (0.7, 0.7) dan radius 0.1.
    glEnd(); // Mengakhiri penggambaran lingkaran.
    
    // Sun Rays
		glColor3f(1.0, 1.0, 0.0); // Warna sinar matahari kuning.
	for (int i = 0; i < 360; i += 30) { // Membuat sinar setiap 30 derajat.
    	float xStart = 0.7 + 0.1 * cos(i * 3.14159 / 180); // Titik awal sinar, di tepi matahari.
    	float yStart = 0.7 + 0.1 * sin(i * 3.14159 / 180);
    	float xEnd = 0.7 + 0.15 * cos(i * 3.14159 / 180);  // Titik akhir sinar, sedikit lebih jauh dari tepi matahari.
    	float yEnd = 0.7 + 0.15 * sin(i * 3.14159 / 180);
    
    	glBegin(GL_LINES); // Memulai penggambaran garis.
    	glVertex2f(xStart, yStart); // Titik awal sinar.
    	glVertex2f(xEnd, yEnd);     // Titik akhir sinar.
    	glEnd(); // Mengakhiri penggambaran garis.
	}

    
    // Draw Clouds
    drawCloud(-0.7, 0.8, 1.0); // Menggambar awan di posisi (-0.7, 0.8) dengan ukuran 1.0.
    drawCloud(0.5, 0.75, 1.2); // Menggambar awan di posisi (0.5, 0.75) dengan ukuran 1.2.
    drawCloud(-0.2, 0.6, 0.8); // Menggambar awan di posisi (-0.2, 0.6) dengan ukuran 0.8.
    drawCloud(0.2, 0.9, 0.9);  // Menggambar awan di posisi (0.2, 0.9) dengan ukuran 0.9.

    
    // Background - Grass
    glColor3f(0.196, 0.804, 0.196); // Warna hijau untuk rumput.
    glBegin(GL_QUADS); // Memulai penggambaran persegi panjang.
    glVertex2f(-1.0, -1.0); // Titik kiri bawah rumput.
    glVertex2f(1.0, -1.0);  // Titik kanan bawah rumput.
    glVertex2f(1.0, 0.0);   // Titik kanan atas rumput.
    glVertex2f(-1.0, 0.0);  // Titik kiri atas rumput.
    glEnd(); // Mengakhiri penggambaran.

    // Car Body with upward curve
    glColor3f(0.0, 0.0, 1.0); // Warna biru untuk body mobil.
    glBegin(GL_POLYGON); // Memulai penggambaran bentuk poligon.
    glVertex2f(-0.5, -0.2); // Titik kiri bawah mobil.
    glVertex2f(0.5, -0.2);  // Titik kanan bawah mobil.
    glVertex2f(0.5, 0.1); // titik kanan atas mobil
    for (float angle = 0; angle <= 180; angle += 10) // Membuat kurva atas mobil.
        glVertex2f(0.3 * cos(angle * 3.14159 / 180), 0.1 + 0.05 * sin(angle * 3.14159 / 180));
    glVertex2f(-0.5, 0.1);  // Titik kiri atas mobil.
    glEnd(); // Mengakhiri penggambaran.


    // Car Roof
    glBegin(GL_POLYGON);
    glVertex2f(-0.3, 0.1); // Titik kiri bawah atap mobil.
    glVertex2f(0.3, 0.1);  // Titik kanan bawah atap mobil.
    glVertex2f(0.2, 0.3);  // Titik kanan atas atap mobil.
    glVertex2f(-0.2, 0.3); // Titik kiri atas atap mobil.
    glEnd();

    // Single Window with Middle Cut
    glColor3f(0.9, 0.9, 0.9); // Warna abu-abu terang untuk jendela.
    glBegin(GL_POLYGON); // Menggambar jendela mobil.
    glVertex2f(-0.22, 0.12);
    glVertex2f(0.22, 0.12);
    glVertex2f(0.15, 0.28);
    glVertex2f(-0.15, 0.28);
    glEnd();


    // Middle Cut
    glColor3f(0.0, 0.0, 1.0); // Warna biru untuk bagian pemisah jendela.
    glBegin(GL_QUADS);
    glVertex2f(-0.02, 0.12);
    glVertex2f(0.02, 0.12);
    glVertex2f(0.02, 0.28);
    glVertex2f(-0.02, 0.28);
    glEnd();


    glColor3f(0.5, 0.5, 0.5); // Menetapkan warna abu-abu untuk pegangan pintu.
	glBegin(GL_QUADS); // Memulai penggambaran bentuk persegi empat (quad).

	// Pegangan pintu kiri
	glVertex2f(-0.18, -0.05); // Titik kiri bawah pegangan kiri.
	glVertex2f(-0.1, -0.05);  // Titik kanan bawah pegangan kiri.
	glVertex2f(-0.1, 0.0);    // Titik kanan atas pegangan kiri.
	glVertex2f(-0.18, 0.0);   // Titik kiri atas pegangan kiri.

	// Pegangan pintu kanan
	glVertex2f(0.1, -0.05);   // Titik kiri bawah pegangan kanan.
	glVertex2f(0.18, -0.05);  // Titik kanan bawah pegangan kanan.
	glVertex2f(0.18, 0.0);    // Titik kanan atas pegangan kanan.
	glVertex2f(0.1, 0.0);     // Titik kiri atas pegangan kanan.

	glEnd(); // Mengakhiri penggambaran quad.


    // Front and Rear Lights (adjusted to be inside car body)
    glColor3f(1.0, 1.0, 0.0); // Menetapkan warna kuning untuk lampu mobil.
	glBegin(GL_QUADS); // Memulai penggambaran bentuk persegi empat.

	// Lampu depan (kanan)
	glVertex2f(0.48, -0.18); // Titik kiri bawah lampu depan.
	glVertex2f(0.5, -0.18);  // Titik kanan bawah lampu depan.
	glVertex2f(0.5, -0.1);   // Titik kanan atas lampu depan.
	glVertex2f(0.48, -0.1);  // Titik kiri atas lampu depan.

	// Lampu belakang (kiri)
	glVertex2f(-0.5, -0.18); // Titik kiri bawah lampu belakang.
	glVertex2f(-0.48, -0.18); // Titik kanan bawah lampu belakang.
	glVertex2f(-0.48, -0.1);  // Titik kanan atas lampu belakang.
	glVertex2f(-0.5, -0.1);   // Titik kiri atas lampu belakang.

	glEnd(); // Mengakhiri penggambaran lampu.


    // Siren
    glColor3f(1.0, 0.0, 0.0); // Menetapkan warna merah untuk sirine.
	glBegin(GL_QUADS); // Memulai penggambaran persegi empat sirine.
	glVertex2f(-0.05, 0.3); // Titik kiri bawah sirine.
	glVertex2f(0.05, 0.3);  // Titik kanan bawah sirine.
	glVertex2f(0.05, 0.35); // Titik kanan atas sirine.
	glVertex2f(-0.05, 0.35); // Titik kiri atas sirine.
	glEnd(); // Mengakhiri penggambaran sirine.


    // Wheels - Outer Black
    glColor3f(0.0, 0.0, 0.0); // Menetapkan warna hitam untuk ban luar.
	glBegin(GL_POLYGON); // Memulai penggambaran lingkaran untuk roda kiri.
	for (int i = 0; i < 360; i += 10) // Loop untuk membentuk lingkaran dari 0° hingga 360°.
    	glVertex2f(-0.3 + 0.08 * cos(i * 3.14159 / 180), -0.2 + 0.08 * sin(i * 3.14159 / 180)); 
    	// Koordinat pusat roda di (-0.3, -0.2) dengan jari-jari 0.08.
	glEnd(); // Mengakhiri penggambaran roda kiri.

	glBegin(GL_POLYGON); // Memulai penggambaran lingkaran untuk roda kanan.
	for (int i = 0; i < 360; i += 10) 
    	glVertex2f(0.3 + 0.08 * cos(i * 3.14159 / 180), -0.2 + 0.08 * sin(i * 3.14159 / 180)); 
   	 // Koordinat pusat roda di (0.3, -0.2) dengan jari-jari 0.08.
	glEnd(); // Mengakhiri penggambaran roda kanan.


    // Wheels - Inner White (Rim)
    glColor3f(1.0, 1.0, 1.0); // Menetapkan warna putih untuk bagian dalam roda (velg).
	glBegin(GL_POLYGON); // Memulai penggambaran lingkaran dalam roda kiri.
	for (int i = 0; i < 360; i += 10) 
    	glVertex2f(-0.3 + 0.04 * cos(i * 3.14159 / 180), -0.2 + 0.04 * sin(i * 3.14159 / 180)); 
    	// Lingkaran dalam dengan jari-jari lebih kecil (0.04).
	glEnd(); // Mengakhiri penggambaran roda dalam kiri.

	glBegin(GL_POLYGON); // Memulai penggambaran lingkaran dalam roda kanan.
	for (int i = 0; i < 360; i += 10) 
    	glVertex2f(0.3 + 0.04 * cos(i * 3.14159 / 180), -0.2 + 0.04 * sin(i * 3.14159 / 180)); 
    // Lingkaran dalam dengan jari-jari lebih kecil (0.04).
	glEnd(); // Mengakhiri penggambaran roda dalam kanan.


    glFlush();// Memaksa OpenGL untuk menampilkan semua objek yang telah digambar ke layar.
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    // Mengatur warna latar belakang (background) menjadi putih.
    // Parameter (R, G, B, Alpha) dengan nilai 1.0 untuk masing-masing menghasilkan warna putih penuh.

    glMatrixMode(GL_PROJECTION); 
    // Mengatur mode matriks ke *projection*, digunakan untuk menentukan tampilan proyeksi.

    glLoadIdentity(); 
    // Menginisialisasi atau mereset matriks proyeksi ke matriks identitas (tanpa transformasi).

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
    // Mengatur proyeksi ortogonal 2D. 
    // Parameter (-1.0, 1.0, -1.0, 1.0) menunjukkan rentang koordinat X dari -1 ke 1, dan Y dari -1 ke 1.
    // Ini memastikan bahwa semua objek digambar dalam koordinat normalisasi.
}


int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    // Inisialisasi GLUT dan memproses argumen dari command line.

    glutCreateWindow("Mobil 2D_24060123120020"); 
    // Membuat jendela tampilan dengan judul "Mobil 2D OpenGL".

    glutInitWindowSize(1000, 400); 
    // Menentukan ukuran jendela sebesar 800 piksel lebar dan 600 piksel tinggi.

    init(); 
    // Memanggil fungsi `init()` untuk menginisialisasi pengaturan awal OpenGL.

    glutDisplayFunc(display); 
    // Menentukan fungsi callback `display` yang akan dipanggil untuk merender objek ke layar.

    glutMainLoop(); 
    // Memulai loop utama GLUT yang terus menjalankan program hingga jendela ditutup.

    return 0; 
    // Mengembalikan nilai 0 untuk menandakan bahwa program berakhir dengan sukses.
}
