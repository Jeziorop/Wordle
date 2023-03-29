# Wordle
Wordle by Jędrzej Kolski & Joanna Zubik
///////////Rozgrywka//////////////
https://pl.wikipedia.org/wiki/Wordle
https://en.wikipedia.org/wiki/Wordle

Aktualnie modyfikowana płytka oznaczona jest obwódką.
Istnieją 2 tryby wprowadzania:
a)biała obwódka (domyślna) - po wprowadzeniu znaku lub skasowaniu obwódka przesuwa się do przodu lub tyłu
b)pomarańczowa obwódka - po wprowadzeniu znaku lub skasowaniu obwódka pozostaje w miejscu, lecz można ją wciąż przesuwać przy pomocy strzałek lub bocznych przycisków myszki/scrolla

///////////Sterowanie/////////////
klawiatura (A-Z), myszka (LPM, PPM) - wprowadzanie znaków
klawiatura (strzałka w prawo i lewo), myszka (przyciski boczne i scroll) - przesuwanie obwódki w bok
klawiatura (Del) - Poddanie się
klawiatura (End), myszka (przycisk w lewym górnym rogu) - Restart
klawiatura (Space), myszka (MPM) - Zmiana trybu wprowadzania
klawiatura (Backspace), myszka (przycisk w prawym dolnym rogu) - Kasowanie

///////Dodatkowe informacje///////
W przypadku wyświetlania błędu dotyczącego brakujących plików .dll należy zainstalować Microsoft Visual C++.
https://www.microsoft.com/pl-pl/download/details.aspx?id=48145

Pliki zasobów powinny znajdować się w folderze "res", lista plików:
	- delete.png
	- restart.png
	- icon.png
	- slowa.txt
	- Hack-Regular.ttf
Jeśli zabraknie któregoś z nich aplikacja może przestać działać poprawnie.

Requirements
Must Have (dependencies)
SFML 2.4.1 or above - http://www.sfml-dev.org/
Linux
```
 sudo apt-get install libsfml-dev
```
Windows
Vist www.sfml-dev.org and download the lastest version of the library.
In project settings,
Add the </path/to/sfml/>/include to your c++ include path.
Then add </path/to/sfml/>/lib to the linker extra library path.
