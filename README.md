<p align="center">
    <img src="/assets/logo.png"/>
</p>

# 👋 Introduction #
Given the exploding nature of the pandemic, the world health machinery suggested regular use of hand sanitizers as a safety measure from COVID-19. The sale of hand sanitizers has increased many folds. Therefore, when there is such large use of hand sanitizers, it becomes extremely important to study and understand the product in a comprehensive manner.

# 📝 About The Project #
### Video Demostration: <a href="https://youtu.be/G4GZ-QFubOY" target="_blank">DIY Smart IoT Hand Sanitizer</a> 🧴 ###
**[DIY Smart IoT Hand Sanitizer](https://youtu.be/G4GZ-QFubOY "Video demostration")** is a product that works similarly to a regular hand sanitizer with a few exceptions that improves the convenience of the personnel who is in charge of refilling the hand sanitizer. We have implemented additional data analytic tools for the person-in-charge to recognize the water level trend time trend and dispensing count which displays the peak usage of the hand sanitizer and the amount of times it has been dispensed over a certain period of time respectively. 

Lastly, basic machine learning techniques have been implemented to predict the amount of dispense count required to reach both "Medium" and "Low" water level, the latter requires the person-in-charge to refill the hand sanitizer.

We have set 3 water levels for the hand sanitizer:
1. Full -> No refill is required
2. Medium -> No refill is required
3. Low -> The user is required to refill the sanitizer

The hand sanitizer is made up of the followings components:
1. [4 X Battery Holder](https://www.sgbotic.com/index.php?dispatch=products.view&product_id=1892 "Video demostration")
2. [Diffused Red LED - 10mm](https://www.sgbotic.com/index.php?dispatch=products.view&product_id=1615 "Video demostration")
3. [Flame Sensor Module](https://www.sgbotic.com/index.php?dispatch=products.view&product_id=2641 "IR Sensor")
4. [Mini Submersible Liquid Pump](https://www.sgbotic.com/index.php?dispatch=products.view&product_id=2452 "Video demostration")
5. [Single Channel Relay Module](https://www.sgbotic.com/index.php?dispatch=products.view&product_id=1906 "Relay")
6. [Push Button Switch](https://www.sgbotic.com/index.php?dispatch=products.view&product_id=589 "Push Button")
7. [Water Sensor - Small](https://www.sgbotic.com/index.php?dispatch=products.view&product_id=2425 "Water Sensor")

#### Circuit diagram ####
<p align="center">
    <img src="/assets/circuit.png" width="50%" height="400"/>
</p>

Tech used:
* Programming language
  * **Python**
  * **Arduino**
* Libraries
  * **matplotlib**
  * **pandas**
  * **seaborn**
  * **scikit-learn**
* Tools
  * **Arduino IDE**
  * **Jupyter notebook**
  * **[ThingSpeak](https://thingspeak.com/ "ThingSpeak")**
  * **VScode**

# ❓ How it works #

### Arduino: ***Hardware*** ###
We will only use Arduino platform to control all the components listed above under "About The Project" header. There is a loop implemented to continously collect data such as the water level of the product, the current state of the push button (Depressed or not) and the infrared value from the IR sensor (The proximity of the human hands from the sensor).

### ThingSpeak and Python: ***Seralise connection*** ###
ThingSpeak and Python are used to collect the data from the hardware portion and to initiate a connection with the Arduino via the COM port respectively. ***Once Python has connected with the Arduino, ThingSpeak will start to store these 2 data, the dispensing count and the water level of the hand sanitizer.*** The disadvantage of using ThingSpeak platform is that the update frequency of the data ranges from 5 to 10 minutes.

### Jupyter notebook: ***Data visualisation and Machine learning*** ###
Extraction of data is performed with a csv file that is linked to a ThingSpeak URL and the data are reorganised into a dataframe with the pandas library.
Data visualisation is performed with **matplotlib and seaborn** libraries whereas machine learning is implemented with **scikit-learn** library. 

***Upon performing data visualisation, we found out that there is a linear trend between these 2 variables, water level and dispensed count***. Thus, we used scikit-learn library to not only predict the amount of dispense count required to reach both "Medium" and "Low" water level, we used it to check the accuracy of the machine learning model with the calculation of R-squared values

#### Data visualisation diagrams ###
- Water level trend and Dispensing Count
  <p align="left">
    <img src="/assets/datavisualisation.png" width="50%" height="400"/>
  </p>
- Regression plot of Water Level against Dispensing Count
  <p align="left">
    <img src="/assets/regressionPlot.png" width="50%" height="400"/>
  </p>

#### Machine learning diagrams
- Test machine learning model against training/simulated data
  <p align="left">
    <img src="/assets/regressionMachine.png" width="50%" height="400"/>
  </p>
- Comparison between true and predicted data -> Dispensed count
  <p align="left">
    <img src="/assets/actualPredicted.png" width="50%" height="400"/>
  </p>