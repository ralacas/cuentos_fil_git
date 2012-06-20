/*
//  cuentosReader.h
//  cuentosFil
//
//  Created by Ra Acosta on 5/19/12.
//  Copyright 2012 Bossacorp. All rights reserved.
//
//  Esta clase sirve para manipular el archivo XML que es un cuento y devolver la información necesaria para 
//  usarlos en el espacio
//*/

#include "ofxXmlSettings.h"
#include "ofMain.h"

class cuentosReader{
public:    
    ofxXmlSettings cuentosXmlFile;
    string nombreDelCuento;
    string lineaActual;
    bool endOfBook;
    int actualLineNumber;
    int numeroTotalDeLineas;
    
    //Constructor y destructor
    cuentosReader(){};
    //~cuentosReader();
    
    string getNombreDelCuento();
    
    string getNextLine();
    bool isEndOfBook();
    void setup();
};
