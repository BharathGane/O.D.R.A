import cv2
from matplotlib import pyplot as plt
import sys
img = cv2.imread(sys.argv[1],0)
img2 = img.copy()

template = cv2.imread('template.jpg',0)
h, w = template.shape[::]

# methods = ['cv2.TM_CCOEFF', 'cv2.TM_CCOEFF_NORMED', 'cv2.TM_CCORR',
			# 'cv2.TM_CCORR_NORMED', 'cv2.TM_SQDIFF', 'cv2.TM_SQDIFF_NORMED']
methods = ['cv2.TM_CCOEFF', 'cv2.TM_CCOEFF_NORMED', 'cv2.TM_SQDIFF', 'cv2.TM_SQDIFF_NORMED']

for meth in methods:
	img = img2.copy()
	method = eval(meth)

	res = cv2.matchTemplate(img,template,method)
	min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)

	if method in [cv2.TM_SQDIFF, cv2.TM_SQDIFF_NORMED]:
		top_left = min_loc
	else:
		top_left = max_loc
	bottom_right = (top_left[0] + w, top_left[1] + h)
	bottom_left = (top_left[0],top_left[1] + h)
	top_right = (top_left[0] + w,top_left[1])
	
	print top_left,top_right,bottom_right,bottom_left
	cv2.rectangle(img,top_left, bottom_right, 255, 2)
	plt.imshow(img,cmap = 'gray')
	plt.imshow(img,cmap = 'gray')
	# plt.plot([top_left[0],top_right[0],bottom_right[0],bottom_left[0]],[top_left[1],top_right[1],bottom_right[1],bottom_left[1]])
	# plt.scatter(top_left[0],top_left[1])
	# plt.scatter(top_right[0],top_right[1])
	# plt.scatter(bottom_right[0],bottom_right[1])
	# plt.scatter(bottom_left[0],bottom_left[1])
	plt.show()