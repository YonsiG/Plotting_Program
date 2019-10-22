#!/bin/env python

import plottery_wrapper as p

p.dump_plot(
        fnames=[
            "h_selected.root",
            "others_selected.root",
            "ttZ_selected.root",
            "tWZ_selected.root",
            "WZ_selected.root",
            "ZZ_selected.root",
            ],
        sig_fnames=[
            "signal_selected.root",
            ],
        legend_labels=[
            "Higgs",
            "Others",
            "t#bar{t}Z",
            "tWZ",
            "WZ",
            "ZZ",
            ],
        signal_labels=["WZZ+ZZZ"],
        usercolors=[2011,920,2005,2007,2003,2001],
        filter_pattern="leptonEta_fourth",
        dogrep=False, # Set it to True to match the pattern provided above (i.e. if filter_pattern="fatjetMass_lead" and dogrep=True, then any histogram object with name "*fatjetMass_lead*" will be plotted)
        dirname="plots/",
        extraoptions= {
            "signal_scale":1,
            "print_yield": True,
            "nbins":15,
            "legend_ncolumns":3,
            "legend_scalex":1.8,
            "legend_scaley":1.2,
            "lumi_value":137,
            "xaxis_label":"#eta",
            "xaxis_ndivisions":505,
#            "remove_underflow":True,
#            "remove_overflow":True,
#            "xaxis_label":"#tau_{21}",
            },
        # _plotter=p.plot_cut_scan  # <--- uncomment this line if you want to perform a cut scan optimization
        )
