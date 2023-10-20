#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <qrencode.h>
#include <fstream>

using namespace std;

bool generateurQrCode(const char *url, string nomFichier){
    
    char text[256];
    snprintf(text, sizeof(text), "https://chart.googleapis.com/chart?cht=qr&chs=300x300&chl=%s", url);
    // snprintf(text, sizeof(text), "", url);

    QRcode* qrcode = QRcode_encodeString(text, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
     if (qrcode == nullptr) {
        std::cerr << "Error: Failed to encode QR code" << std::endl;
        return false;
    }

    fstream out(nomFichier, ios::in | ios::out | ios::trunc); //pour le vider avant d'écrire

    for (int y = 0; y < qrcode->width; y++) {
        for (int x = 0; x < qrcode->width; x++) {
            if (qrcode->data[y * qrcode->width + x] & 1) {
                cout << "██";
                out<< "██";
            } else {
                cout << "  ";
                out << "  ";

            }
        }
        cout << std::endl;
        out<< std::endl;

    }

    QRcode_free(qrcode);
    out.close();

    return true;

}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <Lien de votre site>" << std::endl;
        return EXIT_FAILURE;
    }

    const char* url = argv[1];
    if(generateurQrCode(url, "qrcode.txt"))
        cout<<"1 - Scan le qr ci dessus ou dans le fichier qrcode.txt\n2 - Capturer votre Qr Code"<<endl;
    else
        cout<<"Le Qr code n'a pas ete genere!!!"<<endl;

    


   
   
}
