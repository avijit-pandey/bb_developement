import serial # import Serial Library
import numpy  # Import numpy
import matplotlib.pyplot as plt #import matplotlib library
from drawnow import *

acclx= []
accly= []
acclz= []

arduinoData = serial.Serial('com7', 9600) #Creating our serial object named arduinoData
plt.ion() #Tell matplotlib you want interactive mode to plot live data
cnt=0

def makeFig(): #Create a function that makes our desired plot
#    plt.ylim(80,90)                                 #Set y min and max values
    plt.title('data from IMU')      #Plot the title
#    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('data')                            #Set ylabels
    plt.plot(acclx, 'ro-', label='pitch')       #plot the x-axis data
    plt.plot(accly, 'g^-', label='roll')       #plot the y-axis data    
   # plt.plot(acclz, 'b*-', label='y-acc')       #plot the y-axis data
    plt.legend(loc='upper left')                    #plot the legend
    plt.ylim(-200,200)                           #Set limits of second y axis- adjust to readings you are getting


while True: # While loop that loops forever
    while (arduinoData.inWaiting()==0): #Wait here until there is data
        pass #do nothing
    arduinoString = arduinoData.readline() #read the line of text from the serial port
    print (arduinoString)
    dataArray = arduinoString.decode("utf-8")
    dataArray = dataArray.split(',')   #Split it into an array called dataArray
    print (dataArray)
    acc_x = float( dataArray[0])            #Convert first element to floating number and put in acc_x
    acc_y = float( dataArray[1])            #Convert second element to floating number and put in acc_y
    #acc_z = float( dataArray[2])            #Convert third element to floating number and put in acc_z

#    print(temp,',',P)

    acclx.append(acc_x)                     #Build acclx array by appending acc_x readings
    accly.append(acc_y)                     #Build accly array by appending acc_y readings
    #acclz.append(acc_z)                     #Build acclz array by appending acc_z readings
    drawnow(makeFig)                       #Call drawnow to update our live graph
    plt.pause(0.0000000001)                     #Pause Briefly. Important to keep drawnow from crashing
    cnt=cnt+1
    if(cnt>10):                            #If you have 50 or more points, delete the first one from the array
        acclx.pop(0)                       #This allows us to just see the last 50 data points
        accly.pop(0)
     #   acclz.pop(0)
