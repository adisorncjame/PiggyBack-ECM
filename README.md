# PiggyBack-ECM

**PlggyBack-ECM** is a DIY project designed to enhance the functionality of a standard motorcycle by connecting a Microcontroller Unit (MCU) to add modern features. The aim of this project is to provide additional options and improve the performance and usability of motorcycles, making them more adaptable to modern needs.


---
## Functional Features

- [**Data Logger**](#data-logger): Records and stores performance data from the motorcycle for further analysis and tuning.
- [**Launch Assist**](#launch-assist): Provides optimized throttle control during acceleration from a standstill, ensuring a smooth and efficient start.
- [**Pit Lane Speed Limiter**](#pit-lane-speed-limiter): Limits the motorcycle's speed within the pit lane area for safety and compliance with regulations.
- [**Quick Shift**](#quick-shift): Enables seamless gear shifting without the need to use the clutch, improving shifting speed and rider comfort.

---

### Data Logger
The **Data Logger** captures and stores real-time performance data from the motorcycle's sensors, such as engine RPM, throttle position, and speed. This data can be used for post-ride analysis, allowing the rider to fine-tune the bike's settings for better performance or diagnose any potential issues.

#### Working Diagram:
```plaintext
[Sensor Input] --> [Microcontroller (Data Processing)] --> [Memory Storage]
```
- **Sensor Input**: Sensors on the motorcycle (e.g., RPM, throttle, speed) collect real-time data.
- **Microcontroller**: Processes the sensor data and determines what to store.
- **Memory Storage**: Data is stored in memory (SD card, flash memory) for later analysis.

---

### Launch Assist
**Launch Assist** helps the rider achieve optimal acceleration from a standstill by controlling throttle input and traction. It minimizes wheel spin and provides smooth acceleration, particularly useful during competitive racing or high-performance situations.

#### Working Diagram:
```plaintext
[Throttle Input] --> [Microcontroller (Launch Control Algorithm)] --> [Throttle Output Adjusted] --> [Optimized Acceleration]
```
- **Throttle Input**: Rider twists the throttle to start.
- **Microcontroller**: The launch control algorithm moderates the throttle to prevent wheel spin and optimize grip.
- **Throttle Output**: Adjusted throttle output ensures the bike accelerates smoothly.
  
---

### Pit Lane Speed Limiter
The **Pit Lane Speed Limiter** ensures the motorcycle does not exceed a specific speed while inside the pit lane. It can be activated with a button on the handlebars. This feature is essential in racing environments where speed limits must be strictly followed in the pit area for safety reasons.

#### Working Diagram:
```plaintext
[Speed Sensor] --> [Microcontroller (Speed Limit Logic)] --> [Throttle or Engine Power Limited] --> [Speed Controlled]
```
- **Speed Sensor**: Detects the current speed of the motorcycle.
- **Microcontroller**: Processes the speed and ensures it stays below the set limit when the limiter is activated.
- **Throttle/Engine Power**: Adjusts the engine power or throttle to maintain the required speed.

---


### Quick Shift
The **Quick Shift** system allows the rider to change gears without using the clutch. It cuts the ignition momentarily when the gear shift lever is pressed, reducing the load on the transmission and allowing a smooth, fast shift. This is especially useful in racing for minimizing shift times and maintaining high performance.

#### Working Diagram:
```plaintext
[Gear Shift Lever Pressed] --> [Microcontroller (Ignition Cut Signal)] --> [Ignition Temporarily Cut] --> [Smooth Gear Shift]
```
- **Gear Shift Lever**: The rider presses the lever to change gears.
- **Microcontroller**: Detects the lever press and momentarily cuts ignition.
- **Ignition**: Temporarily cutting ignition allows the gears to shift smoothly without disengaging the clutch.


