**********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************
**********************************************************************************************************************************************************************
RobocraneOpcControl 
**********************************************************************************************************************************************************************
Das Programm dient als Schnittstelle zwischen Kran und Mensch. Es verfügt über eine GUI. Die Kommunikation passiert über OPC und TcpIP. Die SPS fungiert dabei als Server. Derzeit ist keine Sicherheit implementiert. Das Programm ist als absoluter Prototyp zu verstehen. Es darf nur unter Aufsicht von geschultem Personal verwendet werden. Es können unvorhersehbare Bewegungen des Krans ausgelöst werden, welche eine Gefahr für Sachen sowie Leib und Leben darstellen können. Ein Notaus muss in direkter Nähe des Bedieners sein. Jegliche Haftung durch die Verwendung dieses Programms wird ausgeschlossen. 

RoboraneOpcControl schickt Soll-Gelenkspositionen an die SPS. Die SPS hat die Steuer- und Regelung der Aktoren inne. Die SPS schickt die Ist-Gelenkspositionen an RobocraneOpcControl. 

Neben der SPS ist RobocraneOpcControl über das TcpIP Protokoll mit dem Laserscanner verbunden um die Laserscandaten aufzunehmen.

Aufbau der OPC Verbindung: Statusleiste/Verbindungen/Verbinde mit SPS
Aufbau der Verbindung zum Laserscanner: Statusleiste/Verbindungen/Verbinde mit Laserscanner


**********************************************************************************************************************************************************************
﻿TeachIn
**********************************************************************************************************************************************************************
TeachIn ist eine Funktion um den Kran manuell zu steuern und bestimmte Positionen des Krans als Wegpunkte eines Pfads zu speichern. Die Wegpunkte dieses Pfades können dann automatisch, aufeinanderfolgend angefahren werden. Der Pfad ist ein 2-dimensionales Array, die Spalten stellen die 8 Freiheitsgrade dar, die Zeilen die Wegpunkte.

Ablauf TeachIn:
1) „TeachIn On/Off“ aktivieren
2) Kran in gewünschte Position bringen. Mit der Fernbedienung oder im Kran sitzend. 
3) Mit „Wegpunkt speichern“ Kranposition/Pose speichern. Hinweis: alle Achsen beachten (Schaufel, Hochsteller nicht vergessen)
4) In der UI zeigt das Feld „Wegpunkt Nr.“ die Nummer des als letzten gespeicherten Wegpunkt an.
5) Mit „Greifpunkt speichern“ wird in Abhängigkeit von der momentanen Position eine ganze Reihe an Wegpunkten am Ende des Pfades gespeichert. Siehe dazu die Erläuterung unten.
6) Es können momentan maximal 245 Wegpunkte gespeichert werden. (OHNE die Greifroutine am Pfadende)
7) „TeachIn On/Off“ deaktivieren und TeachIn damit abschließen.
8) Nun können alle Wegpunkte des Pfades im Reiter „Pfad konfigurieren“ betrachtet, überprüft und geändert werden. Siehe dazu „Pfad konfigurieren“.

**********************************************************************************************************************************************************************
Greifpunkt speichern – Routine
**********************************************************************************************************************************************************************
Dies ist eine rudimentäre Möglichkeit, abhängig von einer Kranpose/-position, eine Greifroutine für Hackschnitzel dem Pfad hinzuzufügen. Dazu werden die letzten Wegpunkte des Pfades (247..254) beschrieben. Dieser Bereich ist für die Greifroutine reserviert und kann nicht vom TeachIn überschrieben werden. 

Es gibt zwei Möglichkeiten in der GUI die Greifroutine in den Pfad zu schreiben. 
A) Im Reiter „TeachIn“ mit dem Knopf „Greifpunkt speichern“. Hier ist die momentane Position des Kranes der Greifpunkt/Greifpose.
B) Im Reiter „InvKine berechnen“ mit dem Knopf „Greifpunkt in Pfad speichern“. Hier ist die aus der Inverskinematik berechnete Pose der Greifpunkt/Greifpose.

