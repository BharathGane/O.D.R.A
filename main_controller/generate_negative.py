import os
import cv2
import numpy as np
import matplotlib.pyplot as plt

def make_grayscale(image_name):
	img = cv2.imread(image_name,0)
	filename = "grayscale" + image_name + ".png"
	cv2.imwrite(filename,img)

if __name__ == '__main__':
	directory = "../positive/"
	for filename in os.listdir(directory):
		if filename.endswith(".jpg") or filename.endswith(".png"):
			make_grayscale(filename)
		else:
			continue