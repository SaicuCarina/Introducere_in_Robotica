# Introducere_in_Robotica

Acest repositoy contine temele si lucrarile de laborator realizate in cadrul cursului de "Introducere in Robotica" anul 2023-2024 de la Facultatea de Matematica si Infoarmatica din Bucuresti.

# Tema 2

Cerinta:
Trebuie sa controlam fiecare culoare (rosu, verde si albastru) de la un led RGB folosind potentiometre pentru fiecare culoare in parte.

Ce am folosit:
- 1 led RGB
- 3 potentiometre
- 3 rezistente de 330Ω
- 17 fire

Cum am facut:
1. Am facut mai intai un circuit mai simplificat. Am facut ledul RGB sa se aprinda cu fiecare culoare cu un delay de o secunda.
2. Am conectat si potentiometrele si am combinat codul de la subpunctul 1 cu codul de la laborator.
3. In final am modificat codul pentru a fi unul eficient si bine structurat.

Poza:
![WhatsApp Image 2023-10-24 at 21 58 03](https://github.com/SaicuCarina/Introducere_in_Robotica/assets/93483071/0e5dc23d-cf1e-4c16-8162-a00d6621803b)

Link youtube:
https://www.youtube.com/watch?v=3huVZrHhmkI&ab_channel=CarinaSaicu

# Tema 3

Cerinta:
Trebuie sa simulam un lift cu 3 etaje cu leduri, butoane si un buzzer, folosind Arduino.

Ce am folosit:
- 3 led-uri rosii (pentru fiecare etaj in parte)
- 1 led albatru (pentru a simula cum se misca liftul)
- 1 buzzer
- 4 rezistente de 330Ω (pentru fiecare led)
- 1 rezistenta de 100Ω (pentru buzzer)
- 15 fire

Cum am facut:
1. Construirea circuitului:
   - am conectat mai intai un singur led si un singur buton si am facut ledul sa se aprinda cand se apasa butonul
   - am conectat si restul de leduri si restul de butoane si am facut sa se aprinda ca la liniuta anterioara
   - dupa am continuat cu scrierea codului, fara sa conectez buzzer-ul
   - dupa ce am facut beculetele sa lumineze ca in cerinta, am conectat si buzzer-ul
2. Scrierea codului:
   - am facut 3 functii, 2 pentru led-ul care clipeste cand liftul e in miscare si sta aprins cand liftul nu se misca
   - cealalta functie e cea de Start
   - am luat codul de la laborator ca exemplu pentru debounce-ul butonului
   - am scris codul de la debounce pentru fiecare dintre cele trei butoane
   - am facut un switch cu 2 case-uri
   - 0 - liftul sta, 1- liftul se misca
   - in case-ul pentru liftul in miscare am veridicat toate variantele care sunt pentru cele 3 etaje (adica daca led-ul e aprins sau stins), daca era aprins verificam daca a fost apasat un buton de la un alt etaj
   - daca apasam pe butonul de la etajul la care suntem buzzer-ul scoate un sunet
   - daca nu, incepem miscarea spre etajul la care vrem sa ajungem

Poza:
![WhatsApp Image 2023-10-31 at 21 46 32](https://github.com/SaicuCarina/Introducere_in_Robotica/assets/93483071/57510fc4-b7ea-4925-9309-6faccb8a04a5)

Link youtube:
https://youtu.be/hsJig2XF8-s