Was passiert nun, Beschreibung der Greifroutine: 
1) Die jeweilige Referenz Pose/Position des Krans mit den Werten aller Freiheitsgrade wird als Basis genommen um eine Greifroutine zu berechnen. Dabei werden die letzten 7 Wegpunkte des Pfades mit den Werten der Referenz Pose/Positition beschrieben (Nr. 247..254). Nr. 255 bleib immer leer, da die Pfadsteuerung damit das Ende des Pfades erkennt.
2)  Nun werden einzelne Freiheitsgrade neu berechnet und im Array überschrieben. Die Erläuterung der Wps ist nach folgendem Schema aufgebaut:

WPxy:
I)Achsen, die sich von der Referenzposition unterscheiden sind angeführt
II) Beschreibung des Vorganges

WP 247: 
I) Kran 0° ausgerichtet,, Hub auf „hubHighestPoint“, Ausleger auf 370 cm, Schaufel geöffnet 
II) Kran befindet sich in bekannter sicherer Anfangs=Endpose. Wird mit dem TeachIn ein Ablauf geteacht, bspw. der Abwurf der Hackschnitzel über dem Einzugsloch, ist der WP 247 der erste Wegpunkt bzw. eine definierte, bekannte und „sichere“ Pose nach dem „TeachIn“.

WP 248: 
Hub auf „hubHighestPoint“, Ausleger auf 370 cm, Schaufel geöffnet
Kran schwenkt auf Greifpunktwert

WP 249: 
Hub auf „hubHighestPoint“, Schaufel geöffnet
Ausleger wird ausgefahren auf Greifpunktwert

WP 250: 
Hub auf Greifpunktposition * „liftRatioDown“, Schaufel geöffnet
Arm wird gesenkt, und zwar tiefer als der Greifpunktwert, da die Schaufel ja „in den Hackschnitzelberg eintauchen“ soll und bei wiederholtem Greifen ohne neuen Geifpunkt immer weiter senken und greifen soll. Die Positon ist erreicht (posOk[3]=true), wenn der Sollwert des Hubs erreicht ist, oder wenn der Druck über den Grenzwert „druckHubMax“ des Zylinders steigt. (auf der SPS) Dies passiert, wenn die Schaufel gegen die Hackschnitzel/gegen den Boden gedrückt wird. Damit kann auf Druck „in den Haufen“ gegriffen werden. 

WP 251: 
Hub auf Greifpunktposition * „liftRatioDown“, Schaufel geschlossen.
Die offene Schaufel „im Hackschnitzelberg“, wird nun geschlossen. Die Schaufel wird oft nicht vollständig geschlossen, da sich die Hackschnitzel verkeilen. Dazu WP 252

WP 252: 
Schaufel geschlossen
Die Schaufel wird weiter geschlossen und der Arm auf Greifpunktposition angehoben. Nun sollte sich die Schaufel vollständig schließen.

WP 253: 
Hub auf „hubHighestPoint“, Ausleger auf 420 cm, Schaufel geschlossen
Arm wird angehoben und der Ausleger auf 420cm eingefahren. Welcher Freiheitsgrad sich zuerst bewegt oder wie die Bewegung genau stattfindet, ist ungewiss (2-Freiheitsgrade).

WP 254: 
Kran 0° ausgerichtet,, Hub auf „hubHighestPoint“, Ausleger auf 370 cm, Schaufel geschlossen 
Kran dreht sich zurück auf die sichere Anfangs-/Endpose. Bei zyklischer Pfadsteuerung, wird nach diesem bekannten WP 254 wieder WP 0 der Pfadsteuerung angefahren.

