/* Changes
 * @ralacas <15-jun-2012> Se agregó lo referente al manejo del cuento en XML
 *
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Letra.h"
#include "cuentosReader.h"
#include "ofxXmlSettings.h"
#include <vector>

using namespace std;

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofVideoGrabber 		vidGrabber;
    
    ofxCvColorImage			colorImg;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    
    ofxCvContourFinder 	contourFinder;
    
    int 				threshold;
    bool				bLearnBakground;
    
    // Number of columns and rows in our system
    int cols, rows;
    
	//A partir de aqui variables especificas de la aplicacion
    //Metodo que comienza un nuevo renglon
    void nuevoRenglon();
    //Esquina superior izquierda donde comienza a dibujarse la pantalla de cuadritos
    int posXfinal, posYfinal;
    
    //tipograf’a
    ofTrueTypeFont  franklinBook;
    
    float 			counter;
    
    //variables de letras
    int                 numLetras, numLetrasAbajo;
    //char                Letras[256];
    char                LetraArr[2];
    //unsigned int        PosLetrasX[100];
    //float               PosLetrasY[100];
    //float               Velocidad[100];
    bool				bimgGris;
    vector<Letra*> misLetra;
    
    char reportStr[1024];
    char infoArchivoStr[50];
    
    //variables de archivo con cuento
    ifstream cuentoStream; //declare a file stream
    
    //manejo del cuento xml @ralacas 15-jun-2012
    ofxXmlSettings cuentosXml;
    
};