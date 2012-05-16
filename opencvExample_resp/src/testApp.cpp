#include "testApp.h"


//--------------------------------------------------------------
// some new changes
void testApp::setup(){


	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
	#else
        vidPlayer.loadMovie("fingers.mov");
        vidPlayer.play();
	#endif

    /// VIDEO SETUP
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	videoWidth = 320;		//tamaño de la pantalla de captura
	videoHeight = 240;
	videoScale = 2;			//Cuantos pixeles contendr‡ cada cuadrado?
    bgImage.loadImage("oldpaper.jpg");
    bgImage.resize(ofGetWidth(), ofGetHeight());
    personajeTopY = ofGetHeight();
    personajeTopYf = ofGetHeight();
    letraRadio = 20;


	/// CANNY SETUP
    edges.allocate(320,240);
	lowThresh=50;
    highThresh=150;
    aperture=3;


    /// Fuente para letras del libro
    BookFont.loadFont("GoudyBookletter1911.ttf",16);

    /// Fuente para mensajes de debug
    verdana.loadFont("verdana.ttf",8);
    //verdana.loadFont("verdana.ttf",8, false, true);
	verdana.setLineHeight(20.0f);



    /// POSICIÓN INICIAL DE PERSONAJE Y LETRAS
    personajePosInicialX = ofGetWidth()/7/videoScale;;
    personajePosInicialY = ofGetHeight()-(240+50)*videoScale;;
    letrasPosInicialX=10;
    letrasPosInicialY=10;
    MargenAbajo=170;


    /// Inicializacion de las letras
	numLetrasAbajo = 0;


    /// LECTURA DE ARCHIVO PARA CUENTO
    cuentoStream.open( ofToDataPath("cuento1.txt").c_str() ); //open your text file
    if (cuentoStream==NULL) {
            printf( "Error (NO ABIERTO)\n" );
    } else {
        printf( "\nFichero abierto. ");
        string str; //declare a string for storage
        getline(cuentoStream, str); //get a line from the file, put it in the string
        for (int a=0;a<=str.size();a++) {
                Letras[a]=str[a];
        }

    }


	/// cuantas letras contiene el primer renglón?
    numLetras = strlen(Letras);

	/// ciclo para inicializar la posici—n de cada letra hasta arriba de la pantalla as’ como su velocidad de caida.
	int posi = 0;
	for (int j = 0; j < numLetras; j++) {
		if (Letras[j-1] == 'i' || Letras[j-1] == 'l' ) {
			posi = posi + 8;
		} else {
			posi = posi + 13;
		}
		PosLetrasX[j] = posi;
        PosLetrasY[j] = 0;
		Velocidad[j] = (rand()%100);
		Velocidad[j]= Velocidad[j]/100 + 2;
    }

    ///Prepara Letra para ser un str
    Letra[1] = '\0';


    DBG_DISPLAY=true;
    DBG_FONT=24;
    DBG_TOPPERSONAJE=false;

}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.grabFrame();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.idleMovie();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
        #endif

        grayImage = colorImg;
        edges = grayImage;


        /// Run cvCanny.
        cvCanny(
          grayImage.getCvImage(), /// input image
          edges.getCvImage(), /// edges output
          lowThresh,
          highThresh,
          aperture); /// default = 3

        /// Let ofxOpenCv know that the internal texture
        /// needs to be reloaded before drawing it to the screen.
        /// This does not modify the IplImage.
        edges.flagImageChanged();

        ///unsigned char * pixels = edges.getPixels();
        pixels = edges.getPixels();
        int w = grayImage.width;
		int h = grayImage.height;





        /** Se recorre cada pixel del video después de ejecutar Canny, así que sólo hay blanco y negro (0 o 255) y esto aplica
        para los tres colores (r,g,b), así que con verificar uno es suficiente (en este caso trabajamos con r)
        **/
        for (int j = 0; j < videoHeight; j++) {
            for (int i = 1; i <  videoWidth; i++) {

                /** color **/
                //unsigned char r = pixels[(j * videoWidth/videoScale + i)*3];
                //unsigned char g = pixels[(j * videoWidth/videoScale + i)*3 + 1];
                //unsigned char b = pixels[(j * videoWidth/videoScale + i)*3 + 2];


                ///gray scale
                unsigned char r = pixels[(j * videoWidth + i)];

                /// ¿hay color? (podría ser r, g o b, todos traen 0 o 255)
                if (r!=0) {

                    /// por cada frame, pone la linea una vez nada más, en base a esta bandera
                    /// y eso significa que debería dibujarse en el pixel encontrado más arriba
                    if (!DBG_TOPPERSONAJE) {

                        personajeTopY = (int)(j*videoScale) + personajePosInicialY;
                        personajeTopYf = (float)((j*videoScale) + personajePosInicialY);


                        DBG_TOPPERSONAJE=true;
                    }
                    ofSetColor(20,10,10);
                    ofRect(personajePosInicialX + i*videoScale - videoScale/2, personajePosInicialY + j*videoScale - videoScale/2, videoScale, videoScale);
                }
            }
        }
        DBG_TOPPERSONAJE=false;




		///Obtiene el valor de cada pixel en la coordenada de las letras para checar si aœn hay algunas bajando, cuenta cuantas est‡n hasta abajo ya
		numLetrasAbajo = 0;
		for (int j = 0; j < numLetras; j++) {

			/// si no ha llegado hasta abajo...
			if (PosLetrasY[j] < (ofGetHeight()-MargenAbajo)) {

                if (j==DBG_FONT) {

                    bool chocaFlag = false;

                    ///checa contra un solo pixel de X:
                    //unsigned char r = pixels[(int)(PosLetrasY[j]-personajePosInicialX) * w  + PosLetrasX[j]];
                    unsigned char r = pixels[(int)(PosLetrasY[j]-personajePosInicialY) * w  + PosLetrasX[j]];
                    if (r==0) { chocaFlag=true;}
/*
                    ///checa contra varios pixeles de X:
                    for (int nX=-letraRadio/2; nX<=letraRadio/2;nX++) {
                        unsigned char r = pixels[(int)(PosLetrasY[j]-personajePosInicialX) * w  + PosLetrasX[j]+nX];
                        if (r==0) { chocaFlag=true;}
                    }
*/

                    //if ((r==0) && ((abs((int)PosLetrasY[j] - personajeTopY) > letraRadio))) {
                    //if ((chocaFlag) && ((abs((int)PosLetrasY[j] - personajeTopY) > (letraRadio+Velocidad[j])))) {
                    if (abs((int)PosLetrasY[j] - personajeTopY) > (letraRadio+Velocidad[j])) {
                    //if (chocaFlag) {
                        PosLetrasY[j] += Velocidad[j];
                    } else {
                        //PosLetrasY[j]--;
                        PosLetrasY[j]-=Velocidad[j];
                        //PosLetrasY[j]=personajeTopY-10;
                    }

                } else { ///dbg
                    PosLetrasY[j] += Velocidad[j];
                }


			} else {
				numLetrasAbajo++;
			}
		}

		///Si todas est‡n hasta abajo significa que hay que pasar al siguiente rengl—n del cuento
		if (numLetrasAbajo == numLetras) {

            string str; ///declare a string for storage
            getline(cuentoStream, str); ///get a line from the file, put it in the string

            int posi = 0;
            for (int a=0;a<=str.size();a++) {
                Letras[a]=str[a];

                if (Letras[a-1] == 'i' || Letras[a-1] == 'l' ) {
                    posi = posi + 8;
                } else {
                    posi = posi + 13;
                }
                PosLetrasX[a] = posi;

                PosLetrasY[a] = 0;
                Velocidad[a] = (rand()%100);
                Velocidad[a]= Velocidad[a]/100 + 2;
            }
		}
	}


}

