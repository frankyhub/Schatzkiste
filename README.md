<a name="oben"></a>

# Schatzkiste

Mit diesem Projekt wird eine Schatzkiste gebaut, die sich mit dem Betätigen von vier Tasten in der 
richtigen Reihenfolge öffnen lässt. Wird eine Taste betätigt, leuchtet die darüber liegende LED. 
Ist der Tasten-Code richtig eingegeben, gehen die vier weißen LEDs über den Tasten aus, eine grüne 
LED leuchtet und die beiden Servo-Motoren öffnen den Verschluss. Ist die Schatzkiste geöffnet, kann mit jeder 
beliebigen Taste die Schatzkiste wieder verschlossen werden. Ist der Code falsch eingegeben, erlöschen 
die vier LEDS und die Schatzkiste bleibt verschlossen.
Im inneren der Schatzkiste ist ein Reed-Kontakt versteckt. Nur der Eigentümer der Schatzkiste weiß, 
wo sich der Reed-Kontakt befindet. Wird an diesen Reed-Kontakt ein Magnet gehalten, blinken die vier 
Taster-LEDs und der Code kann neu programmiert werden. Nach erfolgreicher Programmierung blinken die 
vier Taster-LEDs erneut. Der Code wird in das EEPROM des NANO geladen, so dass auch bei Spannungsausfall 
der Code erhalten bleibt.

Die Schatzkiste

![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/Schatzkiste.png)

---

## Hardware
Die Stückliste für die Schatzkiste:

+ 1 x NANO
+ 1 x NANO-Shield
+ 2 x Buchsenleisten
+ 2 x Stiftleisten
+ 2 x Servo Motore SG90
+ 2 x 90° Verschluss Winkel
+ 1 x Reed-Kontakt mit Magnet
+ 4 x Taster
+ 4 x LEDs weiß
+ 1 x LED grün
+ 5 x 1kOhm Widerstand
+ 1 x 9V Batterie
+ 1 x 9V Batterie-Clip
+ 1 x Gelaserte Schatzkiste (4mm Sperrholz 600x300)

---


## Aufbau und Montage
Der Aufbau und die Montage der Schatzkiste ist in mehrere Schritte unterteilt.


## Schritt 1: Das Gehäuse
+ Erstelle auf Boxes.PY  eine "Kiste mit eingebundenen Schanier" mit den Abmessungen x=160, y=100 und h=80, Deckelhöhe 28.
+ Füge in die erstellte SVG-Grafik die Löcher für die LEDs und Taster ein
+ Füge in die erstellte SVG-Grafik deine Grafik für die Verziehrung der Schatzkiste ein
+ Schneide das Gehäuse mit dem Lasercutter aus
+ Klebe die Servo-Motoren in den Gehäusedeckel
+ Klebe die Winkel an die Frontplatte
+ Klebe den Reed-Kontakt in das Gehäuse
+ Montiere die LEDs und die Taster an die Gehäuse-Front
+ Verklebe die Gehäuseteile. Die untere Rückwand wird nicht verklebt

![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/schatzkiste_lk.png)


---

## Schritt 2: 3D-Druck
+ Zeichne und drucke 4 Platinen Füße für den NANO, D=5mm x 5mm
+ Klebe die Füße auf die Unterseite des NANO-Shields

![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/spacer5mm.png)


---

## Schritt 3: Verdrahtung und Lötarbeiten
+ Bestücke das NANO-Shield mit den Buchsenleisten und den beiden Stiftleisten für die Servo-Motore
+ Biege an einem Ende der Widerstände und am +Pol der LEDs eine Öse

![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/r-led.jpg)


Führe Anschlussdrähte für die Widerstände und der LEDs durch die Öse und Löte sie an

![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/sk10.png)


![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/sk10.png)


![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/sk12.png)


![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/sk13.png)


Verdrahte das Shield, die LEDs, Taster und den Reed-Kontakt nach den Verdrahtungsplan

![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/Shield.png)


![Schatzkiste](https://github.com/frankyhub/Schatzkiste/blob/main/pic/Verdrahtung.png)


---

## Schritt 4: Inbetriebnahme
+ Kontrolliere alle Verbindungen
+ Lade das Servo-Test Programm in den NANO
+ Versorge die Schatzkiste mit Spannung
+ Teste den Verschluss-Mechanismus mit den Servo-Motoren
+ Wenn der Verschluss ok ist, lade das Haupt-Programm in den NANO
+ Das Programm befindet sich auf deinen Laptop unter Nextcloud/Schatzkiste
+ Aktiviere mit einen Magneten über den Reed-Kontakt die Programmierung des Codes
+ Gibt über die Taster deinen Code ein
+ Teste deinen Code
+ Ist der Code richtig, öffen die Servo-Motor die Verschluss-Einrichtung

---

<div style="position:absolute; left:2cm; ">   
<ol class="breadcrumb" style="border-top: 2px solid black;border-bottom:2px solid black; height: 45px; width: 900px;"> <p align="center"><a href="#oben">nach oben</a></p></ol>
</div>

---
  

