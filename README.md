## Wordle by Jędrzej Kolski
My old project - wordle with adjustments for speedrunners. Half of the code is in Polish and half in English, but I don't intend to touch it, let it be.
#### Gameplay  
[Polish Wikipedia - Wordle](https://pl.wikipedia.org/wiki/Wordle)  
[English Wikipedia - Wordle](https://en.wikipedia.org/wiki/Wordle)

- The currently selected tile is highlighted with a border.  
- Two input modes are available:  
  - **White border (default)**: After entering or deleting a character, the border moves forward or backward automatically.  
  - **Orange border**: After entering or deleting a character, the border remains in place but can be moved using arrow keys, side mouse buttons, or the scroll wheel.

---

#### Controls  

- **Entering characters**:  
  Keyboard (A-Z), Mouse (Left Mouse Button - LMB, Right Mouse Button - RMB)  
- **Moving the border**:  
  Keyboard (Left/Right Arrow), Mouse (side buttons or scroll wheel)  
- **Forfeiting**:  
  Keyboard (Del)  
- **Restarting**:  
  Keyboard (End), Mouse (button in the top-left corner)  
- **Changing input mode**:  
  Keyboard (Space), Mouse (Middle Mouse Button - MMB)  
- **Deleting a character**:  
  Keyboard (Backspace), Mouse (button in the bottom-right corner)  

---

#### Additional Information  

- If an error occurs regarding missing `.dll` files, install Microsoft Visual C++.  
  [Download Microsoft Visual C++](https://www.microsoft.com/pl-pl/download/details.aspx?id=48145)  
- Resource files should be located in the "res" folder. The required files include:  
  - `delete.png`  
  - `restart.png`  
  - `icon.png`  
  - `slowa.txt`  
  - `Hack-Regular.ttf`  

  Missing any of these files may cause the application to malfunction.

## Portable version
simply download wordle.zip, build for windows x64
