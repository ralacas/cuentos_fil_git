#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	franklinBook.loadFont("frabk.ttf",12);

    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(640, 480);

    colorImg.allocate(640, 480);
	grayImage.allocate(640, 480);
	grayBg.allocate(640, 480);
	grayDiff.allocate(640, 480);

	bLearnBakground = true;
	threshold = 80;
	
	bimgGris = false;
	
	posXfinal = 0; 
	posYfinal = 0;
	
	//Inicializacion de las letras
	numLetrasAbajo = 0;
	
	//valor inicial, no sirve de nada.
	numLetras = 0;
	

	/// LECTURA DE ARCHIVO PARA CUENTO
	 cuentoStream.open( ofToDataPath("cuento1.txt").c_str() ); //open your text file
	 if (cuentoStream == NULL)
	 {
		 sprintf(infoArchivoStr, "Error, archivo no abierto");
	 }
	 else
	 {
		 sprintf(infoArchivoStr, "Archivo abierto");
		 
		 
		 string str; //declare a string for storage
		 getline(cuentoStream, str); //get a line from the file, put it in the string
		 for (int a=0;a<=str.size();a++)
		 {
			 Letras[a]=str[a];
		 }

		 //cuantas letras contiene el primer rengl�n?
		 numLetras = strlen(Letras);
	
		 //ciclo para inicializar la posici�n de cada letra hasta arriba de la pantalla as� como su velocidad de caida.
		 int posi = 0;
		 for (int j = 0; j < numLetras; j++)
		 {
			 if (Letras[j-1] == 'i' || Letras[j-1] == 'l' || Letras[j-1] == 'j' )
			 { //estas letras requieren mucho menos espacio, cada letra que les siga debe ir desplazada menos pixeles.
				 posi = posi + 5;
			 }
			 else
			 {
				 posi = posi + 10;
			 }
			 PosLetrasX[j] = posi;  //posici�nX
			 PosLetrasY[j] = 0;     //posici�nY
			 Velocidad[j] = rand()%100;   //velocidad de caida
			 Velocidad[j]= Velocidad[j]/100 + 0.2;
		 }
	
		 //Prepara Letra para ser un str
		 Letra[1] = '\0';
	 }
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0, 0, 0);

    bool bNewFrame = false;

    vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();

	if (bNewFrame){

        colorImg.setFromPixels(vidGrabber.getPixels(), 640, 480);

        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		unsigned char * pixels = grayDiff.getPixels();  //extraemos los pixeles de cada frame de video
		//anchura y altura de la imagen captada
		int w = 640;
		int h = 480;
		
		//Obtiene el valor de cada pixel en la coordenada de las letras para checar si a�n hay algunas bajando, cuenta cuantas est�n hasta abajo ya
		numLetrasAbajo = 0;
		for (int j = 0; j < numLetras; j++)
		{
			if (PosLetrasY[j] < h)// + 10)
			{  //si a�n no llega hasta abajo
				if (pixels[(int)PosLetrasY[j] * w + PosLetrasX[j]] < 255)
				{ //Si la letra se encuentra en una zona color blanco significa que no debe continuar bajando
					PosLetrasY[j] += Velocidad[j];
				}
				else
				{
					PosLetrasY[j]--;
				}
			}
			else
			{   //si la letra lleg� hasta abajo sumamos el n�mero de letras que han llegado
				numLetrasAbajo++;
			}
		}
		
		//Si todas est�n hasta abajo significa que hay que pasar al siguiente rengl�n del cuento
		if (numLetrasAbajo == numLetras)
		{
            string str; ///declare a string for storage
            getline(cuentoStream, str); ///get a line from the file, put it in the string
			
            int posi = 0;
            for (int a=0;a<=str.size();a++) {
                Letras[a]=str[a];
				
                if (Letras[a-1] == 'i' || Letras[a-1] == 'l' || Letras[a-1] == 'j' ) {
                    posi = posi + 5;
                } else {
                    posi = posi + 10;
                }
                PosLetrasX[a] = posi;
				
                PosLetrasY[a] = 0;
                Velocidad[a] = (rand()%100);
                Velocidad[a]= Velocidad[a]/100 + 2;
            }
		}
	}
	sprintf(reportStr, "%s\nthreshold %i (presione +/-)\nfps: %f", infoArchivoStr, threshold, ofGetFrameRate());
}

//--------------------------------------------------------------
void testApp::draw(){

	unsigned char r, g, b;
	
	//Background gris
	ofBackground(100,100,100);
	
	ofSetColor(0xffffff);
	if (bimgGris)  //alterna entre imagen gris, procesada, o imagen a color original
		grayDiff.draw(0, 0, 640, 480);
	else
		colorImg.draw(0, 0, 640, 480);
	
	//define color para la letra
    ofSetColor(0xFFFF00);
	//ciclo que recorre letra por letra y la dibuja en la posici�n en la que se encuentra.
    for (int j = 0; j < numLetras; j++)
	{
        Letra[0] = Letras[j];
        franklinBook.drawString(Letra, posXfinal + PosLetrasX[j], posYfinal + PosLetrasY[j]);
    }
	
	//muestra reporte:
	ofSetHexColor(0xffffff);
	ofDrawBitmapString(reportStr, 20, 600);	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
		case 'g':
			bimgGris = !bimgGris;
			break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


