import cv2
import sys
from matplotlib import pyplot as plot

class object_detect(object):
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
			self.check = img[top_left[1]:top_left[1]+height,top_left[0]:top_left[0]+width]
			cv2.imwrite("final"+".png",self.check)
			plot.show()
			return center_coordinates

	def check_true(self):
		res = cv2.matchTemplate(self.check,self.template,self.methods[0])

if __name__ == "__main__":
	img = cv2.imread(sys.argv[1],0)
	object1 = object_detect()
	object_number = object1.process(img,str(sys.argv[2]))