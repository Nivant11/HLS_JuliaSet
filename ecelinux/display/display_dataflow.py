#display julia set
#https://stackoverflow.com/questions/54294296/how-to-convert-array-of-pixel-values-to-image-for-displaying-using-python-and-op

from PIL import Image
import numpy as np

height = 640
width = 480
max_iter = 1000

infile = str('output/dataflow_output.txt')
julia_output = open(infile, 'r')
lines = julia_output.readlines()
# print(len(lines))

img = np.zeros((height, width, 3), dtype=np.uint8)

index = 0

for h in range(height):
    for w in range(width):
        n = int(lines[index])
        norm = n / max_iter
        # color = np.uint8([255 - int(255 * norm), int(255 * norm), 128])
        # img[h, w, 0] = color[0]
        # img[h, w, 1] = color[1]
        # img[h, w, 2] = color[2]
        if n >= max_iter:
            img[h, w, 0] = 0 
            img[h, w, 1] = 0 
            img[h, w, 2] = 0 
        elif n >= max_iter/2:
            img[h, w, 0] = 255 
            img[h, w, 1] = 0 
            img[h, w, 2] = 0             
        elif n >= max_iter/4:
            img[h, w, 0] = 0 
            img[h, w, 1] = 255 
            img[h, w, 2] = 0 
        elif n >= max_iter/6:
            img[h, w, 0] = 0 
            img[h, w, 1] = 0 
            img[h, w, 2] = 255 
        elif n >= max_iter/8:
            img[h, w, 0] = 255 
            img[h, w, 1] = 255 
            img[h, w, 2] = 0 
        elif n >= max_iter/10:
            img[h, w, 0] = 0 
            img[h, w, 1] = 255 
            img[h, w, 2] = 255 
        elif n >= max_iter/20:
            img[h, w, 0] = 255 
            img[h, w, 1] = 128
            img[h, w, 2] = 255 
        elif n >= max_iter/40:
            img[h, w, 0] = 128 
            img[h, w, 1] = 255 
            img[h, w, 2] = 128 
        elif n >= max_iter/60:
            img[h, w, 0] = 128
            img[h, w, 1] = 128
            img[h, w, 2] = 255 
        elif n >= max_iter/80:
            img[h, w, 0] = 255 
            img[h, w, 1] = 255 
            img[h, w, 2] = 128
        elif n >= max_iter/100:
            img[h, w, 0] = 128
            img[h, w, 1] = 255 
            img[h, w, 2] = 255 
        elif n >= max_iter/200:
            img[h, w, 0] = 255 
            img[h, w, 1] = 128
            img[h, w, 2] = 255 
        elif n >= max_iter/400:
            img[h, w, 0] = 128
            img[h, w, 1] = 0 
            img[h, w, 2] = 255 
        elif n >= max_iter/600:
            img[h, w, 0] = 0 
            img[h, w, 1] = 128
            img[h, w, 2] = 255
        elif n >= max_iter/800:
            img[h, w, 0] = 0 
            img[h, w, 1] = 255
            img[h, w, 2] = 128
        else:
            img[h, w, 0] = 10
            img[h, w, 1] = 10
            img[h, w, 2] = 10
             
        index = index + 1

image = Image.fromarray(img, 'RGB')
image.save('julia_set.png')
image.show()