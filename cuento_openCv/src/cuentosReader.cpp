//
//  cuentosReader.cpp
//  cuentosFil
//
//  Created by Ra Acosta on 5/19/12.
//  Copyright 2012 Bossacorp. All rights reserved.
//

#include "cuentosReader.h"

/*
@ralacas 19-jun-2012
Este archivo carga el cuento y establece los valores iniciales
 TODO: deberìa aqui mejor usar el constructor. investigar
*/
void cuentosReader::setup()
{
    if (!cuentosXmlFile.loadFile("cuentoSettings.xml"))
    {
        ofLogError("++++ No abrio el archivo XML con el cuento");
    }
    else
    {
        cuentosXmlFile.pushTag("cuento");
        
        numeroTotalDeLineas = cuentosXmlFile.getNumTags("linea");

        nombreDelCuento = cuentosXmlFile.getValue("titulo","");
        
        actualLineNumber = cuentosXmlFile.getAttribute("linea","id",0);
        
        lineaActual = cuentosXmlFile.getValue("linea","",actualLineNumber);
        
    }
}

/*
 @ralacas 19-jun-2012
 Aqui devolvemos el nombre del cuento
 */
string cuentosReader::getNombreDelCuento()
{
    return nombreDelCuento; 
}

/*
 @ralacas 19-jun-2012
 Devolvemos siempre la linea siguiente del cuento
 */
string cuentosReader::getNextLine()
{
    if(actualLineNumber < numeroTotalDeLineas)
    {
        lineaActual = cuentosXmlFile.getValue("linea","",actualLineNumber);
        actualLineNumber ++;
        return lineaActual;
    }
    else
    {    
        return lineaActual;
    }
}

/*
 @ralacas 19-jun-2012
 Devuelve true si se alcanzo el final del cuento
 */
bool cuentosReader::isEndOfBook()
{
    return (actualLineNumber == numeroTotalDeLineas);
    
}
