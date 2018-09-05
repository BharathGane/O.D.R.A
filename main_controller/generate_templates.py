import os
import cv2
from PIL import Image
import matplotlib.image as mpimg
from matplotlib import pyplot as plot

def rotate_image(image_name):
	i=0
	img = Image.open(image_name)
	angles = [45,90,135,180,225,270,315]
	for angle in angles:
		img = img.rotate(angle)
		filename = "rotated" + image_name + str(i) + ".png"
		img.save(filename)
		i+=1

def averaging_blur(image_name):
	img = cv2.imread(image_name)
	blur = cv2.blur(img,(5,5))
	filename = "averageBlurred" + image_name + ".png"
	cv2.imwrite(filename,blur)

def gaussian_blur(image_name):
	img = cv2.imread(image_name)
	blur = cv2.GaussianBlur(img,(5,5),0)
	filename = "gaussianBlurred" + image_name + ".png"
	cv2.imwrite(filename,blur)

def median_blur(image_name):
	img = cv2.imread(image_name)
	median = cv2.medianBlur(img,5)
	filename = "medianBlurred" + image_name + ".png"
	cv2.imwrite(filename,median)

def bilateral_filter(image_name):
	img = cv2.imread(image_name)
	blur = cv2.bilateralFilter(img,9,75,75)
	filename = "bilateralFiltered" + image_name + ".png"
	cv2.imwrite(filename,blur)

if __name__ == '__main__':
	directory = "./"
	for filename in os.listdir(directory)
		if filename.endswith(".jpg"):
			rotate_image(filename)
		else:
			continue

	for filename in os.listdir(directory):
		if filename.endswith(".jpg") or filename.endswith(".png"):
			print(os.path.join(directory, filename))
			averaging_blur(filename)
			gaussian_blur(filename)
			median_blur(filename)
			bilateral_filter(filename)
		else:
			continue