**********************************************************************************************************************************************************************
Pfad konfigurieren
**********************************************************************************************************************************************************************
Der Reiter „Pfad konfigurieren“ der GUI bietet die Möglichkeit 
a) den aktuellen Pfad des Arrays anzuzeigen (Statusleiste/Pfad anzeigen/Pfad des Arrays)
b) einen Pfad einer .csv Datei anzuzeigen (Statusleiste/Pfad anzeigen/CSV Datei auswählen)
c) den angezeigten Pfad zu ändern, die Spalten 1..8 sind  die Freiheitsgrade, die Zeilen 1..256 die Wegpunkte. Zu beachten ist, dass die Spalte und Zeilen der Tabelle jeweils mit 1 beginnen, das Array beginnt mit 0. z.B. ist posSollValue[0] der Positionsvorgabewert der Längsfahrt. In der Tabelle entspricht die Spalte 1 statt 0 der Längsfahrt.
d) Der in der Tabelle angezeigte Pfad kann als aktiver Pfad ins Array gespeichert werden. (Tabelle als Pfad ünbernehmen) Bspw. läd man einen Pfad aus einem .csv File in die Tabelle, verändert diesen bei Bedarf und speichert diesen in das Array ab.
e) Der in der Tabelle angezeigte Pfad kann auch dauerhaft als .csv File abgspeichert werden.

**********************************************************************************************************************************************************************
Laserscanner
**********************************************************************************************************************************************************************
Der Reiter „Laserscanner“ der Gui bietet die Möglichkeit
a) den Speicherort für die Laserscandaten festzulegen (Speicherort festlegen)
b) einen einzelnen Messfächer in das gewähle File zu speichern (Messfächer speichern)
c) einen Bereich zu scannen (von „xxx“ bis „xxx“, Bereich scannen)
	I)  ohne Posenprüfung	
Nach Bestätigung der Warnung, dass sich der Kran in Bewegung setzen wird, fährt dieser an 	den Startpunkt. Dort angekommen, beginnt die Aufnahme der Laserscandaten und der Kran fährt zum Ziel. Dort angelangt, wird die Aufnahme der Laserscandaten gestoppt. Im Feld „letzter Scan tatsächlich ab“ wird die tatsächliche Startposition des Scanvorganges in cm angezeigt. Durch die Hysterese bei der Positionierung entspricht das nicht immer genau dem eingestellten Scanbereich.
	II) mit Posenprüfung
	Der Kran wird vor der Fahrt zum Startpunkt in Scanpose gebracht. 
		i)  Der Ausschub wird eingezogen.
		ii) Der Arm wird auf „scanFromHub“ gesenkt oder gehoben.
		iii)Der Kran schwenkt auf 0°.
		iv)Dann Ablauf wie I) ohne Posenprüfung

**********************************************************************************************************************************************************************
Greifpunkt berechnen
**********************************************************************************************************************************************************************
Der Reiter "Greifpunkt berechnen" bietet die Möglichkeit aus Laserdaten welche in einem Logfile gespeichert sind
a) den Greifpunkt zu berechnen (Laserdaten auswählen --> Greifpunkt berechnen)
b) das Oberflächenprofil des gescannten Bereichs darzustellen
c) das Histogramm anzuzeigen
d) die Parameter für die Verarbeitung der Laserscandaten festzulegen

Der berechnete Greifpunkt wird unten ausgegeben. Momentan stürtzt das Programm ab, wenn die Parameter nicht zu den Laserscandaten passen / die Berechnungsfunktion einen Fehler hat / das Logfile fehlerhaft ist.
Der "tatsächliche Startpunkt" des Scans, welche im Reiter "Laserscanner" unten angegeben wird, wird noch nicht beachtet. Startpunkt ist für die derzeitige Berechnungsfunktion immer 0.

**********************************************************************************************************************************************************************
Inverskinematik berechnen
**********************************************************************************************************************************************************************
Der Reiter "InvKine berechnen" bietet die Möglichkeit 
a) 
aus dem Greifpunkt XYZ die notwendigen Gelenksstellungen zu berechnen. Die Berechnung nimmst die SPS vor. Durch drücken der Taste "Inverskinematik berechnen" wird der XYZ Punkt an die SPS übertragen und die berechneten Gelenksstellungen gelesen. 
b)
die berchneten Gelenksstellungen als SollPosition an den Kran zu senden. Der Kran fährt dann auf direktem Weg den Punkt an. Alle Freiheitsgrade auf einmal, keine Logik.
c) 
der berechnete Greifpunkt kann als Greifroutine in den Pfad gespeichert werden. Siehe dazu "Greifpunkt speichern – Routine" weiter oben.




