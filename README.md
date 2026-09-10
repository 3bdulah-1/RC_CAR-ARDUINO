# Bluetooth-Controlled RC Car with Autonomous Obstacle Avoidance

An RC car built on Arduino Uno with two selectable driving modes: manual Bluetooth control and fully autonomous obstacle avoidance, both switchable from a phone app.

## Features

### 🎮 Manual Mode
- Drive the car in real time via Bluetooth from a phone app
- Two white LEDs act as headlights
- Two red LEDs act as taillights
- A buzzer functions as a horn
- All lights and the horn are individually controllable from the app

### 🤖 Autonomous Mode (Obstacle Avoidance)
- An ultrasonic sensor mounted on a servo continuously measures distance to obstacles ahead
- When an object is detected within 20cm, the car stops
- The servo sweeps right, then left, measuring distance at each side
- The car automatically turns toward whichever side has more open space and continues driving
- Mode switching (manual ↔ autonomous) is done from the same phone app

## Hardware Used

- Arduino Uno
- Ultrasonic distance sensor (HC-SR04 or similar) mounted on a servo motor
- Bluetooth module (e.g. HC-05) for phone communication
- 2x white LEDs (headlights), 2x red LEDs (taillights)
- Buzzer (horn)
- DC motors + motor driver
- Car chassis + battery pack

*(fill in exact part models/specs above if you want the README fully accurate)*

## How It Works

The Arduino reads mode-select and drive commands from the Bluetooth module. In manual mode, it maps incoming Bluetooth commands directly to motor and light/horn outputs. In autonomous mode, it runs a loop that pings the ultrasonic sensor, stops the drive motors when an obstacle is within 20cm, sweeps the servo to sample distances left and right, and steers toward the clearer path before resuming.

## Demo

See the video in this repo for a live demonstration of both modes.

## What I'd Improve Next

- Add a safety cutoff for autonomous mode if no clear path is found in either direction
- Log distance readings over time for basic obstacle-mapping

## About This Project

Built as part of a robotics course, as an independent project extending beyond the base course requirements — designing and implementing both control modes myself.
