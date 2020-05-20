# VibeBot DriverBot
This, ladies and gentlemen, is the official repository for the world-famous VibeBot DriverBot!

## Website
The official website is available at http://vibebotbucket.s3.amazonaws.com/joysticks3/nipplejs.html.
      NOTE: due to the fact that maqiatto, the mqtt broker that is used, doesn't support wss just ws, the site needs to be loaded with http, not https.

## How it works
The actual vehicle is made with LEGO technic parts, and on the vehicle there's a TT-engine that propels the vehicle at the back wheels, and on top of the front wheels there is a servo that controls the steering.
The website sends numbers via mqtt to the project's mqtt topic. The first number represents the direction, the next 4 the speed and the last 2 the angle of the servo. The ESP is subscribed to the topic with PubSubClient, and it then divides the payload into its 3 parts and sends these signals to the motor and servo. There is also an AWS back-end with a DynamoDB table as well as 2 lambda functions. This is used to log data, which has been a requirement for this project.

## Live Streaming
During the tests where other people have been able to control the driverbot, a GoPro Hero 7 Black has been mounted on it to live stream the view from the driverbot. This has been quite effective during the test drives, as the remote drivers were able to navigate across 2 rooms in the test house as well as drive out of a sticky situation under a table, with many chairs as an obstacle. The current delay is between 5-15 seconds, most likely due to the GoPro and Twitch both being a bit slow, and currently there doesn't seem to be a way to cut it down. However, the test drivers were able to drive it, so the delay isn't devastating.

## How it works
![Diagram!](/ReadmeBilder/DiagramDriverbot.PNG)

## LOG
The log for the project is available at the log.md file
