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
   - in case-ul pentru liftul in miscare am verificat toate variantele posibile pentru cele 3 etaje (adica daca led-ul e aprins sau stins), daca era aprins verificam daca a fost apasat un buton de la un alt etaj
   - daca apasam pe butonul de la etajul la care suntem buzzer-ul scoate un sunet
   - daca nu, incepem miscarea spre etajul la care vrem sa ajungem

Poza:
![WhatsApp Image 2023-10-31 at 21 46 32](https://github.com/SaicuCarina/Introducere_in_Robotica/assets/93483071/57510fc4-b7ea-4925-9309-6faccb8a04a5)

Link youtube:
https://youtu.be/hsJig2XF8-s

# Tema 4

Cerinta:
Trebuie sa folosim un joystick pentru a controla pozitia pentru fiecare segment in parte a unui display cu 7-segmente. Mutarea dintre segmente trebuie sa fie naturala, doar intre vecini.

Ce am folosit:
- 1 7-segment display
- 1 joystick
- 8 rezistente de 330Ω (pentru fiecare segment in parte)
- 1 rezistenta de 100Ω (pentru buzzer)
- 1 buzzer
- 20 de fire

Cum am facut:
1. Construirea circuitului:
   - initial am folosit circuitul construit in laborator pentru care am scris codul pentru tema
   - dupa ce am facut codul, am adaugat un buzzer care scoate un sunet cand este apasat butonul de la joystick
3. Scrierea codului:
   - am avut 3 functii
   - functia de blink care face ca segmentul pe care ne aflam sa pulseze
   - functia reset care imi reseteaza toate variabilele pentru a reincepe de la segemntul punct
   - functia directionFunct care verifica cum se misca joystick-ul pentru a modifica locul curent si a trece mai departe la urmatorul segment
   - in loop am apelat functia blink, am facut debounce-ul pentru buton unde am integrat si resetul daca am apasat lung pe buton, iar in final am apelat functia directionFunct

Poza:
![WhatsApp Image 2023-11-07 at 22 36 21](https://github.com/SaicuCarina/Introducere_in_Robotica/assets/93483071/c8762a6a-3bf1-444e-ac6b-fe6f70750396)

Link youtube:
https://youtu.be/wclejsGUcd4

# Tema 5

Cerinta: 
Trebuie sa implementam un stopwatch timer cu un 4 digit 7-segment disply si 3 butoane, care ar trebui sa functioneze ca un cronometru de pe telefon. 
Primul buton are varianta de start si stop.
Al doilea buton reseteaza cronometrul.
Al treilea buton retine numarul curent de pe display.

Ce am folosit:
- 1 4 digit 7-segment display
- 3 butoane
- 1 shift register: 74HC595
- 8 rezistente de 330Ω
- multe fire

Cum am facut:
- am inceput cu circuitul facut in laborator la care nu am adaugat nimic nou
- m-am folosit de codul din laborator pe care l-am modificat initial pentru a numara bine secundele
- initial am facut functia reset mai simpla, adica doar sa imi afiseze 000.0 (starea initiala)
- am facut functia de stopwach si am facut functional doar butonul de start/stop
- le-am legat cu butonul de reset ca sa functioneze si el
- in final am implementat si butonul de save care imi salveaza lap-urile intr-un array, cand am facut asta a trebuit sa modific multe in codul de la functia reset, deoarece cu cel initial nu erau vizibile numerele din array

Poza:
![WhatsApp Image 2023-11-15 at 10 51 39](https://github.com/SaicuCarina/Introducere_in_Robotica/assets/93483071/feb88af0-264f-4729-b470-c36e873b24e6)

Link youtube:
https://youtu.be/dZcXDfWr4NY
(in video am exemplificat si ca butonul de reset nu merge cat timp cronometrul ruleaza)

# Tema 6

Cerinta: 
Trebuie sa implementam un meniu cu mai multe functionalitati, care foloseste senzori de leduri.
1. Sensor Settings
   1.1 Sensors Sampling Interval
   1.2 Ultrasonic Alert Threshold
   1.3 LDR Alert Threshold
   1.4 Back
2. Reset Logger Data
   2.1 Yes
   2.2 No
3. System Status
   3.1 Current Sensor Readings
   3.2 Current Sensor Settings
   3.3 Display Logged Data
   3.4 Back
4. RGB LED Control
   4.1 Manual Color Control
   4.2 LED: Toggle Automatic ON/OFF
   4.3 Back
   
Ce am folosit:
- 1 Arduino Uno Board
- 1 Ultrasonic Sensor (HC-SR04)
- 1 LDR (Light-Dependent Resistor)
- 1 led RGB
- 1 buzzer
- 1 rezistenta de 10MΩ
- 1 resitenta de 100Ω
- 3 rezistente de 330Ω
- multe fire

Cum am facut:
- am inceput cu circuitul, dupa ce am pus toate cele necesare din pdf, am adaugat si un buzzer
- m-am folosit de codul din laborator pentru meniu pe care l-am modificat si pentru submeniu
- primul submeniu cu care am inceput a fost 4 pentru a controla ledurile
- nu am reusit sa implementez 2 si 3
- pentru submeniul 1 m-am folosit tot de codul din laborator pentru citirea senzorilor

Poza:
![WhatsApp Image 2023-11-22 at 00 30 49](https://github.com/SaicuCarina/Introducere_in_Robotica/assets/93483071/3d727d05-2bf9-4211-b5a6-8616b0d3efbc)

Link youtube:
https://youtu.be/TtSVICl5axg

# Tema 7

Cerinta: Trebuie sa dezvoltam un joc pe o matrice de leduri 8x8. Trebuie sa avem cel putin e tipuri de elemente: player, bombe, ziduri. Eu am implementat o varianta mai usoara a jocului Bomberman.

Ce am folosit:
- 1 Arduino Uno Board
- joystick
- 8x8 LED Matrix
- MAX7219
- 1 rezistenta de 100K
- 1 rezistenta de 100Ω (pentru buzzer)
- 1 buzzer
- multe fire

Cum am facut:
- am inceput cu circuitul din laborator la care am adaugat un buzzer care face sunet cand bomba explodeaza
- mai intai am scris codul pentru generarea mapei fara sa iau in calcul prima linie ca playerul sa nu se suprapuna cu un zid
- pentru ca mapa sa fie pe 50%-75% din suprafata am facut o formula la care am folosit numarul de leduri de pe matrice
- dupa ce am realizat mapa am plasat playerul in partea din stanga sus a matricei
- mai intai am facut playerul sa se plimbe pe mapa fara ca ledul sa blikaie
- dupa ce am facut asta am modificat codul pentru ca ledul sa blinkaie
- am facut ca playerul sa nu treaca prin pereti si dupa am scris cosul pentru bombe
- in final am adaugat si sunetul la buzzer care se aude cand bomba explodeaza

Poza:
![WhatsApp Image 2023-11-29 at 11 28 20](https://github.com/SaicuCarina/Introducere_in_Robotica/assets/93483071/08d977bd-e32d-428f-8819-21f361f5eb70)

Link youtube:
https://youtu.be/vsAvKWwaPhQ

# Tema 8

Cerinta: Trebuie sa implementez un meniu pe LCD pentru jocul de la tema 7. Meniul trebuie sa contina: Start game, Settings, About.

Ce am folosit:
- 1 Arduino Uno Board
- joystick
- 8x8 LED Matrix
- MAX7219
- 1 rezistenta de 100K
- 1 rezistenta de 100Ω (pentru buzzer)
- 1 buzzer
- 1 LCD
- 1 rezistenta de 330Ω (pentru LCD)
- multe fire

Cum am facut:
- mai intai ai facut mesajul care apare pe LCD la inceput, care dureaza 3 secunde
- am facut meniul principal si navigarea pentru el
- dupa am trecut la submeniul pentru about ca mi se parea cel mai simplu de implementat
- in final am facut si cel pentru setari fara sa modific intensitatea

Poza:

Link youtube:

