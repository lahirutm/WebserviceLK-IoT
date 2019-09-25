# WebserviceLK-IoT

Welcome to WebserviceLK-IoT

WebserviceLK-IoT helps you to integrate your existing devices (NodeMCU-ESP8226, Arduino, ...) with Google Home for FREE !

**How to use : Google Home**

1. Create a webservice.lk account if you do not have one, visiting https://webservice.lk/ 
2. Go to https://console.actions.google.com/
3. Click Add.
4. Name the project. Eg:- WebserviceLK
5. It Takes few seconds to create the project.
6. Now you are on the home screen. Click Home Control.
7. Click Name your Smart Home Action.
8. Name it WebserviceLK. Click Save (in the upper right corner).
9. Click "Account Linking".
10. Select No.
11. Select OAuth, then Select Autherization Code
12. Copy Client ID and Client Secret from WebserviceLK website you have already created.
13. Paste it accordingly and click next.
14. Authorization URL: https://webservice.lk/oauth 
15. Token URL: https://webservice.lk/token
16. Now Enter user (Just "user"). Click next.
17. Enter test. Click Save.
18. Now, Select Actions under Build from left side menu. Click Add your first action.
19. Enter: https://webservice.lk/api/v1/googlehome/event
20. Click Done.
21. Click Test.
22. This will deploy the thing and now you are ready to start testing.

23. Now you need to get control of your devices through Google Asistance by talking to it. So, add few devices in to your webservice.lk account by visiting it.
24. Open your Google Home mobile app in your android phone. (If you do not have it you must install it.) 
25. Go to Home. (Or you can go to Settings)
26. Find Home Control in Left side panel.
27. Now you must see WebserviceLK (Or whatever name you have given, when creating it)
28. Click on it. Now it will open a login page to login. Use your webservice.lk credentials to log in. Now you will see a message with link successful.
29. Now you will see your devices you have created in your webservice.lk account.


Now you can programme your NodeMCU or Arduino & etc to connect with webservice.lk and then you can controll it through Google Home Assitance with voice commands. 

For more information visit https://webservice.lk/how_to

Got basic idea & coding guidence from Kakopappa (Aruna Tennakoon), he has done nice work for connecting your esp-module/arduino to sinric.com with Google Asistance & Amazon Alexa for free.
https://github.com/kakopappa/sinric
