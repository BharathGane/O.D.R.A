import os
import re
import sys
import cv2
import time
import serial
from PIL import Image
from ftplib import FTP
import matplotlib.image as mpimg
from matplotlib import pyplot as plot

class template_matching(object):
	def __init__(self):
		self.methods = ['cv2.TM_CCOEFF']
		self.template = None
	
	def process(self,img,template):
		self.template = cv2.imread(template,0)
		height, width = self.template.shape[::]
		img2 = img.copy()
		self.check = img2 

		for method in self.methods:
			img = img2.copy()
			method = eval(method)

			res = cv2.matchTemplate(img,self.template,method)
			min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)

			if method in [cv2.TM_SQDIFF, cv2.TM_SQDIFF_NORMED]:
				top_left = min_loc
			else:
				top_left = max_loc
			bottom_right = (top_left[0] + width, top_left[1] + height)
			bottom_left = (top_left[0],top_left[1] + height)
			top_right = (top_left[0] + width,top_left[1])

			print top_left,top_right,bottom_right,bottom_left,height,width
			center_coordinates = [0,0]
			plot.imshow(img)
			plot.scatter(top_left[0],top_left[1])
			plot.scatter(top_right[0],top_right[1])
			plot.scatter(bottom_right[0],bottom_right[1])
			plot.scatter(bottom_left[0],bottom_left[1])
			center_coordinates[1] = (top_left[1] + height/2)/2
			center_coordinates[0] = (top_left[0] + width/2)/2
			plot.scatter(center_coordinates[0]*2,center_coordinates[1]*2)
			plot.show()
			print center_coordinates
			return center_coordinates

def crop_image(image_name,port):
	img = Image.open(image_name)

	if port == 2121:
		img2 =img.crop((85,660,2160,2760))
		img2.save("process_image.png")
	elif port == 9999:
		img2 = img.rotate(270)		
		img2 =img.crop((450,1050,2315,2920))
		img2.save("process_image.png")

def download_image(fpt):
	files = ftp.nlst()
	ftp.retrbinary("RETR " + files[-1] ,open("test_me.jpg", 'wb').write)

def object_detect(selected_object):
	if selected_object == 1:
		object_name = "battery"
	elif selected_object == 2:
		object_name = "pendrive"
	object_detection_directory = "/home/kishore/Documents/Projects/O.D.R.A/object_detection/"
	object_directory = "/home/kishore/Documents/Projects/O.D.R.A/main_controller/"
	os.chdir(object_detection_directory)
	positive_directory = object_detection_directory + "objects/" + object_name + "/" + "positive/"
	negative_directory = object_detection_directory + "objects/" + object_name + "/" + "negative/"

	print "Training,..."
	os.system("make train")
	os.system("./output " + positive_directory + " positive.xml")
	os.system("./output " + negative_directory + " negative.xml")
	print "Applying SVM,..."
	os.system("make svm")
	os.system("./output positive.xml negative.xml trainedsvm.xml")
	print "Start object detection,..."
	os.system("make all")
	os.system("./output trainedsvm.xml " + object_directory + "process_image.png")
	os.chdir(object_directory)
	f = open("coordinates.txt","r")
	string = f.readline()
	center_point=[0,0]
	x = re.match(r".(\d+)\D+(\d+)\D+(\d*)\D+(\d*)", string)
	z = map(int,x.groups())
	print z
	center_point[0] = z[2] + z[0]/2
	center_point[1] = z[3] + z[1]/2
	print center_point
	return center_point

if __name__ == '__main__':
	# MENU
	print "** project O.D.R.A **"
	print "What would you like to do ?"
	print "1. Download new/recent image"
	print "2. Pick object from most recent image downloaded"
	print "3. Exit"
	choice = input("Enter your choice: ")
	print "Which object would you like to pick ?"
	print "1. Battery"
	print "2. Pendrive"
	selected_object = input("Enter your choice: ")
	if choice == 1:
		# DOWNLOAD LATEST IMAGE USING FTP
		ftp = FTP()
		port = int(sys.argv[2])
		host = str(sys.argv[1])

		# START FTP SERVER
		ftp.connect(host = host ,port = port) 
		ftp.login("admin","admin123")
		print "Downloading latest image from your phone,..."
		download_image(ftp)
		# CROP ACCORDING TO PHONE
		crop_image("test_me.jpg",port)
		print "What method do you want to test object detection in :"
		print "1. Template Matching"
		print "2. SVM - ML"
		mode = input("Enter your choice: ")
		if mode == 1:
			img = cv2.imread("process_image.png",0)
			object1 = template_matching()
			if selected_object == 1:
				object_name = "battery"
			elif selected_object == 2:
				object_name = "pendrive"
			coordinates = object1.process(img,object_name + ".png")
		elif mode == 2:
			coordinates = object_detect(selected_object)
	elif choice == 2: 
		# RETURN COORDINATES FROM C++ CODE
		print "What method do you want to test object detection in :"
		print "1. Template Matching"
		print "2. SVM - ML"
		mode = input("Enter your choice: ")
		if mode == 1:
			img = cv2.imread("process_image.png",0)
			object1 = template_matching()
			if selected_object == 1:
				object_name = "battery"
			elif selected_object == 2:
				object_name = "pendrive"
			coordinates = object1.process(img,object_name + ".png")
			img = mpimg.imread("final.png")
			plot.imshow(img)
			plot.savefig("plotted.png")

		elif mode == 2:
			coordinates = object_detect(selected_object)
			img = mpimg.imread("final.png")
			plot.imshow(img)
			plot.savefig("plotted.png")
			plot.show()

	# SEND COORDINATES THROUGH SERIAL TO ARDUINO
	ser = serial.Serial('/dev/ttyUSB0',9600)
	time.sleep(2)
	x_coordinate = str(coordinates[0])+"\n"
	ser.write(str(coordinates[0])+"\n")