#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
//#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1;

#include <iostream>
#include <iomanip>

#include "Detector.hpp"
#include "Persona.hpp"
#include "kdTree.hpp"
#include "kdTreeNode.hpp"
//#include "ListaPersonas.hpp"
//#include "Nodo.hpp"
//#include <experimental/filesystem>
// namespace fs = std::experimental::filesystem;

using namespace cv;
using namespace std;

char *newFilepath = new char[300];
bool changedPath = false;

int main(int argc, char **argv)
{
    int salir;
    cout << "Si quiere salir aprete [1] o cualquier otro numero para seguir en el programa" << endl;
    cin >> salir;

    while (1)
    {
        if (salir != 1)
        {
            char *filepath = new char[300];

            cout << "BIENVENIDO A ACME VIGILANCIA" << endl;
            cout << "Ingrese [0] para usuario tipo guardia o [1] para administrador: " << endl;
            int user;
            while (1)
            {

                cin >> user;
                if (user != 0 && user != 1)
                {
                    cout << "Ingrese [0] para usuario tipo guardia o [1] para administrador: " << endl;
                    cin >> user;
                }
                else
                    break;
            }

            if (user == 0)
            {

                cout << "MENU GUARDIA" << endl;
                cout << "ABRIENDO VIDEO" << endl;

                int contadorEntran = 0;
                int contadorSalen = 0;

                kdTree *arbolito = new kdTree();

                Detector detector;
                // char *filepath = new char[200];

                detector.toggleMode();

                for (int i = 1; i <= 20; i++) // cambiar el valor de hasta donde llega i para analizar mas frames
                {
                    if (changedPath)
                    {
                        sprintf(filepath, newFilepath);
                        changedPath = false;
                    }
                    else
                        sprintf(filepath, "C:/Proyectos/Visual Studio 2022/testeo1/passgeway/%d.jpg", i);

                    Mat imagen = imread(filepath);
                    vector<Persona> found = detector.detect(imagen);

                    for (vector<Persona>::iterator j = found.begin(); j != found.end(); ++j)
                    {

                        Persona &p = *j;
                        rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(0, 0, 255), 2);
                        circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(0, 0, 255), 2);

                        kdTreeNode *nodoNuevo = new kdTreeNode(p.getXCentro(), p.getYCentro());

                        if (arbolito->getRoot() == NULL)
                        { // se ingresa nuevo nodo en arbol vacio

                            arbolito->insert(nodoNuevo);
                            nodoNuevo->setYInicial(p.getYCentro());
                            arbolito->setCantidadNodos(arbolito->getCantidadNodos() + 1);
                        }
                        else if (found.size() == arbolito->getCantidadNodos())
                        { // se actualizan los nodos del arbol, asumiendo que son las mismas personas

                            kdTreeNode *NodoMasCercano = arbolito->findClosestPoint(nodoNuevo);
                            NodoMasCercano->setX(p.getXCentro());
                            NodoMasCercano->setY(p.getYCentro());

                            // solo se cuenta cuando se actualiza un nodo, ya que se asume que esa persona se esta moviendo
                            if ((NodoMasCercano->getYInicial() - NodoMasCercano->getY()) > 0 && !NodoMasCercano->getYaContado() && NodoMasCercano->getY() < 200)
                            {
                                contadorEntran++;
                                NodoMasCercano->setYaContado(true);
                            }
                            else if ((NodoMasCercano->getYInicial() - NodoMasCercano->getY()) < 0 && !NodoMasCercano->getYaContado() && NodoMasCercano->getY() > 200)
                            {
                                NodoMasCercano->setYaContado(true);
                                contadorSalen++;
                            }
                        }
                        else if (found.size() > arbolito->getCantidadNodos())
                        { // hay personas nuevas en el frame y se ingresa

                            kdTreeNode *NodoMasCercano = arbolito->findClosestPoint(nodoNuevo);
                            double distancia = NodoMasCercano->findDistanceBetweenTwoPoints(nodoNuevo, NodoMasCercano);

                            if (distancia > 2)
                            { // si se cumple se asume que es una persona nueva y se ingresa

                                arbolito->insert(nodoNuevo);
                                nodoNuevo->setYInicial(p.getYCentro());
                                arbolito->setCantidadNodos(arbolito->getCantidadNodos() + 1);
                            }
                            else
                            { // si se cumple esto es una persona ya presente en arbol y se actualiza

                                NodoMasCercano->setX(p.getXCentro());
                                NodoMasCercano->setY(p.getYCentro());

                                // solo se cuenta cuando se actualiza un nodo, ya que se asume que esa persona se esta moviendo
                                if ((NodoMasCercano->getYInicial() - NodoMasCercano->getY()) > 0 && !NodoMasCercano->getYaContado() && NodoMasCercano->getY() < 200)
                                {
                                    contadorEntran++;
                                    NodoMasCercano->setYaContado(true);
                                }
                                else if ((NodoMasCercano->getYInicial() - NodoMasCercano->getY()) < 0 && !NodoMasCercano->getYaContado() && NodoMasCercano->getY() > 200)
                                {
                                    NodoMasCercano->setYaContado(true);
                                    contadorSalen++;
                                }
                            }
                        }
                        else
                        { // hay que eliminar un nodo del arbol, hay menos personas en el frame

                            kdTreeNode *NodoMasCercano = arbolito->findClosestPoint(nodoNuevo);
                            double distancia = NodoMasCercano->findDistanceBetweenTwoPoints(nodoNuevo, NodoMasCercano);

                            if (distancia > 2)
                            { // si se cumple la persona mas cercana en el arbol esta muy lejos de la del frame, por lo tanto es una persona que ya no esta en el frame

                                arbolito->remove(NodoMasCercano); // se elimina la persona faltante en el frame
                                nodoNuevo->setYInicial(p.getYCentro());
                                arbolito->setCantidadNodos(arbolito->getCantidadNodos() - 1);
                            }
                            else
                            { // si se cumple esto es una persona ya presente en arbol

                                NodoMasCercano->setX(p.getXCentro());
                                NodoMasCercano->setY(p.getYCentro());

                                // solo se cuenta cuando se actualiza un nodo, ya que se asume que esa persona se esta moviendo
                                if ((NodoMasCercano->getYInicial() - NodoMasCercano->getY()) > 0 && !NodoMasCercano->getYaContado() && NodoMasCercano->getY() < 200)
                                    contadorEntran++;
                                else if ((NodoMasCercano->getYInicial() - NodoMasCercano->getY()) < 0 && !NodoMasCercano->getYaContado() && NodoMasCercano->getY() > 200)
                                    contadorSalen++;
                            }
                        }

                        resize(imagen, imagen, Size(800, 400));

                        char str[200];
                        sprintf_s(str, "Total de entradas:""%i",contadorEntran);
                        putText(imagen, str, Point2f(33, 365), FONT_HERSHEY_COMPLEX_SMALL, 0.7, Scalar(0, 0, 255, 0.5), 1);
                        char str2[200];
                        sprintf_s(str2, "Total de salidas:""%i",contadorSalen);
                        putText(imagen, str2, Point2f(33, 385), FONT_HERSHEY_COMPLEX_SMALL, 0.7, Scalar(0, 0, 255, 0.5), 1);
                        char str3[200];
                        sprintf_s(str3, "Frame:""%i",i);
                        putText(imagen, str3, Point2f(10, 20), FONT_HERSHEY_COMPLEX_SMALL, 0.7, Scalar(0, 0, 255, 0.5), 1);

                        line(imagen, Point(0, 200), Point(800, 200), Scalar(0, 0, 255), 2, 8, 0);
                    }

                    imshow("Dectector Personas", imagen);
                    waitKey(1);
                }

                cout << "Entraron:" << contadorEntran << endl;
                cout << "Salieron:" << contadorSalen << endl;
                double vEntran = contadorEntran * 0.360;
                double vSalen = contadorSalen * 0.360;
                cout << "Flujo entrada promedio:" << vEntran << endl;
                cout << "Flujo salida promedio:" << vSalen << endl;
            }

            else
            { // menu administrador

                cout << "MENU ADMINISTRADOR" << endl;
                cout << "Ingrese al path del de la carpeta contenedora de las imagenes a procesar" << endl;
                cin >> newFilepath;
                changedPath = true;
                cout << "Regresando al menu de seleccion de usuario";
            }
        }

        else
            break;
    }
    return 0;
}
