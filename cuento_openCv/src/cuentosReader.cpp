//
//  cuentosReader.cpp
//  cuentosFil
//
//  Created by Ra Acosta on 5/19/12.
//  Copyright 2012 Bossacorp. All rights reserved.
//

#include "cuentosReader.h"
ofxXmlSettings cuentosXmlFile;

void setup()
{
    
    if (cuentosXmlFile.loadFile("cuentoSettings.xml"))
    {
        ofLogError("++++ No abrio el archivo XML con el cuento");
        
    }
}

string getNombreDelCuento()
{
    
}
void setNombreDelCuento()
{
    
}

string getNextLine()
{
    ofxXmlSettings cuentosXmlFile;
    if (!cuentosXmlFile.loadFile("cuentoSettings.xml"))
    {
        ofLogError("++++ No abrio el archivo XML con el cuento");
        
    }else
    {
        string lineToReturn;
        lineToReturn = cuentosXmlFile.getValue("cuento:linea","");
        return lineToReturn;
    }
}
bool isEndOfBook()
{
    
}
