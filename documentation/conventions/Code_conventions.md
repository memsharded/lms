Code-Conventions
================

Um die Struktur im Framework zu gewährleisten:
----------------------------------------------

Code-Dokumentation:
In jedes Modul:
Eine ReadMe.txt, in ihr steht:
- Wer hat es erstelllt
- Wann wurde es erstellt
- Was soll das Modul tun
In jeden Header/jedes c oder cpp file:
- Wer hat es erstellt
- Wann wurde es erstellt
- Was soll es tun
For jede Methode:
- Falls der Methodennamen nicht selbsterklärend ist (Nicht für einen selbst, sondern für jemand anderen, einen kurzen Kommentar)

Bei jedem Hack wird ein Kommentar mit der Formatierung:

    //TODO: HACK {Was er tut}

Falls die Datei unvollständig ist über die includes einen TODO-Kommentar schreiben

Code-Style
-----------
- Referenzen verwenden, Pointer nur wenn nötig.
- Siehe google-styleguide.googlecode.com/svn/trunk/cppguide.html

Git
----
- Nichts auf master pushen, nichts unkompilierbares auf public
- Branches für Funktionen (Features), nicht personen-bezogen.
- D.h. eine branch Parken, Umfeldmodell etc. Wenn diese FUNKTIONIEREN werden sie mit master gemerged. Somit ist in master immer eine vollfunktionsfähige Version.
- Das system kann für Unterpunkte äuquivalent übernommen werden. D.h. Parken -> schnelles parken als zweig (branch) -> Wenn schnelles parken funktioniert in parken mergen und wenn dort alles funktioniert in master mergen.
