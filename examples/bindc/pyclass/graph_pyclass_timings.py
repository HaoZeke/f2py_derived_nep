#!/usr/bin/env python3

from collections import namedtuple
from timer import timer
import pandas as pd
import plotnine as p9
import numpy as np
import bbdir.pycart as pycart

ppoint = namedtuple("ppoint", ['neval', 'timetaken', 'object'])

class fakecart:
  def __new__(cls, *args, **kwargs):
    obj = object.__new__(cls)
    obj.x = 0
    obj.y = 0
    obj.z = 0
    return obj

  def __init__(self, x, y, z):
    self.x = x
    self.y = y
    self.z = z
  def __repr__(self):
    return f"fakecart(x: {self.x}, y: {self.y}, z: {self.z})"

  def unitstep(self):
    self.x = self.x + 1
    self.y = self.y + 1
    self.z = self.z +1


def gen_fcdat(xvals):
    bbk = fakecart(0, 0, 0)
    resdat = []
    for neval in xvals:
        with timer(unit='s') as t:
            [bbk.unitstep() for itr in range(neval)]
            resdat.append(ppoint(neval = neval,
                                 timetaken = t.elapse,
                                 object = 'fakecart'))
    return resdat

def gen_pycdat(xvals):
    aak = pycart.pycart(0, 0, 0)
    resdat = []
    for neval in xvals:
        with timer(unit='s') as t:
            [aak.unitstep() for itr in range(neval)]
            resdat.append(ppoint(neval = neval,
                                 timetaken = t.elapse,
                                 object = 'pycart'))
    return resdat

def gen_fulldat(xvals):
    gfc = pd.DataFrame(gen_fcdat(xvals))
    gpyfc = pd.DataFrame(gen_pycdat(xvals))
    return pd.concat([ gfc, gpyfc ])

def gen_plot(fdat, oname = "plot.png"):
    (p9.ggplot(fdat,
            p9.aes(x='neval',
                   y='timetaken',
                   color='object'))
     + p9.geom_point(size=2)
     + p9.geom_line(size=1.5)
     + p9.xlab("Number of function calls")
     + p9.ylab("Time elapsed (s)")
     + p9.labs(title="Fortran wrapped cartesian derived type timings")
     # + p9.scales.scale_y_log10()
     + p9.theme_538()
     ).save(oname,
            width=10,
            height=10,
            dpi=300)

xvs = np.geomspace(1, 100000, num=400, dtype=int)
gen_plot(gen_fulldat(xvs), "oplot.png")
