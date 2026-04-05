#ifndef IMAGE_PROCESSOR_H_INCLUDED
#define IMAGE_PROCESSOR_H_INCLUDED
#include <string>

class ImageProcessor{

    public :
        int openCam();
        void testeIndiceWebCam();
        int detectarRosto();

    private:
    std::string arquivoFrontalfaceAlt2;
    std::string arquivoLbfmodel;

};

#endif // IMAGE_PROCESSOR_H_INCLUDED
