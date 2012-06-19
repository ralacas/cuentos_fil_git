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

#ifndef cuento_openCv_cuentosReader_h
#define cuento_openCv_cuentosReader_h
#include "ofxXmlSettings.h"
#include "ofMain.h"

class cuentosReader : public ofBaseApp{
public:    
    ofxXmlSettings cuentosXmlFile;
    string nombreDelCuento;
    bool endOfBook;
    int lineNumber;
    
    //Constructor y destructor
    cuentosReader(){};
    ~cuentosReader();
    
    string getNombreDelCuento();
    void setNombreDelCuento();
    
    string getNextLine();
    bool isEndOfBook();
    void setup();
};

#endif