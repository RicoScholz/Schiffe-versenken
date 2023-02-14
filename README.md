# Schiffeversenken
***
## Anwenderdokumentation

Das Spiel "Schiffe Versenken" ist für ein Spieler gedacht, der gegen einen Bot spielt.

### Spielregeln:
1. Jeder Spieler besitzt 6 Schiffe.
2. Schiffe durfen nicht nebeneinander oder diagonal gesetzt werden.
3. Spieler und Bot schiessen abwechselnd, außer wenn einer vom beiden trifft, dann kommt derjenige nochmal dran und darf so lange schiessen bis er verfehlt.
4. Das Spiel wird beendet wenn einer von den Teilnehmern keine Schiffe mehr besitzt.

### Features:
1. Automatische Platzierung der Schiffe
2. Bot als Gegner
3. Koordinateneingabe für den Spieler
4. Scoreboard für den Spieler und den Bot
5. Eingabevaliedierung
6. Endscreen am Ende des Spiels
7. Farben unterscheidung 

## Entwicklerdokumentation

### Technische Umsetzung:
1. Es wird zufällig ausgewählt wer beginnen darf.
2. Jedem Spieler wird ein zweidimensionaler interger Array zugeordnet, welches den Status jedes Feldes angibt. 
     ```
    0 = Leer
    1 = Schiff
    2 = Treffer
    3 = Wasser (kein Treffer)
    ``` 
   Die Spielfelder werden alle mit den Status "0" initialisiert.
3. Darauffolgend wird die Funktion zur Generierung und Platzirung der Schiffe aufgerufen. Es wird erstmal einen zufälligen Koordinaten im Spielfeld ausgewählt, die Richtung des Schiffs wird ausgewählt und es wird geguckt ob die Felder für die Platzierung geeignet sind. Wenn ein Feld nicht geeignet ist wird das ganze Schiff nicht platziert. 
4. Score Anzeige wird generiert.
5. Wenn der Spieler dran ist wird er dazu aufgefordert die Koordinaten einzugeben an dem es geschossen werden soll bzw. es soll an den Koordinaten gecheckt werden was für ein Status des Feld hat. Falls dessen Status "0" (Leer) ist, wird es auf "3" (Wasser bzw. kein Treffer) gesetzt und die Runde wird gewechselt. Falls dessen Status "1" (Schiff) ist, wird es auf "2" (Treffer) gesetzt und der Spieler wird nochmal aufgefordert die Koordinaten einzugeben.
6. Gleichen Prizip wenn der Bot dran ist. Die Koordinaten X & Y werden zufällig zwischen 0-9 ausgewählt. 
7. Das Ganze wird dann in der Funktion "showBoards" formatiert und in der Konsole angezeigt.
