import os
user=input("Enter the img name")
os.system("fswebcam"+ user)
if(user):
    print("imageis captured")
else:
        print("ERROR")