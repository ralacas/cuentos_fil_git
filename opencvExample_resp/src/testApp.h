#ifndef _TEST_APP
#define _TEST_APP

#include <fstream>
#include "ofMain.h"
#include "ofxOpenCv.h"

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file


class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);


        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif


        ofxCvColorImage		    colorImg;           // imagen capturada
        ofxCvGrayscaleImage 	grayImage;          // imagen capturada, convertida a grises
        ofImage                 bgImage;            // imagen de fondo (libro)
        unsigned char * pixels;

        ofTrueTypeFont	        verdana;            // fuente para mensajes de debug
        ofTrueTypeFont          BookFont;           // fuente para letras cayendo

		//*** CANNY ****//
        ofxCvGrayscaleImage     edges;              // imagen para detección de bordes

        //Parámetros de configuración de función Canny
        double                  lowThresh;
        double                  highThresh;
        int                     aperture;

        //Configuración de pantalla
        int                     videoWidth;
        int                     videoHeight;
        int                     videoScale;
        int                     personajePosInicialX;
        int                     personajePosInicialY;
        int                     letrasPosInicialX;
        int                     letrasPosInicialY;


        //variables de letras
        int                     numLetras, numLetrasAbajo;
        char                    Letras[256];
        char                    Letra[2];
        unsigned int            PosLetrasX[100];
        float                   PosLetrasY[100];
        float                   Velocidad[100];
        int                     MargenAbajo;


        //variables de impacto
        int                     personajeTopY;
        float                   personajeTopYf;
        int                     letraRadio;

        //variables de archivo con cuento
        ifstream cuentoStream; //declare a file stream


        //debug
        bool                    DBG_DISPLAY;
        int                     DBG_FONT;
        bool                    DBG_TOPPERSONAJE;

};

#endif
