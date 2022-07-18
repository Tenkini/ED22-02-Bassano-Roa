// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <iomanip>

#include "Detector.hpp"
#include "Persona.hpp"
#include "ListaPersonas.hpp"
#include "ListaPersonas.cpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

    Detector detector;
    Mat imagen;
    imagen = imread("C:/Proyectos/Visual Studio 2022/opencvTests/images/image0293.png");
    detector.toggleMode();
    cout << detector.modeName() << endl;

    int height = imagen.rows;
    int width = imagen.cols;

    Point p1 = (180, 0);
    Point p2 = (0, 120);

    line(imagen, p1, p2, Scalar(0, 255, 255));

    vector<Persona> found = detector.detect(imagen);
    ListaPersonas *lp = new ListaPersonas();

    for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
    {
        Persona p = *i;
        Nodo *n = new Nodo(p);
        cout << "(" << p.getXComienzo() << ", " << p.getYComienzo() << ")" << endl;
        //detector.adjustRect(r);
        rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(0, 255, 0), 2);
        circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(0, 0, 255), 3);
        circle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), 3, cv::Scalar(255, 0, 255), 2);
        circle(imagen, cv::Point(p.getXFin(), p.getYFin()), 3, cv::Scalar(0, 255, 255), 2);
        lp->insertar(n);
    }
    Nodo *aux = lp->getFirst();
    do
    {
        cout << "(" << aux->getPersona().getXComienzo() << ", " << aux->getPersona().getYComienzo() << ")" << endl;
        aux = aux->getNext();
    } while (aux != lp->getFirst());
    
    
    imshow("People detector", imagen);
    waitKey(0);

    return 0;
}