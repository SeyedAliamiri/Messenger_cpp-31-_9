# AP Project

This is Advanced Programming project.

group name: c++(=31)

**built with:** c++ and QT creator




# Messenger

**•  Stay in touch with your friends**

**•  Join to groups and channels**

**•  Join your friends group and chat with them**

**•  Create your own channel and publish whatever you want** 



![Screenshot 2023-07-05 174356](https://github.com/SeyedAliamiri/Messenger_cpp-31-_9/assets/124011267/dac39838-169a-432d-bebd-f7991bd3ccda)




## Save Data In Hard Disk

•  DATA storage in json files

Data is saved automaticly and you can veiw messeges offline.

When someone logs into program, a file named main_user.json will be created,

and we have 3 folders for save users, chats, and groups information (everyyhing has a .json file).

If you log in you can use program until you log out.




## Server

Server responses slowly  so please wait for changes and  execute commands, and please dont click again just wait a few seconds.

Connection with server is through http request and response.




## Clean Architecture

We built our program based on clean architecture principles:

**Entity classes:** 
•  chat, user, group, channel, main_user

**Use Cases:**
•  send and receive message
•  create group and channel
•  join into group and channel
•  log out
•  log in
•  sign up
•  find user
...

**Controller class:**
•    Mainwindow

**View classes(UI):**

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



![Screenshot 2023-07-05 174915](https://github.com/SeyedAliamiri/Messenger_cpp-31-_9/assets/124011267/106ea061-bf0c-42ea-8c3d-7f445fc52083)

![Screenshot 2023-07-05 174737](https://github.com/SeyedAliamiri/Messenger_cpp-31-_9/assets/124011267/e1c01f96-3ec8-46bb-a7d1-da3248a6c6d4)

