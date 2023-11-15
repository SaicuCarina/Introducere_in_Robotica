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
