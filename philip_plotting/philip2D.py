#!/bin/env python

import ROOT as r

r.gROOT.SetBatch(True)
r.gStyle.SetOptStat(False)

f = r.TFile("../Ceres_looping/outfiles/Z+Jet_selected.root")

h = f.Get("fatjettau21_Pt_sub")

c1 = r.TCanvas()

p = h.ProfileX()

p.SetLineColor(2)
p.SetLineWidth(2)

h.Draw("colz")
p.Draw("epsame")

c1.SaveAs("2Dplots/Z+Jet/fatjettau21_Pt_sub.pdf")
