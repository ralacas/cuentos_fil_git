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

class cuentosReader : public ofBaseApp{
    
    ofxXmlSettings  cuentosXml;
    string nombreDelCuento;
    bool endOfBook;
    int lineNumber;
    
public:
    
    string getNombreDelCuento();
    void setNombreDelCuento();
    
    string getNextLine();
    bool isEndOfBook();
    
    void setup();
};