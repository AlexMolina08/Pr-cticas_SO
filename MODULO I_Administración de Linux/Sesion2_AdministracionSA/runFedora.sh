#!/bin/bash
#Copia los archivos del S.O Fedora en /temp y lo ejecuta

fedoraRoute='/home/alex/UNI/20-21/Sistemas_Operativos/Practicas/FEDORA'

echo '\n---COPIANDO FEDORA EN /tmp---\n'
cp $fedoraRoute/*.gz /tmp
gunzip /tmp/*.gz
cd /tmp
chmod u+x kernel32-3.0.4
echo '\n---EJECUTANDO FEDORA---\n'
./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m

