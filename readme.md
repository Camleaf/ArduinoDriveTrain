


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
![alt text](image.png)

### Controller Design Images

<img src="./JournalImg/Controller_CAD_done.png" width="500">
<img src="./Wiring/Controller diagram_bb.png" width="350">
<img src="./Wiring/Controller diagram_schem.png" width="350">


### BOM

I have a lot of parts at home and 3D printing capabilities so this list is just what I don't have.

|Item #|Name                     |Quantity|Type            |Description             |Cost |Link                                                                                                                                                                                                                                                                        |FIELD8|FIELD9|FIELD10|
|------|-------------------------|--------|----------------|------------------------|-----|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|------|-------|
|1     |BTS7960                  |2       |2pcs            |Motor Driver            |6.04 |https://www.aliexpress.com/item/1005006795884033.html?spm=a2g0o.cart.0.0.37ee38dastskZr&mp=1                                                                                                                                                                                |      |      |       |
|2     |XY joystick              |1       |5pcs            |Joystick for controller |3.21 |https://www.aliexpress.com/item/1005009059629265.html?spm=a2g0o.cart.0.0.37ee38dastskZr&mp=1                                                                                                                                                                                |      |      |       |
|3     |7.4v 1500mAh battery pack|1       |3pcs charger    |Powers motors/servos    |11.29|https://www.aliexpress.com/item/1005007104046547.html?spm=a2g0o.cart.0.0.37ee38dastskZr&mp=1                                                                                                                                                                                |      |      |       |
|4     |JGB37 DC motor           |4       |6V bracket motor|main motors             |16.63|https://www.aliexpress.com/item/1005009003269281.html?spm=a2g0o.cart.0.0.37ee38dastskZr&mp=1                                                                                                                                                                                |      |      |       |
|5     |Arduino Mega             |1       |official-cable  |microprocessor          |12.99|https://www.aliexpress.com/item/1005006661386732.html?spm=a2g0o.cart.0.0.37ee38dastskZr&mp=1                                                                                                                                                                                |      |      |       |
|6     |JX PDI-6221mg servos     |1       |4pc             |servos to rotate motor  |16.63|https://www.aliexpress.com/item/32880168203.html?spm=a2g0o.cart.0.0.37ee38dastskZr&mp=1                                                                                                                                                                                     |      |      |       |
|7     |USB power bank           |1       |1pc             |Power for microprocessor|10.71|https://www.aliexpress.com/item/1005008829680504.html?spm=a2g0o.productlist.main.49.7667cea7mv3Tqw&algo_pvid=4fdae823-0f43-4341-80e5-c249a84bc11f&pdp_ext_f=%7B%22order%22%3A%22-1%22%2C%22eval%22%3A%221%22%7D&utparam-url=scene%3Asearch%7Cquery_from%3A#nav-specification|      |      |       |
|      |Shipping                 |N/A     |N/A             |N/A                     |36.47|                                                                                                                                                                                                                                                                           |


Total: $129.92 USD

With tax: $146.8096 USD

