
from glob import glob
from os.path import splitext
import Image

jpglist = glob( "data/profile/*.png" )

for jpg in jpglist:
    im = Image.open(jpg)
    png = splitext(jpg)[0]+".png"
    im.save(png)
    print png
