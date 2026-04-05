#include <iostream>
#include <fstream>
#include "utils/image_processor.hpp"
#include "utils/LogSistema.hpp"
#include "utils/VerificarArquivo.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>


using namespace std;
using namespace cv;
using namespace cv::face;

LogSistema logger;
VerificarArquivo arquivoXML;

int ImageProcessor::openCam() {

   logger.logInfo("openCam: inicio");
   cv::VideoCapture cap;

   int indices[] = {0, 1, 2};
   bool abriu = false;

   for (int i : indices) {
       cap.open(i, cv::CAP_V4L2);
       if (cap.isOpened()) {
           std::cout << "Sucesso! Webcam aberta no indice: " << i << "\n" << std::endl << std::flush;
           logger.logInfo("openCam: webcam aberta no indice " + std::to_string(i));
           abriu = true;
           break;
       }
    }

    if (!abriu) {
        std::cerr << "Erro: Nenhuma webcam encontrada nos indices 0, 1 ou 2!" << "\n" << std::endl;
        logger.logError("openCam: nenhuma webcam encontrada em 0/1/2");
        return -1;
    }

    cv::Mat frame;
    cv::namedWindow("Minha Webcam", cv::WINDOW_AUTOSIZE);

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            std::cout << "Aguardando sinal da camera..." << "\n" << std::endl;
            cv::waitKey(500);
            continue;
        }

        cv::imshow("Minha Webcam", frame);

        if (cv::waitKey(30) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();
    logger.logInfo("openCam: finalizado");
    return 0;
}

int ImageProcessor::detectarRosto() {

    logger.logInfo("detectarRosto: inicio");

    CascadeClassifier face_cascade;
    if (!face_cascade.load(arquivoXML.getFrontalfaceAlt2("haarcascade_frontalface_alt2.xml"))) {
        logger.logError("Erro ao carregar arquivo XML!");
        return -1;
    }


    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Erro ao abrir a webcam!" << endl;
        return -1;
    }

    Mat frame, gray;
    while (true) {
        cap >> frame; // Captura o frame atual
        if (frame.empty()) break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);

        vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));

        for (size_t i = 0; i < faces.size(); i++) {
            rectangle(frame, faces[i], Scalar(0, 255, 0), 2);
        }

        imshow("Webcam - Face Detection", frame);

        char c = (char)waitKey(10);
        if (c == 27 || c == 'q') break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}

void ImageProcessor::testeIndiceWebCam() {
    LogSistema logger;
    logger.logInfo("testeIndiceWebCam: inicio");
    std::cout << "\n=== Testando indices disponiveis de webcam ===" << std::endl;

    int indices[] = {0, 1, 2, 3};

    for (int i : indices) {
        cv::VideoCapture testCap;
        testCap.open(i, cv::CAP_V4L2);

        if (testCap.isOpened()) {
            std::cout << "[ENCONTRADO] Webcam funcional no indice: " << i << std::endl;
            logger.logInfo("testeIndiceWebCam: webcam encontrada no indice " + std::to_string(i));
            testCap.release();
        } else {
            std::cout << "[NAO ENCONTRADO] Indice " << i << " nao disponivel" << std::endl;
            logger.logInfo("testeIndiceWebCam: webcam nao encontrada no indice " + std::to_string(i));
        }
    }

    std::cout << "=== Teste finalizado ===\n" << std::endl;
    logger.logInfo("testeIndiceWebCam: finalizado");
}
