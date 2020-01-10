# Memory Test

Acest proiect isi propune crearea unui joc de testare a **memoriei** vizuale, de scurta durata.

# Installation

Pentru a putea testa acest proiect, e nevoie de Arduino [IDE](https://www.arduino.cc/en/main/software), de componentele prezentate in [documentatie](https://github.com/georgiannechifor/Memory-Test/blob/master/Documentation.docx?raw=true) in Figura 1 si de o telecomanda prin care se vor trasmite datele de la utilizator catre program.

# How it works?

Dupa incarcarea [codului](https://github.com/georgiannechifor/Memory-Test/blob/master/proiectPMP.ino) pe placa Arduino si conectarea componentelor la aceasta, pe afisor vor aparea 5 numere generate in mod aleator care vor trebui memorate pentru ca mai apoi, sa fie tastate cu ajutorul telecomenzii. In timp ce utilizatorul introduce numere, pe afisor va aparea tasta apasata pe telecomanda. In urma introducerii numerelor, exista doua posibilitati:
1. Numerele introduse au fost corecte, caz in care se vor genera alte 5 numere iar scorul se va incrementa cu 1 (scorul va fi afisat inainte de generarea numerelor)
2. Numere introduse au fost gresite, caz in care se va afisa numarul 0 si vor fi afisate din nou cele 5 numere.

