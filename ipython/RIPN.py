#################################################################################
#
# name: RIPN.py (ROOT IPython Notebook)
# date: 07 Dec 14
# auth: Zach Hartwig
# mail: hartwig@psfc.mit.edu
#
# desc: The ZNotebookCanvas class contained within this Python module
#       enables ROOT graphics to be embedded as inline images within
#       iPython Notebooks. ZNotebookCanvas is derived from ROOT's
#       TCanvas and exposes all of the default TCanvas options to the
#       user. New methods have been added that enable the user to
#       select a file type, export canvas image to file, and then
#       import the image via proper Python methods to the notebook.
#
#       The difference between using a TCanvas and a ZNotebookCanvas
#       is that the latter requires that (a) the user call
#       ZNotebookCanvas::Draw() when ready to insert the graphics into
#       the notebook and (b) that ZNotebookDraw() be the last method
#       called within a notebook cell for the graphics to appear.
#
# 2run: Ensure that the PyROOT libraries and  RIPN module is available
#       to Python via environment configuration within .bashrc:
#       'export PYTHONPATH=$ROOTSYS/lib:/home/solonite/root/ROOTUtilities/ipython:$PYTHONPATH'
#
#       Then include include the following line within the IPython notebook:
#       'from RIPN import ZNotebookCanvas'
#
#################################################################################

from ROOT import TCanvas
from IPython.display import Image, SVG
from scipy.constants import golden
import os

class ZNotebookCanvas(TCanvas):

    # Constructor: (x,y) of canvas size optional
    def __init__(self, x=700, y=int(700./golden)):
        TCanvas.__init__(self, '', '', 0, 0, x, y)

        self.SetLeftMargin(0.12)
        self.SetRightMargin(0.92)
        self.SetTopMargin(0.92)
        self.SetBottomMargin(0.15)

        # Image attributes
        self.image_file = '/tmp/tmp'
        self.image_type = "png"
        self.image = 0


    # Insert all objects in the draw_list to the canvas. Return value is
    # the IPython.display SVG/Image object containing the image
    def Insert(self):    

        # Update the canvas
        self.Update()

        image_extension = "." + self.image_type

        # Insert an SVG file into the notebook
        if image_extension == '.svg':
            image_name = self.image_file + image_extension
            self.Print(image_name)
            self.image = SVG(filename=image_name)

        # Insert an
        elif image_extension == '.jpg' or image_extension == '.png':
            image_name = self.image_file + image_extension
            self.Print(image_name)
            self.image = Image(filename=image_name, format=image_extension)

        os.system('rm -f ' + self.image_file + image_extension)

        return self.image


    # Enable user to define the desired image type
    def SetFileType(self, type):

        if type == 'png' or type == 'svg' or type == 'jpg':
            self.image_type = type
        else:
            print "Error! Only png, svg, and jpg are acceptable image types!"
