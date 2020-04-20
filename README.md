# VibeBot DriverBot
This, ladies and gentlemen, is the official repository for the world-famous VibeBot DriverBot!

## Website
The official website is available at http://vibebotbucket.s3.amazonaws.com/joysticks3/nipplejs.html.
      NOTE: due to the fact that maqiatto, the mqtt broker that is used, doesn't support wss just ws, the site needs to be loaded with http, not https.

## How it works
The actual vehicle is made with LEGO technic parts, and on the vehicle there's a TT-motor that propels the vehicle at the back wheels, and on top of the front wheels there is a servo that controls the steering.
The website sends numbers via mqtt to the project's mqtt topic. The first number represents the direction, the next 4 the speed and the last 2 the angle of the servo. The ESP is subscribed to the topic with PubSubClient, and it then divides the payload into its 3 parts and sends these signals to the motor and servo.

## Future Development
The project's team, me, is working hard on mounting a GoPro camera on the vehicle. This camera can be controlled via an app to live stream to Twitch. The current website in-development has embedded a Twitch live-stream, and when the live stream is set up and the camera is mounted, the live-stream will be shown on the website to allow for more efficient remote steering of the vehicle for purposes of, for example, fetching toilet paper or exploring unknown terrains.

## LOG
The log for the project is available at the log.md file