//--------------------------------------------------------------
void testApp::draw(){

	/// draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetColor(0xffffff);
    bgImage.draw(0,0);


    int w = grayImage.width;



    if (DBG_DISPLAY) {

        /// muestra video original
        colorImg.draw(ofGetWidth()-320, ofGetHeight()-240);


        /// MUESTRA REGLA PARA UBICAR POSICIÓN DE PIXELES
        for (int ReglaY = 0; ReglaY < ofGetHeight(); ReglaY+=20) {
            char ReglaStr[255] ="\0"; // an array of chars
            ofSetColor(0x666666);
            ofLine(0,ReglaY,ofGetWidth(),ReglaY);
            sprintf(ReglaStr, "%i", ReglaY);
            ofSetColor(0x000000);
            verdana.drawString(ReglaStr, 10,ReglaY-5);
        }


        /// Recuadro de video
        ofSetColor(0xABABAB);
        ofRect(personajePosInicialX,personajePosInicialY,videoWidth*videoScale,videoHeight*videoScale);

        /// EN EL VIDEO MUESTRA REGLA PARA UBICAR POSICIÓN DE PIXELES
        for (int ReglaY = personajePosInicialY; ReglaY < personajePosInicialY+videoHeight*videoScale; ReglaY+=20) {
            char ReglaStr[255] ="\0"; // an array of chars
            ofSetColor(0x666666);
            ofLine(personajePosInicialX-20,ReglaY,personajePosInicialX+videoWidth*videoScale+40,ReglaY);
            sprintf(ReglaStr, "%i", ReglaY-personajePosInicialY);
            ofSetColor(0x000000);
            verdana.drawString(ReglaStr, personajePosInicialX-20,ReglaY-5);
        }

        //personajeTopY = (int)(j*videoScale) + personajePosInicialY;
        //personajeTopYf = (float)((j*videoScale) + personajePosInicialY);

        /// Recuadro de datos:
        ofSetColor(0xFFFFFF);
        ofRect(ofGetWidth()-240,30,200,300);

        verdana.drawString("\nPersonaje Top:",ofGetWidth()-200,110);
        char fpsStr[255] ="\0"; // an array of chars
        ofSetColor(0x000000);

        //sprintf(fpsStr, "\nj: %i ", j);
        //verdana.drawString(fpsStr, 600,140);


        sprintf(fpsStr, "\nPersonaje y: %i ", personajeTopY);
        verdana.drawString(fpsStr, ofGetWidth()-200,160);

        sprintf(fpsStr, "\nPantalla height: %i ", ofGetHeight());
        verdana.drawString(fpsStr, ofGetWidth()-200,180);

        /// Línea de top
        ofLine(0,personajeTopYf,ofGetWidth(),personajeTopYf);


    }




    /** Se recorre cada pixel del video después de ejecutar Canny, así que sólo hay blanco y negro (0 o 255) y esto aplica
    para los tres colores (r,g,b), así que con verificar uno es suficiente (en este caso trabajamos con r)
    **/
    for (int j = 0; j < videoHeight; j++) {
        for (int i = 1; i <  videoWidth; i++) {

			/** color **/
			//unsigned char r = pixels[(j * videoWidth/videoScale + i)*3];
			//unsigned char g = pixels[(j * videoWidth/videoScale + i)*3 + 1];
			//unsigned char b = pixels[(j * videoWidth/videoScale + i)*3 + 2];


			///gray scale
			unsigned char r = pixels[(j * videoWidth + i)];
			//unsigned char g = pixels[(j * videoWidth + i) + 1];
			//unsigned char b = pixels[(j * videoWidth + i) + 2];

			/// ¿hay color? (podría ser r, g o b, todos traen 0 o 255)
			if (r!=0) {
                ofSetColor(20,10,10);
                ofRect(personajePosInicialX + i*videoScale - videoScale/2, personajePosInicialY + j*videoScale - videoScale/2, videoScale, videoScale);
            }
		}
	}



	///define color para la letra
	///ciclo que recorre letra por letra y la dibuja en la posici—n en la que se encuentra.
    for (int j = 0; j < numLetras; j++) {

        if ((DBG_DISPLAY) && (j==DBG_FONT)) {
            verdana.drawString("Letras:",ofGetWidth()-200,40);
            char fpsStr[255] ="\0"; // an array of chars
            ofSetColor(0x000000);

            sprintf(fpsStr, "PosLetrasY: %f", PosLetrasY[j] + letrasPosInicialY);
            verdana.drawString(fpsStr, ofGetWidth()-200,60);

            ofSetColor(0xFFFFFF);
            ofCircle(letrasPosInicialX + PosLetrasX[j],PosLetrasY[j] + letrasPosInicialY,letraRadio+Velocidad[j]);


        }
        ofSetColor(40,20,20);
        Letra[0] = Letras[j];
        BookFont.drawString(Letra, letrasPosInicialX + PosLetrasX[j], letrasPosInicialY + PosLetrasY[j]);
    }


}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	switch (key){
	    case ' ':
            if (!DBG_DISPLAY) {
                DBG_DISPLAY=true;
            } else {
                DBG_DISPLAY=false;
            }
            break;
		case 'a':
			lowThresh ++;
			if (lowThresh >255) lowThresh = 255;
			break;
		case 'z':
			lowThresh --;
			if (lowThresh < 0) lowThresh = 0;
			break;
		case 's':
			lowThresh ++;
			if (lowThresh >255) lowThresh = 255;
			break;
		case 'x':
			lowThresh --;
			if (lowThresh < 0) lowThresh = 0;
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

