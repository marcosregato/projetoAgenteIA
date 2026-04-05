#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>
#include "utils/VerificarArquivo.hpp"
#include "utils/LogSistema.hpp"

namespace fs = std::filesystem;
using namespace cv;
using namespace cv::face;


std::string VerificarArquivo::getFrontalfaceAlt2(const std::string &nomeArquivo){
    LogSistema logger;

  logger.logInfo("isVerificarArquivo: inicio");

    //CascadeClassifier faceDetector;
    std::vector<std::string> listCascade = {
        "haarcascades/" + nomeArquivo,
        "../haarcascades/" + nomeArquivo,
        "/usr/share/opencv4/haarcascades/" + nomeArquivo,
        "/usr/local/share/opencv4/haarcascades/" + nomeArquivo
    };

    for (const auto& path : listCascade) {
        if (fs::exists(path) && fs::is_regular_file(path)) {
            logger.logInfo("haarcascade_frontalface_alt2 carregado: " + path);
            return path;
        }
    }

    logger.logError("Nao foi possivel encontrar: " + nomeArquivo);
    return "";

}

std::string VerificarArquivo::getLbfmodel(const std::string &nomeArquivo){
    LogSistema logger;
    logger.logInfo("isLbfmodel: inicio");

    Ptr<Facemark> facemark = FacemarkLBF::create();

    std::vector<std::string> listLbfModel = {
        "lbfmodel/" + nomeArquivo,
        "../lbfmodel/" + nomeArquivo,
        "/usr/share/opencv4/lbfmodel/" + nomeArquivo,
        "/usr/local/share/opencv4/lbfmodel/" + nomeArquivo
    };

    for (const auto& path : listLbfModel) {
        if (fs::exists(path) && fs::is_regular_file(path)) {
            facemark->loadModel(path);
            logger.logInfo("lbfmodel carregado: " + path);
            return path;
        }
    }

    logger.logError("Nao foi possivel encontrar: " + nomeArquivo);
    return "";
}
