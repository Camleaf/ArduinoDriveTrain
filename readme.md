


# Three wheel Crab drivetrain

**Description:** This robot can move in any direction without turning, using the Crab drive motion. It is controlled with the attached controller joysticks with the left joystick for arcade movement relative to the heading, and the right joystick to control the heading.

**Motivation:** I did this project because I wanted a challenge, also because I am looking towards joining an FRC team for the first time next year, and I wanted to make a drivetrain inspired by some robots I saw there. This project ended up taking less time than I anticipated (mostly because I was putting in 7-8 hour days on it), but it was still very fun.

**File Layout**:
 - **CAD**: contains the STEP files for the entire built, imports and all
 - **FIRMWARE**: contains all the code put on the microcontrollers
 - **WIRING**: Contains fritzing file, breadboard view and schematic view images, for both the controller and the car
 - **PRODUCTION**: Contains the individual .3mf files which will be 3D printed
 - **JOURNALIMG**: Where I store all the images I used for my journal


### Car Design Images

<img src="./JournalImg/car_CAD.png" width="500">
<img src="./JournalImg/Car_CAD_expanded.png" width="500">
<img src="./Wiring/Car diagram_bb.png" width="350">
<img src="./Wiring/Car diagram_schem.png" width="350">


### Controller Design Images

<img src="./JournalImg/Controller_CAD_done.png" width="500">
<img src="./Wiring/Controller diagram_bb.png" width="350">
<img src="./Wiring/Controller diagram_schem.png" width="350">


### BOM

Item # |	Part Name |	Quantity | Type | Description|	Source |	Cost (USD)
--- | --- | --- | --- | --- | ---
1  | Arduino Due|	1 | N/A | Microcontroller for car |	AliExpress | $16.52
2  | USB Power Bank|	1 | N/A | Powers microcontroller | AliExpress | $17.45
3  | 4 20kg Servos |	1 | N/A | Rotates motors around yaw|	AliExpress | $47.79
4  | DC motor |	4 | 6V bracket motor 300rpm| The main motors |	AliExpress | $33.43
5  | Battery pack |	1 | 3pcs | Powers motors |	AliExpress | $14.98
6  | BTS7960 |2 | N/A | Motor driver |	AliExpress | $6.08
7  | Joysticks | 1 | N/A | Joysticks for controller |	AliExpress | $3.42

Shipping: $ 20.5 USD

Total: $160.17 USD
^ This may be well below because of Aliexpress first time shopper discounts,
but I used the full prices even though

