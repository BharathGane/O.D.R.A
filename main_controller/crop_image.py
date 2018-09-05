import os
import sys
from PIL import Image
import matplotlib.image as mpimg
from matplotlib import pyplot as plot

i=0
def crop_image(image_name, new_image_name):
	global i 
	img = Image.open(image_name)
	img2 =img.crop((85,660,2160,2760))
	file_name = new_image_name + str(i) + ".png";
	img2.save(file_name)
	# img2.show()
	i+=1

if __name__ == '__main__':
	new_file_name = raw_input("Enter new generic file name: ")
	directory = "./"
	for filename in os.listdir(directory):
		if filename.endswith(".jpg"): 
			print(os.path.join(directory, filename))
			crop_image(filename,new_file_name)
		else:
			continue