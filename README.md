# AP_project

This is Advanced Programming project.

group name: c++(=31)

group number = 9

**built with:** c++ and QT creator




# Messenger

•  Stay in touch with your friends

•  Join to groups and channels

•  Join your friends group and chat with them

•  Create your own channel and publish whatever you want 




## SAVE DATA IN HARD DISK

•  DATA storage in json files

Data is saved automaticly and you can veiw messeges offline.

When someone logs into program, a file named main_user.json will be created,

and we have 3 folders for save users, chats, and groups information (everyyhing has a .json file).

If you log in you can use program until you log out.




## SERVER

Server responses slowly  so please wait for changes and  execute commands, and please dont click again just wait a few seconds.

Connection with server is through http request and response.




## CLEAN ARCHITECTURE

We built our program based on clean architecture principles:

**ENTITIES classes:** 
•  chat, user, group, channel, main_user

**USE CASES:**
•  send and receive message
•  create group and channel
•  join into group and channel
•  log out
•  log in
•  sign up
•  find user
...

**CONTOROLER class:**
•    Mainwindow

**VIEW classes(UI):**

•  main_page
•  sign_up
•  log_in
•  create_channe
•  create_group
•  join_group
•  join_channel
•  new_user
...




## Polymorphism

•  most of classes inherits from QObject.
•  chat class is an abstract class that channel, group, user inherit from.




## Thread

every 1500 ms program updates (server responses slowly).
list of messeges and list of users updates.




# Install

you can easily install this program.
just extract messenger installer.zip and run messenger.exe to install app everywhere you want and then just run application and enjoy :)





